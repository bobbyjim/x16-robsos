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
#ifndef _trunk_h_
#define _trunk_h_

#include "common.h"

#define     TRUNK_RECORD_SIZE    32

//
// string data in the header
//
#define     TRKSTR_STATUS(x)        ((char*) (0xa000 + x * 5))
#define     TRKSTR_TYPE(x)          ((char*) (0xa028 + x * 4))
#define     TRKSTR_DIR(x)           ((char*) (0xa048 + x * 3))
#define     TRKSTR_LINE(x)          ((char*) (0xa054 + x * 3))
#define     TRKSTR_SELECT(x)        ((char*) (0xa05a + x * 3))
#define     TRKSTR_CARD(x)          ((char*) (0xa066 + x * 4))

#define     TRKMEM_TRUNK_DATA(x)    ((Trunk*) (0xa07a + x * TRUNK_RECORD_SIZE))
#define     TRKMEM_TRUNK_STATE(x)   (TRKMEM_TRUNK_DATA(x)->state)

#define     TRKMEM_TRUNK_COUNT   64

#define     TRUNK_STATE_INSV     0
#define     TRUNK_STATE_CBSY     1
#define     TRUNK_STATE_MANB     2
#define     TRUNK_STATE_SYSB     3
#define     TRUNK_STATE_ISTB     4
#define     TRUNK_STATE_OFFL     5
#define     TRUNK_STATE_FUBAR    6
#define     TRUNK_STATE_HCF      7

typedef struct {
   byte searchUID;
   char clli[13];       // include the null byte to align the structure

   // CLLI components
   int ttype:      3; // low bits
   int direction:  2;
   int line:       1;
   int select:     2;

   // TRKMEM components
   int sgroup:     5; // low bits
   int ckt:        3;

   int state:      3; // low bits
   int dtc:        3;
   int memvar1:    2;

   int memvar2:    4; // low bits
   int memvar3:    4;

   int alarm:      4; // low bits
   int severity:   4;
} Trunk;

void  trk_initTrunks();
byte  trk_getTrunkAlarmCount();
char* trk_getTrunkAlarmType();
char* trk_getTrunkSeverity();
char* trk_getStatusLabel( byte trunk );
byte  trk_getStatus( byte trunk );
void trk_print(Trunk* trunk);

#endif
