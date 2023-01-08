/*author:plapacz6@gmail.com, data:2023-01-02, licence: GPLv3*/
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include "cli_timer.h"
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
    /* 
    timer adds entered time to current time
    then start waiting on the expected moment    
    */
      {
      alarm_tm = fill_in_tm(alarm);
      if(fillintm_error != 0){
        fprintf(stderr, "%s %s\n", "format of time not correct", alarm);
      }
      fprintf(stdout, "%s %s\n", 
        "ttimer has been set on:", asctime(&alarm_tm));
      }
      return 0;      
    case stopper:
    /*
    sleep for a second, and checking if user press stop button
    (command - space key in terminal window)
    then display commands window
      space - continue
      esc - end    
    */
      while(1){
        sleep(1000);
        fflush(stdin);
        char key;
        fread(&key, 1, 1, stdin);
        if(key == ' ')
          if(show_pause_menu() == 1) 
            break;          
        if(key == 27)        
          break;
      }//while
      return 0;
    case alarmer:
    /*
    alarm simply wait for expected moment
    */
     {
      alarm_tm = fill_in_tm(alarm);
      if(fillintm_error != 0){
        fprintf(stderr, "%s %s\n", "format of time not correct", alarm);
      }
      fprintf(stdout, "%s %s\n", 
        "alarm has been set on:", asctime(&alarm_tm));
      } 
      double interval = difftime(mktime(&alarm_tm), time(NULL) ); //???
      fprintf(stdout, "%s %g %s\n", "sleeping for", interval, " miliseconds");
      sleep((time_t)interval);
      fprintf(stdout, "%s\n", "ALARM, ALARM, ALARM !!!");
      return 0;
  }
  
  /* ------------------------------------- */

  return 0;
}

int show_pause_menu(){
  fprintf(stdin, "%s \n",
  "*****************************************************"
  "         space -> pause / contunue"
  "           esc -> stop / end"
  "*****************************************************");
  char key;
  fflush(stdin);
  fread(&key, 1, 1, stdin);
  if(key == ' ') return 1;
  return 0;
}




