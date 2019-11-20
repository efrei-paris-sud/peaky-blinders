
/* program to put message on a MAX7219s.
Set up in No Decode mode.
*/
// ************************************ //
//a_presetup
#include <SPI.h>

// define pins usage
// D11-12-13 SPI interface

byte ss0 = 10;
byte x;
// define variables
// bytes to send to MAX7219s, with some initial data
byte displayArray[] = {
  0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55,0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa}; //16 bytes

// define 7219 register addresses for setup
byte decode_mode = 0x09; // 0x00 = No decode for digits 7-0
byte intensity_level = 0x0A; // 0x08 = mid level. Range is 0x00 to 0x0F
byte scan_limit = 0x0B; // 0x07 for all columns
byte shutdown_normal = 0x0C; // 0x00 - shutdown, 0x01 = normal
byte display_test = 0x0F; // 0x00 = normal, 0x01 = display test mode all on full

// ************************************ //

// b_setup
void setup(){

  pinMode (ss0, OUTPUT);
  digitalWrite (ss0, HIGH);

  Serial.begin(115200);

  // turn on SPI port
  SPI.begin();

  /*  set up MAX7219 registers  */

  // decode to No decode mode
  digitalWrite (ss0, LOW);
  SPI.transfer (decode_mode);
  SPI.transfer (0x00);
  digitalWrite (ss0, HIGH);

  Serial.println("No decode mode");

  // intensity to mid level
  digitalWrite (ss0, LOW);
  SPI.transfer (intensity_level);
  SPI.transfer (0x0f);
  digitalWrite (ss0, HIGH);

  Serial.println("Intensity");

  // scan limit to all 7 columns
  digitalWrite (ss0, LOW);
  SPI.transfer (scan_limit);
  SPI.transfer (0x07);
  digitalWrite (ss0, HIGH);

  Serial.println("Scan Limit");


  // dispay test On
  digitalWrite (ss0, LOW);
  SPI.transfer (display_test);
  SPI.transfer (0x01);
  digitalWrite (ss0, HIGH);
  delay(200);

  Serial.println("Display test on");

  // dispay test to normal
  digitalWrite (ss0, LOW);
  SPI.transfer (display_test);
  SPI.transfer (0x00);
  digitalWrite (ss0, HIGH);
  delay(200);

  Serial.println("Display test off");

  // shutdown to Normal mode
  digitalWrite (ss0, LOW);
  SPI.transfer (shutdown_normal);
  SPI.transfer (0x01);
  digitalWrite (ss0, HIGH);

  Serial.println("Normal mode");

  delay(250);

  Serial.println("setup done");

}
// ************************************ //

// c_loop
void loop(){

  // ************************************ //
  Serial.println("slaveSelect0 low "); // put data in registers 1 to 9. 16  bit transfer - address/data
  for (x = 1; x<9; x=x+1){
    digitalWrite (ss0, LOW);
    SPI.transfer (x);
    SPI.transfer(displayArray[x-1]);// array 0 to 7
    digitalWrite (ss0, HIGH);
  }

  delay(1000);

  Serial.println("slaveSelect0 high");

  for (x = 1; x<9; x=x+1){ 
    digitalWrite (ss0, LOW);
    SPI.transfer (x);
    SPI.transfer(displayArray[x+7]); // array 8 t0 15
    digitalWrite (ss0, HIGH);
  }

  delay(1000);

} // end loop
