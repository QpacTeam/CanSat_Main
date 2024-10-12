#include <Arduino.h>
#include "SwTimer.h"
#include "GPS.h"

#define SWTIMER_CH_GPS 2
#define Data ((String)(""))
#define MAX_LEN 150

UART gps(4, 5, NC, NC);

static char buffer[MAX_LEN];
static unsigned int len;
const char* GPS_Data;


void GPS_Init(void) {
  unsigned int i;
  i = MAX_LEN;
  char *dst;
  dst = buffer;
  while (i--) {
    *dst++ = 0;
  }

  len = 0;
  gps.begin(9600);
}

const char* GPS_Run(void) {
  
  unsigned int n;
  char ch;
  if ((n = gps.available()) > 0) {  //   if ((n = gps.available() > 0 ) {
    ch = gps.read();
    switch (ch) {
      case '$':
        {
          len = 0;
          buffer[len] = ch;
          len++;
          if (len == MAX_LEN) {
            len = 0;
          }
          break;
        }
      case '\n':
        {
          buffer[len] = ch;
          len++;
          if (len == MAX_LEN) {
            len = 0;
          }
          if (len > 1) {
            GPS_Data = buffer;
            return GPS_Data;
          }
          break;
        }
      default:
        {
          buffer[len] = ch;
          len++;
          if (len == MAX_LEN) {
            len = 0;
          }
          break;
        }
    }
  }
}

// TODO adatkivitel

#undef SWTIMER_CH_GPS
#undef Data((String)(""))
#undef MAX_LEN 150
