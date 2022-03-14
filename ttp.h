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
#ifndef _ttp_h_
#define _ttp_h_

#include "common.h"
#include "ckt.h"


#define     MAIN_DISPLAY_TOP        8
#define     MAIN_DISPLAY_BOTTOM     57


void ttp_run();
int ttp_readLine();

void ttp_writeScreen();
void ttp_post( char* clli );

//void ttp_post_number(int trunknum);
int ttp_bsy();
int ttp_rts();
int ttp_offl();

void ttp_next( Circuit* circuit );
void ttp_first( Circuit* circuit );
void ttp_list_trunks();

#endif
