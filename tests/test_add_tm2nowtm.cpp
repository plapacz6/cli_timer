/*author:plapacz6@gmail.com, data:2023-01-03, licence: GPLv3*/
#include <catch2/catch_all.hpp>
#include "../add_tm2nowtm.h"
#include <time.h>


TEST_CASE("adding seconds", "[seconds]"){
  struct tm tm0;
  struct tm tm1;
  struct tm tm2;
  time_t now;
  time(&now);
  tm0 = *localtime(&now);  //copy of interenal tm struct

  tm1 = tm0;
  tm2 = tm0;

  // tm1.tm_isdst =
  // tm1.tm_yday = 
  // tm1.tm_wday = 
  // tm1.tm_year = 
  // tm1.tm_mon = 
  // tm1.tm_mday = 
  // tm1.tm_hour = 
  // tm1.tm_min = 
  // tm1.tm_sec = 

  // tm2.tm_isdst = 
  // tm2.tm_yday = 
  // tm2.tm_wday = 
  // tm2.tm_year = 
  // tm2.tm_mon = 
  // tm2.tm_mday = 
  // tm2.tm_hour = 
  // tm2.tm_min = 
  // tm2.tm_sec = 

  // tm3.tm_isdst = tm1.tm_isdst;
  // tm3.tm_yday = tm1.tm_yday;
  // tm3.tm_wday = tm1.tm_wday;
  // tm3.tm_year = tm1.tm_year;
  // tm3.tm_mon = tm1.tm_mon;
  // tm3.tm_mday = tm1.tm_mday;
  // tm3.tm_hour = tm1.tm_hour;
  // tm3.tm_min = tm1.tm_min;
  // tm3.tm_sec = tm1.tm_sec;

  SECTION(""){
    tm1.tm_sec
    REQUIRE();
  };
  
};
TEST_CASE("adding minuntes", "[minuntes]"){

};
TEST_CASE("adding hours", "[hours]"){

};
TEST_CASE("adding days", "[days day_of_week day_of_year]"){

};
TEST_CASE("adding month", "[month]"){

};
TEST_CASE("adding yeasr", "[years dist_year]"){
};



