#include "SwTimer.h"
#include "Buzzer.h"
#include "BMP.h"
#include "GPS.h"
#include "Truster.h"
#include "Card.h"
#include "Check.h"
#include "LoRa.h"
#include "ImU.h"

static int Data_Typ;
static int Main_State = 0;

/*  
    0 = kilövés előtt
    1 = rakétában
    2 = küldetés közben
    3 = Földön
*/

void setup(void) {

  Serial.begin(9600);

  SwTimer_Init(1);

  GPS_Init();
  Buzzer_Init();
  BMP_Init();
  SD_Init();
  Truster_Init();
  ImU_Init();


  Check_Run();  // <- System check


  SwTimer_Set_Continues(0, 100, Main_Measurement); 

}

unsigned long counter = 0;

void loop(void) {

  SwTimer_Run();

  switch (Main_State) {
    case 0:
      {  //kilövés előtt

        break;
      }
    case 1:
      {  //rakétában
        if ()


        break;
      }
    case 2:
      {  //levegőben
        static bool run = true;
        if (run) {


          run = false;
        }



        break;
      }
    case 3:
      {  //földön
        static bool run = true;
        if (run) {
          SwTimer_Set_Continues(1, 100, Buzzer_tick);
          run = false;
        }




        break;
      }
    default: 
      {
      // WHAT THE FUCK
      break;
      }
  }
  counter++;
}

void Main_Measurement() {

  const char* Data_Stream;

  Data_Stream = BMP_Run();
  SD_run(0, Data_Stream);
  LoRa_Run(0, Data_Stream);

  Data_Stream = ImU_Run();
  SD_run(0, Data_Stream);
  LoRa_Run(0, Data_Stream);

}

#undef SWTIMER_CH_BUZZER
