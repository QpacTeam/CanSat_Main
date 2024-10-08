/*#define pRes0 7
#define pRes1 6
#define pRes2
#define pRes3 
*/
int val;


void setup() {

  Serial.begin(9600);
  delay(1000);
  //pinMode(21, INPUT);
  /*
  pinMode(pRes1, INPUT);
  pinMode(pRes2, INPUT);
  pinMode(pRes3, INPUT);*/
}

void loop() {
  //val = analogRead(21);
  Serial.println(val);
  delay(2); 
}
