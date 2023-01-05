/*author:plapacz6@gmail.com, data:2023-01-02, licence: GPLv3*/
#ifndef CLI_TIMER_H
#define CLI_TIMER_H
/****************************************************/
#include <time.h>
#include <unistd.h>
#include "add_tm2nowtm.h"
#include "fill_in_tm_from_str.h"
extern char *optarg;
extern int optind, optopt;
int show_pause_menu();
/****************************************************/
#endif // CLI_TIMER_H