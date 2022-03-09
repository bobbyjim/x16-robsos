#include <conio.h>

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

char* alarmLabel[4] = {
	".",
	" Min",
	" Maj",
	"C.."
};

char* severity[4] = {
	"",
	"  *   ",
	"  M   ",
	" *C*  "
};

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
}

void trk_print(Trunk* trunk)
{
   cprintf("%12s  typ %d dir %d lin %d sel %d   sgp %2d ckt   %d st %d dtc %d mv %d   %2d %d",
         trunk->clli,
         trunk->ttype,
         trunk->direction,
         trunk->line,
         trunk->select,
         trunk->sgroup,
         trunk->ckt,
         trunk->state,
         trunk->dtc,
         trunk->memvar1,
         trunk->memvar2,
         trunk->memvar3
   );
}

byte trk_getTrunkAlarmCount()
{
   byte x;
   byte alarms[4];

   for(x=0; x<TRKMEM_TRUNK_COUNT; ++x)
   {
      ++alarms[TRKMEM_TRUNK_STATE(x)];
   }

   highAlarmCount = 0;
   highAlarmIndex = 0;

   for(x=0; x<4; ++x)
   {
      if(alarms[x]>0)
      {
         highAlarmCount=alarms[x];
         highAlarmIndex=x;
      }
   }
   //cprintf(" high alarm = %u, count = %u \r\n", highAlarmIndex, highAlarmCount);
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

