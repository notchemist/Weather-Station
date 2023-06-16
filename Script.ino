#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <SD.h>

#define DHTPIN 2
#define DHTTYPE DHT11
#define LDRPIN A0
#define SD_CHIP_SELECT 10

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 20, 4);

File dataFile;

void setup() {
  Serial.begin(9600);
  lcd.begin(20, 4);
  lcd.backlight();

  if (!SD.begin(SD_CHIP_SELECT)) {
    Serial.println("Impossibile inizializzare la scheda SD. Verifica la connessione!");
    while (1);
  }

  lcd.print("Stazione Meteo");
  lcd.setCursor(0, 1);
  lcd.print("Inizializzazione...");

  delay(2000);
  lcd.clear();

  String fileName = getFileName();
  dataFile = SD.open(fileName, FILE_WRITE);
  if (!dataFile) {
    Serial.println("Errore durante l'apertura del file!");
    while (1);
  }

  lcd.print("File: ");
  lcd.setCursor(0, 1);
  lcd.print(fileName);

  dht.begin();
}

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  int lightLevel = analogRead(LDRPIN);

  String data = "Temp: " + String(temperature) + " C  Humidity: " + String(humidity) + " %  Light Level: " + String(lightLevel);
  lcd.clear();
  lcd.print(data);

  Serial.println(data);
  dataFile.println(data);
  dataFile.flush();

  delay(300000);  // 5 minuti
}

String getFileName() {
  String fileName;
  char timestamp[15];
  sprintf(timestamp, "%04d%02d%02d.txt", year(), month(), day());
  fileName = String(timestamp);
  return fileName;
}
