/*
ITE io RW Library
Copyright 2014-2020

*/
#ifndef ITEioRW

#define ITEioRW
#include<windows.h> 

extern "C" {
// write a byte to register
void WINAPI WriteIoPortByte(WORD port,BYTE value);

// read a byte from register
BYTE WINAPI ReadIoPortByte(WORD port);

// open driver
bool WINAPI ITEDrvopen(void);

// remove driver
void WINAPI ITEDrvclose(void);
}
#endif
 