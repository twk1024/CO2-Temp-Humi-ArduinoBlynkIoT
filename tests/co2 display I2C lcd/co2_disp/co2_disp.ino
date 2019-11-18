#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <MHZ19.h>

SoftwareSerial ss(D7,D8);
MHZ19 mhz(&ss);

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, D1, D2);

void setup()
{
  Serial.begin(115200);
  Serial.println(F("Starting..."));
  ss.begin(9600);
    
  lcd.begin();
	lcd.backlight();
  lcd.clear();
	lcd.print("CO2:");

  lcd.setCursor(0,1);
  lcd.print("Temp:");

}

void loop()
{
  MHZ19_RESULT response = mhz.retrieveData();
  if (response == MHZ19_RESULT_OK)
  {
    Serial.print(F("CO2: "));
    Serial.println(mhz.getCO2());
//    Serial.print(F("Min CO2: "));
//    Serial.println(mhz.getMinCO2());
    Serial.print(F("Temperature: "));
    Serial.println(mhz.getTemperature());
    Serial.print(F("Accuracy: "));
    Serial.println(mhz.getAccuracy());
  }
  else
  {
    Serial.print(F("Error, code: "));
    Serial.println(response);
  }
  
  lcd.setCursor(5,0);
  lcd.print(mhz.getCO2());
  lcd.setCursor(6,1);
  lcd.print(mhz.getTemperature());
  
  delay(15000);
	
}
