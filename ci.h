#ifndef _CI_H_
#define _CI_H_

#include "common.h"

#define  STATE_CI             0
#define  STATE_DISKUT         1
#define  STATE_LOGUTIL        2
#define  STATE_TRAVER         3
#define  STATE_RESTART        4
#define  STATE_MAPCI          5
#define  STATE_MTC            6
#define  STATE_TRK            7
#define  STATE_TTP            8

void ci_login();
void ci_run();
void ci_prompt();
int  ci_readLine();

char* ci_inputToLower(char* in, char* out);
char* ci_inputToUpper(char* in, char* out);
char* ci_toUpper(char* s);
char* ci_toLower(char* s);

int   ci_confirm(char* msg);

#endif