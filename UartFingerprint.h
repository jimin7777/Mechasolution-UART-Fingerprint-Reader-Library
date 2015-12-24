#ifndef UARTF
#define UARTF

#if ARDUINO < 100
  #include <WProgram.h>
#else
  #include <Arduino.h>
#endif
#include  <SoftwareSerial.h>

#define ACK_SUCCESS 		0x00
#define ACK_FAIL		  	0x01
#define ACK_FULL		  	0x04
#define ACK_NOUSER			0x05
#define ACK_USER_EXIST	0x06
#define ACK_FIN_EXIST		0x07
#define ACK_TIMEOUT			0x08

#define CMD_SLEEP		  	0x2c
#define CMD_MODE		  	0x2d
#define CMD_ADD1		  	0x01
#define CMD_ADD2		  	0x02
#define CMD_ADD3		  	0x03
#define CMD_DEL_USER		0x04
#define CMD_D_ALL_USER	0x05
#define CMD_CNT_USER		0x09
#define CMD_COMP_1_1  	0x0b
#define CMD_COMP_I_N		0x0c
#define CMD_USER_PRIV		0x0A
#define CMD_GET_VER			0x26//soon..
#define CMD_COMP_LV			0x28//soon..
#define CMD_UPLOAD			0x24//soon..
#define CMD_UPLOAD_EX	  0x03//soon..
//15.12.24 ---- 산타할아버지 저 여자친구 주세요.
#define UART_BAUD       19200
//메카솔루션 화이팅
//#define CHEKING (A,B,C) (((A^B) = C)? 1:0)

class UARTFinger {
  public:

    UARTFinger(SoftwareSerial *);

    UARTFinger(HardwareSerial *);
    
    int begin();
    
    void Sleep();
    
    void Mode(byte value);
    
    int AddUser1(uint16_t id,byte privilege);
    
    int AddUser2(uint16_t id,byte privilege);
    
    int AddUser3(uint16_t id,byte privilege);
    
    int DelUser();
    
    int DelUser(uint16_t id);
    
    void CountUser();
    
    int Compare(uint16_t id);
    
    int Compare();
    
    int GetPrivilege(uint16_t id);
    //void
    
  private:
    byte FORMAT[8] = {0xf5,0x00,0x00,0x00,0x00,0x00,0x00,0xf5};
    
    SoftwareSerial *sofSeri = NULL;
    HardwareSerial *hwSeri = NULL;
    Stream *Seri;
    int send(byte *);
    int cheker(byte *);
};


#endif
