
#include <Servo.h>

Servo myservo;
int pos = 0;

// sends servo data and MPU6050 data through radio
// transmission to raspberry
// digitalRead() digitalWrite()

void setup() {
  Serial.begin(9600);
  Serial.write("Hello serial!\n");
  CoreInitSequence();
}

void CoreInitSequence() {
  //MotorCalibration();
  Serial.write("Startup sequence\n");
  //LightShow(6);
  delay(1000);
  Serial.write("Calibrate Motor\n");
  MotorCalibration();
}

void LightShow(int sec) {
  
  pinMode(LED_BUILTIN, OUTPUT);

  int i_delay = 1000;
  int c = 1;

  for (int s = sec; s > 0; s --) {
    
    Serial.print(s);
    Serial.write("\n");
    c = c * 2;
    for (int i = 0; i < c; i ++) {
        digitalWrite(LED_BUILTIN, HIGH); 
        delay(i_delay/c);                     
        digitalWrite(LED_BUILTIN, LOW);
        delay(i_delay/c);
    }
    
    digitalWrite(LED_BUILTIN, HIGH); 
  }
  Serial.write("End");
}

void ExtraPins() {
  // The analog pins can be used identically to the digital pins, using the aliases A
  pinMode(A0, OUTPUT);
  digitalWrite(A0, HIGH);
}

void loop() {

}

void WakeUpJoint(int Pin, int Start, int Relax, int Stop) {
  
  myservo.attach(Pin); 

  for (int i = Start; i <= Stop; i += 1) {
    myservo.write(i); 
    delay(100);
  }
  
  myservo.write(Relax);
}

void MotorCalibration() {
  // Foot
  //WakeUpJoint(9, 103, 170, 179);

  
  myservo.attach(2);
  myservo.write(103);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      

  for (int i = 103; i <= 179; i += 1) {
    Serial.write("position \n");
    Serial.print(i);
    myservo.write(i); 
    delay(100);
  }
  
  myservo.write(170); 
  
  Serial.write("done\n"); 
}


void SendPulse() {
  for (int i = 0; i < 100; i ++) {
    digitalWrite(0, HIGH);
    delay(2);
    digitalWrite(1, HIGH);
    delay(18);  
  }
  Serial.write("Done\n");
}



// Servo mappings
#define FOOT = 0
#define ANKLE = 1
#define KNEE = 2
#define BOTTOCKS = 3
#define GROIN = 4

/*
 * {"FOOT": [
 *  "Pin": 9,
 *  "StartPos": 100, //103
 *  "Relax": 170,
 *  "EndPos": 180 // 179
 * ]}
 * 
 */
