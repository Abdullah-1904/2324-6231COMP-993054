#include <SPI.h>
#include <SD.h>
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT22 
DHT dht(DHTPIN, DHTTYPE);

File myFile;
int chipSelect = 4;

void setup() {
  Serial.begin(9600);
  dht.begin();

  // Initializing my SD card
  SD.begin(chipSelect);

  // Checking for SD card 
  if (!SD.begin(chipSelect)) {
    Serial.println("SD card initialization failed!");
    return;
  }
  Serial.println("SD card initialized.");
}

void loop() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

    // so you have to close this one before opening another.
  myFile = SD.open("datalog.txt", FILE_WRITE);

  // If the file opened okay, write to it:
  if (myFile) {
    myFile.print("Temperature: ");
    myFile.print(temperature);
    myFile.print(" C, Humidity: ");
    myFile.print(humidity);
    myFile.println(" %");
    
    // Close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("Error opening datalog.txt");
  }

  //  outputing temp and humidity 
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" C, Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  // this will cause a delay of 5 seconds before this loop reruns
  delay(5000);
}