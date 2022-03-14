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

#define     TRUNK_ERROR_NO_TRUNK_POSTED                 -1
#define     TRUNK_ERROR_CANNOT_RTS_AN_OFFLINE_TRUNK     -2

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

/*
print $out pack 'A4x', $_ for @state;       # 3 bits,  40 bytes
print $out pack 'A3x', $_ for @trunks;      # 3 bits,  32 bytes
print $out pack 'A2x', $_ for @direction;   # 2 bits,  12 bytes
print $out pack 'A2x' , $_ for @line;       # 1 bit,   12 bytes
print $out pack 'A2x', $_ for @select;      # 2 bits,  12 bytes
print $out pack 'A4x', $_ for @card;        # 2 bits,  20 bytes
*/
typedef struct {
    //
    //  Strings should take up 128 bytes
    //
    char state[8][5];
    char trunkType[8][4];
    char direction[4][3];
    char line[2][3];
    char select[4][3];
    char card[4][5];

    //
    //  64 trunks at 32 bytes = 2048 bytes
    //
    Trunk trunk[64];
} Trunkmem;


void  trk_initTrunks();
byte  trk_getTrunkAlarmCount();
char* trk_getTrunkAlarmType();
char* trk_getTrunkSeverity();
char* trk_getStatusLabel( byte trunk );
byte  trk_getStatus( byte trunk );
void trk_print(Trunk* trunk);
Trunk* trk_findByClli(char* clli);

#endif
