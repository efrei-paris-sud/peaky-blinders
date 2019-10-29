/**
 * Control led brightness using joystick
 * 
 */

int valx = 0;  // variable to store the value read

void setup() {
  pinMode(9, OUTPUT);
  Serial.begin(9600);           //  setup serial
}

void loop() {
  valx = analogRead(A0);  // read the input pin

  analogWrite(9, map(valx, 0, 1023, 0, 255));
  
}
