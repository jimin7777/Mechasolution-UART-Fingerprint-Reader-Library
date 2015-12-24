#include "UARTFingerprint.h"

UARTFinger::UARTFinger(SoftwareSerial *Serial){
  sofSeri = Serial;
  Seri    = sofSeri;
}

UARTFinger::UARTFinger(HardwareSerial *Serial){
  hwSeri  = Serial;
  Seri    = hwSeri;
}

int UARTFinger::begin(){
  if(hwSeri){hwSeri->begin(UART_BAUD); return 0;}
  if(sofSeri){sofSeri->begin(UART_BAUD); return 0;}
  return -1;
}

void UARTFinger::Sleep(){//수면모드로 접속..
  byte CMD[8];
  for(int i = 0; i < 8; i++){
    CMD[i] = FORMAT[i];
  }
  CMD[1] = CMD_SLEEP;
  send(CMD);
}

void UARTFinger::Mode(byte value){
  byte CMD[8];
  for(int i = 0; i < 8; i++){
    CMD[i] = FORMAT[i];
  }
  CMD[1] = CMD_MODE;
  CMD[4] = value;
  send(CMD);
}

int UARTFinger::AddUser1(uint16_t id,byte privilege){
  if(id>0xfff) return -1;
  byte idL = (id & 0xff);
  byte idH = (id >> 8) & 0xff;
  byte CMD[8];
  for(int i = 0; i < 8; i++){
    CMD[i] = FORMAT[i];
  }
  CMD[1] = CMD_ADD1;
  CMD[2] = idH;
  CMD[3] = idL;
  CMD[4] = privilege;
  send(CMD);
}

int UARTFinger::AddUser2(uint16_t id,byte privilege){
  if(id>0xfff) return -1;
  byte idL = (id & 0xff);
  byte idH = (id >> 8) & 0xff;
  byte CMD[8];
  for(int i = 0; i < 8; i++){
    CMD[i] = FORMAT[i];
  }
  CMD[1] = CMD_ADD2;
  CMD[2] = idH;
  CMD[3] = idL;
  CMD[4] = privilege;
  send(CMD);
  return 0;
}

int UARTFinger::AddUser3(uint16_t id,byte privilege){
  if(id>0xfff) return -1;
  byte idL = (id & 0xff);
  byte idH = (id >> 8) & 0xff;
  byte CMD[8];
  for(int i = 0; i < 8; i++){
    CMD[i] = FORMAT[i];
  }
  CMD[1] = CMD_ADD3;
  CMD[2] = idH;
  CMD[3] = idL;
  CMD[4] = privilege;
  send(CMD);
  return 0;
}

int UARTFinger::DelUser(){
  byte CMD[8];
  for(int i = 0; i < 8; i++){
    CMD[i] = FORMAT[i];
  }
  CMD[1] = CMD_D_ALL_USER;
  send(CMD);
  return 0;
}

int UARTFinger::DelUser(uint16_t id){
  byte CMD[8];
  for(int i = 0; i < 8; i++){
    CMD[i] = FORMAT[i];
  }
  CMD[1] = CMD_DEL_USER;
  if(id>0xfff) return -1;
  byte idL = (id & 0xff);
  byte idH = (id >> 8) & 0x0f;
  CMD[2] = idH;
  CMD[3] = idL;
  send(CMD);
  return 0;
}

void UARTFinger::CountUser(){
  byte CMD[8];
  for(int i = 0; i < 8; i++){
    CMD[i] = FORMAT[i];
  }
  CMD[1] = CMD_CNT_USER;
  send(CMD);
}

int UARTFinger::Compare(uint16_t id){
  byte CMD[8];
  for(int i = 0; i < 8; i++){
    CMD[i] = FORMAT[i];
  }
  CMD[1] = CMD_COMP_1_1;
  if(id>0xfff) return -1;
  byte idL = (id & 0xff);
  byte idH = (id >> 8) & 0x0f;
  CMD[2] = idH;
  CMD[3] = idL;
  send(CMD);
  return 0;
}

int UARTFinger::Compare(){
  byte CMD[8];
  for(int i = 0; i < 8; i++){
    CMD[i] = FORMAT[i];
  }
  CMD[1] = CMD_COMP_I_N;
  send(CMD);
  return 0;
}

int UARTFinger::GetPrivilege(uint16_t id){
  byte CMD[8];
  for(int i = 0; i<8;i++){
    CMD[i] = FORMAT[i];
  }
  CMD[1] = CMD_USER_PRIV;
  if(id>0xfff) return -1;
  byte idL = (id & 0xff);
  byte idH = (id >> 8) & 0x0f;
  CMD[2] = idH;
  CMD[3] = idL;
  send(CMD);
  return 0;
}

int UARTFinger::send(byte *data){
  byte cheker = 0x00;
  for(int i = 1; i < 6; i++){
    cheker ^= data[i];
  }
  data[6] = cheker;
  for(int i = 0;i < 8;i++)
  {
    Seri->write(data[i]);
  }
}

