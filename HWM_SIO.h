//---------------------------------------------------------------------------
//****************************************//
//              102/03/22                 //
//         HWM SIO Function               //
//         Author Seng Wen Hsin           //
//         (C)2013  ITE Tech. Inc.        //
//****************************************//

#ifndef HWM_SIOH
#define HWM_SIOH
//#include "ITEioRW.h"
#include <windows.h>
#include "OlsApi.h"
//---------------------------------------------------------------------------

class HWM_SIO
{
   public:


//------------------------------ChangeLDN----------------------------------//
              static void ChangeLDN(int LDN);

//-------------------------------解鎖--------------------------------------//
              static void EnterPnp();

//-------------------------------上鎖--------------------------------------//
              static void ExitPnp();

//------------------------Get LDN Base Address-----------------------------//
              static void Get_LDN_BaseAddr(int LDN_Input,int &MSB,int &LSB);

//-------------------------------Get Chip ID-------------------------------//
              static void Get_ChipID(int &MSB,int &LSB);

//-------------------------------Read Register-----------------------------//
              static void ReadRegister(int Index,int &Data,int Bank_num );

//------------------------------Write Register-----------------------------//
              static void WriteRegister(int Index, int Data,int Bank_num );

//-------------------------------Read GPIO Register-----------------------------//
              static void ReadGPIORegister(int Index,int &Data ) ;
//------------------------------Write GPIO Register-----------------------------//
              static void WriteGPIORegister(int Index, int Data );

//------------------------------Get CPU FAN Speed--------------------------//
              static void GetCPU_FanSpeed(int &Data);
//----------------------------Get System Fan Speed-------------------------//
              static void GetSYS_FanSpeed(int &Data);
//----------------------------Get Third Fan Speed--------------------------//
              static void GetThird_FanSpeed(int &Data);
//----------------------------Get CPU Temp---------------------------------//
              static void Get_Temp(int NO,int &Data);
              static void GetFour_FanSpeed(int &Data);
              static void GetFive_FanSpeed(int &Data);
              static void GetSix_FanSpeed(int &Data);
              static void GetExSix_FanSpeed(int &Data);
//--------------------------Get IO Count-----------------------------------//
              static int Get_IO_count(void);
              //static void WriteIoPortByte(WORD port,BYTE value);
              //static BYTE ReadIoPortByte(WORD port);
              static int GetGPIO_Bit(int index,int bit_index);
              static void SetGPIO_Bit(int index,int bit_index,bool HL);
              static void DecToBCD(int a);
              static void SetGPIO_IO(int index,int bit_Index,bool inout);
              static void SetGPIO_enable(int Index,int bit_Index,bool onoff);
              static void SetGPIO_8786bit_condition(int Index,int bit_index);
};
#endif
