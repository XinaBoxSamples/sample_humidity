#include <xCore.h>  //include xCore library
#include <xSW01.h>  //include sensor library
#include <xOD01.h>

#if defined(ESP8266)
#define RED   RED
#define GREEN GREEN
#define BLUE  BLUE
#include <ESP8266WiFi.h>
#define Serial Serial

#elif defined(ARDUINO_SAMD_ZERO)
#define RED   CC03_RED
#define GREEN CC03_GREEN
#define BLUE  CC03_BLUE
#define Serial SerialUSB

#elif defined(ARDUINO_AVR_PRO)
#define RED   CC01_RED
#define GREEN CC01_GREEN
#define BLUE  CC01_BLUE
#define Serial Serial

#elif defined(ESP32)
#define RED   CW02_RED
#define GREEN CW02_GREEN
#define BLUE  CW02_BLUE
#define Serial Serial
#endif

// Create a variable for the storage of data received from SW01  
  float Relative_Humidity;
  unsigned long previousMilli_1 = 0;  // timing variable for serial monitor
  const long interval_1= 5000;        // time delay for serial monitor
  bool flag;

  
const int DELAY_TIME = 1000;

xSW01 SW01;

void setup() {

  #if defined(ESP8266)
  WiFi.forceSleepBegin();
  Wire.begin(2, 14);
  Wire.setClockStretchLimit(15000);

#elif defined(ARDUINO_SAMD_ZERO)
  Wire.begin();

#elif defined(ARDUINO_AVR_PRO)
  Wire.begin();

#elif defined(ESP32)
  Wire.begin();

#endif

  // Start the Serial Monitor
  Serial.begin(115200);
  
  // Start the SW01
  SW01.begin();
  OLED.begin();

  //Intialising variables
  Relative_Humidity = 0;
  
  OD01.println("Humidity Project");
  OD01.println("=================");
  
  //Delay for sensor to normalise
  delay(3000);
}

void loop() {
  
  // Read and calculate data from SW01 sensor
  SW01.poll();
  
  // Request the temperature measurement from SW01 and store in
  // the temperature variable   
  Relative_Humidity = SW01.getHumidity(); // Relative Humidity in Percentage format
  display_humidity();
  
}

void display_humidity() {

  // timing delay according to interval_1 variable
  // do not use the delay() function as it will pause all operations
  unsigned long currentMilli_1 = millis();
  if(currentMilli_1 - previousMilli_1 >= interval_1){
    previousMilli_1 = currentMilli_1;
    if(flag == false){
      flag = true;
    }
    else{
      flag = false;
    }
   
    
 // Show data over the Serial Monitor   
  OD01.print("Relative_Humidity: ");
  OD01.print(Relative_Humidity);
  OD01.println(" %");
  }
}

