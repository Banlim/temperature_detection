#include<SPI.h>
#define OBJECT 0xA0 // 대상 온도 커맨드
#define SENSOR 0xA1 // 센서 온도 커맨드
#define MAXTIME 3000 // 측정 시간

const int chipSelectPin = 10;
unsigned char Timer1_Flag = 0;;
int iOBJECT, iSENSOR; // 부호 2byte 온도 저장 변수 
int inputPIN = 2;
int statusPIR = 0;
int valueRead = 0;
char *strName[] = {"test1", "test2", "test3", "test4", "test5"};

float maxtemp = 0; //온도 최대값
float temp = 0; //측정 온도
int tick = 0;


void setup() {
  /* DTS 온도 센서 모듈 */
  /* Setting SCE & SPI */
  digitalWrite(chipSelectPin , HIGH); // SCE High Level
  pinMode(chipSelectPin , OUTPUT); // SCE OUTPUT Mode
  SPI.setDataMode(SPI_MODE3); // SPI Mode
  SPI.setClockDivider(SPI_CLOCK_DIV16); // 16MHz/16 = 1MHz
  SPI.setBitOrder(MSBFIRST); // MSB First
  SPI.begin(); // Initialize SPI
  
  delay(500); // Sensor initialization time
  Timer1_Init(); // Timer1 setup : 500ms(2Hz) interval
  //Serial.begin(9600);
  interrupts(); // enable all interrupts

  /* 인체 감지 센서 */
  pinMode(inputPIN, INPUT);
  Serial.begin(9600);
}

int SPI_COMMAND (unsigned char cCMD){
  unsigned char T_high_byte, T_low_byte;
  
  digitalWrite(chipSelectPin , LOW); // SCE Low Level
  delayMicroseconds(10); // delay(10us)
  SPI.transfer(cCMD); // transfer 1st Byte
  delayMicroseconds(10); // delay(10us)
  T_low_byte = SPI.transfer(0x22); // transfer 2nd Byte
  delayMicroseconds(10); // delay(10us)
  T_high_byte = SPI.transfer(0x22); // transfer 3rd Byte
  delayMicroseconds(10); // delay(10us)
  digitalWrite(chipSelectPin , HIGH); // SCE High Level

  return (T_high_byte<<8 | T_low_byte); // 온도값 return
}

ISR(TIMER1_OVF_vect) { // interrupt service routine (Timer1 overflow)
  TCNT1 = 34286; // preload timer : 이 값을 바꾸지 마세요.
  Timer1_Flag = 1; // Timer 1 Set Flag
} 

void Timer1_Init(void){
 TCCR1A = 0;
 TCCR1B = 0;
 TCNT1 = 34286; // preload timer 65536-16MHz/256/2Hz
 TCCR1B |= (1 << CS12); // 256 prescaler
 TIMSK1 |= (1 << TOIE1); // enable timer overflow interrupt
}

void loop() {


//    /*인체 감지 센서*/
//    valueRead = digitalRead(inputPIN);    
//    
//    if ((valueRead == HIGH)  &&  (statusPIR == LOW)) {    
//      Serial.println("Motion detected!");    
//      statusPIR = HIGH;    
//    }  
//    else{  
//      if((valueRead == LOW) && (statusPIR == HIGH)){  
//        Serial.println("Motion ended!");    
//        statusPIR = LOW;  
//      }  
//    } 
  // 추후에 qr 리더기로 정보 받으면 온도 측정하는 걸로 수정
  if(Timer1_Flag){ // 500ms 마다 반복 실행(Timer 1 Flag check)
    /* DTS온도 체크 */
    iOBJECT= SPI_COMMAND(OBJECT); // 대상 온도 Read
    temp = float(iOBJECT) / 100;
    tick = 0;

    if(temp > 35){
      while(tick < MAXTIME)
      {
        iOBJECT= SPI_COMMAND(OBJECT);
        temp = float(iOBJECT) / 100;
        maxtemp = max(temp, maxtemp);
        delay(200);
        tick += 200;
      }

      int randomNum = random(1000,9000);
      char *phone = "010-1234-5678";
      Serial.print(strName[random(4)]);
      Serial.print(",");
      Serial.print(randomNum);
      Serial.print(",");
      Serial.print(phone);
      Serial.print(",");
      Serial.println(maxtemp, 2);
      //Serial.println(float(iOBJECT)/100, 2);
    }
    maxtemp = 0;
    
    delay(1500);
  }
  
}
