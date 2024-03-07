#include <Servo.h>

const int buttonPin = 2;
const int ledPin = 13;

int mode = 0;

Servo servo_updown;
Servo servo_rightleft;

int threshold_value = 2;

int ldrtopr = 0;  // top-right LDR
int ldrtopl = 1;  // top-left LDR
int ldrbotr = 2;  //  bottom-right LDR
int ldrbotl = 3;  // bottom-left  LDR
volatile int topl = 0;
volatile int topr = 0;
volatile int botl = 0;
volatile int botr = 0;

char switchstate;
String primit = "";
String numar = "";

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);

  servo_updown.attach(5);  //Servo motor up-down movement
  servo_rightleft.attach(6);


  attachInterrupt(digitalPinToInterrupt(buttonPin), functieUnu, RISING);
}

void loop() {
  if (mode % 2 == 0) {
    automaticsolartracker();
  } else {
    while (Serial.available() > 0) {
      switchstate = Serial.read();
      if (switchstate != 'q') {
        if (switchstate >= '0' && switchstate <= '9') {
          numar.concat(switchstate);
        } else {
          primit.concat(switchstate);
        }
      } else {
        Serial.println("Received termination signal");
        Serial.println("Command received: " + primit);
        Serial.println("Number received: " + numar);
        delay(15);
        if (primit == "u" || primit == " u") {
          servo_rightleft.write(numar.toInt());
          primit = "";
          numar = "";
          Serial.flush();
        } else {
          if (primit == "d" || primit == " d") {
            servo_updown.write(numar.toInt());
          }
          primit = "";
          numar = "";
          Serial.flush();
        }
      }
    }
  }
}

void functieUnu() {
  if (mode % 2 == 0) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }
  mode = mode + 1;
}

void automaticsolartracker() {
  //capturing analog values of each LDR
  topr = analogRead(A0);  //capturing analog value of top right LDR
  topl = analogRead(A1);  //capturing analog value of top left LDR
  botr = analogRead(A2);  //capturing analog value of bot right LDR
  botl = analogRead(A3);  //capturing analog value of bot left LDR

  Serial.print("TOPR=");
  Serial.println(topr);
  Serial.print("TOPL=");
  Serial.println(topl);
  Serial.print("BOTR=");
  Serial.println(botr);
  Serial.print("BOTL=");
  Serial.println(botl);

  // calculating average
  int avgtop = (topr + topl) / 2;    //average  of top LDRs
  int avgbot = (botr + botl) / 2;    //average of bottom LDRs
  int avgleft = (topl + botl) / 2;   //average of left LDRs
  int avgright = (topr + botr) / 2;  //average of right LDRs

  //Get the different
  int diffelev = avgtop - avgbot;    //Get the different average betwen  LDRs top and LDRs bot
  int diffazi = avgright - avgleft;  //Get the different  average betwen LDRs right and LDRs left

  //left-right movement of  solar tracker
  Serial.print("Diffelev");
  Serial.println(diffelev);
  Serial.print("Diffazi");
  Serial.println(diffazi);

  int x = servo_rightleft.read();
  Serial.print("X = ");
  Serial.println(x);
  delay(500);
  if (abs(diffazi) >= threshold_value) {  //Change  position only if light difference is bigger then the threshold_value
    if (diffazi > 0) {
      Serial.print(" < ");
      if (x < 180) {
        Serial.print(" + ");
        servo_rightleft.write(x + 10);
        Serial.println(" scris ");
      }
    }
    if (diffazi < 0) {
      if (x > 0) {
        servo_rightleft.write(x - 10);
      }
    }
  }

  //up-down movement of solar tracker
  if (abs(diffelev) >= threshold_value) {  //Change position only if light  difference is bigger then thethreshold_value
    int y = servo_updown.read();
    if (diffelev > 0) {
      if (y < 180) {
        servo_updown.write(y + 10);
      }
    }
    if (diffelev < 0) {
      if (y > 0) {
        servo_updown.write(y - 10);
      }
    }
  }
}