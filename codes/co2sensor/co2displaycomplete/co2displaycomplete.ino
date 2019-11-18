#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <MHZ19.h>
#include <dht11.h>         

//taewook wifi
char auth[] = "yVlpBz0CF7FF-NGoexfkT5mHoGwHtXGI";
char ssid[] = "wifissid";
char pass[] = "wifipassword";


SoftwareSerial ss(D7,D8);
MHZ19 mhz(&ss);

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, D1, D2);


dht11 DHT11;      

#define DHT11PIN D5                     

//led setup
//int R = A0 ;
//int G = D3 ;
//int B = D4 ;

//buzzer
//int buzzer = D3;        

 

void setup()
{
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  Serial.println(F("Starting..."));
  ss.begin(9600);
    
  lcd.begin();
	lcd.backlight();
  lcd.clear();

  pinMode(D0, OUTPUT);
  pinMode(D4, OUTPUT);

  //pinMode(buzzer, OUTPUT);   
    Serial.println("DHT11 TEST PROGRAM ");            // 'DHT11 TEST PROGRAM'를 시리얼 통신으로 송신하고 줄을 바꿉니다.
  Serial.print("LIBRARY VERSION: ");                // 'LIBRARY VERSION: '를 시리얼 통신으로 송신합니다.
  Serial.println(DHT11LIB_VERSION);                 // DHT11LIB_VERSION 변수값을 시리얼 통신으로 송신하고 줄을 바꿉니다.
  Serial.println();     

}


double Fahrenheit(double celsius)                    // Fahrenheit라는 함수를 만듭니다. 함수의 입력값은 celsius에 저장됩니다.
{
  return 1.8 * celsius + 32;                         // 입력된 celsius값을 1.8를 곱하고 32를 더하여 출력합니다.
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

//dht11
  Serial.println("\n");                             // 줄바꿈을 츨력하고 줄을 바꿉니다 (2줄을 바꿈)
  int chk = DHT11.read(DHT11PIN);                    // DHT11PIN에서 받은 값을 chk에 저장합니다.
  Serial.print("Humidity (%): ");                   // 'Humidity (%): '를 시리얼 통신으로 출력합니다.
  Serial.println((float)DHT11.humidity, 2);         // DHT11.humidity 값을 소수점 2자리수까지 출력하고 줄을 바꿉니다.
  Serial.print("Temperature (oC): ");               // 'Temperature (oC): '를 시리얼 통신으로 출력합니다.
  Serial.println((float)DHT11.temperature, 2);      // DHT11.temperature 값을 소수점 2자리수까지 출력하고 줄을 바꿉니다.
  Serial.print("Temperature (oF): ");               // 'Temperature (oF): '를 시리얼 통신으로 출력합니다.
  Serial.println(Fahrenheit(DHT11.temperature), 2); // DHT11.temperature 값을 소수점 2자리수까지 출력하고 줄을 바꿉니다.
  delay(2000);                                       // 2초동안 지연시킵니다.


  //notify
   if (mhz.getCO2() > 2000)
  {
    Blynk.notify("CO2 - 1500ppm 초과");
    //Blynk.email("twk10242@gmail.com", "CO2 측정 알림", "경고 - 센서의 CO2 측정값이 1500ppm 초과하였습니다!");
    }

    if (DHT11.humidity > 80)
  {
    Blynk.notify("습도 - 80% 초과");
    //Blynk.email("twk10242@gmail.com", "습도 측정 알림", "주의 - 센서의 습도(%) 측정값이 80%를 초과하였습니다!");
    }

     if (DHT11.temperature > 28)
  {
    Blynk.notify("온도 - 30C 초과");
    //Blynk.email("twk10242@gmail.com", "온도 측정 알림", "주의 - 센서의 온도(C) 측정값이 30C를 초과하였습니다!");
    }
  
  lcd.clear();
  lcd.print("CO2:");
  lcd.setCursor(5,0);
  lcd.print(mhz.getCO2());
  lcd.setCursor(9,0);
  lcd.print("ppm");
  
  lcd.setCursor(0,1);
  lcd.print("Temp:");
  lcd.setCursor(6,1);
  lcd.print((float)DHT11.temperature, 0);
  lcd.setCursor(9,1);
  lcd.print("C");

  lcd.setCursor(13,0);
  lcd.print("Humi:");
  lcd.setCursor(13,1);
  lcd.print((float)DHT11.humidity, 0);

  Blynk.virtualWrite(V0, mhz.getCO2());
  Blynk.virtualWrite(V1, DHT11.humidity);
  Blynk.virtualWrite(V2, DHT11.temperature);


  if (mhz.getCO2() > 1500)
  {
    digitalWrite(D0, LOW);
    digitalWrite(D4, HIGH);

 // digitalWrite(buzzer, HIGH);
                
  }
  else
  {
    digitalWrite(D0, HIGH);
    digitalWrite(D4, LOW);

   // digitalWrite(buzzer, LOW);
   
  }
  
  delay(15000);
	
}
