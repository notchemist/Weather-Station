# Weather-Station
This is a weather station Arduino script.
Make sure you have installed the Adafruit_Sensor, DHT, LiquidCrystal_I2C and SD libraries in your Arduino IDE. This script uses a DHT11 sensor to measure temperature and moisture, a photoresistor to detect ambient light, an SD card module to save the data to a text file renamed based on the current day, and a 20x4 LCD screen to display the data, every 5 minutes. The data will also be printed on the serial port.
