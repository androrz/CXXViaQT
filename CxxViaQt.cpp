#include <windows.h>
#include "CxxViaQt.h"
#include "OlsApi.h"

int addr = 0x2E;
int GPIO_addr;

CxxViaQt::CxxViaQt(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    if (!InitializeOls()) {
        printf("initialize error!\n\r");
        DWORD status = GetDllStatus();
        printf("dll status: %d!\n\r", status);
    }
    chipCheck();
    getGpioAddress();
    connect(ui.btn_get, &QPushButton::clicked, [=]() {

        });

    connect(&timer_, &QTimer::timeout, [=]() {
        QString bit = QString::number(HWM_SIO1->GetGPIO_Bit(6, 6));
        ui.lbl_bit->setText(bit);
        });
    timer_.setInterval(500);
    timer_.start();
}

void CxxViaQt::chipCheck()
{
    int MSB, LSB;

    HWM_SIO1->Get_ChipID(MSB, LSB);
    g_ChipID = MSB * 256 + LSB;
    if (((g_ChipID >> 4) == 0x872) || ((g_ChipID >> 4) == 0x873) || ((g_ChipID >> 4) == 0x877) || ((g_ChipID >> 4) == 0x878) || ((g_ChipID >> 8) == 0x86) || ((g_ChipID >> 4) == 0x870) || ((g_ChipID >> 4) == 0x871) || ((g_ChipID >> 4) == 0x875))
    {
        ;
    }
    else
    {
        addr = 0x4E;
        HWM_SIO1->Get_ChipID(MSB, LSB);
    }
    g_ChipID = MSB * 256 + LSB;
    if ((g_ChipID >> 4) == 0x876)
    {
        addr = 0x4E;
        HWM_SIO1->Get_ChipID(MSB, LSB);
        g_ChipID = MSB * 256 + LSB;
    }
    if (g_ChipID != 0x8785) {
        printf("wrong chipid!\r\n");
    }
    ui.lbl_chipid->setText(QString::number(g_ChipID, 16));
}

void CxxViaQt::getGpioAddress()
{
    int MSB, LSB;
    HWM_SIO1->Get_LDN_BaseAddr(0x07, MSB, LSB);
    GPIO_addr = MSB * 256 + LSB;
    ui.lbl_address->setText(QString::number(GPIO_addr, 16));
}
