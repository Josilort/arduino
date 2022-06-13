int senden = 8;
int empfangen = 12;

int datenbitsanz = 8;
int baud = 9600;
int b0;
int b1;
int b2;
int b3;
int b4;
int b5;
int b6;
int b7;

void setup() {
  Serial.begin(9600);

  pinMode(senden, OUTPUT);
  pinMode(empfangen, INPUT);
}

void loop() {
  digitalWrite(senden, LOW);
  delay(1000);
  digitalWrite(senden, HIGH);

  Serial.println(digitalRead(empfangen));
  delay(1000);
}