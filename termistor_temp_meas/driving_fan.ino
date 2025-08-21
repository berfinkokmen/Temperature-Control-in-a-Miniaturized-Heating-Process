const int fanPin = 9; // PWM pin where the fan is connected

void initializeFan() {
  pinMode(fanPin, OUTPUT);
}

void setFanSpeed(int pwmValue) {
  analogWrite(fanPin, pwmValue);
}
