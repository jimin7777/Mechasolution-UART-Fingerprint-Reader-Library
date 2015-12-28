#include <SoftwareSerial.h>
#include <MECHA_UARTFingerprint.h>
SoftwareSerial sofSeri(2,3);
MECHA_UARTFinger fin = MECHA_UARTFinger(&sofSeri);
void setup() {
  Serial.begin(9600);
  fin.begin();
  fin.AddUser1(1,3);
  //1은 사용자 ID, 3은 사용자 권한. AddUser1,2,3 3회 반복
  //the 1 is user ID, 3 is users Privilege. AddUser1,2,3  3times repeat
  fin.GetRespon();
  //반환값을 수신합니다. 함수마다 계속 반복하는것을 추천드립니다.
  //always have the Respon
  if(ACK_SUCCESS == fin.GetFeedback()){
    Serial.println("Success add user 1/3");
  }
  fin.AddUser2(1,3);
  fin.GetRespon();
  if(ACK_SUCCESS == fin.GetFeedback()){
    Serial.println("Success add user 2/3");
  }
  fin.AddUser3(1,3);
  fin.GetRespon();
  if(ACK_SUCCESS == fin.GetFeedback()){
    Serial.println("Success add user 3/3");
  }
}

void loop() {
  delay(5000);
  fin.Compare();
  //지문을 매칭합니다.
  //Compare the fingerprint
  fin.GetRespon(); 
  if(ACK_NOUSER != fin.GetFeedback()){
    Serial.print("USER ID: ");
    Serial.println(fin.GetPacket());
  }else {
    Serial.print("ERROR Feedback is: ");
    Serial.println(fin.GetFeedback(),HEX);
  }
}
