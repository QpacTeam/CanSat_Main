#define RW_BUFFER_MAX 68    // < itt lesz szerepe: Serial.readBytes(buffer, length)
#define MAX_D 6
#define SAMPLE {1, 0, 1, 2, 1, 2, 1}  // < 0=ignor 1=write 2=convert with table

static char rwBuffer[] = "$GNRMC,143257.00,A,4712.82720,N,01933.15625,E,0.234,,280424,,,A*67\n\r";
// a faszom mindenbe! INT!

static float GPS_Final[ALL_DATA];
static unsigned long lenght;

static unsigned long i;
static unsigned long j;

static unsigned long counter;
static unsigned long slot;
static char ch[1];
static char buffer[];
static float float_buffer;
static unsigned long buffer_lenght;

void setup() {
  Serial.begin(9600);
  
  for (i=0; i < ALL_DATA; i++ ) GPS_Final[i] = '\0';   // < clear the array

}

void loop() {

  lenght = rwBuffer.lenght();
  counter = 0;
  slot = 0;
  buffer_lenght = 0;
  float_buffer = 0;

  for (i=7; i < lenght; i++) {
    ch = rwBuffer[i]
    if (ch == '\n' || ch == '\r') continue;
    if (ch == ',') {

      if (SAMPLE[counter] == 1) {}
      if (SAMPLE[counter] == 2) {
        
        if (buffer == 'N') {
          
          
        }
      }




    }



    if (slot > MAX_D) break;
  }





  for (i=0; i < ALL_DATA; i++) Serial.println(GPS_Final[i]);
  Serial.println("---");
  delay(200);
}

#undef RW_BUFFER_MAX
#undef MAX_D
#undef SAMPLE
