#include <Wire.h>
#include <IRremote.h>
int RECV_PIN = 12;

#define SLAVE_ADDRESS 0x10
byte data_to_echo = 0;
#define relay_start 8
int relays[4] = {1,1,1,1};
IRrecv irrecv(RECV_PIN);

decode_results results;


void setup() 
{
  
  irrecv.enableIRIn();
  Serial.begin(9600);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(receiveData);
  Wire.onRequest(sendData);
}

void receiveData(int bytecount)
{
  for (int i = 0; i < bytecount; i++) {
    data_to_echo = Wire.read();
  }
  
}
void sendData()
{
  Serial.println(data_to_echo, BIN);
  Serial.println((data_to_echo & 63)+relay_start, DEC);
  Serial.println(data_to_echo & 64, BIN);
  Serial.println();
  digitalWrite((data_to_echo & 63)+relay_start, data_to_echo  & 64);
  relays[(data_to_echo & 63)] = (data_to_echo & 64) ? 1:0;
  Wire.write(data_to_echo);
}


void toggle(int relay){
  relays[relay] = !relays[relay];
  digitalWrite(relay+relay_start, relays[relay]);
}


void dump(decode_results *results) {
  int count = results->rawlen;
  if (results->decode_type == UNKNOWN) {
    Serial.println("Could not decode message");
  } 
  else {
    if (results->decode_type == NEC) {
      Serial.print("Decoded NEC: ");
    } 
    else if (results->decode_type == SONY) {
      Serial.print("Decoded SONY: ");
    } 
    else if (results->decode_type == RC5) {
      Serial.print("Decoded RC5: ");
    } 
    else if (results->decode_type == RC6) {
      Serial.print("Decoded RC6: ");
    }
    Serial.print(results->value, HEX);
    Serial.print(" (");
    Serial.print(results->bits, DEC);
    Serial.println(" bits)");
  }
  Serial.print("Raw (");
  Serial.print(count, DEC);
  Serial.print("): ");

  for (int i = 0; i < count; i++) {
    if ((i % 2) == 1) {
      Serial.print(results->rawbuf[i]*USECPERTICK, DEC);
    } 
    else {
      Serial.print(-(int)results->rawbuf[i]*USECPERTICK, DEC);
    }
    Serial.print(" ");
  }
  Serial.println("");
}

void loop() {
  if (irrecv.decode(&results)) {
    dump(&results);
    irrecv.resume();
  }
  if(results.value != 0){
 // Serial.println(results.value, HEX);  
  }
  
  if (results.value == 0xFF6897) {
    relay_one();
    results.value = 0x00000000;
  }

  if (results.value == 0xFF30CF) {
    relay_two();
    results.value = 0x00000000;
  }

  if (results.value == 0xFF18E7) {
    relay_three();
    results.value = 0x00000000;
  }

  if (results.value == 0xFF7A85) {
    relay_four();
    results.value = 0x00000000;
  }
  
  if(results.value == 0xFFFFFFFF){
    results.value = 0x00000000;
  }
} 

void relay_one() {
  toggle(0);
} 

void relay_two() {
  toggle(1);
}

void relay_three() {
  toggle(2);
}

void relay_four() {
  toggle(3);
}
