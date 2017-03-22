/*Samuel Boakye (skb3bb)
Dining Band- Humiditiy Sensor and Vibrator
Created 2/22/2017
*/
#include "DHT.h"

#define DHTPIN 2     // what digital pin we're connected to

//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

DHT dht(DHTPIN, DHTTYPE);
const int motorPin = 10; //The pin for the motor

void setup() {
  Serial.begin(9600); //Prints out current values 
  Serial.println("DHTxx test!");

  dht.begin();
  pinMode(motorPin, OUTPUT);
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);
 float beats;
  // if ( h > 90 && t > 90) { //Threshold for a hot food.
  if (h > 0 && h <90) {
    digitalWrite(motorPin, HIGH);
    delay(1000);
    digitalWrite(motorPin, LOW);
    delay(2000);
  }
  if (h >= 90 ) {
    digitalWrite(motorPin, HIGH);
    delay(5000);
    digitalWrite(motorPin, LOW);
    delay(10);
    
    Serial.print("Vibrator ON!"); //Prints out vibrator on
    
    //delay(1000-10*h);
  }
  else{
    digitalWrite(motorPin, LOW);
  }
  Serial.print("Humidity: ");
  Serial.print(h); //Humidity Value
  Serial.print(" %\t");
  Serial.print("Temperature: "); 
  Serial.print(t); //Temperature value
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t");
  Serial.print("Heat index: ");
  Serial.print(hic); //Prints heat index value
  Serial.print(" *C ");
  Serial.print(hif);
  Serial.println(" *F");
}
