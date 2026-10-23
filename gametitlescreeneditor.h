#pragma once

#include <QString>

class QWidget;

bool editGameTitleScreen(QWidget *parent, const QString &projectRoot, QString *errorOut = nullptr);
