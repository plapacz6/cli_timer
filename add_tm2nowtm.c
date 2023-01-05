/*author:plapacz6@gmail.com, data:2023-01-03, licence: GPLv3*/
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>

#include "add_tm2nowtm.h"


struct tm add_tm2tm(const struct tm tm1, const struct tm tm2){
  struct tm tm3 = tm2;

  tm3.tm_sec += tm1.tm_sec;
  
  tm3.tm_min += tm1.tm_min + tm3.tm_sec/60;
  tm3.tm_sec %= 60;

  tm3.tm_hour += tm1.tm_hour + tm3.tm_min/60;
  tm3.tm_min %= 60;

  tm3.tm_mday += tm1.tm_mday;

  tm3.tm_wday += tm1.tm_mday;
  while(tm3.tm_wday < 7){
    tm3.tm_wday -= 7;
  }

  tm3.tm_yday += tm1.tm_mday;
  if(tm3.tm_yday > (tm3.tm_isdst ? 366 : 365)){
    tm3.tm_yday -= (tm3.tm_isdst ? 366 : 365);
  }
  switch(tm3.tm_mon){
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
      if(tm3.tm_mday > 31){
        tm3.tm_mon++;
        tm3.tm_mday -= 31;
      }
      break;
    case 4:
    case 6:
    case 9:
    case 11:
      if(tm3.tm_mday > 30){
        tm3.tm_mon++;
        tm3.tm_mday -= 30;
      }    
      break;
    case 2:
      if(tm3.tm_mday >  (tm3.tm_isdst ? 29 : 28)){
        tm3.tm_mon++;
        tm3.tm_mday -=  (tm3.tm_isdst ? 29 : 28);
      }    
      break;
  }

  tm3.tm_mon += tm1.tm_mon;
  if(tm3.tm_mon > 12){
    tm3.tm_year++;
    tm3.tm_mon -= 12;
    
  }
    
  tm3.tm_isdst %= 1984; //  tm1.tm_isdst;
  
  //tm3.tm_year = tm1.tm_year;

  return tm3;
}

struct tm add_tm2nowtm(const struct tm tm1){
  time_t now;
  
  time(&now);  
  struct tm tm2 = *localtime(&now);
  struct tm tm3;

  tm3 = add_tm2tm(tm1, tm2);

  return tm3;
}