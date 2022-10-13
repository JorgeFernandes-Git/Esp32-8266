#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "html_code.h"

#define USE_INTRANET // uncomment to connect through a router, need ssid and pass

const char* ssid = "Vodafone-7173DA";
const char* password = "Vbs4SWybtH";

// use as an access point
const char* AP_ssid = "ESP32myAP";
const char* AP_password = "12345678"; // min 8 chars

IPAddress Actual_IP;

// can be modified
IPAddress PageIP(192, 168, 1, 22);
IPAddress gateway(192, 168, 1, 5);
IPAddress subnet(255, 255, 255, 0);
IPAddress ip;

// used pins on ESP8266 UA
#define PIN_ON_BOARD_LED 2
#define PIN_PWM_GREEN_LED 12
#define PIN_BLUE_LED 13
#define PIN_RED_LED 15
#define PIN_BTN 4
#define PIN_BTN_FLASH 0
#define PIN_LIGHT_RES 0

// variables to store measure data and sensor states
int BitsA0 = 0, BitsA0_real = 0; // brightness sensor
float VoltsA0 = 0; // convert to volts
int pwm_led = 0; // pwm value
uint32_t SensorUpdate = 0; // time between updates
bool LED2 = true, LED13 = false, LED15 = false; // flags for outputs, led2 is normally closed
bool BTN = true, BTN_FLASH = true; // flags for inputs, both are normally closed

// the XML array size needs to be bigger that your maximum expected size. 2048 is way too big for this example
char XML[2048];

// just some buffer holder for char operations
char buf[32];

ESP8266WebServer server(80);

void setup() {

  // start serial
  Serial.begin(9600);

  // initiate pins output
  pinMode(PIN_ON_BOARD_LED, OUTPUT);
  pinMode(PIN_PWM_GREEN_LED, OUTPUT);
  pinMode(PIN_BLUE_LED, OUTPUT);
  pinMode(PIN_RED_LED, OUTPUT);
  // initiate pins input
  pinMode(PIN_BTN, INPUT);
  pinMode(PIN_BTN_FLASH, INPUT);

  // start with outputs off
  digitalWrite(PIN_ON_BOARD_LED, LED2);
  digitalWrite(PIN_BLUE_LED, LED13);
  digitalWrite(PIN_RED_LED, LED15);

  analogWrite(PIN_PWM_GREEN_LED, 0);

#ifdef USE_INTRANET
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Connected to ");
  Serial.println(ssid);
  Actual_IP = WiFi.localIP();
  Serial.println("IP address: "); 
  Serial.print(Actual_IP);
  delay(100);
#endif

#ifndef USE_INTRANET
  WiFi.softAPConfig(PageIP, gateway, subnet);
  delay(100);
  WiFi.softAP(AP_ssid, AP_password);
  delay(100);
  Serial.println("");
  Serial.println("Access Point Ready!");
  Serial.println("");
  Serial.println("Connect to: "); 
  Serial.println(AP_ssid);
  Serial.println("Password: ");
  Serial.println(AP_password);
  Actual_IP = WiFi.softAPIP();
  Serial.println("IP address: "); 
  Serial.print(Actual_IP);
#endif

  server.on("/", SendWebsite);
  server.on("/xml", SendXML);
  server.on("/UPDATE_SLIDER", UpdateSlider);
  server.on("/BUTTON_0", ProcessButton_0);
  server.on("/BUTTON_1", ProcessButton_1);
  server.on("/BUTTON_2", ProcessButton_2);
  server.begin();

}

void loop() {
  if ((millis() - SensorUpdate) >= 50) {
    SensorUpdate = millis();
    /*
    // inverter o sinal analógico
    BitsA0_real = analogRead(PIN_LIGHT_RES);
    BitsA0 = map(analogRead(PIN_LIGHT_RES), 0, 1023, 1023, 0);
    VoltsA0 = BitsA0_real * 3.3 / 1024;
    */
    
    // modo normal
    BitsA0 = analogRead(PIN_LIGHT_RES);
    VoltsA0 = BitsA0 * 3.3 / 1024;
    
    BTN = digitalRead(PIN_BTN);
    BTN_FLASH = digitalRead(PIN_BTN_FLASH);
  }
  server.handleClient();
}

void UpdateSlider() {
  String t_state = server.arg("VALUE");
  pwm_led = t_state.toInt();
  analogWrite(PIN_PWM_GREEN_LED, pwm_led);
  server.send(200, "text/plain", ""); //Send web page
}

void ProcessButton_0() {
  LED2 = !LED2;
  digitalWrite(PIN_ON_BOARD_LED, LED2);
  server.send(200, "text/plain", ""); //Send web page
}

void ProcessButton_1() {
  LED13 = !LED13;
  digitalWrite(PIN_BLUE_LED, LED13);
  server.send(200, "text/plain", ""); //Send web page
}

void ProcessButton_2() {
  LED15 = !LED15;
  digitalWrite(PIN_RED_LED, LED15);
  server.send(200, "text/plain", ""); //Send web page
}

void SendWebsite() {
  server.send(200, "text/html", PAGE_MAIN);
}

void SendXML() {
  strcpy(XML, "<?xml version = '1.0'?>\n<Data>\n");
  // send bitsA0
  sprintf(buf, "<B0>%d</B0>\n", BitsA0);
  strcat(XML, buf);
  // send Volts0
  sprintf(buf, "<V0>%d.%d</V0>\n", (int) (VoltsA0), abs((int) (VoltsA0 * 10)  - ((int) (VoltsA0) * 10)));
  strcat(XML, buf);

  // send BTN state
  if (BTN) {
    strcat(XML, "<BTN>0</BTN>\n");
  }
  else {
    strcat(XML, "<BTN>1</BTN>\n");
  }

  // send BTN_FLASH state
  if (BTN_FLASH) {
    strcat(XML, "<BTN_FLASH>0</BTN_FLASH>\n");
  }
  else {
    strcat(XML, "<BTN_FLASH>1</BTN_FLASH>\n");
  }

  // show led2 status
  if (LED2) {
    strcat(XML, "<LED2>1</LED2>\n");
  }
  else {
    strcat(XML, "<LED2>0</LED2>\n");
  }

  // show led13 status
  if (LED13) {
    strcat(XML, "<LED13>1</LED13>\n");
  }
  else {
    strcat(XML, "<LED13>0</LED13>\n");
  }

  // show led15 status
  if (LED15) {
    strcat(XML, "<LED15>1</LED15>\n");
  }
  else {
    strcat(XML, "<LED15>0</LED15>\n");
  }

  strcat(XML, "</Data>\n");
  Serial.println(XML);
  server.send(200, "text/xml", XML);
}
