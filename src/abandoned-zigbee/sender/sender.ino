#include <SoftwareSerial.h>
SoftwareSerial zigbee(2, 3);
int count;
 
void setup()
{
    zigbee.begin(9600);                 
    Serial.begin(9600);                     
    count = 0;
}
 
/***************************************
*  MAIN LOOP
***************************************/
 
void loop()
{
  String sentence = "Envoi du mot Sending";
  sentence += count;
  Serial.println(sentence);
  xbee.println(sentence);
  count++;
  delay(300);
}
