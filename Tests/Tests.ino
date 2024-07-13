/*
Ez a kód példa arra, hogan lehet adatot szegmenseket kiragadni a GPS adatfolyamból.
  Man:
    > A Data_to_Get array tartalmazza a sorszámokat, hogy melyik elemeket akarjuk kivenni. $GPSLL a 0-ás index, alma az 1-es és így tovább
    > Az elemek megadásánál a Data_to_Get-ben a növekvő sorrend fontos!
    > A program csinálni fog egy processed_Data nevű array-t, ami pontosan akkora amekkorának lennie kell, és sorrendben tartalmazza a kívánt elemeket.
    > A 27-dik sorban valamiért a sizeof() függvény négyszeres értéket ad vissza, nem tudom miért. Egy egyszerű osztással korrigálva van, de ez potenciális problémaforrás!

*/

static const unsigned int Data_to_Get[] = {1, 3, 5, 6};

static arduino::String gec = "$GPSLL,alam,korte,fasz,padlizsan,patkany,shit,zigizik,imi,berci,jociegyfasz*77";


void setup() {

  Serial.begin(9600);
}


void loop() {

  static arduino::String buffer = "";
  unsigned int element = 0;   // NE LEGYEN STATIC
  unsigned int sep = 0;
  unsigned int all_data = (sizeof(Data_to_Get)/4);    // < Ha valami elbaszódik, ezt ellenőrizd először!
  arduino::String proc_Data[all_data];

  for (int i =1; i <= (gec.length()-4); i++) {
    if (gec.charAt(i)== ',') {
      if (sep == Data_to_Get[element]) {
        proc_Data[element] = buffer;
        buffer = "";
        element++;
      }
      sep++;
    }
    else if (sep == Data_to_Get[element]) buffer += String(gec.charAt(i));
  }
  proc_Data[element] = buffer;

  for (int i =0; i < all_data; i++) {
    Serial.println(proc_Data[i]);
  }

  Serial.println("---------------");
  delay(1000);

}
