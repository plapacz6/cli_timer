#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
/****************************************************/
extern char *optarg;
extern int optind, optopt;
struct tm fill_in_tm(const char *str_time);
extern int fillintm_error;
/****************************************************/
int main(int argc, char **argv){

  char c;
  #define HH_MM_SS (10)  //8+1
  char alarm[HH_MM_SS];
  enum mode_t {
    gettimer = 0,
    ttimer,
    stopper,
    alarmer,    
    COUNT
  } mode = gettimer;
  struct tm alarm_tm;
  time_t alarm_time_t;

  /* ------------------------------------- */

  while( (c = getopt(argc, argv, ":m:sa:h")) != -1){
  
  switch(c){
    case 'm':   //timer  , minutnik
        strncpy(alarm, optarg, HH_MM_SS);  //??  -1
        //alarm[HH_MM_SS - 1] = 0;
        mode = ttimer;
      break;
    case 's':   //stopper
      mode = stopper; 
      break;
    case 'a':   //a   - alarm
        strncpy(alarm, optarg, HH_MM_SS);  //??  -1
        //alarm[HH_MM_SS - 1] = 0;
        mode = alarmer;
      break;
    case 'h':
      printf("%s", 
      "usage:\n"
      "  print_time [-h | -m HH:MM:SS | -a HH:MM:SS | -s]\n"
      "    -h : help\n"
      "    -m : ttimer\n"
      "    -a : alarm\n"
      "    -s : stoper\n"
      "  without - simple print current time\n");
      return 0;
    case ':':   //lack of option
    case '?':   //unknown option
    default:
      assert("error during option parsing" == "");      
  }//switch
  }//while

  /* ------------------------------------- */

  switch(mode){
    case gettimer:
      {
      struct tm* local_time;
      time_t t = time(NULL);
      local_time = localtime(&t);
      printf("%s", asctime(local_time));
      printf("%s", ctime(&t));
      }
      return 0;
    case ttimer: 
      {
      alarm_tm = fill_in_tm(alarm);
      if(fillintm_error != 0){
        fprintf(stderr, "%s %s\n", "format of time not correct", alarm);
      }
      fprintf(stdout, "%s %s\n", 
        "ttimer has been setted on:", asctime(&alarm_tm));
      }
      return 0;      
    case stopper:
      return 0;
    case alarmer:
      return 0;
  }
  
  /* ------------------------------------- */

  return 0;
}


/****************************************************/
int fillintm_error = 0;
struct tm fill_in_tm(const char *str_time) {
  struct tm encoded_time, *ptm;
  time_t t = time(NULL);
  ptm = localtime(&t);
  encoded_time.tm_isdst = ptm->tm_isdst;
  encoded_time.tm_yday = ptm->tm_yday;
  encoded_time.tm_wday = ptm->tm_wday;
  encoded_time.tm_year = ptm->tm_year;
  encoded_time.tm_mon = ptm->tm_mon;
  encoded_time.tm_mday = ptm->tm_mday;
  encoded_time.tm_hour = ptm->tm_hour;
  encoded_time.tm_min = ptm->tm_min;
  encoded_time.tm_sec = ptm->tm_sec;


  /* checking if on each position of str_time is correct symbol */
  
  /*length of str_time must be equal 8 */
  if(strlen(str_time) != 8){
    fillintm_error = -1;
    fprintf(stderr, "%s %s\n", "length of time != 8", str_time);
    goto exit1;
  }
  
  /* checking if at index 2 and 5 is : or - for simlpilcity of use keypad*/
  /*  HH:MM:SS
      01234567  */
  if( 
    (str_time[2] != ':' || str_time[5] != ':')
    &&
    (str_time[2] != '-' || str_time[5] != '-') 
  ){
    fillintm_error = -1;
    fprintf(stderr, "%s %s\n", "wrong seperatos in", str_time);
    goto exit1;
  }
  
  /* if housr are in propoer format */
  if(
      ( /*  12 hours format */
        ( str_time[0] == '0' || str_time[0] == '1') &&
        ( str_time[1] >= '0' && str_time[1] <= '9')
      )
      ||
      ( /*  24 hours format */
        (
          ( str_time[0] >= '0' && str_time[0] <= '1') &&
          ( str_time[1] >= '0' && str_time[1] <= '9')
        )
        ||
        (
          ( str_time[0] == '2'                      ) &&
          ( str_time[1] >= '0' && str_time[1] <= '3')
        )
      )
  )//if
  {
    /*  FILL IN HOURS  */
    int h1 = str_time[0] - 48;
    int h2 = str_time[1] - 48;
    int h = h1 * 12 + h2;
    encoded_time.tm_hour = h;
    //encoded_time.
  }
  else {  /* wrong hours format */
    fillintm_error = -2;
    fprintf(stderr, "%s %s\n", "hours are not correct", str_time);
    goto exit1;
  }


  /*  checking if format of minutes is correct */
  if(      
      (
        ( str_time[3] >= '0' && str_time[3] <= '5') &&
        ( str_time[4] >= '0' && str_time[4] <= '9')
      )
  ){
     /*FILL IN MINUTES */
    int m1 = str_time[3] - 48;
    int m2 = str_time[4] - 48;
    int m = m1 * 10 + m2;
    encoded_time.tm_min = m;
  }
  else {  /* wrong minuntes format */
    fillintm_error = -3;
    fprintf(stderr, "%s %s\n", "minutes are wrong", str_time);
    goto exit1;
  }




  /*  checking if format of seconds is correct */
  if(      
      (
        ( str_time[6] >= '0' && str_time[6] <= '5') &&
        ( str_time[7] >= '0' && str_time[7] <= '9')
      )
  ){
     /*FILL IN SECONDS */
    int s1 = str_time[6] - 48;
    int s2 = str_time[7] - 48;
    int s = s1 * 10 + s2;
    encoded_time.tm_sec = s;
  }
  else {  /* wrong seconds format */
    fillintm_error = -4;
    fprintf(stderr, "%s %s\n", "seconds are not correct", str_time);
    goto exit1;
  }


  exit1:
  return encoded_time;
}
