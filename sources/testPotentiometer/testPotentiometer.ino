const int tolerance = 1023 * 0.05;
const int center = 1023 / 2;
const int downThreshold = center - tolerance;
const int upThreshold = center + tolerance;

void setup() {
  Serial.begin(9600);
  //Serial.print("center: ");
  //Serial.println(center);
  //Serial.print("downThreshold: ");
  //Serial.println(downThreshold);
  //Serial.print("upThreshold: ");
  //Serial.println(upThreshold);
}

void loop() {
    // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  if (sensorValue > upThreshold) {
    Serial.println("clockwise");
  } else if (sensorValue < downThreshold) {
    Serial.println("counter clockwise");
  } else {
    Serial.println("Centered");
  }
  delay(100);        // delay in between reads for stability
}

