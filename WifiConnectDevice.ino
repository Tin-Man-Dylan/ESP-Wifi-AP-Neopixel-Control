#include <ESP8266WiFi.h>
//#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <EEPROM.h>
#include <NeoPixelBus.h>

#define pixelCount 12


NeoPixelBus strip = NeoPixelBus(pixelCount, 13);

RgbColor red = RgbColor(128, 0, 0);
RgbColor green = RgbColor(0, 128, 0);
RgbColor blue = RgbColor(0, 0, 128);
RgbColor off = RgbColor(0, 0, 0);

int wifiOn = 0;
int cnt=0;


ESP8266WebServer server(80);

void LoginPage() {
	server.send(200, "text/html", "file:///C:/Users/Dylan%20Belvedere/Desktop/ORA_ESP2.html");
}
void R() {
  for (uint8_t pixel = 0; pixel < pixelCount; pixel++)
    {
          strip.SetPixelColor(pixel, red);
          strip.Show();
    }
  server.send(200, "text/html", "RED");
}
void OFF() {
  for (uint8_t pixel = 0; pixel < pixelCount; pixel++)
    {
          strip.SetPixelColor(pixel, off);
          strip.Show();
    }
  server.send(200, "text/html", "OFF");
}
void RGB()
{
String redvalString=server.arg("RED");
String greenvalString=server.arg("GREEN");
String bluevalString=server.arg("BLUE");
int redval = redvalString.toInt();
int greenval = greenvalString.toInt();
int blueval = bluevalString.toInt();
RgbColor rgb = RgbColor(redval, greenval, blueval);
  
for (uint8_t pixel = 0; pixel < pixelCount; pixel++)
    {
          strip.SetPixelColor(pixel, rgb);
          strip.Show();
    }
  server.send(204, "text/html", "RGB");
}

void setup() {
  delay(1000);
  Serial.begin(115200);

  strip.Begin();
  strip.Show();


 // IPAddress Ip = (192, 168, 3, 1);
  //IPAddress NMask = (192, 168, 3, 1);
  //WiFi.softAPConfig(Ip, Ip, NMask);
  WiFi.softAP("ORASCENTS", "12345678", 6); // SSID, Password, Channel frequency which sets frequency of WiFI Communication
  
  WiFi.mode(WIFI_AP);
  
   server.begin();
 
  delay(500);
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());
 
 	server.on("/connect", LoginPage);
	server.begin();
	Serial.println("HTTP server started");

  server.on("/login", []() {
  String ssid=server.arg("SSID");
  Serial.println(ssid);
  String password=server.arg("Password");
  Serial.println(password);
  int ssidLeng = ssid.length();
  int passLeng = password.length();
  EEPROM.begin(100);
  EEPROM.write(1, ssidLeng);
  EEPROM.write(2, passLeng);
        for (int i = 0; i < ssidLeng; ++i)
          {
            EEPROM.write(i+3, ssid[i]);
            Serial.print("Wrote: ");
            Serial.println(ssid[i]); 
          }
        for (int i = 0; i < passLeng; ++i)
          {
            EEPROM.write(ssidLeng+i+3, password[i]);
            Serial.print("Wrote: ");
            Serial.println(password[i]); 
          }  
  EEPROM.write(0, 1);
  EEPROM.commit();
 // char value = EEPROM.read(3);
//Serial.println(value);
  server.send(200, "text/plain", "Your SSID is " + ssid + " and password is " + password);
});

  
server.on("/r", R);
server.on("/off", OFF);
server.on("/RGB", RGB);
  
}

void loop() {



 
  if(EEPROM.read(0) == 1 && wifiOn == 0)
  {
  int esidLeng = EEPROM.read(1);
  int epassLeng = EEPROM.read(2);// reading the length of the field from EEPROM

  String esid;
  String epass = "";
    
   Serial.println(esidLeng);
   Serial.println(epassLeng);
   for (int i = 0; i < esidLeng; ++i)
    {
      esid += char(EEPROM.read(i+3));
     // Serial.println(char(EEPROM.read(i+3)));
    }
      for (int i = 0; i < epassLeng; ++i)
    {
      epass += char(EEPROM.read(i+3+esidLeng));
     // Serial.println(char(EEPROM.read(i+3+esidLeng)));
    }
    delay(10);
   Serial.println(esid);
   Serial.println(epass);
    char value = EEPROM.read(4);
    Serial.println(value);


    
    WiFi.begin(esid.c_str(), epass.c_str());
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    server.handleClient();
  }

  Serial.println("");
  Serial.println("WiFi connected");
  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  wifiOn = 1;
  Serial.println(wifiOn);
  WiFi.mode(WIFI_STA);
 
  }


  server.handleClient();

 




}

