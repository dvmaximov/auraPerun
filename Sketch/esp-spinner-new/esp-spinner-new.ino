#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
#include <Esp.h>

#define NUM_LEDS 93
#define NUM_RINGS 5
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

bool enable[] = {false, false, false, false, false, false}; // [Центральное, Кольцо 1, Кольцо 2, Кольцо 3, Кольцо 4, Кольцо 5]
int period[] = {500, 500, 500, 500, 500, 500}; // [Центральное, Кольцо 1, Кольцо 2, Кольцо 3, Кольцо 4, Кольцо 5]
int num_leds[] = {0, 8, 12, 16, 24, 32}; // [Центральное, Кольцо 1, Кольцо 2, Кольцо 3, Кольцо 4, Кольцо 5]
int start_led[] = {0, 1, 9, 21, 37, 61}; // [Центральное, Кольцо 1, Кольцо 2, Кольцо 3, Кольцо 4, Кольцо 5]
int end_led[] = {0, 8, 20, 36, 60, 92}; // [Центральное, Кольцо 1, Кольцо 2, Кольцо 3, Кольцо 4, Кольцо 5]
uint8_t colors[][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}; // [Центральное, Кольцо 1, Кольцо 2, Кольцо 3, Кольцо 4, Кольцо 5]
uint directions[] = {0, 0, 0, 0, 0, 0}; // [Центральное, Кольцо 1, Кольцо 2, Кольцо 3, Кольцо 4, Кольцо 5]
uint blockSizes[] = {1, 1, 1, 1, 1, 1}; // [Центральное, Кольцо 1, Кольцо 2, Кольцо 3, Кольцо 4, Кольцо 5]
bool firstStart[] = {false, true, true, true, true, true}; // [Центральное, Кольцо 1, Кольцо 2, Кольцо 3, Кольцо 4, Кольцо 5]
unsigned long timers[] = {0, 0, 0, 0, 0, 0}; // [Центральное, Кольцо 1, Кольцо 2, Кольцо 3, Кольцо 4, Кольцо 5]
int8_t counters[] = {0, 0, 0, 0, 0, 0}; // [Центральное, Кольцо 1, Кольцо 2, Кольцо 3, Кольцо 4, Кольцо 5]

bool center1_0 = true;

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
    
    stringToRGB(Color0, colors[0]);
    stringToRGB(Color1, colors[1]);
    stringToRGB(Color2, colors[2]);
    stringToRGB(Color3, colors[3]);
    stringToRGB(Color4, colors[4]);
    stringToRGB(Color5, colors[5]);

    enable[0] = JSONData["enable0"].as<bool>();
    enable[1] = JSONData["enable1"].as<bool>();
    enable[2] = JSONData["enable2"].as<bool>();
    enable[3] = JSONData["enable3"].as<bool>();
    enable[4] = JSONData["enable4"].as<bool>();
    enable[5] = JSONData["enable5"].as<bool>();
    
    int Period0 = JSONData["period0"].as<int>();
    int Period1 = JSONData["period1"].as<int>();
    int Period2 = JSONData["period2"].as<int>();
    int Period3 = JSONData["period3"].as<int>();
    int Period4 = JSONData["period4"].as<int>();
    int Period5 = JSONData["period5"].as<int>();

    period[1] = Period1 / num_leds[1];
    period[2] = Period2 / num_leds[2];
    period[3] = Period3 / num_leds[3];
    period[4] = Period4 / num_leds[4];
    period[5] = Period5 / num_leds[5];
    period[0] = Period0 / 2;

    directions[1] = JSONData["direction1"].as<int>();
    directions[2] = JSONData["direction2"].as<int>();
    directions[3] = JSONData["direction3"].as<int>();
    directions[4] = JSONData["direction4"].as<int>();
    directions[5] = JSONData["direction5"].as<int>();


    blockSizes[1] = JSONData["blockSize1"].as<int>();
    blockSizes[2] = JSONData["blockSize2"].as<int>();
    blockSizes[3] = JSONData["blockSize3"].as<int>();
    blockSizes[4] = JSONData["blockSize4"].as<int>();
    blockSizes[5] = JSONData["blockSize5"].as<int>();

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
  // ESP.wdtDisable();
  ESP.wdtEnable(WDTO_1S);
  // hw_wdt_disable();
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
  for (uint8_t i = 1; i <= NUM_RINGS; i++) {
    firstStart[i] = true;
  }
  
  timers[0] = millis();
  for (uint8_t i = 1; i <= NUM_RINGS; i++) {
    timers[i] = timers[0];
  }

  for (uint8_t i = 1; i <= NUM_RINGS; i++) {
    counters[i] = directions[i] == 0? start_led[i] - 1 : start_led[i] + 1;
  }

  center1_0 = true;

  clear();
  isStarted = true;
  server.send(200,"application/json", "Ok");
}

void stop(){
  isStarted = false;
  for (uint8_t i = 0; i <= 5; i++) {
    enable[i] = false;
  }
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
  if (directions[num] == 0) {
    RING.setPixelColor(start_led[num], r, g, b);
    for (uint8_t i = start_led[num]; i < blockSizes[num] + start_led[num] - 1; i++) {
      int8_t pos = counters[num] - i;
      if ( pos == 0) {
        pos = end_led[num];
      } else if ( pos < 0 ) {
        pos = end_led[num] - abs(pos);
      }
      RING.setPixelColor(pos, r, g, b);
    }
  } else {
    for (uint8_t pos = 0 + start_led[num]; pos < blockSizes[num] + start_led[num]; pos++) {
      RING.setPixelColor(pos, r, g, b);
    }
  }
}

void nextSetColors(int num, uint8_t r, uint8_t g, uint8_t b) {
  int8_t pos;
  if (directions[num] == 0) {
    pos = counters[num] - blockSizes[num] - start_led[num] + 1;
    if (pos == 0) {
      pos = end_led[num];
    } else if (pos < 0 ) {
      pos = end_led[num] - abs(pos);
    } else {
      pos = pos + start_led[num] - 1;
    }
  } else {
    if (counters[num] <= end_led[num] - blockSizes[num]) {
      pos = blockSizes[num] + counters[num];
    } else {
      pos = blockSizes[num] - num_leds[num] + counters[num];
    }
  }
  RING.setPixelColor(counters[num], r, g, b);
  RING.setPixelColor(pos, BLACK[0], BLACK[1], BLACK[2]);
}

void setColors(int num, uint8_t r, uint8_t g, uint8_t b){
  if (firstStart[num]) {
    firstSetColors(num, r, g, b);
    firstStart[num] = false;
  } else {
    nextSetColors(num, r, g, b);
  }
}

void setCounter(int num){
  if (directions[num] == 0) {
    counters[num]++;
    if (counters[num] > end_led[num]) counters[num] = start_led[num];
   } else {
    counters[num]--;
    if (counters[num] < start_led[num]) counters[num] = end_led[num];
  }
}

void loop() {
  server.handleClient();
  delay(1);
  ESP.wdtFeed();
  if (isStarted) {
    for (uint8_t i = 1; i <= NUM_RINGS; i++)
    if (enable[i]) {
      if ((millis() - timers[i]) > period[i]) {
        setCounter(i);
        setColors(i, colors[i][0], colors[i][1], colors[i][2]);
        timers[i] = millis();
      }
      delay(1);
      ESP.wdtFeed();
    }
 
    if (enable[0]) {
      if ((millis() - timers[0]) > period[0]) {

        if (center1_0) {
          RING.setPixelColor(0, colors[0][0], colors[0][1], colors[0][2]);
        } 
        else {
          RING.setPixelColor(0, BLACK[0], BLACK[1], BLACK[2]);
        }
        center1_0 = !center1_0;
        timers[0] = millis();
      }
      ESP.wdtFeed();
    }
    RING.show();
    delay(1);
}
}
