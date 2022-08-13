#include <Servo.h> // Adds the Servo library to control servos.

Servo servoBase, servoArm, servoForearm, servoHand, servoGripper; // Initiates the types of servos that will be used.
int servoBasePos, servoArmPos, servoForearmPos, servoHandPos, servoGripperPos; // Initiates the int values for the servo position.

int servoSpeed = 15; // Initiates the speed in which the servos would move, in this instance, how fast the robot moves.

// Defining the color sensor pins:
#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8
 
// Values inputed from the Calibration sketch:
int redMin = 399, redMax = 791;
int greenMin = 406, greenMax = 800;
int blueMin = 299, blueMax = 569;
 
// Variables for Color Pulse Width Measurements:
int redPW = 0, greenPW = 0, bluePW = 0;
 
// Variables for final Color values:
int redValue, greenValue, blueValue;
 
void setup() {
  // Set S0 - S3 as outputs:
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  
  // Set Sensor output as input:
  pinMode(sensorOut, INPUT);
  
  // Set Frequency scaling to 20%:
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  
  // Setup Serial Monitor:
  Serial.begin(9600);

  // Initiates which pins are connected to each and every servo that will be used:
  servoBase.attach(9);
  servoArm.attach(10);
  servoForearm.attach(11);
  servoHand.attach(12);
  servoGripper.attach(13);

  // Initiates the servos to the fixed position of the servos upon startup:
  servoBasePos = 179;
  servoBase.write(servoBasePos);
  servoArmPos = 150;
  servoArm.write(servoArmPos);
  servoForearmPos = 100;
  servoForearm.write(servoForearmPos);
  servoHandPos = 90;
  servoHand.write(servoHandPos);
  servoGripperPos = 80;
  servoGripper.write(servoGripperPos);
}
 
void loop() {
  // Read Red value.
  redPW = getRedPW();
  // Map to value from 0-255.
  redValue = map(redPW, redMin,redMax,255,0);
  // Delay to stabilize sensor.
  delay(200);
  
  // Read Green value.
  greenPW = getGreenPW();
  // Map to value from 0-255.
  greenValue = map(greenPW, greenMin,greenMax,255,0);
  // Delay to stabilize sensor.
  delay(200);
  
  // Read Blue value.
  bluePW = getBluePW();
  // Map to value from 0-255.
  blueValue = map(bluePW, blueMin,blueMax,255,0);
  // Delay to stabilize sensor.
  delay(200);
  
  // Print output to Serial Monitor:
  Serial.print("R = "); Serial.print(redValue);
  Serial.print(" - G = "); Serial.print(greenValue);
  Serial.print(" - B = "); Serial.println(blueValue);

  // Conditions for each color to initiate the robot movements for each basket:
  if (redValue > greenValue && redValue > blueValue && redValue >= 280) { // If colour is RED.
    Serial.println("RED");
    redBasket();
  } else if (greenValue >= 100 && redValue <= 100 && blueValue <= 100) { // If colour is GREEN.
    Serial.println("GREEN");
    greenBasket();
  } else if (blueValue > redValue && blueValue > greenValue && blueValue >= 100) { // If colour is BLUE.
    Serial.println("BLUE");
    blueBasket();
  } else {
    //Serial.println("Color not detected...");
  }
}
 
// Function to read Red Pulse Widths:
int getRedPW() {
  // Set sensor to read Red only.
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  // Define integer to represent Pulse Width.
  int PW;
  // Read the output Pulse Width.
  PW = pulseIn(sensorOut, LOW);
  // Return the value.
  return PW;
}
 
// Function to read Green Pulse Widths:
int getGreenPW() {
  // Set sensor to read Green only.
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  // Define integer to represent Pulse Width.
  int PW;
  // Read the output Pulse Width.
  PW = pulseIn(sensorOut, LOW);
  // Return the value.
  return PW;
}
 
// Function to read Blue Pulse Widths:
int getBluePW() {
  // Set sensor to read Blue only.
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  // Define integer to represent Pulse Width.
  int PW;
  // Read the output Pulse Width
  PW = pulseIn(sensorOut, LOW);
  // Return the value.
  return PW;
}

void blueBasket() { // Robot Arm movements to move to the BLUE Basket if the colour BLUE is detected:
  // Moves servoArm to grab item:
  for (int angle = 150; angle >= 125; angle-=1) {
  servoArm.write(angle);
  delay (servoSpeed); //50
  }
  // Moves servoForearm to grab item:
  for (int angle = 90; angle <= 103; angle+=1) {
  servoForearm.write(angle);
  delay (servoSpeed);
  }
  // Moves servoHand to grab item:
  for (int angle = 90; angle >= 32; angle-=1) {
  servoHand.write(angle);
  delay (servoSpeed);
  }
  // Moves servoGripper to grab item:
  for (int angle = servoGripperPos; angle >= 50; angle-=1) {
  servoGripper.write(angle);
  delay (servoSpeed);
  }
  // Moves servoHand to normal position:
  for (int angle = 32; angle <= 90; angle+=1) {
  servoHand.write(angle);
  delay (servoSpeed);
  }  
  // Moves servoForearm to normal position:
  for (int angle = 103; angle >= 90; angle-=1) {
  servoForearm.write(angle);
  delay (servoSpeed);
  }
  // Moves servoArm to normal position:
  for (int angle = 125; angle <= 150; angle+=1) { 
  servoArm.write(angle);
  delay (servoSpeed);
  }
  // Moves servoBase to basket position:
  for (int angle = servoBasePos; angle >= 122; angle-=1) {
  servoBase.write(angle);
  delay (servoSpeed);
  }
  // Moves servoForearm to basket position:
  for (int angle = 100; angle <= 122; angle+=1) {
  servoForearm.write(angle);
  delay (servoSpeed);
  }
  // Moves gripper to normal position:
  for (int angle = 50; angle <= servoGripperPos; angle+=1) {
  servoGripper.write(angle);
  delay (servoSpeed);
  }
  // Moves servoForearm back to normal position:
  for (int angle = 122; angle >= 100; angle-=1) {
  servoForearm.write(angle);
  delay (servoSpeed);
  }
  // Moves servoBase to normal position:
  for (int angle = 122; angle <= servoBasePos; angle+=1) {
  servoBase.write(angle);
  delay (servoSpeed);
  }
}

void greenBasket() { // Robot Arm movements to move to the GREEN Basket if the colour GREEN is detected:
  // Moves servoArm to grab item:
  for (int angle = 150; angle >= 125; angle-=1) {
  servoArm.write(angle);
  delay (servoSpeed);
  }
  // Moves servoForearm to grab item:
  for (int angle = 90; angle <= 103; angle+=1) {
  servoForearm.write(angle);
  delay (servoSpeed);
  }
  // Moves servoHand to grab item:
  for (int angle = 90; angle >= 32; angle-=1) {
  servoHand.write(angle);
  delay (servoSpeed);
  }
  // Moves servoGripper to grab item:
  for (int angle = servoGripperPos; angle >= 50; angle-=1) {
  servoGripper.write(angle);
  delay (servoSpeed);
  }
  // Moves servoHand to normal position:
  for (int angle = 32; angle <= 90; angle+=1) {
  servoHand.write(angle);
  delay (servoSpeed);
  }  
  // Moves servoForearm to normal position:
  for (int angle = 103; angle >= 90; angle-=1) {
  servoForearm.write(angle);
  delay (servoSpeed);
  }
  // Moves servoArm to normal position:
  for (int angle = 125; angle <= 150; angle+=1) {
  servoArm.write(angle);
  delay (servoSpeed);
  }
  // Moves servoBase to basket position:
  for (int angle = servoBasePos; angle >= 109; angle-=1) {
  servoBase.write(angle);
  delay (servoSpeed);
  }
  // Moves servoForearm to basket position:
  for (int angle = 100; angle <= 122; angle+=1) {
  servoForearm.write(angle);
  delay (servoSpeed);
  }
  // Moves gripper to normal position:
  for (int angle = 50; angle <= servoGripperPos; angle+=1) {
  servoGripper.write(angle);
  delay (servoSpeed);
  }
  // Moves servoForearm back to normal position:
  for (int angle = 122; angle >= 100; angle-=1) {
  servoForearm.write(angle);
  delay (servoSpeed);
  }
  // Moves servoBase to normal position:
  for (int angle = 109; angle <= servoBasePos; angle+=1) {
  servoBase.write(angle);
  delay (servoSpeed);
  }
}

void redBasket() { // Robot Arm movements to move to the RED Basket if the colour RED is detected:
  // Moves servoArm to grab item:
  for (int angle = 150; angle >= 125; angle-=1) {
  servoArm.write(angle);
  delay (servoSpeed);
  }
  // Moves servoForearm to grab item:
  for (int angle = 90; angle <= 103; angle+=1) {
  servoForearm.write(angle);
  delay (servoSpeed);
  }
  // Moves servoHand to grab item:
  for (int angle = 90; angle >= 32; angle-=1) {
  servoHand.write(angle);
  delay (servoSpeed);
  }
  // Moves servoGripper to grab item:
  for (int angle = servoGripperPos; angle >= 50; angle-=1) {
  servoGripper.write(angle);
  delay (servoSpeed);
  }
  // Moves servoHand to normal position:
  for (int angle = 32; angle <= 90; angle+=1) {
  servoHand.write(angle);
  delay (servoSpeed);
  }  
  // Moves servoForearm to normal position:
  for (int angle = 103; angle >= 90; angle-=1) {
  servoForearm.write(angle);
  delay (servoSpeed);
  }
  // Moves servoArm to normal position:
  for (int angle = 125; angle <= 150; angle+=1) {
  servoArm.write(angle);
  delay (servoSpeed);
  }
    // Moves servoBase to basket position:
  for (int angle = servoBasePos; angle >= 92; angle-=1) {
  servoBase.write(angle);
  delay (servoSpeed);
  }
  // Moves servoForearm to basket position:
  for (int angle = 100; angle <= 130; angle+=1) {
  servoForearm.write(angle);
  delay (servoSpeed);
  }
   // Moves gripper to normal position:
  for (int angle = 50; angle <= servoGripperPos; angle+=1) {
  servoGripper.write(angle);
  delay (servoSpeed);
  }
  // Moves servoForearm back to normal position:
  for (int angle = 123; angle >= 100; angle-=1) {
  servoForearm.write(angle);
  delay (servoSpeed);
  }
  // Moves servoBase to normal position:
  for (int angle = 92; angle <= servoBasePos; angle+=1) {
  servoBase.write(angle);
  delay (servoSpeed);
  }
}