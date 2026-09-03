#include <PS2X_lib.h>
#include <L29x.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <SoftwareSerial.h>

#define ARDUINO_RX 0
#define ARDUINO_TX 1

SoftwareSerial mySerial(ARDUINO_RX, ARDUINO_TX);
static int8_t Send_buf[8] = {0} ;
#define CMD_SEL_DEV 0X09
#define DEV_TF 0X02
#define CMD_PLAY_W_VOL 0X22

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

L29x motor1(13,12,11);
L29x motor2(8,9,10);
L29x motor3(A1,A0,3);

PS2X ps2x;
byte Type = 0;
byte vibrate = 0;
int RY=0, LY=0;

int error = 0;
byte type = 0;

bool move;

#define PS2_DAT        4  
#define PS2_CMD        5 
#define PS2_SEL        6 
#define PS2_CLK        7 
#define pressures   false
#define rumble      false

void setup(){

  pinMode(2, OUTPUT);
  pinMode(A3, OUTPUT);
  mySerial.begin(9600);
  randomSeed(analogRead(0));

  delay(300);
  error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);
  if(error == 0){
    Serial.println("Found Controller configured successful");
  }  
  else if(error == 1)
    Serial.println("No controller found");
  else if(error == 2)
    Serial.println("Controller found not accepting commands");
  else if(error == 3)
    Serial.println("Controller refusing Pressures mode");
  type = ps2x.readType(); 
  switch(type) {
    case 0:
      Serial.println("Unknown Controller");
      break;
    case 1:
      Serial.println("DualShock Controller");
      break;
    case 2:
      Serial.println("GuitarHero Controller");
      break;
  case 3:
      Serial.println("Wireless DualShock Controller");
      break;
   }

  pwm.begin();
  pwm.setPWMFreq(60);
  delay(10);
}


void loop(){

delay(200);
ps2x.read_gamepad();  

RY = ps2x.Analog(PSS_RY);
LY = ps2x.Analog(PSS_LY);

if (move){
 if (RY< 5){ motor1.fwd(200);}   // Right wheel
 if ((RY > 4) && (RY< 70)){motor1.fwd(100);}
 if ((RY > 69) && (RY< 120)){motor1.fwd(60);}
 if ((RY > 119) && (RY< 150)){motor1.coast();}
 if ((RY > 159) && (RY< 220)){motor1.bwd(40);}
 if ((RY > 219) && (RY< 250)){motor1.bwd(80);}
 if (RY > 249){motor1.bwd(120);}
 
 if (LY< 5){ motor2.fwd(200);}   // Left wheel
 if ((LY > 4) && (LY< 70)){motor2.fwd(100);}
 if ((LY > 69) && (LY< 120)){motor2.fwd(60);}
 if ((LY > 119) && (LY< 150)){motor2.coast();}
 if ((LY > 159) && (LY< 220)){motor2.bwd(40);}
 if ((LY > 219) && (LY< 250)){motor2.bwd(80);}
 if (LY > 249){motor2.bwd(120);}  
}

if(ps2x.Button(PSB_PAD_DOWN)){   // Head down
   motor3.fwd(200);
   delay(100);}
 else {motor3.coast(); } 

if(ps2x.Button(PSB_PAD_UP)){   // Head up
   motor3.bwd(200);
   delay(100);}
 else {motor3.coast(); } 


if(ps2x.Button(PSB_GREEN)){      // Probe Out
   probeSound();
   digitalWrite(2, LOW);
   delay(200);
   ps2x.read_gamepad(); }
else   

if(ps2x.Button(PSB_BLUE)){       // Probe In
   probeSound();
   digitalWrite(2, HIGH); 
   delay(200);
   ps2x.read_gamepad(); }
else   

if(ps2x.Button(PSB_L2)){     // Laser Fire
   digitalWrite(A3, HIGH);
   laserSound();
   delay(1000);
   digitalWrite(A3, LOW);
   ps2x.read_gamepad(); }
else
   
if(ps2x.Button(PSB_PAD_RIGHT)){  // Wag
  wag();}
else
   
if(ps2x.Button(PSB_PAD_LEFT)){  // Speak Random
   ears();}
   
if(ps2x.Button(PSB_PAD_LEFT)){  // Speak Random
   randoSound();}
else

if(ps2x.Button(PSB_RED)){       // Laser Out
   pwm.setPWM(2, 0, 150);
   weaponSound();}
else

if(ps2x.Button(PSB_PINK)){      // Laser In
    pwm.setPWM(2, 0, 550);
    weaponSound();}
else

if(ps2x.Button(PSB_START))      // Walk
    move = true;
else

if(ps2x.Button(PSB_SELECT))     // Sit
    move = false;


} 

// ---------------  Sub routines --------------

void sendCommand(int8_t command, int16_t dat){
  delay(20);
  Send_buf[0] = 0x7e;
  Send_buf[1] = 0xff;
  Send_buf[2] = 0x06;
  Send_buf[3] = command;
  Send_buf[4] = 0x00;
  Send_buf[5] = 0x1e;
  Send_buf[6] = (int8_t)(dat);
  Send_buf[7] = 0xef;
  for (uint8_t i = 0; i < 8; i++){
    mySerial.write(Send_buf[i]) ;
  }
}

void laserSound(){ 
  sendCommand(CMD_SEL_DEV, DEV_TF);
  delay(200);
  sendCommand(CMD_PLAY_W_VOL,0X0F02);
//  delay(1000);
  ps2x.read_gamepad(); 
}

void weaponSound(){ 
  sendCommand(CMD_SEL_DEV, DEV_TF);
  delay(200);
  sendCommand(CMD_PLAY_W_VOL,0X0F03);
  delay(2000);
  ps2x.read_gamepad(); 
}

void probeSound(){ 
  sendCommand(CMD_SEL_DEV, DEV_TF);
  delay(200);
  sendCommand(CMD_PLAY_W_VOL,0X0F01);
  delay(2000);
  ps2x.read_gamepad(); 
}

void randoSound(){ 
  int16_t clip;
  clip = 0X0F04 + random(1,22);
  delay(200);
  sendCommand(CMD_SEL_DEV, DEV_TF);
  delay(200);
  sendCommand(CMD_PLAY_W_VOL,clip);
  delay(2000);
  ps2x.read_gamepad();
}

void wag(){
  for (int i = 0; i <= 5; i++) {
     pwm.setPWM(0, 0, 475);
     delay(200);
     pwm.setPWM(0, 0, 375);
     delay(200);
     pwm.setPWM(0, 0, 275);
     delay(200);
     pwm.setPWM(0, 0, 375);
     delay(200);
  }
  for (int i = 0; i <= 5; i++) {
     pwm.setPWM(1, 0, 475);
     delay(200);
     pwm.setPWM(1, 0, 375);
     delay(200);
     pwm.setPWM(1, 0, 275);
     delay(200);
     pwm.setPWM(1, 0, 375);
     delay(200);   
  }
  ps2x.read_gamepad();
  delay(200);
}  

void ears(){
  for (int i = 0; i <= 5; i++) {
     pwm.setPWM(3, 0, 475);
     pwm.setPWM(4, 0, 275);
     delay(200);
     pwm.setPWM(3, 0, 275);
     pwm.setPWM(4, 0, 475);
     delay(200);
  }
  pwm.setPWM(3, 0, 375);
  pwm.setPWM(4, 0, 375);
  delay(200);
}
