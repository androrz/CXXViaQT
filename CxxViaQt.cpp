#include "CxxViaQt.h"

CxxViaQt::CxxViaQt(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    connect(ui.btn_get, &QPushButton::clicked, [=]() {
        
        });
}
