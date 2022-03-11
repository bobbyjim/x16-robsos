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

void ttp_run(char *lineInputBuffer);
int ttp_readLine(char *in);

void ttp_writeScreen();
void ttp_post( char* clli );
void ttp_post_number(int trunknum);
void ttp_bsy(int trunknum);
void ttp_rts(int trunknum);

void ttp_next( Circuit* circuit );
void ttp_first( Circuit* circuit );
void ttp_list_trunks();

#endif
