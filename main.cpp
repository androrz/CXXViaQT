#include "CxxViaQt.h"
#include <QtWidgets/QApplication>
#include <windows.h>

int main(int argc, char *argv[])
{
#ifndef DEBUG
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
#endif

#if (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0))
	QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QGuiApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
#if (QT_VERSION >= QT_VERSION_CHECK(5, 14, 0))
	QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
#endif
#endif

    QApplication a(argc, argv);
    CxxViaQt w;
    w.show();
    return a.exec();
}
