
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <cx16.h>
#include <time.h>

#include "ttp.h"
#include "trk.h"
#include "pause.h"

char trunk[18];
int  trunknum = -1;

time_t t;
struct tm brokenDownTime;
struct tm *bdt = &brokenDownTime;
clock_t clockTime;


int ttp_readLine(char* lineInputBuffer)
{
   gotoxy(0,58);
   cclear(79);
   time(&t);
   bdt = localtime(&t);
   cprintf("\r Time  %2d:%2d  %c", bdt->tm_hour, bdt->tm_min, '%');

   if (!fgets(lineInputBuffer, sizeof(lineInputBuffer), stdin))
   {
      //printf("\n");
      return 0;
   }
   lineInputBuffer[strlen(lineInputBuffer)-1] = '\0'; // chop newline
   return 1;
}

void ttp_run(char *lineInputBuffer)
{
   ttp_writeScreen(); 

   ttp_post("dal776twdtls"); 

   if(!strcmp(lineInputBuffer, "trunks"))
   {
      ttp_list_trunks();
   }
   else if(sscanf(lineInputBuffer, "post %d", &trunknum) == 1)
   {
      ttp_post_number(trunknum);
   }
   else if(!strcmp(lineInputBuffer, "bsy"))
   {
      ttp_bsy(trunknum);
      ttp_post_number(trunknum);
   }
   else if(!strcmp(lineInputBuffer, "rts"))
   {
      ttp_rts(trunknum);
      ttp_post_number(trunknum);
   }
}

void ttp_writeScreen()
{
   byte alarmCount = trk_getTrunkAlarmCount();

   pause();
   clrscr();
//   cputsxy(0,0,"  CC     CMC     IOD     Net     PM     CCS     Lns     Trks     Ext    APPL");
   pause();
   cputsxy(0,0,"                 IOD             PM     CCS     Lns     Trks     Ext    APPL");

   gotoxy(56,2);
   pause();
   cprintf("%-2u", alarmCount);
   pause();
   cputsxy(58,2, trk_getTrunkAlarmType());
   revers(1);
   pause();
   cputsxy(55,4, trk_getTrunkSeverity());
   revers(0);
}

void ttp_post_number(int trunknum)
{
   Trunk* trunk = TRKMEM_TRUNK_DATA(trunknum);
   RAM_BANK = 1;

   pause();
   cputsxy(13,7, "POST     3   ELQ           BSYQ         DIG                        ");
   revers(1);
   pause();
   cputsxy(13,9,"TTP");
   revers(0);
   pause();
   cputsxy(17,9,     "27-0027                                                        ");
   pause();
   cputsxy(13,11,"CKT TYPE     PM NO          COM LANG     STA   R  DOT TE  RESULT   ");
          //      2W S7 S7 gwc   8      5   mg36c7ibn2w     1 idl                    ");
   gotoxy(13,13);
   pause();
   cprintf("%2s S7 S7 %3s  %2d   %2d  %12s    %1d %3s                    ",
      TRKSTR_DIR( trunk->direction ),
      "GWC",
      trunk->ckt,
      trunk->sgroup,
      trunk->clli,
      trunk->memvar1,
      TRKSTR_STATUS(trunk->state)
   );
   pause();
   cputsxy(13,15,"                                               r                 ");
      
}

void ttp_post(char* clli)
{
   byte row = 9;

   RAM_BANK = 1;

   cputsxy(13,5,"POST     3   ELQ            BSYQ         DIG                       ");
   cputsxy(13,6,"TTP 27-0027                                                        ");
   cputsxy(13,7,"CKT TYPE     PM NO            COM LANG     STA   R   DOT TE  RESULT");
   cputsxy(13,8,"2w s7 s7 gwc   8      5   mg36c7ibn2w     1 idl                    ");
   cputsxy(13,9,"                                                 r                 ");

   gotoxy(13,12);
   cprintf("%s", clli );

   cputsxy(13,16,"POST G mg36c7ibn2w    ");
   cputsxy(13,17,"LAST CKTN = 4         ");
   cputsxy(13,18,"SHORT CLLI IS: mg36c7 ");
   cputsxy(13,19,"OK,CKT POSTED         ");
}

void ttp_list_trunks()
{
   int x;
   for(x=0; x<TRKMEM_TRUNK_COUNT; ++x)
   {
      gotoxy(3,20+x);
      trk_print(TRKMEM_TRUNK_DATA(x));
   }
}

void ttp_bsy(int trunknum)
{
   TRKMEM_TRUNK_DATA(trunknum)->state = TRUNK_STATE_MANB;
}

void ttp_rts(int trunknum)
{
   TRKMEM_TRUNK_DATA(trunknum)->state = TRUNK_STATE_INSV;
}
