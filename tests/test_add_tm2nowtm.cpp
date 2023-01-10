/*author:plapacz6@gmail.com, data:2023-01-03, licence: GPLv3*/
#include <catch2/catch_all.hpp>
#include "../add_tm2nowtm.h"
#include <time.h>

TEST_CASE("adding amount of time to struct tm <time.h>") {
  struct tm tm0;
  struct tm tm1;
  struct tmA tm2;
  struct tm tm3;

SECTION ("init"){
  
  time_t now;
  time(&now);
  tm0 = *localtime(&now);  //copy of interenal tm struct

  tm1 = tm0;  
  REQUIRE( (tm1.tm_isdst == 1 ||  tm1.tm_isdst == 0) == 1);
  
  //all test (except explicitily set others) have not transitional year
  tm1.tm_year = 1985;
  tm1.tm_isdst = 0;
  
  //amounth of time
  //calcualted
  // tm2.tm_isdst = 0;
  // tm2.tm_yday = 0;
  // tm2.tm_wday = 0;
  //editable
  // tm2.tm_year = 0; //123
  // tm2.tm_mon = 0;
  tm2.tm_day = 0;
  tm2.tm_hour = 0;
  tm2.tm_min = 0;
  tm2.tm_sec = 0;

  SECTION("adding seconds", "[seconds]"){
    

    SECTION("all pozition at last pozistion"){
      //TODO - and adding 1 sec


      SECTION("adding to 0 day of 1984 FOUR YEARS"){
        tm1.tm_sec = 0;
        tm1.tm_min = 0;
        tm1.tm_hour = 0;
        tm1.tm_yday = 0;
        tm1.tm_year = 1984;
        tm1.tm_isdst = 1;
        tm2.tm_day = 1461;

        tm3 = add_tm2tm(tm1, tm2);
        REQUIRE(tm3.tm_sec == 0);
        REQUIRE(tm3.tm_min == 0);      
        REQUIRE(tm3.tm_hour == 0);      
        REQUIRE(tm3.tm_yday == 0);        
        REQUIRE(tm3.tm_year == 1988);      
        REQUIRE(tm3.tm_isdst == 1);      
        REQUIRE(tm3.tm_mday == 1);        
        REQUIRE(tm3.tm_wday == (1 + (0+1461%7)));        
      };       
    }

    SECTION("minute on beginnin"){
      tm1.tm_min = 1;
      
      SECTION("adding zero sec 0"){
        tm1.tm_sec = 0;
        tm2.tm_sec = 0;

        tm3 = add_tm2tm(tm1, tm2);
        REQUIRE(tm3.tm_sec == 0);
        REQUIRE(tm3.tm_min == tm1.tm_min);      
      };        
      SECTION("adding 1 sec do 0"){
        tm1.tm_sec = 0;
        tm2.tm_sec = 1;

        tm3 = add_tm2tm(tm1, tm2);
        REQUIRE(tm3.tm_sec == 1);
        REQUIRE(tm3.tm_min == tm1.tm_min);
      };
      SECTION("adding 1 sec to 59"){
        tm1.tm_sec = 59;
        tm2.tm_sec = 1;

        tm3 = add_tm2tm(tm1, tm2);
        REQUIRE(tm3.tm_sec == 0);
        REQUIRE(tm3.tm_min == tm1.tm_min + 1);      
      };
      SECTION("adding 59 sec to 1"){
        tm1.tm_sec = 1;
        tm2.tm_sec = 59;

        tm3 = add_tm2tm(tm1, tm2);
        REQUIRE(tm3.tm_sec == 0);
        REQUIRE(tm3.tm_min == tm1.tm_min + 1);      
      };
    };  
  };


  SECTION("adding minuntes", "[minuntes]"){

    SECTION("hours on begining"){
      tm1.tm_hour = 1;
      tm1.tm_sec = 0;
      tm2.tm_sec = 0;    

      SECTION("minute 0 + 0"){
        tm1.tm_min = 0;
        tm2.tm_min = 0;

        tm3 = add_tm2tm(tm1, tm2);
        REQUIRE(tm3.tm_min == 0);
        REQUIRE(tm3.tm_hour == tm1.tm_hour);
      };     
      SECTION("minute 0 + one minute"){
        tm1.tm_min = 0;
        tm2.tm_min = 1;

        tm3 = add_tm2tm(tm1, tm2);
        REQUIRE(tm3.tm_min == 1);
        REQUIRE(tm3.tm_hour == tm1.tm_hour);
      };
      SECTION("minute 59 + one minunte"){
        tm1.tm_min = 59;
        tm2.tm_min = 1;

        tm3 = add_tm2tm(tm1, tm2);
        REQUIRE(tm3.tm_min == 0);
        REQUIRE(tm3.tm_hour == tm1.tm_hour + 1);
      };
      SECTION("minute 1 + 59 minuntes"){
        tm1.tm_min = 1;
        tm2.tm_min = 59;

        tm3 = add_tm2tm(tm1, tm2);
        REQUIRE(tm3.tm_min == 0);
        REQUIRE(tm3.tm_hour == tm1.tm_hour + 1);
      };   
    };
  };  


  SECTION("adding hours", "[hours]"){

    SECTION(""){
      tm1.tm_mday = 1;
      tm1.tm_sec = 0;
      tm1.tm_min = 0;
      
      SECTION("hour 0 + 0"){
        tm1.tm_hour = 0;
        tm2.tm_hour = 0;

        tm3 = add_tm2tm(tm1, tm2);
        REQUIRE(tm3.tm_hour == 0);
        REQUIRE(tm3.tm_mday == 1);
      };            
      SECTION("hour 0+ one hour"){
        tm1.tm_hour = 0;
        tm2.tm_hour = 1;

        tm3 = add_tm2tm(tm1, tm2);
        REQUIRE(tm3.tm_hour == 1);
        REQUIRE(tm3.tm_mday == 1);
      };
      SECTION("hour 23 + one hour"){      
        tm1.tm_hour = 23;
        tm2.tm_hour = 1;

        tm3 = add_tm2tm(tm1, tm2);
        REQUIRE(tm3.tm_hour == 0);
        REQUIRE(tm3.tm_mday == 2);
      };
      SECTION("hour 0 + 23 hours"){      
        tm1.tm_hour = 1;
        tm2.tm_hour = 23;

        tm3 = add_tm2tm(tm1, tm2);
        REQUIRE(tm3.tm_hour == 0);
        REQUIRE(tm3.tm_mday == 2);
      };
    };
  };


  SECTION("adding days", "[days day_of_week day_of_year]"){

    SECTION(""){    
      tm1.tm_mon = 0; //January    

      SECTION("first day of month +0 days"){
        tm1.tm_mday = 1;  //
        tm1.tm_yday = 0; 
        tm1.tm_wday = 1;  //monday

        tm2.tm_day = 0;  //we adding 0-days 

        tm3 = add_tm2tm(tm1, tm2);
        REQUIRE(tm3.tm_mday == 1); //w/o change
        REQUIRE(tm3.tm_mon == 0);  //w/o change //January
        REQUIRE(tm3.tm_yday == 0); //w/o change
        REQUIRE(tm3.tm_wday == 1); //w/o change : monday
      };            
      SECTION("day 0 (1-st of month) + one day"){
        tm1.tm_mday = 1;  //first day of month (31-days January)
        tm1.tm_yday = 0;  //first day of yaer    
        tm1.tm_wday = 1;  //first day of week (monday)

        tm2.tm_day = 1;  //we adding one day

        tm3 = add_tm2tm(tm1, tm2);      
        REQUIRE(tm3.tm_mday == 1); 
        REQUIRE(tm3.tm_mon == 0);  //January remain      
        REQUIRE(tm3.tm_yday == 1); 
        REQUIRE(tm3.tm_wday == 2); 
      };
      SECTION("day 31 (of March) + one day"){
        tm1.tm_mon = 2; //March
        tm1.tm_isdst = 0;
        tm1.tm_year = 1985;
        tm1.tm_mday = 31;  //first day of month (31-days January)
        tm1.tm_yday = 0;  //first day of yaer    
        tm1.tm_wday = 1;  //first day of week (monday)

        tm2.tm_day = 1;  //we adding one day

        tm3 = add_tm2tm(tm1, tm2);      
        REQUIRE(tm3.tm_mday == 1); 
        REQUIRE(tm3.tm_mon == 3);  //April
        REQUIRE(tm3.tm_yday == (31+28+31+1)); 
        REQUIRE(tm3.tm_wday == ((tm1.tm_wday - 1) +(31+28+31)%7) +1); 
      };      
      SECTION("day 1 + 31 days"){      
        tm1.tm_mday = 1; //first day of month
        tm1.tm_yday = 0; 
        tm1.tm_wday = 1;  //monday

        tm2.tm_day = 31;  //we adding all day of current month

        tm3 = add_tm2tm(tm1, tm2);
        REQUIRE(tm3.tm_mday == 1); //first day of next month
        REQUIRE(tm3.tm_mon == 1);  //February
        REQUIRE(tm3.tm_yday == 31); //31 of January + 
        REQUIRE(tm3.tm_wday == ((tm1.tm_wday-1) + 31 % 7) + 1); //tuesday - one day after
      };    
      SECTION("january day 31+ one day"){      
        tm1.tm_mday = 31; //last day of month
        tm1.tm_yday = 30; 
        tm1.tm_wday = 1;  //monday

        tm2.tm_day = 1;  //we adding one day

        tm3 = add_tm2tm(tm1, tm2);
        REQUIRE(tm3.tm_mday == 1); //first day of next month
        REQUIRE(tm3.tm_mon == 1);  //February
        REQUIRE(tm3.tm_yday == 31); //31 of January + 
        REQUIRE(tm3.tm_wday == ((tm1.tm_wday-1) + 31 % 7) + 1); //tuesday - one day after
      };    
      SECTION("non-transitional february day 28+ one day"){     
        tm1.tm_mon = 1; //February
        tm1.tm_isdst = 0; //28days

        tm1.tm_year = 1983;
        tm1.tm_mday = 31+28; //last day of month
        tm1.tm_yday = 30+28-1; 
        tm1.tm_wday = 1;  //monday

        tm2.tm_day = 1;  //we adding one day

        tm3 = add_tm2tm(tm1, tm2);
        REQUIRE(tm3.tm_mday == 1); //first day of next month
        REQUIRE(tm3.tm_mon == 2); //march
        REQUIRE(tm3.tm_yday == 0+31+28); 
        REQUIRE(tm3.tm_wday == ((tm1.tm_wday-1) + 28 % 7) + 1); 
        REQUIRE(tm3.tm_isdst == 0); 
      };
      SECTION("transitional february day 28+ one day"){     
        tm1.tm_mon = 1; //February
        tm1.tm_isdst = 1; //29days

        tm1.tm_year = 1984;
        tm1.tm_mday = 31+28; //last day of month
        tm1.tm_yday = 0+31+28-1; 
        tm1.tm_wday = 1;  //monday

        tm2.tm_day = 1;  //we adding one day

        tm3 = add_tm2tm(tm1, tm2);
        REQUIRE(tm3.tm_mday == 29); //first day of next month
        REQUIRE(tm3.tm_mon == 1); //February
        REQUIRE(tm3.tm_yday == 0+31+28); 
        REQUIRE(tm3.tm_wday == ((tm1.tm_wday-1) + 28 % 7) + 1); 
        REQUIRE(tm3.tm_isdst == 1); 
      };    
      SECTION("transitional february day 29+ one day"){     
        tm1.tm_mon = 1; //February
        tm1.tm_isdst = 1; //29days      

        tm1.tm_year = 1984;
        tm1.tm_mday = 29; //last day of month
        tm1.tm_yday = 0+31+29-1; 
        tm1.tm_wday = 1;  //monday

        tm2.tm_day = 1;  //we adding one day

        tm3 = add_tm2tm(tm1, tm2);
        REQUIRE(tm3.tm_mday == 1); //first day of next month
        REQUIRE(tm3.tm_mon == 2);  //March
        REQUIRE(tm3.tm_yday == 0+31+29); 
        REQUIRE(tm3.tm_wday == ((tm1.tm_wday-1) + 29 % 7) + 1); 
        REQUIRE(tm3.tm_isdst == 1); 
      };
      SECTION("march day 30+ one day"){     
        tm1.tm_mon = 2; //March

        tm1.tm_mday = 30; //last day of month
        tm1.tm_yday = 0+31+28+30-1; 
        tm1.tm_wday = 1;  //monday

        tm2.tm_day = 1;  //we adding one day

        tm3 = add_tm2tm(tm1, tm2);
        REQUIRE(tm3.tm_mday == 1); //first day of next month
        REQUIRE(tm3.tm_mon == 3);  //April
        REQUIRE(tm3.tm_yday == 0+31+28+30); //31 of January + 
        REQUIRE(tm3.tm_wday == ((tm1.tm_wday-1) + 30 % 7) + 1); //tuesday - one day after
      };    
    


    };
  };


  SECTION("adding month", "[month]"){

  };


SECTION("adding yeasr", "[years dist_year]"){

};
}//SECTION INIT
}; //TEST CASE

