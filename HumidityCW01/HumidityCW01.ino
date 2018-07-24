#include <xCore.h>  //include xCore library @ https://github.com/xinabox/xCore
#include <xSW01.h>  //include sensor library @ https://github.com/xinabox/xSW01
#include <xOD01.h>  //include sensor library @ https://github.com/xinabox/xOD01



// Create a variable for the storage of data received from SW01  
  float Relative_Humidity;
  unsigned long previousMilli_1 = 0;  // timing variable for serial monitor
  const long interval_1= 5000;        // time delay for serial monitor
  bool flag;

  
const int DELAY_TIME = 1000;

xSW01 SW01;

void setup() {
  // Start the Serial Monitor
  Serial.begin(115200);

  // START I2C COMMUNICATION
  Wire.begin(2, 14);
  
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

