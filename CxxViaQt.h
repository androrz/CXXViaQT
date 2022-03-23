#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_CxxViaQt.h"

class CxxViaQt : public QMainWindow
{
    Q_OBJECT

public:
    CxxViaQt(QWidget *parent = Q_NULLPTR);

private:
    Ui::CxxViaQtClass ui;
};
