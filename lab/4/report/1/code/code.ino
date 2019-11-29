#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "Testtest";
const char* password = "efreiyant";

void scanNetworks() {
 
  int numberOfNetworks = WiFi.scanNetworks();
 
  Serial.print("Number of networks found: ");
  Serial.println(numberOfNetworks);
 
  for (int i = 0; i < numberOfNetworks; i++) {
 
    Serial.print("Network name: ");
    Serial.println(WiFi.SSID(i));
 
    Serial.print("Signal strength: ");
    Serial.println(WiFi.RSSI(i));
 
    Serial.print("MAC address: ");
    Serial.println(WiFi.BSSIDstr(i));
 
    //Serial.print("Encryption type: ");
    //Serial.print(WiFi.encryptionType(i)); the type is  wifi_auth_mode_t
   
    Serial.println("-----------------------");
 
  }
}

void connectToNetwork() {
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Establishing connection to WiFi..");
  }
  
  Serial.println("Connected to network");
}

void printWiFiInfo() {
  Serial.println(WiFi.macAddress());
  Serial.println(WiFi.localIP());
 
  //WiFi.disconnect(true);
  //Serial.println(WiFi.localIP());
}

void SendGetRequest(){
 if ((WiFi.status() == WL_CONNECTED)) { //Check the current connection status
 
    HTTPClient http;
 
    http.begin("https://openweathermap.org/data/2.5/weather?q=Paris,fr&appid=b6907d289e10d714a6e88b30761fae22&unit=metrics"); //Specify the URL 
    //(A test json server: https://jsonplaceholder.typicode.com/guide.html)
    
    int httpCode = http.GET();     //Make the request
 
    if (httpCode > 0) { //Check for the returning code
 
        String payload = http.getString();
        //Serial.println(httpCode);
        //Serial.println(payload);
        
        DynamicJsonDocument doc(2048);
        deserializeJson(doc, payload);
        JsonObject obj = doc.as<JsonObject>();
        float temp = obj["main"]["temp"];
        Serial.print("Temperature : ");
        Serial.println(temp);
      }
 
    else {
      Serial.println("Error on HTTP request Code:"+httpCode);
    }
 
    http.end(); //Free the resources
  }
}

void setup() {
  Serial.begin(9600);
  scanNetworks();
  connectToNetwork();
  printWiFiInfo();
}

void loop() {  
  SendGetRequest();
  delay(5);

}
