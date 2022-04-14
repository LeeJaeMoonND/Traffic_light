int red = 500;

void setup() {
  // put your setup code here, to run once:
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
}

void loop() {
  digitalWrite(2, HIGH);
  delay(red);
  digitalWrite(2, LOW);

  digitalWrite(3, HIGH);
  delay(2000);
  digitalWrite(3, LOW);

  digitalWrite(4, HIGH);
  delay(2000);
  digitalWrite(4, LOW);
}
