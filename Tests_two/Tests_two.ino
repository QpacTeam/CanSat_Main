
#define Data_to_Get 4

arduino::String raw = "$GNRMC,143257.00,A,4712.82720,N,01933.15625,E,0.234,,280424,,,A*67$GNVTG,,T,,M,0.234,N,0.434,K,A*3B$GNGGA,143257.00,4712.82720,N,01933.15625,E,1,11,0.98,147.7,M,38.7,M,,*4E$GNGSA,A,3,08,10,27,21,32,23,02,,,,,,1.95,0.98,1.69*13$GNGSA,A,3,67,82,68,66,,,,,,,,,1.95,0.98,1.69*1B$GPGSV,3,1,09,02,27,284,24,08,70,273,19,10,64,061,34,14,05,332,*7D$GPGSV,3,2,09,16,12,198,,21,43,288,28,23,27,051,38,27,61,164,40*77$GPGSV,3,3,09,32,34,126,36*46$GLGSV,3,1,11,66,15,027,29,67,57,070,32,68,45,161,30,69,03,187,*60$GLGSV,3,2,11,73,13,261,,74,20,305,,75,06,355,28,81,04,108,16*6E$GLGSV,3,3,11,82,48,088,38,83,67,357,,84,14,300,*59$GNGLL,4712.82720,N,01933.15625,E,143257.00,A,A*73"; 


arduino::String GPS_Data[5];

void setup() {
  Serial.begin(9600);

}

void Local_Data_Prep() {  // < cut on $ < make 5 different line

  static arduino::String buffer = "";
  unsigned int line = 0; // < NE LEGYEN STATIC
  unsigned int dollar_sign = 0;
  char priv = 'B';

//  TODO GNGGA and GNGSA megoldani


  for (int i =7; i <= (raw.length()); i++) {
    if (raw.charAt(i) == '$') {
      if (priv != raw.charAt(i+5)) {
        priv = raw.charAt(i+5);
        GPS_Data[dollar_sign] = buffer;
        dollar_sign++;
        i += 6;
      }
      buffer = "";
    }
    else buffer += raw[i];
  }
  GPS_Data[4] = buffer;




  for (int i=0; i < 5; i++) {
    Serial.println(GPS_Data[i]);
  }
  Serial.println("");


}

void Data_Process() {

}

void loop() {
  delay(2000);

  Local_Data_Prep();
}
