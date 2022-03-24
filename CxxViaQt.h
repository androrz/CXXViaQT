#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_CxxViaQt.h"
#include "HWM_SIO.h"
#include <QTimer>

class CxxViaQt : public QMainWindow
{
	Q_OBJECT

public:
	CxxViaQt(QWidget* parent = Q_NULLPTR);
private:
	void chipCheck();
	void getGpioAddress();
private:
	Ui::CxxViaQtClass ui;
	HWM_SIO* HWM_SIO1;
	int g_ChipID;
	QTimer timer_;
};
