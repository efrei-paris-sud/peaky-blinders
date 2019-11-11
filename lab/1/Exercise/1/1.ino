/**
 * Control led brightness using a variable resistor
 * 
 */

int val = 0;  // variable to store the value read

void setup() {
  pinMode(11, OUTPUT);
  Serial.begin(9600);           //  setup serial
}

void loop() {
  val = analogRead(A0);  // read the input pin

  analogWrite(11, map(val, 0, 1023, 0, 255));
  
}
