#define pRes0 A7
#define pRes1 A6
#define pRes2
#define pRes3 

int val;


void setup() {

  Serial.begin(9600);

  pinMode(pRes0, INPUT);
  /*
  pinMode(pRes1, INPUT);
  pinMode(pRes2, INPUT);
  pinMode(pRes3, INPUT);*/
}

void loop() {
  val = analogRead(pRes0);
  Serial.prinln(val);
  delay(2); 
}
