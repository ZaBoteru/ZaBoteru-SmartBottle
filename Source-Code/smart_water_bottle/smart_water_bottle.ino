#include <ESP8266Firebase.h>
#include <ESP8266WiFi.h>

#include <HX711_ADC.h>
#include <HX711.h>

#include <LiquidCrystal_I2C.h>

#include<SoftwareSerial.h>

#include <OneWire.h>
#include <DallasTemperature.h>

#define UV_LED 14

#define RED_PIN 15

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define tempSensorPin 0 // Arduino pin connected to DS18B20 sensor's DQ pin
OneWire oneWire(tempSensorPin);         // setup a oneWire instance
DallasTemperature tempSensor(&oneWire); // pass oneWire to DallasTemperature library

#define motorPin 2 //motor transistor is connected to pin 2

#define heaterPin 16

Firebase firebase("https://your-firebase-project-url.firebaseio.com/");
#define _SSID "your_wifi_ssid"
#define _PASSWORD "your_wifi_password"

#define HX711_dout 12 //mcu > HX711 dout pin
#define HX711_sck 13 //mcu > HX711 sck pin

float emptyBottleWeight = 113.0;
float previousWaterLevel = 0.0;
float currentWaterLevel = 0.0;
float temperature;
String needRefill;

HX711 scale;

void setup() {
  pinMode(UV_LED, OUTPUT);
  pinMode(RED_PIN, OUTPUT);
  pinMode(motorPin, OUTPUT);
  pinMode(heaterPin, OUTPUT);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  Serial.print("Connecting to: ");
  Serial.println(_SSID);
  lcd.init();                         // initialize the lcd 
  lcd.backlight();                    // turn on the backlight
  lcd.clear();
  tempSensor.begin();                 // initialize the sensor
  WiFi.begin(_SSID, _PASSWORD);
  scale.begin(HX711_dout, HX711_sck);

  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi Connected");

  // Print the IP address
  Serial.print("IP Address: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());

  scale.set_scale(653.125);             // this value is obtained by calibrating the scale with known weights
  scale.tare();                         // reset the scale to 0
}

void loop(){

// LOAD CELL
  Serial.print("one reading:\t");
  Serial.println(scale.get_units(), 1);
  delay(1000);

  if (scale.get_units() >= emptyBottleWeight){
    currentWaterLevel = scale.get_units() - emptyBottleWeight;
  }
  Serial.println(currentWaterLevel);
  if (currentWaterLevel < 0.75 * previousWaterLevel){
    firebase.setFloat("/ESP/drunkAmount", previousWaterLevel - currentWaterLevel);
    Serial.println("new drunkAmount setted");
  }

  // HEATER
  if (firebase.getString("/ESP/Heater")){
    String heaterState = firebase.getString("/ESP/Heater");
    if(heaterState == "1"){
      Serial.println("Sterilization Activated");
      digitalWrite(heaterPin, HIGH);
    }
    else{
      Serial.println("Sterilization Deactivated");
      digitalWrite(heaterPin, LOW);
    }
  }

  // TEMPERATURE SENSOR 
  tempSensor.requestTemperatures();             // send the command to get temperatures
  temperature = tempSensor.getTempCByIndex(0);  // read temperature in Celsius
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println("°C");
  firebase.setFloat("/ESP/temperature", temperature);
  delay(1000);

  lcd.clear();
  lcd.print("Liq Level " + String((int)currentWaterLevel) + "ml");
  lcd.setCursor(0, 1);
  lcd.print("Water Temp " + String((int)temperature) + "C");

// UV LED
  if (firebase.getString("/ESP/LED")){
    String ledState = firebase.getString("/ESP/LED");
    if(ledState == "1"){
      Serial.println("Sterilization Activated");
      digitalWrite(UV_LED, HIGH);
    }
    else{
      Serial.println("Sterilization Deactivated");
      digitalWrite(UV_LED, LOW);
    }
  }

  // RGB LED for remaining amount of water indication
    if (currentWaterLevel <= 375){
      // Yellow (turn red ON with green always ON):
      digitalWrite(RED_PIN, HIGH);
      delay(500);
    }
    else {
      // Green (Green is always ON):
      digitalWrite(RED_PIN, LOW);
      delay(500);
    }

  // VIBRATION MOTOR
    needRefill = firebase.getString("/ESP/needRefill");
    if (needRefill == "true"){
      digitalWrite(motorPin, HIGH); //vibrate
      delay(1000);  // delay one second
      digitalWrite(motorPin, LOW);  //stop vibrating
      delay(1000); //wait one second.
      digitalWrite(motorPin, HIGH); //vibrate
      delay(1000);  // delay one second
      digitalWrite(motorPin, LOW);  //stop vibrating
      delay(1000); //wait one second.
  }
  previousWaterLevel = currentWaterLevel;
  delay(2000);
}