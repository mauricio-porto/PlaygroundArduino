#include <AccelStepper.h>

AccelStepper stepperX(AccelStepper::FULL4WIRE, 2, 3, 4, 5);
AccelStepper stepperY(AccelStepper::FULL4WIRE, 8, 9, 10, 11);

const long STEPS = 10000;
const int SPEED = 100;

const int tolerance = 1023 * 0.05;
const int center = 1023 / 2;
const int downThreshold = center - tolerance;
const int upThreshold = center + tolerance;

const int sensorX = A0;
const int sensorY = A1;

void setup() {
  Serial.begin(9600);

  // Configure each stepper
  stepperX.setMaxSpeed(1000.0);
  //stepperX.setSpeed(100);

  stepperY.setMaxSpeed(1000.0);
  //stepperY.setSpeed(100);

  balance();
}

void loop() {  
  delay(10);
}

void balance() {

  boolean needCenterX = true;
  boolean needCenterY = true;
  long xsteps;
  long ysteps;

  int xPos = analogRead(sensorX);
  if (xPos > upThreshold) {
      Serial.println("Move X clockwise");
      xsteps = STEPS;
      //stepperX.move(xsteps);
      stepperX.setSpeed(SPEED);
  } else if (xPos < downThreshold) {
      Serial.println("Move X counter clockwise");
      xsteps = -STEPS;
      //stepperX.move(xsteps);
      stepperX.setSpeed(-SPEED);
  }
  int yPos = analogRead(sensorY);
  if (yPos > upThreshold) {
      Serial.println("Move Y clockwise");
      ysteps = STEPS;
      //stepperY.move(ysteps);
      stepperY.setSpeed(SPEED);
  } else if (yPos < downThreshold) {
      Serial.println("Move Y counter clockwise");
      ysteps = -STEPS;
      //stepperY.move(ysteps);
      stepperY.setSpeed(-SPEED);
  }
 
  while (needCenterX || needCenterY) {

    int xPos = analogRead(sensorX);
    if (xPos < upThreshold && xPos > downThreshold) {
      stepperX.stop();
      needCenterX = false;
      Serial.println("X is centered");
    } else {
      stepperX.runSpeed();
      //stepperX.run();
      //stepperX.move(xsteps);
    }

    int yPos = analogRead(sensorY);
    if (yPos < upThreshold && yPos > downThreshold) {
      stepperY.stop();
      needCenterY = false;
      Serial.println("Y is centered");
    } else {
      stepperY.runSpeed();
      //stepperY.run();
      //stepperY.move(ysteps);
    }
  }
}
