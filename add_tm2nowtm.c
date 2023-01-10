/*author:plapacz6@gmail.com, data:2023-01-03, licence: GPLv3*/
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>

#include "add_tm2nowtm.h"


struct tm add_tm2tm(const struct tm tm1, const struct tmA tm2){
  int mc_days[2][12] = {
      { 
        31,28,31,30,31,30,
        31,31,30,31,30,31
      },
      { 
        31,29,31,30,31,30,
        31,31,30,31,30,31
      }
    };  
  unsigned long amount_of_days = 0;  
  struct tm tm3 = tm1;


  tm3.tm_sec += tm2.tm_sec;
  
  tm3.tm_min += tm2.tm_min + tm3.tm_sec/60;
  tm3.tm_sec %= 60;

  tm3.tm_hour += tm2.tm_hour + tm3.tm_min/60;
  tm3.tm_min %= 60;

  amount_of_days = tm2.tm_day + tm3.tm_hour/24;
  tm3.tm_mday += tm2.tm_day + tm3.tm_hour/24;  
  tm3.tm_hour %=24;
  
  tm3.tm_yday += amount_of_days;


  /*** calculation of the corresponding year ***/  
  #define FOUR_YEARS ((3*365 + 366))
  tm3.tm_year += tm3.tm_yday / FOUR_YEARS;
  tm3.tm_yday %= FOUR_YEARS;  
  #undef FOUR_YEARS

  
  #define DAYS_OF_CURR_YEAR ( ( (tm3.tm_year - 1984) % 4 ) ? 365 : 366 )
  #define IS_TRANS_YEAR ( ((tm3.tm_year - 1984) % 4) ? 0 : 1 )
  while(tm3.tm_yday > DAYS_OF_CURR_YEAR ) {
    tm3.tm_yday -= DAYS_OF_CURR_YEAR;
    tm3.tm_year++;
    tm3.tm_isdst = IS_TRANS_YEAR; //  tm3.tm_isdst;    
  } 
            assert(tm3.tm_yday < DAYS_OF_CURR_YEAR);            
  #undef DAYS_OF_CURR_YEAR
  #undef IS_TRANS_YEAR


  /*** calculation of the corresponding month, and day in that month ***/
  unsigned long days = tm3.tm_yday;
  int curr_mc_idx = 0; 
            assert(tm3.tm_isdst == 0 || tm3.tm_isdst == 1);  
  while(days > mc_days[tm3.tm_isdst][curr_mc_idx]){
    days -= mc_days[tm3.tm_isdst][curr_mc_idx];    
    curr_mc_idx++;    
            assert(curr_mc_idx <= 12);
  }
  tm3.tm_mon = curr_mc_idx;
  tm3.tm_mday = days + 1;  
  tm3.tm_yday = days;  
  
  
  /*** calculation of the corresponding day of week ***/
  //tm_wday - stating from 1
  tm3.tm_wday = (((tm3.tm_wday - 1) + amount_of_days) % 7) + 1;
  
  return tm3;
}

struct tm add_tm2nowtm(const struct tmA tm2){
  time_t now;
  
  time(&now);  
  struct tm tm1 = *localtime(&now);
  struct tm tm3;

  tm3 = add_tm2tm(tm1, tm2);

  return tm3;
}