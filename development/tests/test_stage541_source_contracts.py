from pathlib import Path
import re
r=Path(__file__).resolve().parents[2]
files=['gamedesigner.cpp','gameadventureeditor.cpp','gameadventuregen.cpp','gamehudeditor.cpp','gamedesigner_export.cpp','gamedesigner_project.cpp','splashscreenwidget.cpp']
# Scan C++ strings for accidentally embedded raw newlines; ignore comments and char literals.
def scan(path):
 s=path.read_text();s=re.sub(r'R"([A-Za-z0-9_]*)\(.*?\)\1"',lambda m:' '*len(m.group(0)) if '\n' not in m.group(0) else ''.join('\n' if ch=='\n' else ' ' for ch in m.group(0)),s,flags=re.S);mode='code';start=0;line=1;errors=[];i=0
 while i<len(s):
  c=s[i];d=s[i+1] if i+1<len(s) else ''
  if mode=='code':
   if c=='"':mode='string';start=line
   elif c=="'":mode='char';start=line
   elif c=='/' and d=='/':mode='line';i+=1
   elif c=='/' and d=='*':mode='block';i+=1
  elif mode=='string':
   if c=='\\':i+=1
   elif c=='"':mode='code'
   elif c=='\n':errors.append(('raw newline in string',start));mode='code'
  elif mode=='char':
   if c=='\\':i+=1
   elif c=="'":mode='code'
   elif c=='\n':errors.append(('newline in char',start));mode='code'
  elif mode=='line':
   if c=='\n':mode='code'
  elif mode=='block':
   if c=='*' and d=='/':mode='code';i+=1
  if c=='\n':line+=1
  i+=1
 return errors
for f in files:
 issues=scan(r/f)
 print('lex',f,'OK' if not issues else issues[:12]);assert not issues
checks={
 'runtime HUD shared palette remaps tiles and icons':all(x in (r/'gamehudeditor.cpp').read_text() for x in ['tileRemap[atlas.pixelIndex', 'iconRemap[icon.pixelIndex','HUD palette source (tiles, text, items)']),
 'inventory own atlas persistence':all(x in (r/'gameadventureeditor.cpp').read_text() for x in ['iconAtlasId','iconTileSize','Selected item']),
 'icon atlas generation':all(x in (r/'gameadventuregen.cpp').read_text() for x in ['ITEM_ICON_SETUP','game_adventure_item_atlas','iconTileSize']),
 'icon atlas runtime':all(x in (r/'idelibs/codehelpers/game/adventureruntime.rulec').read_text() for x in ['ga_icon_atlas','icon.imgdat=pixels','game_adventure_item_atlas']),
 'persist save/load':all(x in (r/'gamedesigner_project.cpp').read_text() for x in ['pickupPersistent']),
 'persist runtime condition':all(x in (r/'idelibs/codehelpers/game/gameworlditems.rulec').read_text() for x in ['persistent_was_active[i] && !pickups[i].active','cg_pickup_permanently_collected[i]']),
 'persist world inventory bridging':all(x in (r/'gamedesigner.cpp').read_text() for x in ['persistentItemsFromSavedWorlds','effectiveAdventure.insert']),
 'array naming': 'const QRegularExpression numbered' in (r/'gamedesigner.cpp').read_text(),
 'visible viewport imports': '(m_view->viewport()->rect().center())' in (r/'gamedesigner.cpp').read_text(),
 'generator uses sprite PPB icon atlases': 'if (r.kind == QStringLiteral("sprite") || r.kind == QStringLiteral("tileatlas"))' in (r/'gamedesigner.cpp').read_text(),
 'splash version': 'Build: 5.41.1.231026' in (r/'splashscreenwidget.cpp').read_text(),
}
for k,v in checks.items():print('PASS' if v else 'FAIL',k)
assert all(checks.values())
