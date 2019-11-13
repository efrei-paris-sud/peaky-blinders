#define buzzer 4                                                                           // affectation des broches

String inString = ""; 


void setup() {
  // initialize serial:
  Serial.begin(9600);
}

void loop() {
  while (Serial.available() > 0) {
    int inChar = Serial.read();
    if (isDigit(inChar)) {
      // convert the incoming byte to a char and add it to the string:
      inString += (char)inChar;
    }
    // if you get a newline, print the string, then the string's value:
    if (inChar == '\n') {
      Serial.print("Value:");
      Serial.println(inString.toInt());
      Serial.print("String: ");
      Serial.println(inString);

      int buzzerF = inString.toInt();
      tone(buzzer, buzzerF, 500);
      delay(500);
      inString = "";
    }
  }
}
