//---------------------------------------------------------------------------


#pragma hdrstop

#include "HWM_SIO.h"
#include <math.h>




//---------------------------------------------------------------------------

#pragma package(smart_init)
extern int addr;
extern int GPIO_addr;
int bit[8];

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//名稱:ChangeLDN()                                                            //
//功能:改變LDN                                                                //
//輸入:LDN                                                                    //
//輸出:none                                                                   //
//日期:102/03/27                                                              //
//Author: Seng Wen Hsin                                                       //
//----------------------------------------------------------------------------//
////////////////////////////////////////////////////////////////////////////////
void HWM_SIO::ChangeLDN(int LDN)
{
        EnterPnp();

        WriteIoPortByte( addr, 0x07);
        WriteIoPortByte( addr+1, LDN);
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//名稱:EnterPnp()                                                             //
//功能:進入PnP模式進行讀寫設定                                                //
//輸入:none                                                                   //
//輸出:none                                                                   //
//日期:102/03/27                                                              //
//Author: Seng Wen Hsin                                                       //
//----------------------------------------------------------------------------//
////////////////////////////////////////////////////////////////////////////////
void HWM_SIO::EnterPnp()
{
        int cmd = (addr==0x2E)?(0x55):(0xAA);
        WriteIoPortByte( addr, 0x87);
        WriteIoPortByte( addr, 0x01);
        WriteIoPortByte( addr, 0x55);
        WriteIoPortByte( addr, cmd);
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//名稱:ExitPnp()                                                              //
//功能:離開PnP模式將讀寫上鎖                                                  //
//輸入:none                                                                   //
//輸出:none                                                                   //
//日期:102/03/27                                                              //
//Author: Seng Wen Hsin                                                       //
//----------------------------------------------------------------------------//
////////////////////////////////////////////////////////////////////////////////
void HWM_SIO::ExitPnp()
{
        WriteIoPortByte( addr, 0x02);
        WriteIoPortByte( addr+1, 0x02);
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//名稱:Get_LDN_BaseAddr(int,int &,int &)                                      //
//功能:獲取不同LDN Base Address                                               //
//輸入:LDN_Input                                                              //
//輸出:MSB,LSB                                                                //
//日期:102/03/27                                                              //
//Author: Seng Wen Hsin                                                       //
//----------------------------------------------------------------------------//
////////////////////////////////////////////////////////////////////////////////
void HWM_SIO::Get_LDN_BaseAddr(int LDN_Input,int &MSB,int &LSB)
{
        WORD wPortAddr =addr;
        EnterPnp();

        WriteIoPortByte( wPortAddr, 0x07);
        WriteIoPortByte( wPortAddr+1 , LDN_Input) ;
        WriteIoPortByte( wPortAddr , 0x62) ;
        MSB = ReadIoPortByte( wPortAddr+1 ) ;

        WriteIoPortByte( wPortAddr , 0x63) ;
        LSB = ReadIoPortByte( wPortAddr+1 ) ;
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//名稱:Get_ChipID(int &,int &)                                                //
//功能:獲取Chip ID                                                            //
//輸入:none                                                                   //
//輸出:MSB,LSB                                                                //
//日期:102/03/27                                                              //
//Author: Seng Wen Hsin                                                       //
//----------------------------------------------------------------------------//
////////////////////////////////////////////////////////////////////////////////
void HWM_SIO::Get_ChipID(int &MSB,int &LSB)
{
        WORD wPortAddr =addr;
        EnterPnp();
        WriteIoPortByte( wPortAddr , 0x20) ;
        MSB = ReadIoPortByte( wPortAddr+1 ) ;
        WriteIoPortByte( wPortAddr , 0x21 ) ;
        LSB = ReadIoPortByte( wPortAddr+1 ) ;
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//名稱:ReadRegister(int ,int &)                                               //
//功能:讀取HardWare Monitor Rigister 內容                                     //
//輸入:Index                                                                  //
//輸出:Data                                                                   //
//日期:102/03/27                                                              //
//Author: Seng Wen Hsin                                                       //
//----------------------------------------------------------------------------//
////////////////////////////////////////////////////////////////////////////////
void HWM_SIO::ReadRegister(int Index,int &Data,int Bank_num )
{

        int MSB,LSB,BaseAddr;

        Get_LDN_BaseAddr(0x04,MSB,LSB);
        BaseAddr = (MSB<<8)+LSB+5;

        WORD wPortAddr =BaseAddr;

        int Bank_reg;
        int Bankbit7_5_index[3]={0,1,2};

        EnterPnp();
        WriteIoPortByte( wPortAddr ,  0x06) ;
        Bank_reg = ReadIoPortByte( wPortAddr+1 ) ;

        Bank_reg = Bank_reg & 0x1F;
        Bank_reg = (Bankbit7_5_index[Bank_num]<<5)+ Bank_reg;

        WriteIoPortByte( wPortAddr ,  0x06) ;
        WriteIoPortByte( wPortAddr+1 , Bank_reg) ;

        EnterPnp();
        WriteIoPortByte(wPortAddr ,  Index) ;
        Data = ReadIoPortByte( wPortAddr+1 ) ;

}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//名稱:WriteRegister(int , int )                                              //
//功能:寫入HardWare Monitor Rigister 內容                                     //
//輸入:Index ,Data                                                            //
//輸出:none                                                                   //
//日期:102/03/27                                                              //
//Author: Seng Wen Hsin                                                       //
//----------------------------------------------------------------------------//
////////////////////////////////////////////////////////////////////////////////
void HWM_SIO::WriteRegister(int Index, int Data,int Bank_num )
{
        int MSB,LSB,BaseAddr;
        Get_LDN_BaseAddr(0x04,MSB,LSB);
        BaseAddr = (MSB<<8)+LSB+5;

        WORD wPortAddr = BaseAddr;
        int Bank_reg;
        int Bankbit7_5_index[3]={0,1,2};
        EnterPnp();
        WriteIoPortByte( wPortAddr ,  0x06) ;
        Bank_reg = ReadIoPortByte( wPortAddr+1 ) ;

        Bank_reg = Bank_reg & 0x1F;
        Bank_reg = (Bankbit7_5_index[Bank_num]<<5)+ Bank_reg;

        WriteIoPortByte( wPortAddr ,  0x06) ;
        WriteIoPortByte( wPortAddr+1 , Bank_reg) ;

        EnterPnp();
        WriteIoPortByte( wPortAddr ,  Index) ;
        WriteIoPortByte( wPortAddr+1 , Data) ;

}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//名稱:ReadGPIORegister(int ,int &)                                               //
//功能:讀取GPIO Rigister 內容                                     //
//輸入:Index                                                                  //
//輸出:Data                                                                   //
//日期:102/04/08                                                              //
//Author: Seng Wen Hsin                                                       //
//----------------------------------------------------------------------------//
////////////////////////////////////////////////////////////////////////////////
void HWM_SIO::ReadGPIORegister(int Index,int &Data )
{



        WORD wPortAddr =GPIO_addr;

        //EnterPnp();
        Data = ReadIoPortByte( wPortAddr+Index ) ;

}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//名稱:WriteGPIORegister(int , int )                                              //
//功能:寫入GPIO Rigister 內容                                     //
//輸入:Index ,Data                                                            //
//輸出:none                                                                   //
//日期:103/04/08                                                              //
//Author: Seng Wen Hsin                                                       //
//----------------------------------------------------------------------------//
////////////////////////////////////////////////////////////////////////////////
void HWM_SIO::WriteGPIORegister(int Index, int Data)
{
        WORD wPortAddr =GPIO_addr;

        //EnterPnp();
        WriteIoPortByte( wPortAddr+Index ,  Data) ;


}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//名稱:GetCPU_FanSpeed(int &)                                                 //
//功能:讀取cpu fan 轉速                                                       //
//輸入:none                                                                   //
//輸出:Data                                                                   //
//日期:102/03/27                                                              //
//Author: Seng Wen Hsin                                                       //
//----------------------------------------------------------------------------//
////////////////////////////////////////////////////////////////////////////////
void HWM_SIO::GetCPU_FanSpeed(int &Data)
{

  int Data1,Data2;
  ReadRegister(0x0D,Data1,0);
  ReadRegister(0x18,Data2,0);
  Data = (Data2<<8)+Data1;
  if(Data!=0)
  {
   Data = 1350000/(Data*2);
  }
  if(Data2==0xFF)
  {
     Data = 0;
  }
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//名稱:GetSYS_FanSpeed(int &)                                                 //
//功能:讀取System fan 轉速                                                    //
//輸入:none                                                                   //
//輸出:Data                                                                   //
//日期:102/03/27                                                              //
//Author: Seng Wen Hsin                                                       //
//----------------------------------------------------------------------------//
////////////////////////////////////////////////////////////////////////////////
void HWM_SIO::GetSYS_FanSpeed(int &Data)
{
  int Data1,Data2;
  ReadRegister(0x0E,Data1,0);
  ReadRegister(0x19,Data2,0);
  Data = (Data2<<8)+Data1;
  if(Data!=0)
  {
   Data = 1350000/(Data*2);
  }
  if(Data2==0xFF)
  {
     Data = 0;
  }
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//名稱:GetThird_FanSpeed(int &)                                               //
//功能:讀取Third fan 轉速                                                     //
//輸入:none                                                                   //
//輸出:Data                                                                   //
//日期:102/03/27                                                              //
//Author: Seng Wen Hsin                                                       //
//----------------------------------------------------------------------------//
////////////////////////////////////////////////////////////////////////////////
void HWM_SIO::GetThird_FanSpeed(int &Data)
{
  int Data1,Data2;
  ReadRegister(0x0F,Data1,0);
  ReadRegister(0x1A,Data2,0);
  Data = (Data2<<8)+Data1;
  if(Data!=0)
  {
   Data = 1350000/(Data*2);
  }
  if(Data2==0xFF)
  {
     Data = 0;
  }
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//名稱:Get_Temp(int,int &)                                                    //
//功能:讀取CPU(1),system(2),third(3) 溫度                                     //
//輸入:NO                                                                     //
//輸出:Data                                                                   //
//日期:102/03/27                                                              //
//Author: Seng Wen Hsin                                                       //
//----------------------------------------------------------------------------//
////////////////////////////////////////////////////////////////////////////////
void HWM_SIO::Get_Temp(int NO,int &Data)
{
 ReadRegister(0x28+NO,Data,0);
 if(Data>127)
 {
  Data = Data-256;     //2's+1表示法
 }
}

void HWM_SIO::GetFour_FanSpeed(int &Data)
{
  int Data1,Data2;
  ReadRegister(0x80,Data1,0);
  ReadRegister(0x81,Data2,0);
  Data = (Data2<<8)+Data1;
  if(Data!=0)
  {
   Data = 1350000/(Data*2);
  }
  if(Data2==0xFF)
  {
     Data = 0;
  }
}

void HWM_SIO::GetFive_FanSpeed(int &Data)
{
  int Data1,Data2;
  ReadRegister(0x82,Data1,0);
  ReadRegister(0x83,Data2,0);
  Data = (Data2<<8)+Data1;
  if(Data!=0)
  {
   Data = 1350000/(Data*2);
  }
  if(Data2==0xFF)
  {
     Data = 0;
  }
}

void HWM_SIO::GetSix_FanSpeed(int &Data)
{
  int Data1,Data2;
  ReadRegister(0x93,Data1,0);
  ReadRegister(0x94,Data2,0);
  Data = (Data2<<8)+Data1;
  if(Data!=0)
  {
   Data = 1350000/(Data*2);
  }
  if(Data2==0xFF)
  {
     Data = 0;
  }
}

void HWM_SIO::GetExSix_FanSpeed(int &Data)
{
  int Data1,Data2;
  ReadRegister(0x4C,Data1,0);
  ReadRegister(0x4D,Data2,0);
  Data = (Data2<<8)+Data1;
  if(Data!=0)
  {
   Data = 1350000/(Data*2);
  }
  if(Data2==0xFF)
  {
     Data = 0;
  }
}
int HWM_SIO::GetGPIO_Bit(int Index,int bit_index)
{
        int Data;
        WORD wPortAddr =GPIO_addr;

        EnterPnp();
        Data = ReadIoPortByte( wPortAddr+Index ) ;
        DecToBCD(Data);
        return bit[bit_index];

}
void HWM_SIO::SetGPIO_Bit(int Index,int bit_index,bool HL)   //index=00:GP1 index=01:GP2
{
        int Data;
        WORD wPortAddr =GPIO_addr;

        EnterPnp();
        Data = ReadIoPortByte( wPortAddr+Index-1 ) ;
        DecToBCD(Data);
        bit[bit_index]= HL;
        Data = (128*bit[7])+(64*bit[6])+(32*bit[5])+(16*bit[4])+(8*bit[3])+(4*bit[2])+(2*bit[1])+(bit[0]);
        WriteIoPortByte( wPortAddr+Index-1 , Data);

}
void HWM_SIO::SetGPIO_IO(int Index,int bit_Index,bool inout)     //Set Simple IO in or out  GP1:index1 GP2:index2 GP3:index3
{
        BYTE bit_H[8]={1,2,4,8,16,32,64,128};
        BYTE bit_L[8]={0xFE,0xFD,0xFB,0xF7,0xEF,0xDF,0xBF,0x7F};
        ChangeLDN(0x07);
        int Data;
        WriteIoPortByte( addr, 0xC8+Index-1);
        Data = ReadIoPortByte( addr+1 ) ;
        WriteIoPortByte( addr, 0xC8+Index-1);
        if(inout)
        {
          Data = Data | bit_H[bit_Index];
          WriteIoPortByte( addr+1 , Data) ;
        }
        else
        {
           Data = Data & bit_L[bit_Index];
           WriteIoPortByte( addr+1 , Data) ;
        }
}
void HWM_SIO::SetGPIO_enable(int Index,int bit_Index,bool onoff)
{
        BYTE bit_H[8]={1,2,4,8,16,32,64,128};
        BYTE bit_L[8]={0xFE,0xFD,0xFB,0xF7,0xEF,0xDF,0xBF,0x7F};
        ChangeLDN(0x07);
        int Data;
        WriteIoPortByte( addr, 0xC0+Index-1);
        Data = ReadIoPortByte( addr+1 ) ;
        WriteIoPortByte( addr, 0xC0+Index-1);
        if(onoff)
        {
          Data = Data | bit_H[bit_Index];
          WriteIoPortByte( addr+1 , Data) ;
        }
        else
        {
           Data = Data & bit_L[bit_Index];
           WriteIoPortByte( addr+1 , Data) ;
        }

}
void HWM_SIO::SetGPIO_8786bit_condition(int Index,int bit_index)  //index1=>GP10 ,index2=>GP20 ......
{
     int Data;
     int or_data;
     if(Index<6)
     {

          ChangeLDN(0x07);
          WriteIoPortByte( addr , 0x25+Index-1) ;
          Data = ReadIoPortByte( addr+1 ) ;
          if((Index==5)&& (bit_index==7) )
          {
            or_data = pow(2,bit_index-1);
            Data = Data |or_data ;

          }
          else
          {
            or_data = pow(2,bit_index) ;
            Data = Data |or_data ;
          }
          WriteIoPortByte( addr , 0x25+Index-1) ;
          WriteIoPortByte( addr+1, Data ) ;
     }
     if(Index==6)
     {
          ChangeLDN(0x07);
          WriteIoPortByte( addr , 0x29) ;
          Data = ReadIoPortByte( addr+1 ) ;
          if(bit_index<3)
          {
            or_data = pow(2,6) ;
            Data = Data|or_data ;
          }
          else
          {
            or_data = pow(2,7) ;
            Data = Data|or_data ;
          }
          WriteIoPortByte( addr , 0x29) ;
          WriteIoPortByte( addr+1, Data ) ;
     }
     if(Index==7)
     {
         ChangeLDN(0x03);
         WriteIoPortByte( addr , 0x30) ;
         WriteIoPortByte( addr+1 , 0x00);
         Data=0;
     }
     if(Index==8)
     {
         ChangeLDN(0x03);
         WriteIoPortByte( addr , 0x2C) ;
         Data = ReadIoPortByte( addr+1 ) ;
         Data = Data|0x80 ;
         WriteIoPortByte( addr+1 , Data);
     }

}

void HWM_SIO::DecToBCD(int a)
{
   for(int i=0;i<8;i++)
   {
      bit[i] = a%2;
      a = a/2;
      //StringGrid1->Cells[1][]
   }
}

