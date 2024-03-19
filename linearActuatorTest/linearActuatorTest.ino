//Linear actuator test code

int motorA = 2;
int motorB = 3;

void setup() {
  pinMode(motorA, OUTPUT);
  pinMode(motorB, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  //Move forward
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(motorA, HIGH);
  digitalWrite(motorB, LOW);
  delay(1000);
  //Pause
  digitalWrite(motorA, LOW);
  digitalWrite(motorB, LOW);
  delay(1000);
  //Move backward
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(motorA, LOW);
  digitalWrite(motorB, HIGH);
  delay(1000);
}
