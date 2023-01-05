/*author:plapacz6@gmail.com, data:2023-01-03, licence: GPLv3*/
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>

#include "add_tm2nowtm.h"

struct tm add_tm2nowtm(const struct tm tm1){
  struct tm now;
  int change = 0;
  time(&now);

  now.tm_sec += tm1.tm_sec;
  change = 1;
  
  now.tm_min += tm1.tm_min + now.tm_sec/60;
  now.tm_sec %= 60;

  now.tm_hour += tm1.tm_hour + now.tm_min/60;
  now.tm_min %= 60;

  now.tm_mday += tm1.tm_mday;

  now.tm_wday += tm1.tm_mday;
  while(now.tm_wday < 7){
    now.tm_wday -= 7;
  }

  now.tm_yday += tm1.tm_mday;
  if(now.tm_yday > (now.tm_isdst ? 366 : 365)){
    now.tm_yday -= (now.tm_isdst ? 366 : 365);
  }
  switch(now.tm_mon){
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
      if(now.tm_mday > 31){
        now.tm_mon++;
        now.tm_mday -= 31;
      }
      break;
    case 4:
    case 6:
    case 9:
    case 11:
      if(now.tm_mday > 30){
        now.tm_mon++;
        now.tm_mday -= 30;
      }    
      break;
    case 2:
      if(now.tm_mday >  (now.tm_isdst ? 29 : 28)){
        now.tm_mon++;
        now.tm_mday -=  (now.tm_isdst ? 29 : 28);
      }    
      break;
  }

  now.tm_mon += tm1.tm_mon;
  if(now.tm_mon > 12){
    now.tm_year++;
    now.tm_mon -= 12;
    
  }
    
  now.tm_isdst %= 1984; //  tm1.tm_isdst;
  
  //now.tm_year = tm1.tm_year;
  
  return now;
}