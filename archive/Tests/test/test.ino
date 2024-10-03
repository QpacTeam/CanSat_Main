#include <SPI.h>
#include <SD.h>

UART LoRa(4, 5);
UART GPS(8, 9);
char a = 'abcdefgh';
char b;
char* c;
const int chipSelect = 10;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  LoRa.begin(115200);
  GPS.begin(9600);
  delay(2000);
  Serial.println("start");

  if (!SD.begin(chipSelect)) {
    Serial.println("initialization failed. Things to check:");
  }
  else {
    Serial.println("initialization done.");
  }
}

void loop() {
  if (GPS.available()>0) {
    while (GPS.available()>0) {
      b=GPS.read();
      Serial.print(b);
      c+= b;
      
    }
    File dataFile = SD.open("GPS001.txt", FILE_WRITE);
    if (dataFile) {
        dataFile.print(c);
        dataFile.close();
        c = "";
     }
     else {
       Serial.println("error opening datalog.txt");
     }
  }
  //LoRa.print("radio tx 0123456789 1\r\n");

  delay(10);
}
