#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
#include <Esp.h>
// #include <FastLED.h>

#define NUM_LEDS 93
#define DATA_PIN1 4 //D2 RING круг
#define BRIGHTNESS  100

Adafruit_NeoPixel RING(NUM_LEDS, DATA_PIN1, NEO_GRB + NEO_KHZ800);

//Параметры устройства
String espName = "AuraPerun";
String espType = "spinner";
String espID = "1";

//Параметры сети (роутер)
const char* ssid     = "9031";
const char* password = "zdMy9031";
// const char* ssid     = "centrett";
// const char* password = "238452323";

uint8_t RED[] = {255, 0, 0};
uint8_t BLUE[] = {0, 0, 255};
uint8_t WHITE[] = {255, 255, 255};
uint8_t BLACK[] = {0, 0, 0};

ESP8266WebServer server (80);

//Параметры программы светодиодной ленты
String programSetting = "default";

//Кольцо 5
bool enable5 = false;
int num_leds1_5 = 32;
int period1_5 = 500;
int start1_5 = 61;
int end1_5 = 92;
unsigned long timer1_5;
int counter1_5  = 0;
uint8_t color5[] = {0, 0, 0};
uint direction5 = 1;
int blockSize5 = 1;
bool firstStart5 = true;

//Кольцо 4
bool enable4 = false;
int num_leds1_4 = 24;
int period1_4 = 500;
int start1_4 = 37;
int end1_4 = 60;
unsigned long timer1_4;
int counter1_4  = 0;
uint8_t color4[] = {0, 0, 0};
uint direction4 = 1;
int blockSize4 = 1;
bool firstStart4 = true;


//Кольцо 3
bool enable3 = false;
int num_leds1_3 = 16;
int period1_3 = 500;
int start1_3 = 21;
int end1_3 = 36;
unsigned long timer1_3;
int counter1_3  = 0;
uint8_t color3[] = {0, 0, 0};
uint direction3 = 1;
int blockSize3 = 1;
bool firstStart3 = true;

//Кольцо 2
bool enable2 = false;
int num_leds1_2 = 12;
int period1_2 = 500;
int start1_2 = 9;
int end1_2 = 20;
unsigned long timer1_2;
int counter1_2  = 0;
uint8_t color2[] = {0, 0, 0};
uint direction2 = 1;
int blockSize2 = 1;
bool firstStart2 = true;


//Кольцо 1
bool enable1 = false;
int num_leds1_1 = 8;
int period1_1 = 500;
int start1_1 = 1;
int end1_1 = 8;
unsigned long timer1_1;
int counter1_1  = 0;
uint8_t color1[] = {0, 0, 0};
uint direction1 = 1;
int blockSize1 = 1;
bool firstStart1 = true;

//Центральное
bool enable0 = false;
int period1_0 = 500;
bool center1_0 = true;
unsigned long timer1_0;
uint8_t color0[] = {0, 0, 0};


bool isStarted = false;

void check(){
  StaticJsonDocument<300> JSONData;
  JSONData["espName"] = espName;
  JSONData["espType"] = espType;
  JSONData["espID"] = espID;
  JSONData["ip"] = WiFi.localIP().toString();
  JSONData["started"] = isStarted;
  char data[300];
  serializeJson(JSONData,data);
  server.send(200, "application/json", data);
}

// void getProgram(){
//   StaticJsonDocument<300> JSONData;
//   JSONData["programSetting"] = programSetting;

//   JSONData["enable1"] = enable1;
//   JSONData["externalColor1"] = String(externalColor1);
//   JSONData["internalColor1"] =  String(internalColor1);
//   JSONData["centerColor1"] =  String(centerColor1);
//   JSONData["externalPeriod1"] = externalPeriod1;
//   JSONData["internalPeriod1"] = internalPeriod1;
//   JSONData["centerPeriod1"] = centerPeriod1;
//   JSONData["externalDirection1"] = externalDirection1;
//   JSONData["internalDirection1"] = internalDirection1;
//   JSONData["blockSize1"] = blockSize1;

//   JSONData["isStarted"] = isStarted;
//   char data[300];
//   serializeJson(JSONData,data);
//   server.send(200, "application/json", data);
// }

void stringToRGB(String value, uint8_t * color) {
  String sr = String(value[1]) + String(value[2]);
  String sg = String(value[3]) + String(value[4]);
  String sb = String(value[5]) + String(value[6]);
  color[0] = (int) strtol(&sr[0], NULL, 16);
  color[1] = (int) strtol(&sg[0], NULL, 16);
  color[2] = (int) strtol(&sb[0], NULL, 16);
}

void setProgram(){

//    if(JSONData.containsKey("number")){
//     server.send(200,"application/json", String(JSONData["number"].as<int>())+" Received");
//    }

  StaticJsonDocument<300> JSONData;
  String jsonString = server.arg("plain");
  DeserializationError error = deserializeJson(JSONData, jsonString);

  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    server.send(500,"application/json","Error in parsing");
    return;
  } else {

    String Color0 = JSONData["color0"].as<String>();
    String Color1 = JSONData["color1"].as<String>();
    String Color2 = JSONData["color2"].as<String>();
    String Color3 = JSONData["color3"].as<String>();
    String Color4 = JSONData["color4"].as<String>();
    String Color5 = JSONData["color5"].as<String>();
    
    stringToRGB(Color0, color0);
    stringToRGB(Color1, color1);
    stringToRGB(Color2, color2);
    stringToRGB(Color3, color3);
    stringToRGB(Color4, color4);
    stringToRGB(Color5, color5);

    enable0 = JSONData["enable0"].as<bool>();
    enable1 = JSONData["enable1"].as<bool>();
    enable2 = JSONData["enable2"].as<bool>();
    enable3 = JSONData["enable3"].as<bool>();
    enable4 = JSONData["enable4"].as<bool>();
    enable5 = JSONData["enable5"].as<bool>();
    
    int Period0 = JSONData["period0"].as<int>();
    int Period1 = JSONData["period1"].as<int>();
    int Period2 = JSONData["period2"].as<int>();
    int Period3 = JSONData["period3"].as<int>();
    int Period4 = JSONData["period4"].as<int>();
    int Period5 = JSONData["period5"].as<int>();

    period1_1 = Period1 / num_leds1_1;
    period1_2 = Period2 / num_leds1_2;
    period1_3 = Period3 / num_leds1_3;
    period1_4 = Period4 / num_leds1_4;
    period1_5 = Period5 / num_leds1_5;
    period1_0 = Period0 / 2;
    

    direction1 = JSONData["direction1"].as<int>();
    direction2 = JSONData["direction2"].as<int>();
    direction3 = JSONData["direction3"].as<int>();
    direction4 = JSONData["direction4"].as<int>();
    direction5 = JSONData["direction5"].as<int>();


    blockSize1 = JSONData["blockSize1"].as<int>();
    blockSize2 = JSONData["blockSize2"].as<int>();
    blockSize3 = JSONData["blockSize3"].as<int>();
    blockSize4 = JSONData["blockSize4"].as<int>();
    blockSize5 = JSONData["blockSize5"].as<int>();

    // Serial.println(direction1);

    programSetting = "custom";
    server.send(200,"application/json", "Ok");
  }
}

void wifiConnect() {
  WiFi.mode(WIFI_STA);
  WiFi.setSleepMode(WIFI_NONE_SLEEP);
  WiFi.setAutoReconnect(true);
  WiFi.persistent(true);

  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println(WiFi.localIP());
}

void hw_wdt_disable(){
  *((volatile uint32_t*) 0x60000900) &= ~(1); // Hardware WDT OFF
}

void hw_wdt_enable(){
  *((volatile uint32_t*) 0x60000900) |= 1; // Hardware WDT ON
}

void setup() {
  delay( 1000 );
  // hw_wdt_disable();
  // ESP.wdtDisable();
  RING.begin();
  RING.setBrightness(100);
  Serial.begin(115200);

  wifiConnect();

  delay(500);

  //Настройка WEB сервера
  server.enableCORS(true);
  server.on("/check", HTTP_GET, check);
  // server.on("/getProgram", HTTP_GET, getProgram);
  server.on("/setProgram", HTTP_POST, setProgram);
  server.on("/start", HTTP_GET, start);
  server.on("/stop", HTTP_GET, stop);
  // server.on("/reconnect", HTTP_GET, wifiConnect);
  server.begin();
}


void start(){
  firstStart1 = true;
  firstStart2 = true;
  firstStart3 = true;
  firstStart4 = true;
  firstStart5 = true;

  timer1_0 = millis();
  timer1_1 = timer1_0;
  timer1_2 = timer1_0;
  timer1_3 = timer1_0;
  timer1_4 = timer1_0;
  timer1_5 = timer1_0;

  counter1_1 = direction1 == 0? start1_1 - 1 : start1_1 + 1;
  counter1_2 = direction2 == 0? start1_2 - 1 : start1_2 + 1;
  counter1_3 = direction3 == 0? start1_3 - 1 : start1_3 + 1;
  counter1_4 = direction4 == 0? start1_4 - 1 : start1_4 + 1;
  counter1_5 = direction5 == 0? start1_5 - 1 : start1_5 + 1;
  center1_0 = true;

  clear();
  isStarted = true;
  server.send(200,"application/json", "Ok");
}

void stop(){
  isStarted = false;
  enable0 = false;
  enable1 = false;
  enable2 = false;
  enable3 = false;
  enable4 = false;
  enable5 = false; 
  clear();
  server.send(200,"application/json", "Ok");
}

void clear() {
  for (int i = 0; i < NUM_LEDS; i++) { 
    RING.setPixelColor(i, BLACK[0], BLACK[1], BLACK[2]); 
  }
  RING.show();
}

void firstSetColors(int num, uint8_t r, uint8_t g, uint8_t b) {
  int counter;
  int startLed;
  int end;
  uint8_t endLed;
  int direction;
  int blockSize;
  switch (num) {
    case 1:
      counter = counter1_1;
      startLed = start1_1;
      endLed = end1_1;
      direction = direction1;
      blockSize = blockSize1;
      break;
    case 2:
      counter = counter1_2;
      startLed = start1_2;
      endLed = end1_2;      
      direction = direction2;
      blockSize = blockSize2;
      break;
    case 3:
      counter = counter1_3;
      startLed = start1_3;
      endLed = end1_3;  
      direction = direction3;
      blockSize = blockSize3;

      break;
    case 4:
      counter = counter1_4;
      startLed = start1_4;
      endLed = end1_4;  
      direction = direction4;
      blockSize = blockSize4;
      break;
    case 5:
      counter = counter1_5;
      startLed = start1_5;
      endLed = end1_5;  
      direction = direction5;
      blockSize = blockSize5;
      break;
  }

    if (direction == 0) {
      Serial.print(counter);      
      Serial.print(" ");
      for (uint8_t i = startLed; i < blockSize + startLed - 1; i++) {
        int8_t pos = counter - i;
        if ( pos == 0) {
          pos = endLed;
        } else if ( pos < 0 ) {
          pos = endLed - abs(pos);
        }
        // Serial.print("counter ");
        // Serial.println(counter);
        Serial.print(pos);
        Serial.print(" ");
      }
      Serial.println("");
    } else {
      for (uint8_t pos = 0 + startLed; pos < blockSize + startLed; pos++) {
        // Serial.print("counter ");
        // Serial.println(counter);
        Serial.print(pos);
        Serial.print(" ");
      }
      Serial.println("");
    }

}

void nextSetColors(int num, uint8_t r, uint8_t g, uint8_t b) {
  int counter;
  int startLed;
  int end;
  uint8_t endLed;
  int direction;
  int blockSize;
  switch (num) {
    case 1:
      counter = counter1_1;
      startLed = start1_1;
      endLed = end1_1;
      direction = direction1;
      blockSize = blockSize1;
      break;
    case 2:
      counter = counter1_2;
      startLed = start1_2;
      endLed = end1_2;      
      direction = direction2;
      blockSize = blockSize2;
      break;
    case 3:
      counter = counter1_3;
      startLed = start1_3;
      endLed = end1_3;  
      direction = direction3;
      blockSize = blockSize3;

      break;
    case 4:
      counter = counter1_4;
      startLed = start1_4;
      endLed = end1_4;  
      direction = direction4;
      blockSize = blockSize4;
      break;
    case 5:
      counter = counter1_5;
      startLed = start1_5;
      endLed = end1_5;  
      direction = direction5;
      blockSize = blockSize5;
      break;
  }
    Serial.print(counter);
    Serial.print(" ");
    if (direction == 0) {

      int8_t pos = counter - blockSize - startLed + 1;
      if (pos == 0) {
        pos = endLed;
      } else if (pos < 0 ) {
        pos = endLed - abs(pos);
      } else {
        pos = pos + startLed - 1;
      }
      Serial.print(blockSize);
      Serial.print(" ");   
      Serial.print(startLed);
      Serial.print(" ");   
      Serial.print(pos);
      Serial.println("");
    } else {
      int8_t pos = counter - blockSize - 2;
      // if (pos == startLed - 1) {
      //   pos = endLed;
      // } 
      // else 
      // if (pos < startLed ) {
      //   pos = counter + blockSize;
      // } 
      Serial.print(blockSize);
      Serial.print(" ");   
      Serial.print(startLed);
      Serial.print(" ");          
      Serial.print(pos);
      Serial.print(" ");           
    }
    Serial.println("");           

}

void setColors(int num, uint8_t r, uint8_t g, uint8_t b){
  Serial.print("Ring ");
  Serial.print(num);
  Serial.print("   ");
  // wdt_reset();
  // yield();
  bool first;
  switch (num) {
    case 1:
      first = firstStart1;
      break;
    case 2:
      first = firstStart2;
      break;
    case 3:
      first = firstStart3;
      break;
    case 4:
      first = firstStart4;
      break;
    case 5:
      first = firstStart5;
      break;
  }

  if (first) {
    firstSetColors(num, r, g, b);
    first = false;
  } else {
    nextSetColors(num, r, g, b);
  }

  switch (num) {
    case 1:
      firstStart1 = first;
      break;
    case 2:
      firstStart2 = first;
      break;
    case 3:
      firstStart3 = first;
      break;
    case 4:
      firstStart4 = first;
      break;
    case 5:
      firstStart5 = first;
      break;
  }
}

void setCounter(int num){
  // wdt_reset();
  // yield();
  // ESP.wdtFeed();
  int counter;
  // int num_leds;
  int direction;
  int start;
  int end;
  switch (num) {
    case 5:
      counter = counter1_5;
      // num_leds = num_leds1_5;
      direction = direction5;
      start = start1_5;
      end = end1_5;      
      break;
    case 1:
      counter = counter1_1;
      // num_leds = num_leds1_1;
      direction = direction1;
      start = start1_1;
      end = end1_1;      
      break;
    case 2:
      counter = counter1_2;
      // num_leds = num_leds1_2;
      direction = direction2;
      start = start1_2;
      end = end1_2;      
      break;
    case 3:
      counter = counter1_3;
      // num_leds = num_leds1_3;
      direction = direction3;
      start = start1_3;
      end = end1_3;      
      break;
    case 4:
      counter = counter1_4;
      // num_leds = num_leds1_4;
      direction = direction4;
      start = start1_4;
      end = end1_4;      
      break;
  }
  if (direction == 0) {
    counter++;
    if (counter > end) counter = start;
   } else {
    counter--;
    if (counter < start) counter = end;
  }
  switch (num) {
    case 5:
      counter1_5 = counter;
      break;
    case 1:
      counter1_1 = counter;
      break;
    case 2:
      counter1_2 = counter;
      break;
    case 3:
      counter1_3 = counter;
      break;
    case 4:
      counter1_4 = counter;
      break;
  }
}

void loop() {
  server.handleClient();
  delay(5);
  // wdt_reset();
  // yield();
  if (isStarted) {
    if (enable1) {
      if ((millis() - timer1_1) > period1_1) {
        // setColors1(1, BLACK[0], BLACK[1], BLACK[2]);
        setCounter(1);
        setColors(1, color1[0], color1[1], color1[2]);
        timer1_1 = millis();
      }
      // ESP.wdtFeed();
      // yield();
    }
    if (enable2) {
      if ((millis() - timer1_2) > period1_2) {
        // setColors1(2, BLACK[0], BLACK[1], BLACK[2]);
        setCounter(2);
        setColors(2, color2[0], color2[1], color2[2]);
        timer1_2 = millis();
      }
      // ESP.wdtFeed();
      // yield();
    }
    if (enable3) {
      if ((millis() - timer1_3) > period1_3) {
        // setColors1(3, BLACK[0], BLACK[1], BLACK[2]);
        setCounter(3);
        setColors(3, color3[0], color3[1], color3[2]);
        timer1_3 = millis();
      }
      // ESP.wdtFeed();
      // yield();
    }
    if (enable4) {
      if ((millis() - timer1_4) > period1_4) {
        // setColors1(4, BLACK[0], BLACK[1], BLACK[2]);
        setCounter(4);
        setColors(4, color4[0], color4[1], color4[2]);
        timer1_4 = millis();
      }
      // ESP.wdtFeed();
      // yield();
    }
    if (enable5) {
      if ((millis() - timer1_5) > period1_5) {
        // setColors1(5, BLACK[0], BLACK[1], BLACK[2]);
        setCounter(5);
        setColors(5, color5[0], color5[1], color5[2]);
        timer1_5 = millis();
      }
      // ESP.wdtFeed();
      // yield();
    }
 
    // if (enable0) {
    //   if ((millis() - timer1_0) > period1_0) {

    //     if (center1_0) {
    //       RING.setPixelColor(0, color0[0], color0[1], color0[2]);
    //     } 
    //     else {
    //       RING.setPixelColor(0, BLACK[0], BLACK[1], BLACK[2]);
    //     }
    //     center1_0 = !center1_0;
    //     timer1_0 = millis();
    //   }
    //   ESP.wdtFeed();
    //   yield();
    //  }
    RING.show();
  //   wdt_reset();
  //   yield();
  }
}
