#ifndef SIDBOX_GAMEQUESTJOURNALEDITOR_H
#define SIDBOX_GAMEQUESTJOURNALEDITOR_H
#include <QString>
class QWidget;
/* Project-wide display style saved separately from quest progress / IDs. */
bool editGameQuestJournal(QWidget *parent,const QString &projectRoot,QString *error=nullptr);
#endif
