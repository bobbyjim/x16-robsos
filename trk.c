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
#include <conio.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "ci.h"
#include "trk.h"
#include "common.h"

byte  highAlarmCount, highAlarmIndex;

char* status[8] = {
	"InSv",
	"CBsy",
	"ManB",
	"SysB",
	"ISTb",
	"OffL",
   "",
   ""
};

char* alarmLabel[6] = {
	".",
	" Min",
   " Min",
   " Min",
	" Maj",
	"C.. "
};

char* severity[4] = {
	"",
	"  *   ",
	"  M   ",
	" *C*  "
};

Trunkmem* trkmem;

Trunk* trk_findByClli(char* clli)
{
   int x;

   ci_toUpper(clli);
   setBank(BANK_TRUNKMEM);
   for(x=0; x<TRKMEM_TRUNK_COUNT; ++x)
   {
      // only match the first six characters
      if (!strncmp(TRKMEM_TRUNK_DATA(x)->clli, clli, 6))
         return TRKMEM_TRUNK_DATA(x);
   }
   return 0;
}

char* trk_getStatusLabel( byte trunk )
{
   return status[ TRKMEM_TRUNK_STATE(trunk) ];
}

byte trk_getStatus( byte trunk )
{
   return TRKMEM_TRUNK_STATE(trunk);
}

void trk_initTrunks()
{
   trkmem = (Trunkmem*)(0xa000); // mind the bank when you actually read this.
}

void trk_print(Trunk* trunk)
{
   setBank(BANK_TRUNKMEM);

   cprintf("%12s  lin %d sel %d   sgp %2d ckt   %d st %d dtc %d",
         trunk->clli,
         //trunk->ttype,      // typ %d
         //trunk->direction,  // dir %d
         trunk->line,
         trunk->select,
         trunk->sgroup,
         trunk->ckt,
         trunk->state,
         trunk->dtc //,
         //trunk->memvar1,   // %d
         //trunk->memvar2,   // %d
         //trunk->memvar3    // %d
   );
}

byte trk_getTrunkAlarmCount()
{
   byte x;
   byte alarms[8] = { 0,0,0,0,0,0,0,0 };

   for(x=0; x<TRKMEM_TRUNK_COUNT; ++x)
   {
      ++alarms[TRKMEM_TRUNK_STATE(x)];
   }

   highAlarmCount = 0;
   highAlarmIndex = 0;

   for(x=1; x<5; ++x)
   {
      //cprintf("index %d: count = %u | high alarm index = %u, count = %u\r\n", x, alarms[x], highAlarmIndex, highAlarmCount);
      if(alarms[x]>0)
      {
         highAlarmCount=alarms[x];
         highAlarmIndex=x;
      }
   }
   return highAlarmCount;
}

char* trk_getTrunkAlarmType()
{
   return alarmLabel[ highAlarmIndex ];
}

char* trk_getTrunkSeverity()
{
   byte x;
   byte val = 0;
   for(x=0; x<TRKMEM_TRUNK_COUNT; ++x)
   {
      val = TRKMEM_TRUNK_DATA(x)->severity > val? TRKMEM_TRUNK_DATA(x)->severity : val;
   }
   return severity[val];
}

