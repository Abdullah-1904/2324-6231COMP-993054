#include <DHT.h> // library for DHT sensor

#define DHTPIN 2 // Pin number in arduino  that is connected to my DHt22 data pin
#define DHTTYPE DHT22 // Defining my DHT sensor
DHT dht(DHTPIN, DHTTYPE);

int greenLEDPin = 9; // Green led is for "OK" status
int redLEDPin = 8;   // this Red led is for "!OK" status

void setup() {
  Serial.begin(9600);  
  dht.begin();
  
  pinMode(greenLEDPin, OUTPUT);
  pinMode(redLEDPin, OUTPUT);
}

void loop() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Humidity: "); 
  Serial.print(humidity);
  Serial.print(" %\t");
  Serial.print("Temperature: "); 
  Serial.print(temperature);
  Serial.println(" *C ");

  if (temperature >= 20 && temperature <= 25 && humidity >= 60 && humidity <= 70) {
    digitalWrite(greenLEDPin, HIGH);
    digitalWrite(redLEDPin, LOW);
  } else {
    digitalWrite(greenLEDPin, LOW);
    digitalWrite(redLEDPin, HIGH);
  }

  delay(2000); // Delay for 2 seconds
}
