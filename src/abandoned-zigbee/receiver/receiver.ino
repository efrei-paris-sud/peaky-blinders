#include <SoftwareSerial.h>
SoftwareSerial zigbee(2, 3);
 
void setup()
{
    zigbee.begin(9600);                 
    Serial.begin(9600);                     
}
 
/***************************************
*  MAIN LOOP
***************************************/
 
void loop()
{
  if(zigbee.available()) {
    while(zigbee.available())  {
      Serial.write(zigbee.read());
      }
    }
}
