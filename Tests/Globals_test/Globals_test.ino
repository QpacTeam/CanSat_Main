
#define MAX 4

//"$GNRMC,143257.00,A,4712.82720,N,01933.15625,E,0.234,,280424,,,A*67\n\r$GNVTG,,T,,M,0.234,N,0.434,K,A*3B$GNGGA,143257.00,4712.82720,N,01933.15625,E,1,11,0.98,147.7,M,38.7,M,,*4E$GNGSA,A,3,08,10,27,21,32,23,02,,,,,,1.95,0.98,1.69*13$GNGSA,A,3,67,82,68,66,,,,,,,,,1.95,0.98,1.69*1B$GPGSV,3,1,09,02,27,284,24,08,70,273,19,10,64,061,34,14,05,332,*7D$GNGLL,4712.82720,N,01933.15625,E,143257.00,A,A*73";

static arduino::String Raw = "$GNRMC,143257.00,A,4712.82720,N,01933.15625,E,0.234,,280424,,,A*67\n\r$GNVTG,,T,,M,0.234,N,0.434,K,A*3B\n\r$GNGGA,143257.00,4712.82720,N,01933.15625,E,1,11,0.98,147.7,M,38.7,M,,*4E\n\r";
arduino::String Final[MAX];


void setup() {
  Serial.begin(9600);

}

void loop() {
  unsigned long Lenght = Raw.length();
  char Point = 'A';

  for (int i; i < Lenght; i++) {
    Point = Raw.charAt(i);
    if (Point != '\n' && Point != '\r'){
      Serial.print(Point);
    }
  }
  Serial.println();
  Serial.println(Raw);
  Serial.println();
  Serial.println();
  Serial.println();
  delay(500);
}

#undef MAX
