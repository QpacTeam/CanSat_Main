arduino::String thing;
UART LoRa(4, 5, NC, NC);





void setup() {
  Serial.begin(9600);
  LoRa.begin(9600);
  Serial.setTimeout(1000);
}

void loop() {
  //Serial.println("a");
  if (LoRa.available() > 0) {
    thing = String(LoRa.read());
    Serial.println(thing);
  }
}
