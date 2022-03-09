#ifndef _CI_H_
#define _CI_H_

#include "common.h"

#define  STATE_CI             0
#define  STATE_DISKUT         1
#define  STATE_LOGUTIL        2
#define  STATE_MAPCI          3
#define  STATE_MTC            4
#define  STATE_TTP            5

void login();
void ci_run();
void ci_prompt();
int  ci_readLine();

char* ci_inputToLower(char* in, char* out);
char* ci_inputToUpper(char* in, char* out);
char* ci_toUpper(char* s);
char* ci_toLower(char* s);

#endif