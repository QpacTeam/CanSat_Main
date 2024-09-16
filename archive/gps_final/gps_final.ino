
char sign[5];
bool dollarjel = false;
int signindex = 0;
char ggaline[128];
bool rec = false;
int lineindex = 0;

UART GPS(8, 9);

void setup() {
  Serial.begin(9600);
  GPS.begin(9600);
  delay(1000);

}


void loop() {

}
