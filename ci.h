/*
    ROBSOS

    Copyright (C) 2022 Robert Eaglestone

    This file is part of ROBSOS

    ROBSOS is free software: you can redistribute it and/or modify
    it under the terms of the MIT License.

    ROBSOS is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    MIT License for more details.

    You should have received a copy of the MIT License along with ROBSOS.  
    If not, see <https://mit-license.org/>.
*/
#ifndef _CI_H_
#define _CI_H_

#include "common.h"

#define     EQ(s1,s2)       (!strcmp(s1,s2))
#define     ELIFEQ(s1,s2)   else if (!strcmp(s1,s2))

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
void ci_setState(byte st);

char* ci_inputToLower(char* in, char* out);
char* ci_inputToUpper(char* in, char* out);
char* ci_toUpper(char* s);
char* ci_toLower(char* s);

int   ci_confirm(char* msg);

#endif