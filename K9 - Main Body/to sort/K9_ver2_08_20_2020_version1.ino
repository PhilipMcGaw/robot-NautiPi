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

L29x motor1(12, 11, 3); // right
L29x motor2(9, 8, 10); // left

PS2X ps2x;

byte Type = 0;
int Lazerpin = A1;
int DY = 150; // delay value
int x = 0; // loop value
byte vibrate = 0;
int RY = 0, LY = 0;
int i = 0;
int error = 0;
byte type = 0;
int min_servo = 110;
int max_servo = 660;
int default_head = 400;
bool probe = true;
bool gun = false;
int PIN_HEAD = 11; // which servo channel is which
int PIN_EARS = 0;
int PIN_PROBE = 8;
int PIN_GUN = 4;
int lazer_off = 1;
int lazer_on = 0;
int  head = default_head;
bool move;

#define PS2_DAT        4
#define PS2_CMD        5
#define PS2_SEL        6
#define PS2_CLK        7
#define pressures   false
#define rumble      false

void setup() {

  mySerial.begin(9600);

  delay(300);
  error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);
  if (error == 0) {
    Serial.println("Found Controller configured successful");

  }
  else if (error == 1)
    Serial.println("No controller found");
  else if (error == 2)
    Serial.println("Controller found not accepting commands");
  else if (error == 3)
    Serial.println("Controller refusing Pressures mode");
  type = ps2x.readType();
  switch (type) {
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
  delay(DY);

  // retract probe
  Probein();

  // center head
  pwm.setPWM(PIN_HEAD, 0, default_head);
  delay(DY);

  // reset lazer
  pinMode(Lazerpin, OUTPUT);
  digitalWrite(Lazerpin, lazer_on);
  delay(500);
  digitalWrite(Lazerpin, lazer_off);

  //lazergun();

  // retract gun
  gunin();
  startSound();
}
void loop() {

  delay(DY);
  ps2x.read_gamepad(); //pad values

  if (move) {
    twostick();
  }
  if (!move) {
    //tank();
  }
  if (ps2x.Button(PSB_PAD_LEFT)) { // head center
    centerhead();
  }
  else if (ps2x.Button(PSB_PAD_DOWN)) { // Head down
    headdown();
  }
  else if (ps2x.Button(PSB_PAD_UP)) { // Head up
    headup();
  }
  else if (ps2x.Button(PSB_PAD_RIGHT)) { // Head up
    nod();
  }
  else if (ps2x.Button(PSB_GREEN)) {   // Probe Out
    Probeinout();
  }
  else if (ps2x.Button(PSB_PINK)) {   // Laser in/Out
    if (gun) {
      gunin();
    }
    else {
      gunout();
    }
  }
  else if (ps2x.Button(PSB_RED)) {   // Laser Fire
    if (gun) {
      digitalWrite(Lazerpin, lazer_on);
      laserSound();
      delay(1200);
      digitalWrite(Lazerpin, lazer_off);
      ps2x.read_gamepad();
      delay(DY);
    }
    else {
      gunout();
      digitalWrite(Lazerpin, lazer_on);
      laserSound();
      delay(1200);
      digitalWrite(Lazerpin, lazer_off);
      ps2x.read_gamepad();
      delay(DY);
    }
  }
  else if (ps2x.Button(PSB_L1)) {
    sendCommand(CMD_PLAY_W_VOL, 0X08); delay(200);// I am k9 mark 3
  }
  else if (ps2x.Button(PSB_L2)) { // ears wiggle
    // sendCommand(CMD_PLAY_W_VOL, 0X16);
    ears();
    ps2x.read_gamepad();
    delay(DY);
  }
  else if (ps2x.Button(PSB_R2)) { // affirmitive
    sendCommand(CMD_PLAY_W_VOL, 0X01);
    ps2x.read_gamepad();
    delay(DY);
  }
  else if (ps2x.Button(PSB_R1)) { // not programed to bark
    sendCommand(CMD_PLAY_W_VOL, 0X1A); delay(2000);
    ps2x.read_gamepad();
    delay(DY);
  }
  else if (ps2x.Button(PSB_BLUE )) {   // Walk
    if (!move) {
      move = true;
      sendCommand(CMD_PLAY_W_VOL, 0X07); delay(2000); // still able to assist
      ps2x.read_gamepad();
      delay(DY);
    } else {
      move = false;
      sendCommand(CMD_PLAY_W_VOL, 0X19); delay(2000);// drive system regenerating
      ps2x.read_gamepad();
      delay(DY);
    }

  }

}

// ---------------  Sub routines --------------

void sendCommand(int8_t command, int16_t dat) {
  delay(20);
  Send_buf[0] = 0x7e;
  Send_buf[1] = 0xff;
  Send_buf[2] = 0x06;
  Send_buf[3] = command;
  Send_buf[4] = 0x00;
  Send_buf[5] = 0x1e;
  Send_buf[6] = (int8_t)(dat);
  Send_buf[7] = 0xef;
  for (uint8_t i = 0; i < 8; i++) {
    mySerial.write(Send_buf[i]) ;
  }
}

void laserSound() {
  sendCommand(CMD_SEL_DEV, DEV_TF);
  sendCommand(CMD_PLAY_W_VOL, 0X017);
  delay(DY);
  ps2x.read_gamepad();
}

void weaponSound() {
  sendCommand(CMD_PLAY_W_VOL, 0X002);
  delay(DY);
  ps2x.read_gamepad();
}


void startSound() {
  // sendCommand(CMD_SEL_DEV, DEV_TF);
  // sendCommand(CMD_PLAY_W_VOL,0X01); delay(2000); // affirmitiveaffirmitvie
  // sendCommand(CMD_PLAY_W_VOL,0X02); delay(2000); //  an effeicent machine
  // sendCommand(CMD_PLAY_W_VOL,0X03); delay(2000); // considerable data available
  // sendCommand(CMD_PLAY_W_VOL,0X04); delay(2000); // better
  // sendCommand(CMD_PLAY_W_VOL,0X05); delay(2000); // congrats unnessacary
  // sendCommand(CMD_PLAY_W_VOL, 0X06); delay(2000); // great danger

  // sendCommand(CMD_PLAY_W_VOL,0X07); delay(2000);// abl to assist
  sendCommand(CMD_PLAY_W_VOL, 0X08); delay(2000); // I am k9 mark 3
  //sendCommand(CMD_PLAY_W_VOL,0X09); delay(2000); // insuff data
  //  sendCommand(CMD_PLAY_W_VOL,0X10); delay(2000); //probe
  //   sendCommand(CMD_PLAY_W_VOL,0X11); delay(2000); // no available  data
  //   sendCommand(CMD_PLAY_W_VOL,0X12); delay(2000); //  pleas be specific

  //  sendCommand(CMD_PLAY_W_VOL, 0X13); delay(2000); // quicker and better
  //   sendCommand(CMD_PLAY_W_VOL,0X14); delay(2000); // reject
  //  sendCommand(CMD_PLAY_W_VOL,0X15); delay(2000); // probe
  //   sendCommand(CMD_PLAY_W_VOL,0X16); delay(2000); // ears
  //   sendCommand(CMD_PLAY_W_VOL,0X17); delay(2000); //gun
  // sendCommand(CMD_PLAY_W_VOL, 0X18); delay(2000); // malfunction in drive system
  //  sendCommand(CMD_PLAY_W_VOL,0X19); delay(2000);// drive system regenern
  //  sendCommand(CMD_PLAY_W_VOL,0X20); delay(2000);// quicker and better
  //  sendCommand(CMD_PLAY_W_VOL,0X21); delay(2000);// reject
  //  sendCommand(CMD_PLAY_W_VOL,0X22); delay(2000);//
  //  sendCommand(CMD_PLAY_W_VOL,0X23); delay(2000);//
  //  sendCommand(CMD_PLAY_W_VOL,0X24); delay(2000);//
  //  sendCommand(CMD_PLAY_W_VOL,0X25); delay(2000);//
  // sendCommand(CMD_PLAY_W_VOL,0X26); delay(2000);// reject
  //  sendCommand(CMD_PLAY_W_VOL, 0X1A); delay(2000); //I am not programmed to bark

  //    sendCommand(CMD_PLAY_W_VOL, 0X1B); delay(2000); //The doctors faithful friend
  //   sendCommand(CMD_PLAY_W_VOL, 0X1C); delay(2000); //accessing K9 unit
  //   sendCommand(CMD_PLAY_W_VOL, 0X1D); delay(2000); //insuffient data
  //   sendCommand(CMD_PLAY_W_VOL, 0X1E); delay(2000); //Drive systems regenerating
  //  sendCommand(CMD_PLAY_W_VOL, 0X1F); delay(2000); //danger
  //   sendCommand(CMD_PLAY_W_VOL, 0X2A); delay(2000); //Danger Doctor
  //  sendCommand(CMD_PLAY_W_VOL, 0X2B); delay(2000); // Theme
  //  sendCommand(CMD_PLAY_W_VOL, 0X2C); delay(2000); //theme
  //  sendCommand(CMD_PLAY_W_VOL, 0X2D); delay(2000); //theme
  //  sendCommand(CMD_PLAY_W_VOL, 0X2E); delay(2000); //farwel
  //  sendCommand(CMD_PLAY_W_VOL, 0X2F); delay(2000); //goodbye
}

void probeSound() {
  sendCommand(CMD_SEL_DEV, DEV_TF);
  delay(DY);
  sendCommand(CMD_PLAY_W_VOL, 0X0F10);
  ps2x.read_gamepad();
}

void wag() {
  for (int i = 0; i <= 5; i++) {
    pwm.setPWM(0, 0, 475);
    delay(100);
    pwm.setPWM(0, 0, 375);
    delay(100);
    pwm.setPWM(0, 0, 275);
    delay(100);
    pwm.setPWM(0, 0, 375);
    delay(100);
  }
  for (int i = 0; i <= 5; i++) {
    pwm.setPWM(1, 0, 475);
    delay(100);
    pwm.setPWM(1, 0, 375);
    delay(100);
    pwm.setPWM(1, 0, 275);
    delay(100);
    pwm.setPWM(1, 0, 375);
    delay(100);
  }
  ps2x.read_gamepad();
  delay(20);
}

void ears() {
  for (int i = 0; i <= 2; i++) {
    for (uint16_t microsec = 300; microsec < 2800; microsec = microsec + 40) {
      pwm.writeMicroseconds(0, microsec);

      delay(5);
    }
    for (uint16_t microsec = 2800; microsec > 300; microsec = microsec - 40) {
      pwm.writeMicroseconds(0, microsec);
      delay(5);
    }
  }

}

void gunin() {
  pwm.setPWM(PIN_GUN, 0, max_servo - 130);
  gun = false;
  delay(DY);
  ps2x.read_gamepad();
}
void gunout() {
  pwm.setPWM(PIN_GUN, 0, min_servo);
  gun = true;
  delay(DY);
  ps2x.read_gamepad();
}

void Probein() {
  pwm.setPWM(PIN_PROBE, 0, max_servo - 260);
  probe = false;
  delay(1000);
}

void Probeout() {
  pwm.setPWM(PIN_PROBE, 0, min_servo);
  probeSound();
  delay(1000);
  probe = true;
}
void Probeinout() {
  if (probe) {
    Probein();
  }
  else {
    Probeout();
  }
  ps2x.read_gamepad();
  delay(DY);
}

void twostick() {

  RY = ps2x.Analog(PSS_LY); //stick values
  LY = ps2x.Analog(PSS_RY); //stick values


  if (RY < 5) {
    motor1.fwd(255); // Right wheel
  }
  if ((RY > 5) && (RY < 16)) {
    motor1.fwd(235);
  }
  if ((RY > 15) && (RY < 26)) {
    motor1.fwd(215);
  }
  if ((RY > 25) && (RY < 36)) {
    motor1.fwd(195);
  }
  if ((RY > 35) && (RY < 46)) {
    motor1.fwd(175);
  }
  if ((RY > 45) && (RY < 56)) {
    motor1.fwd(155);
  }
  if ((RY > 55) && (RY < 66)) {
    motor1.fwd(135);
  }
  if ((RY > 65) && (RY < 76)) {
    motor1.fwd(115);
  }
  if ((RY > 75) && (RY < 86)) {
    motor1.fwd(95);
  }
  if ((RY > 85) && (RY < 96)) {
    motor1.fwd(75);
  }
  if ((RY > 95) && (RY < 106)) {
    motor1.fwd(55);
  }
  if ((RY > 105) && (RY < 116)) {
    motor1.fwd(35);
  }
  if ((RY > 115) && (RY < 126)) {
    motor1.fwd(5);
  }
  if ((RY > 125) && (RY < 130)) {
    motor1.coast();
  }
  if ((RY > 130) && (RY < 140)) {
    motor1.bwd(35);
  }
  if ((RY > 140) && (RY < 150)) {
    motor1.bwd(55);
  }
  if ((RY > 150) && (RY < 160)) {
    motor1.bwd(75);
  }
  if ((RY > 160) && (RY < 170)) {
    motor1.bwd(95);
  }
  if ((RY > 170) && (RY < 180)) {
    motor1.bwd(115);
  }
  if ((RY > 180) && (RY < 190)) {
    motor1.bwd(135);
  }
  if ((RY > 190) && (RY < 200)) {
    motor1.bwd(155);
  }
  if ((RY > 200) && (RY < 210)) {
    motor1.bwd(175);
  }
  if ((RY > 210) && (RY < 220)) {
    motor1.bwd(195);
  }
  if ((RY > 220) && (RY < 230)) {
    motor1.bwd(205);
  }
  if ((RY > 230) && (RY < 240)) {
    motor1.bwd(225);
  }
  if ((RY > 240) && (RY < 250)) {
    motor1.bwd(245);
  }
  if (RY > 250) {
    motor1.bwd(255);
  }

  if (LY < 5) {
    motor2.fwd(255); // LEFT wheel
  }
  if ((LY > 5) && (LY < 16)) {
    motor2.fwd(235);
  }
  if ((LY > 15) && (LY < 26)) {
    motor2.fwd(215);
  }
  if ((LY > 25) && (LY < 36)) {
    motor2.fwd(195);
  }
  if ((LY > 35) && (LY < 46)) {
    motor2.fwd(175);
  }
  if ((LY > 45) && (LY < 56)) {
    motor2.fwd(155);
  }
  if ((LY > 55) && (LY < 66)) {
    motor2.fwd(135);
  }
  if ((LY > 65) && (LY < 76)) {
    motor2.fwd(115);
  }
  if ((LY > 75) && (LY < 86)) {
    motor2.fwd(95);
  }
  if ((LY > 85) && (LY < 96)) {
    motor2.fwd(75);
  }
  if ((LY > 95) && (LY < 106)) {
    motor2.fwd(55);
  }
  if ((LY > 105) && (LY < 116)) {
    motor2.fwd(35);
  }
  if ((LY > 115) && (LY < 126)) {
    motor2.fwd(5);
  }
  if ((LY > 125) && (LY < 130)) {
    motor2.coast();
  }
  if ((LY > 130) && (LY < 140)) {
    motor2.bwd(35);
  }
  if ((LY > 140) && (LY < 150)) {
    motor2.bwd(55);
  }
  if ((LY > 150) && (LY < 160)) {
    motor2.bwd(75);
  }
  if ((LY > 160) && (LY < 170)) {
    motor2.bwd(95);
  }
  if ((LY > 170) && (LY < 180)) {
    motor2.bwd(115);
  }
  if ((LY > 180) && (LY < 190)) {
    motor2.bwd(135);
  }
  if ((LY > 190) && (LY < 200)) {
    motor2.bwd(155);
  }
  if ((LY > 200) && (LY < 210)) {
    motor2.bwd(175);
  }
  if ((LY > 210) && (LY < 220)) {
    motor2.bwd(195);
  }
  if ((LY > 220) && (LY < 230)) {
    motor2.bwd(205);
  }
  if ((LY > 230) && (LY < 240)) {
    motor2.bwd(225);
  }
  if ((LY > 240) && (LY < 250)) {
    motor2.bwd(245);
  }
  if (LY > 250) {
    motor2.bwd(255);
  }
}
void tank() {
  RY = ps2x.Analog(PSS_LY); //stick values
  LY = ps2x.Analog(PSS_RY); //stick values
}

void nod() {
  for (int i = 0; i <= 3; i++) {
    centerhead();
    delay(4);
    headdown();
    delay(4);
  }
  centerhead();
}
void centerhead() {
  if (head > default_head) {
    i = 0;
    x = head - default_head;
    for (i = 0; i < x; i = i + 1) {
      head = head - 1;
      pwm.setPWM(PIN_HEAD, 0, head);
      delay(4);
      ps2x.read_gamepad();
    }
  }
  else if (head < default_head) {
    i = 0;
    x = default_head - head;
    for (i = 0; i < x; i = i + 1) {
      head = head + 1;
      pwm.setPWM(PIN_HEAD, 0, head);
      delay(4);
      ps2x.read_gamepad();
    }
  }

}
void headdown() {
  i = 0;
  x = head - (min_servo + 145); // 145 is the throw to the end of the servo relational to the robot
  for (i = 0; i < x; i = i + 1) {
    head = head - 1;
    pwm.setPWM(PIN_HEAD, 0, head);
    delay(5);
    ps2x.read_gamepad();
  }
}

void headup() {
  i = 0;
  x = (max_servo - 85) - head;// 55 is the throw to the end of the servo relational to the robot
  for (i = 0; i < x; i = i + 1) {
    head = head + 1;
    pwm.setPWM(PIN_HEAD, 0, head);
    delay(4);
    ps2x.read_gamepad();
  }
}
