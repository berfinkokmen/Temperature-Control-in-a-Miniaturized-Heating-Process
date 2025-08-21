#include <math.h>
#define led 2
float error = 0;
int setPoint = 30;
int integral = 0;
float Kc = 0.1851;
int Ki = 0;
int Kd = 0;
float Ti = 163.13;
float Td = 9.61;
int derivative = 0;
float error_prev = 0;
float control;
unsigned long delayValue = 100;
int maxIntegral = 50; // Define a maximum value for the integral term
int minIntegral = -50; // Define a minimum value for the integral term


void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
}
double Termistor(int analogRead) {
  double temperature;
  temperature = log(((10240000 / analogRead) - 10000));
  temperature = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * temperature * temperature)) * temperature);
  temperature = temperature - 273.15;
  return temperature;
}

void loop() {
  int value = analogRead(A0);
  double temperature = Termistor(value);
  error_prev=error;
  integral += error;
  error = temperature - setPoint;
  derivative = (error-error_prev)/delayValue;
 
  if ((error > 0 && error_prev < 0) || (error < 0 && error_prev > 0)) {
    integral = 0;
  } else {
    // Accumulate the integral only if the control is not saturated
    if (control <= 127 && control >= -64) {
      integral += error;
      integral = constrain(integral, minIntegral, maxIntegral);
    }
  }
  control = Kc * (error +  Ki * integral /Ti + Kd * derivative * Td);
  // Saturate control signal to actuator's bounds
  control = constrain(control, -64, 127);


  Serial.print("Temperature: ");
  Serial.println(temperature);
  Serial.flush();
  //setFanSpeed(128 + control);
  setGateVoltage(192 - control);
  // if (error > 0) {
  // setGateVoltage(64);
  // } else if (error < 0){
  //   setGateVoltage(255);
  // }
  // Serial.print("Integral: ");
  // Serial.println(integral);
  Serial.print("Control: ");
  Serial.println(control);


  delay(delayValue);
}