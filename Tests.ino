
#define Data_to_Get 4

static arduino::String gec = "$GPSLL,alam,korte,fasz,padlizsan,patkany,shit,zigizik,imi,berci,jociegyfasz*77";
static arduino::String lista[6];

void setup() {
  Serial.begin(9600);
}

void loop() {
/*
  gec.length()

  for (int i =6, <= gec.lenght()-3, i++) {
    if (gec.charAt(i) == ",") {
      coma++;
    }
  }
*/

  static arduino::String buffer = "";
  /* NE LEGYEN STATIC > */ unsigned int elem = 0; /* < NE LEGYEN STATIC */
  unsigned int comma = 0;

  for (int i =1; i <= (gec.length()-4); i++) {
    if (gec.charAt(i)== ',') {
      if (comma == Data_to_Get) {
        lista[elem] = buffer;
        elem++;
        comma++;
        buffer = "";
      }
      else comma++;
    }
    else if (comma == Data_to_Get) buffer += String(gec.charAt(i));
  }
  lista[elem] = buffer;

  Serial.println(lista[0]);
  Serial.println(lista[1]);

}

arduino::String cut() {

}
