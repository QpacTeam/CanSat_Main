#define MAX 6

static arduino::String Raw = "$GNRMC,143257.00,A,4712.82720,N,01933.15625,E,0.234,,280424,,,A*67\n\r$GNVTG,,T,,M,0.234,N,0.434,K,A*3B\n\r$GNGGA,143257.00,4712.82720,N,01933.15625,E,1,11,0.98,147.7,M,38.7,M,,*4E\n\r$GNGSA,A,3,08,21,32,02,,,,,,,,,3.72,2.13";
arduino::String Final[MAX];

static const unsigned long needed[] = {1, 0, 1, 1, 1, 1, 1};

static unsigned long Lenght;
static unsigned long i;
static unsigned long counter = 0;
static unsigned long slot = 0;

static char ch = 'A';
arduino::String buffer = "";

  static unsigned long dTime = 0;     // < Test timer 

void setup() {
  Serial.begin(9600);
  for (i=0; i < MAX; i++) Final[i] = "";

}

void loop() {

  dTime = micros();

  Lenght = Raw.length();
  counter = 0;
  slot = 0;

  ch = 'A';
  buffer = "";

  for (i=7; i< Lenght; i++) {     // timecomplexity: O(n)
    ch = Raw.charAt(i);
    if (ch == '\n' || ch == '\r') continue;
    if (ch == ',') {

      if (needed[counter] == 1) {

        Final[slot] = buffer;
        Serial.println(buffer);
        slot++;
      
      }

      buffer = "";
      counter++;
      continue;
    }
    if (needed[counter] == 1) buffer = buffer + ch;
    if (slot == MAX-1) break;
  }

  Serial.println();
  Serial.println(micros()-dTime);

  Serial.println();
  Serial.println();



  delay(3000);
}

#undef MAX
