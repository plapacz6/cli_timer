/*author:plapacz6@gmail.com, data:2023-01-03, licence: GPLv3*/
#ifndef FILL_IN_TM_FROM_STR
#define FILL_IN_TM_FROM_STR
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif


struct tm fill_in_tm(const char *str_time);
extern int fillintm_error;


#ifdef __cplusplus
}
#endif

#endif // FILL_IN_TM_FROM_STR