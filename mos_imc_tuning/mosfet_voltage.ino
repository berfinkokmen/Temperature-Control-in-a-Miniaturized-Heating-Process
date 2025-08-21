const int MosPin = 10; // PWM pin where the fan is connected

void initializeGate() {
  pinMode(MosPin, OUTPUT);
}

void setGateVoltage(int pwmValue) {
  analogWrite(MosPin, pwmValue);
}
