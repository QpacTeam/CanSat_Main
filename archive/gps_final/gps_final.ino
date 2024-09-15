
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

  while (GPS.available() > 0){

    char a = GPS.read();  //  < takes in one character  <<<

    if (a == '\n') {
      //SAVE SOMEWHERE GGALINE!!!
      for (int i = 0; i <= lineindex; i++){
        ggaline[i] = '';
      }
      lineindex = 0;
      rec = false;
    }

    if (rec){
      ggaline[lineindex] = a;
    }

    if (signindex == 5){
      signindex = 0;
      dollarjel = false;
      Serial.println(sign);
      if (sign[0] == 'G' && sign[1] == 'P' && sign[2] == 'G' && sign[3] == 'G' && sign[4] == 'A') {
        rec = true;
      }
    }

    if (dollarjel){
      sign[signindex] = a;
      signindex++;
    }

    if (a == '$'){
      dollarjel = true;
      Serial.println("dollár");
    }
  }

}
