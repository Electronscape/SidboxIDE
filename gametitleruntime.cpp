#include "gametitleruntime.h"
#include "ppbcodec.h"
#include "gamepalette.h"
#include "gametilemap.h"

#include <QDir>
#include <QDirIterator>
#include <QFile>
#include <QFileInfo>
#include <QImage>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMap>
#include <QSaveFile>
#include <QStringList>
#include <QVector>

namespace {
QString jsonPath(const QString &root) {
    return QDir(root).filePath(QStringLiteral(".sidbox-title-screen.json"));
}
QJsonObject readTitle(const QString &root) {
    QFile file(jsonPath(root));
    if (!file.open(QIODevice::ReadOnly)) return {};
    return QJsonDocument::fromJson(file.readAll()).object();
}
QString cString(const QString &input) {
    QByteArray bytes=input.toLatin1();
    QString out=QStringLiteral("\"");
    for (unsigned char ch:bytes) {
        if (ch=='\\') out += QStringLiteral("\\\\");
        else if (ch=='\"') out += QStringLiteral("\\\"");
        else if (ch>=32 && ch<127) out += QChar(ch);
        else out += QStringLiteral("\\%1").arg(unsigned(ch),3,8,QLatin1Char('0'));
    }
    return out+QLatin1Char('"');
}
int between(const QJsonObject &o, const char *key, int def, int min, int max) {
    return qBound(min,o.value(QLatin1String(key)).toInt(def),max);
}
QString safeRelative(const QDir &project,const QString &raw,QString *error) {
    if (raw.isEmpty()) return {};
    const QString file=QFileInfo(project.filePath(raw)).canonicalFilePath();
    if (file.isEmpty() || !QFileInfo(file).isFile() ||
        !(file.startsWith(project.canonicalPath()+QLatin1Char('/')))) {
        if (error) *error=QStringLiteral("Invalid/missing project title asset: %1").arg(raw);
        return {};
    }
    return project.relativeFilePath(file);
}
struct Image { QString relative; int width=0,height=0; QImage preview; };
}
namespace GameTitleRuntime {
bool enabled(const QString &root) {
    return readTitle(root).value(QStringLiteral("enabled")).toBool(false);
}
bool generate(const QString &root,const QString &fallbackWorld,
              const QString &sdkTemplateRoot,QString *error) {
    if (error) error->clear();
    const QJsonObject config=readTitle(root);
    if (!config.value(QStringLiteral("enabled")).toBool(false)) return true;
    const QDir project(root);
    QVector<Image> images;
    auto imageIndex=[&](const QString &raw) -> int {
        if (raw.isEmpty()) return -1;
        QString failed;
        const QString relative=safeRelative(project,raw,&failed);
        if (relative.isEmpty()) { if(error)*error=failed; return -2; }
        for(int i=0;i<images.size();++i) if(images[i].relative==relative)return i;
        SidboxPpb::Picture picture;
        QString ppbError;
        if (!SidboxPpb::read(project.filePath(relative),&picture,&ppbError)
            || picture.indexed.isNull() || picture.indexed.size().width()*qint64(picture.indexed.size().height())>2097152) {
            if(error)*error=QStringLiteral("Invalid title PPB %1: %2").arg(relative,ppbError);
            return -2;
        }
        Image entry;
        entry.relative=relative;
        entry.width=picture.indexed.width();entry.height=picture.indexed.height();
        entry.preview=picture.indexed;
        images.push_back(entry);
        return images.size()-1;
    };
    const QJsonObject background=config.value(QStringLiteral("background")).toObject();
    const int backgroundIndex=imageIndex(background.value(QStringLiteral("path")).toString());
    if(backgroundIndex==-2) return false;
    auto imageArt=[&](const QJsonObject &obj,const QString &label,bool *ok)->QString {
        const bool isPpb=obj.value(QStringLiteral("mode")).toString()==QStringLiteral("ppb");
        const int img=isPpb?imageIndex(obj.value(QStringLiteral("path")).toString()):-1;
        if(img==-2 || (isPpb && img==-1)) {
            if(error && error->isEmpty())*error=QStringLiteral("Title PPB artwork '%1' has no file selected").arg(label);
            *ok=false;return {};
        }
        int cell=between(obj,"cellSize",0,0,32);
        if(cell!=8 && cell!=16 && cell!=32)cell=0;
        int frame=between(obj,"frame",0,0,65535);
        if(img>=0 && cell>0) {
            const int cols=images[img].width/cell;
            const int rows=images[img].height/cell;
            if (cols<=0 || rows<=0 || frame>=cols*rows || frame>255) {
                if(error)*error=QStringLiteral("Title artwork '%1': cell %2 is invalid (BOB supports 0..255)").arg(label).arg(frame);
                *ok=false;return {};
            }
        }
        const int x=between(obj,"x",0,-4096,4096),y=between(obj,"y",0,-4096,4096);
        const int legacy=between(obj,"fontSize",1,1,4);
        const int sx=between(obj,"fontSizeX",legacy,1,4),sy=between(obj,"fontSizeY",legacy,1,4);
        return QStringLiteral("{%1,%2,%3,%4,%5,%6,%7,%8,%9,%10,%11,%12}")
            .arg(cString(label)).arg(x).arg(y).arg(img).arg(cell).arg(frame)
            .arg(between(obj,"foreground",15,0,255)).arg(between(obj,"outline",0,0,255))
            .arg(obj.value(QStringLiteral("outlineEnabled")).toBool()?1:0).arg(sx).arg(sy)
            .arg(between(obj,"outlineThickness",1,1,4));
    };
    bool valid=true;
    const QString heading=imageArt(config.value(QStringLiteral("titleArt")).toObject(),config.value(QStringLiteral("title")).toString(),&valid);
    const QString subtitle=imageArt(config.value(QStringLiteral("subtitleArt")).toObject(),config.value(QStringLiteral("subtitle")).toString(),&valid);
    if(!valid) return false;
    QStringList menuStrings;
    const QJsonArray menu=config.value(QStringLiteral("menuItems")).toArray();
    const QDir worldDirectory(root);
    for(const QJsonValue &entry:menu) {
        const QJsonObject item=entry.toObject();
        const QString label=item.value(QStringLiteral("label")).toString();
        QString action=item.value(QStringLiteral("action")).toString();
        int code=0;
        if(action==QStringLiteral("start"))code=1;
        else if(action==QStringLiteral("goto"))code=2;
        else if(action==QStringLiteral("load"))code=3;
        else if(action==QStringLiteral("options"))code=4;
        else if(action==QStringLiteral("quit"))code=5;
        if (!code) { if(error)*error=QStringLiteral("Unknown title action for '%1': %2").arg(label,action);return false; }
        QString world=item.value(QStringLiteral("world")).toString();
        if(code==1||code==2) {
            if(world.isEmpty()) {
                // The current design already supplied a sanitised world ID;
                // its original .sbgm filename need not have that same spelling.
                world=fallbackWorld;
            } else {
                const QString designFile=worldDirectory.filePath(world+QStringLiteral(".sbgm"));
                if(!QFileInfo::exists(designFile)) {
                    if(error)*error=QStringLiteral("Title option '%1' targets missing world '%2'").arg(label,world);
                    return false;
                }
                // The editor lists the friendly .sbgm filename; the compiled
                // world manager registers its sanitised, stable C world name.
                world=sidboxTilemapWorldBaseName(designFile);
            }
        } else world.clear();
        QString start=item.value(QStringLiteral("playerStart")).toString();
        if(start.isEmpty())start=QStringLiteral("default");
        const QString art=imageArt(item.value(QStringLiteral("display")).toObject(),label,&valid);
        if(!valid)return false;
        menuStrings.append(QStringLiteral("{%1,%2,%3,%4}").arg(art).arg(code).arg(cString(world)).arg(cString(start)));
    }
    if(menuStrings.isEmpty()) {
        const QString art=imageArt({},QStringLiteral("Start Game"),&valid);
        menuStrings.append(QStringLiteral("{%1,1,%2,%3}").arg(art,cString(fallbackWorld),cString(QStringLiteral("default"))));
    }
    QString music=config.value(QStringLiteral("music")).toString();
    if(!music.isEmpty()) {
        QString failed;music=safeRelative(project,music,&failed);
        if(music.isEmpty()) {if(error)*error=failed;return false;}
    }
    // Options panel shares the title CLUT and title images. Its secondary
    // PPB is optional; an empty path reuses the main menu's background.
    const QJsonObject opts=config.value(QStringLiteral("optionsScreen")).toObject();
    const QJsonObject optBg=opts.value(QStringLiteral("background")).toObject();
    const int optionsBgIndex=optBg.value(QStringLiteral("path")).toString().isEmpty() ? -1 :
                             imageIndex(optBg.value(QStringLiteral("path")).toString());
    if(optionsBgIndex==-2)return false;
    const QString optionsBgMode=optBg.value(QStringLiteral("mode")).toString();
    const QString optHeading=opts.value(QStringLiteral("title")).toString(QStringLiteral("OPTIONS"));
    const int fg=between(opts,"foreground",15,0,255);
    const int sx=between(opts,"fontSizeX",1,1,4),sy=between(opts,"fontSizeY",1,1,4);
    auto optionsArt=[&](const QString &text,int x,int y,int foreground,int outline,bool outlined,int thickness){
        return QStringLiteral("{%1,%2,%3,-1,0,0,%4,%5,%6,%7,%8,%9}")
            .arg(cString(text)).arg(x).arg(y).arg(foreground).arg(outline)
            .arg(outlined?1:0).arg(sx).arg(sy).arg(thickness);
    };
    const QString optionsHeading=optionsArt(optHeading,between(opts,"titleX",196,-4096,4096),
        between(opts,"titleY",29,-4096,4096),between(opts,"titleForeground",fg,0,255),
        between(opts,"titleOutline",0,0,255),opts.value(QStringLiteral("titleOutlineEnabled")).toBool(false),
        between(opts,"titleOutlineThickness",1,1,4));
    const QStringList optionDefaults={QStringLiteral("Music"),QStringLiteral("Music Volume"),
        QStringLiteral("Sound Effects"),QStringLiteral("SFX Volume"),
        QStringLiteral("Screen Shake"),QStringLiteral("Text Speed"),
        QStringLiteral("Difficulty"),QStringLiteral("Back")};
    QStringList optionsItems, optionsVisible, optionsBarPositions, optionsBarColours;
    const QJsonArray optRows=opts.value(QStringLiteral("items")).toArray();
    for(int i=0;i<optionDefaults.size();++i){
        const QJsonObject row=i<optRows.size()?optRows[i].toObject():QJsonObject{};
        const int rowFg=between(row,"foreground",fg,0,255);
        optionsItems<<optionsArt(row.value(QStringLiteral("label")).toString(optionDefaults[i]),
            between(row,"x",72,-4096,4096),between(row,"y",76+i*27,-4096,4096),
            rowFg,between(row,"outline",0,0,255),row.value(QStringLiteral("outlineEnabled")).toBool(false),
            between(row,"outlineThickness",1,1,4));
        optionsVisible << (row.value(QStringLiteral("visible")).toBool(true)?QStringLiteral("1"):QStringLiteral("0"));
        if(i==1 || i==3 || i==5){
            const int labelX=between(row,"x",72,-4096,4096);
            const int labelY=between(row,"y",76+i*27,-4096,4096);
            optionsBarPositions << QStringLiteral("{%1,%2}")
                .arg(between(row,"barX",labelX+175,-4096,4096))
                .arg(between(row,"barY",labelY+2,-4096,4096));
            optionsBarColours << QString::number(between(row,"barColour",rowFg,0,255));
        }
    }
    const int defMusicVol=between(opts,"musicVolume",80,0,100);
    const int defSfxVol=between(opts,"sfxVolume",100,0,100);
    const int defSpeed=between(opts,"textSpeed",50,0,100);
    const int defDifficulty=between(opts,"difficulty",1,0,2);
    const int easyMult=between(opts,"easyMultiplier",75,25,300);
    const int hardMult=between(opts,"hardMultiplier",150,25,300);
    QVector<QRgb> palette;
    const QString palSource=config.value(QStringLiteral("textPalette")).toString();
    if(!palSource.isEmpty()) {
        QString failed;const QString source=safeRelative(project,palSource,&failed);
        if(source.isEmpty()){if(error)*error=failed;return false;}
        if(source.endsWith(QStringLiteral(".ppb"),Qt::CaseInsensitive)) {
            SidboxPpb::Picture colourSource;
            if (!SidboxPpb::read(project.filePath(source), &colourSource, &failed)) {
                if (error) *error=failed;
                return false;
            }
            palette=colourSource.indexed.colorTable();
        } else palette=SidboxGamePalette::readPalette(project.filePath(source),false,&failed);
        if(palette.size()!=256){if(error)*error=QStringLiteral("Cannot read title text palette: %1").arg(failed);return false;}
    } else if(backgroundIndex>=0)palette=images[backgroundIndex].preview.colorTable();
    else {
        // Match the Title Screen Designer's alphabetical PPB fallback when
        // no background or explicit text CLUT is selected.
        QStringList choices;
        QDirIterator iterator(root,QStringList{QStringLiteral("*.ppb")},
                              QDir::Files | QDir::NoSymLinks,QDirIterator::Subdirectories);
        while(iterator.hasNext()) choices << project.relativeFilePath(iterator.next());
        choices.sort(Qt::CaseInsensitive);
        if(!choices.isEmpty()) {
            SidboxPpb::Picture fallback;
            if(SidboxPpb::read(project.filePath(choices.first()),&fallback))
                palette=fallback.indexed.colorTable();
        }
    }
    if(palette.size()!=256) {
        palette=QVector<QRgb>(256,qRgb(0,0,0));
        palette[15]=qRgb(255,255,255);
    }
    // Stage 5.67: an optional private ARGB CLUT embedded in title JSON.
    // Never alter the imported palette or PPB indices.
    const QJsonArray overrides=config.value(QStringLiteral("titleClut")).toArray();
    if(overrides.size()==256) {
        QVector<QRgb> edited; edited.reserve(256);
        bool validOverride=true;
        for(const QJsonValue &v:overrides) {
            bool ok=false;
            const QString hex=v.toString();
            const quint32 argb=hex.toUInt(&ok,16);
            if(!ok || hex.size()!=8) {validOverride=false;break;}
            edited.append(QRgb(argb));
        }
        if(!validOverride) {
            if(error)*error=QStringLiteral("Invalid titleClut ARGB palette override");
            return false;
        }
        palette=edited;
    }
    // Foreground index zero clears the title graphics plane. It MUST remain
    // transparent to reveal the separate background plane.
    palette[0]=qRgba(qRed(palette[0]),qGreen(palette[0]),qBlue(palette[0]),0);
    // Separate hardware background CLUTs, derived from their own PPB sheets.
    // Background pixels are opaque even where a source palette sets alpha 0.
    const auto opaqueBackground=[&](int imageIndex)->QStringList {
        QVector<QRgb> colours(256,qRgb(0,0,0));
        if(imageIndex>=0 && imageIndex<images.size() && images[imageIndex].preview.colorTable().size()==256)
            colours=images[imageIndex].preview.colorTable();
        QStringList encoded;
        for(QRgb col:colours)encoded.append(QStringLiteral("0x%1u").arg(quint32(qRgba(qRed(col),qGreen(col),qBlue(col),255)),8,16,QLatin1Char('0')));
        return encoded;
    };
    QStringList rgb;
    for(QRgb col:palette)rgb.append(QStringLiteral("0x%1u").arg(quint32(col),8,16,QLatin1Char('0')));
    const QStringList mainBgColours=opaqueBackground(backgroundIndex);
    const QStringList optionsBgColours=opaqueBackground(optionsBgIndex>=0?optionsBgIndex:backgroundIndex);
    QStringList imgLines;
    for(const Image &im:images)
        imgLines << QStringLiteral("    {%1,%2,%3,0}").arg(cString(im.relative)).arg(im.width).arg(im.height);
    if(imgLines.isEmpty())imgLines << QStringLiteral("    {\"\",0,0,0}");
    QFile templ(QDir(sdkTemplateRoot).filePath(QStringLiteral("gametitle-runtime.rulec")));
    if(!templ.open(QIODevice::ReadOnly)) {
        if(error)*error=QStringLiteral("Missing SIDBOX title runtime template: %1").arg(templ.fileName());
        return false;
    }
    QString code=QString::fromUtf8(templ.readAll());
    const QString mode=background.value(QStringLiteral("mode")).toString();
    const QString selector=config.value(QStringLiteral("menuSelector")).toString();
    int sel=selector==QStringLiteral("rect")?1:selector==QStringLiteral("arrow")?2:selector==QStringLiteral("underline")?3:0;
    const QMap<QString,QString> values={
        {QStringLiteral("@TITLE_IMAGE_COUNT@"),QString::number(qMax(1,images.size()))},
        {QStringLiteral("@TITLE_IMAGES@"),imgLines.join(QStringLiteral(",\n"))},
        {QStringLiteral("@TITLE_MENU_COUNT@"),QString::number(menuStrings.size())},
        {QStringLiteral("@TITLE_MENU_LENGTH@"),QString::number(menuStrings.size())},
        {QStringLiteral("@TITLE_MENU@"),QStringLiteral("    ")+menuStrings.join(QStringLiteral(",\n    "))},
        {QStringLiteral("@TITLE_PALETTE@"),QStringLiteral("    ")+rgb.join(QStringLiteral(", "))},
        {QStringLiteral("@TITLE_BACKGROUND_PALETTE@"),QStringLiteral("    ")+mainBgColours.join(QStringLiteral(", "))},
        {QStringLiteral("@TITLE_OPTIONS_BACKGROUND_PALETTE@"),QStringLiteral("    ")+optionsBgColours.join(QStringLiteral(", "))},
        {QStringLiteral("@TITLE_HEADING@"),heading},
        {QStringLiteral("@TITLE_SUBTITLE@"),subtitle},
        {QStringLiteral("@TITLE_SELECTOR@"),QString::number(sel)},
        {QStringLiteral("@TITLE_SELECTOR_COLOUR@"),QString::number(between(config,"selectorColour",15,0,255))},
        {QStringLiteral("@TITLE_BACKGROUND_INDEX@"),QString::number(backgroundIndex)},
        {QStringLiteral("@TITLE_BACKGROUND_MODE@"),QString::number(mode==QStringLiteral("direct_ready")?1:mode==QStringLiteral("direct_convert")?2:0)},
        {QStringLiteral("@TITLE_MUSIC@"),cString(music)},
        {QStringLiteral("@TITLE_DEFAULT_WORLD@"),cString(fallbackWorld)},
        {QStringLiteral("@TITLE_OPTIONS_HEADING@"),optionsHeading},
        {QStringLiteral("@TITLE_OPTIONS_ITEMS@"),optionsItems.join(QStringLiteral(",\n    "))},
        {QStringLiteral("@TITLE_OPTIONS_VISIBLE@"),optionsVisible.join(QStringLiteral(","))},
        {QStringLiteral("@TITLE_OPTIONS_BAR_POS@"),optionsBarPositions.join(QStringLiteral(","))},
        {QStringLiteral("@TITLE_OPTIONS_BAR_COLOURS@"),optionsBarColours.join(QStringLiteral(","))},
        {QStringLiteral("@TITLE_OPTIONS_BACKGROUND@"),QString::number(optionsBgIndex)},
        {QStringLiteral("@TITLE_OPTIONS_BG_MODE@"),QString::number(optionsBgMode==QStringLiteral("direct_ready")?1:optionsBgMode==QStringLiteral("direct_convert")?2:0)},
        {QStringLiteral("@TITLE_OPT_DEFAULT_MUSIC@"),opts.value(QStringLiteral("music")).toBool(true)?QStringLiteral("1"):QStringLiteral("0")},
        {QStringLiteral("@TITLE_OPT_DEFAULT_MUSIC_VOL@"),QString::number(defMusicVol)},
        {QStringLiteral("@TITLE_OPT_DEFAULT_SFX@"),opts.value(QStringLiteral("sfx")).toBool(true)?QStringLiteral("1"):QStringLiteral("0")},
        {QStringLiteral("@TITLE_OPT_DEFAULT_SFX_VOL@"),QString::number(defSfxVol)},
        {QStringLiteral("@TITLE_OPT_DEFAULT_SHAKE@"),opts.value(QStringLiteral("shake")).toBool(true)?QStringLiteral("1"):QStringLiteral("0")},
        {QStringLiteral("@TITLE_OPT_DEFAULT_SPEED@"),QString::number(defSpeed)},
        {QStringLiteral("@TITLE_OPT_DEFAULT_DIFFICULTY@"),QString::number(defDifficulty)},
        {QStringLiteral("@TITLE_OPT_EASY_MULT@"),QString::number(easyMult)},
        {QStringLiteral("@TITLE_OPT_HARD_MULT@"),QString::number(hardMult)}
    };
    for(auto it=values.cbegin();it!=values.cend();++it)code.replace(it.key(),it.value());
    const QString folder=project.filePath(QStringLiteral("gamehelpers"));
    if(!QDir().mkpath(folder)){if(error)*error=QStringLiteral("Cannot create gamehelpers directory");return false;}
    const auto write=[&](const QString &name,const QByteArray &bytes)->bool {
        QSaveFile out(QDir(folder).filePath(name));
        if(!out.open(QIODevice::WriteOnly) || out.write(bytes)!=bytes.size() || !out.commit()) {
            if(error)*error=QStringLiteral("Cannot write gamehelpers/%1").arg(name);
            return false;
        }
        return true;
    };
    const QByteArray header=R"TITLE(/* GENERATED by CoderGirl Stage 5.65. */
#ifndef SIDBOX_GAMETITLE_H
#define SIDBOX_GAMETITLE_H
#include <stdint.h>
/* Returns 1 when a world is selected, otherwise 0 on Quit. */
uint8_t gametitle_run(const char **world,const char **start);
int8_t gametitle_load_slot(void);
/* Settings are in-memory for this first pass: no TFCard writes while MP3 plays. */
uint8_t gametitle_music_enabled(void);
uint8_t gametitle_sfx_enabled(void);
uint8_t gametitle_shake_enabled(void);
uint8_t gametitle_music_volume(void);  /* 0..100, mixer integration pending */
uint8_t gametitle_sfx_volume(void);    /* 0..100 */
uint8_t gametitle_text_speed(void);    /* 0..100, consumed by game dialogue */
uint8_t gametitle_difficulty(void);    /* 0 Easy, 1 Normal, 2 Hard */
uint16_t gametitle_difficulty_percent(void);
uint16_t gametitle_scale_sfx(uint16_t raw_volume); /* applies SFX on/off and 0..100 gain */
#endif
)TITLE";
    return write(QStringLiteral("gametitle.h"),header) &&
           write(QStringLiteral("gametitle.c"),code.toUtf8());
}
}
