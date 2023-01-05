#include <time.h>
#include <stdio.h>

#define PT(X) printf("%s : %d\n", #X, now_tm.X);



int main(){
  time_t now;
  time(&now);
  struct tm now_tm = *localtime(&now);
  printf("\n\n%s\n", ctime(&now));
  PT(tm_isdst); //0 not transitional year
  PT(tm_yday);  //from 0
  PT(tm_wday);  //from 1   1-monday
  PT(tm_year);  //123
  PT(tm_mon);   //from 0
  PT(tm_mday);  //from 1  like in callendar
  PT(tm_hour);  //from 0  like on a clock
  PT(tm_min);   //from 0  like on a clock
  PT(tm_sec);   //from 0  like on a clock

  return 0;
  
}
