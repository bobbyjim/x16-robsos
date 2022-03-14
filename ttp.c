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
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <cx16.h>
#include <time.h>

#include "ci.h"
#include "ttp.h"
#include "trk.h"
#include "pause.h"

char trunk[18];
int  trunknum = -1;

time_t t;
struct tm brokenDownTime;
struct tm *bdt = &brokenDownTime;
clock_t clockTime;

Trunk* tmptrunk;

extern Trunkmem* trkmem; // our trunks and trunk-related constants are here
extern char ciInputBuffer[80];
extern char ciLowerBuffer[80];
extern int i1, i2;
extern char c1[80], c2[20], c3[20];

char postedClli[16];
Trunk* postedTrunk;

void ttp_clear_center()
{
   byte row;
   for(row=MAIN_DISPLAY_TOP; row<MAIN_DISPLAY_BOTTOM; ++row)
   {
      gotoxy(13,row);
      cclear(67);
   }
}

int ttp_readLine(char* prompt)
{
   gotoxy(0,58);
   cclear(79);
   time(&t);
   bdt = localtime(&t);
   cprintf("\r Time  %2d:%2d  %c%s", bdt->tm_hour, bdt->tm_min, '%', prompt);

   if (!fgets(ciInputBuffer, sizeof(ciInputBuffer), stdin))
   {
      //printf("\n");
      return 0;
   }
   ciInputBuffer[strlen(ciInputBuffer)-1] = '\0'; // chop newline
   ci_inputToLower(ciInputBuffer, ciLowerBuffer);
   return 1;
}

void ttp_run()
{
   ci_setState(STATE_TRK);
   ttp_writeScreen(); 
   
   while(ttp_readLine(""))
   {
   //   ttp_post("dal776twdtls"); 
   
      if(!strcmp(ciLowerBuffer, "trunks"))
      {
         ttp_list_trunks();
      }
      else if (1 == sscanf(ciInputBuffer, "post %s", postedClli))
      {
         ttp_post(postedClli);
      }
/*      else if (1 == sscanf(ciLowerBuffer, "post %d", &trunknum))
      {
         ttp_post_number(trunknum);
      }*/
      else if(!strcmp(ciLowerBuffer, "bsy"))
      {
         ttp_bsy();
         ttp_post(postedClli);
      }
      else if(!strcmp(ciLowerBuffer, "rts"))
      {
         ttp_rts();
         ttp_post(postedClli);
      }
      else if(!strcmp(ciLowerBuffer, "offl"))
      {
         ttp_offl();
         ttp_post(postedClli);
      }
   }
}

char* ttp_menu[] = {
   "QUIT",
   "Post_",
   "SEIZE",
   "",
   "BSY",
   "RTS",
   "TST",
   "",
   "CktInfo",
   "CktLoc",
   "Hold",
   "NEXT",
   "RLS",
   "Ckt_",
   "TrnslVf_",
   "StkSdr_",
   "Pads",
   "Level"
};

void ttp_writeScreen()
{
   byte i;
   byte alarmCount = trk_getTrunkAlarmCount();

   pause();
   clrscr();
   pause();

   revers(1);
   gotoxy(0,6);
   cputs("TTP         \r\n            \r\n");
   for(i=0; i<18; ++i)
   {
      cprintf("   %-8s \r\n            \r\n", ttp_menu[i]);
      pause_short();
   }
   revers(0);

// cputsxy(0,0,"   CC     CMC     IOD     Net     PM     CCS     Lns     Trks     Ext    APPL");
   cputsxy(0,0,"                  IOD             PM     CCS     Lns     Trks     Ext    APPL");

   gotoxy(57,2);
   pause();
   cprintf("%-2u", alarmCount);
   pause();
   cputsxy(59,2, trk_getTrunkAlarmType());
   revers(1);
   pause();
   cputsxy(56,4, trk_getTrunkSeverity());
   revers(0);
}

// void ttp_post_number(int trunknum)
// {
//    tmptrunk = TRKMEM_TRUNK_DATA(trunknum);
 
//    ttp_clear_center();

//    pause();
//    cputsxy(13,7, "POST     3   ELQ            BSYQ         DIG                        ");
//    revers(1);
//    pause();
//    cputsxy(13,9,"TTP");
//    revers(0);
//    pause();
//    cputsxy(17,9,     "27-0027                                                        ");
//    pause();
//    cputsxy(13,11,"CKT TYPE     PM NO           COM LANG     STA   R  DOT TE  RESULT  ");
//           //      2W S7 S7 gwc   8      5   mg36c7ibn2w     1 idl                    ");
//    gotoxy(13,13);
//    pause();
//    cprintf("%2s S7 S7 %3s  %2d   %2d  %12s    %1d %3s                    ",
//       TRKSTR_DIR( tmptrunk->direction ),
//       "GWC",
//       tmptrunk->ckt,
//       tmptrunk->sgroup,
//       tmptrunk->clli,
//       tmptrunk->memvar1,
//       TRKSTR_STATUS(tmptrunk->state)
//    );
//    pause();
//    cputsxy(13,15,"                                               r                 ");
      
// }

void slow_rewrite(int x, int y, int len, char* line)
{
   pause_short();
   gotoxy(x,y);
   cclear(len);
   gotoxy(x,y);
   cputsxy(x,y,line);
}

void ttp_post(char* clli)
{
   char* direction;
   char* ttype;
   char* card;
   byte  dtc;
   byte  bstate;
   char* state;
   byte  sgroup;
   byte  ckt;
   char  shortClli[7];

   tmptrunk = trk_findByClli(clli);

//   ttp_clear_center();

   if (!tmptrunk)
   {
      printf("CLLI %s not found.", clli);
      return;
   }

   postedTrunk = tmptrunk; // hang on to this for later.

   direction = trkmem->direction[ tmptrunk->direction ];
   ttype     = trkmem->trunkType[ tmptrunk->ttype ];
   card      = trkmem->card[ tmptrunk->dtc ];
   sgroup    = tmptrunk->sgroup;
   dtc       = tmptrunk->dtc;
   bstate    = tmptrunk->state;
   state     = trkmem->state[ tmptrunk->state ];
   ckt       = tmptrunk->ckt;

   if (bstate == 0) state = "IDL "; // hack

   // short clli is first 6 chars of clli
   strncpy(shortClli, tmptrunk->clli, 6);

   slow_rewrite(13, 8, 67, "POST     3   ELQ            BSYQ         DIG                       ");

   pause();
   revers(1);
   cputsxy(13,10,"TTP");
   revers(0);

   slow_rewrite(16, 10, 64, " 27-0027                                                        ");
   slow_rewrite(13, 12, 67, "CKT TYPE     PM NO           COM LANG     STA   R   DOT TE  RESULT ");
// cputsxy(13,14,"2w s7 s7 gwc   8     5  mg36c7ibn2w     1 idl                      ");

   pause();
   gotoxy(13,14);
   cprintf("%2s %-5s %3s  %2u    %2u  %12s    %u %3s",
      direction,
      ttype,
      card,

      dtc,
      sgroup,

      tmptrunk->clli,

      bstate,
      state
   );

   slow_rewrite(13,16,67,"                                                r                  ");
   slow_rewrite(13,28,67,""); 

   pause();
   gotoxy(13,28);
   cprintf("POST G %s", tmptrunk->clli);

   slow_rewrite(13,30,67,"LAST CKTN = 4         ");

   pause();
   gotoxy(13,32);
   cprintf("SHORT CLLI IS: %s", shortClli);

   slow_rewrite(13,34,67,"OK,CKT POSTED         ");
}

void ttp_list_trunks()
{
   int x;
   int y=0;

   ttp_clear_center();

   for(x=0; x<TRKMEM_TRUNK_COUNT; ++x)
   {
      gotoxy(14,20+y*2);
      cclear(60);
      gotox(14);
      trk_print(TRKMEM_TRUNK_DATA(x));
      ++y;

      if (y > 10)
      {
         y = 0;
         ttp_readLine("Press <RETURN> to continue");
      }
   }
}

int ttp_bsy()
{
   if (postedTrunk)
   {
      postedTrunk->state = TRUNK_STATE_MANB;
      return TRUNK_STATE_MANB;
   }
   return TRUNK_ERROR_NO_TRUNK_POSTED;
}

int ttp_offl()
{
   if (postedTrunk)
   {
      postedTrunk->state = TRUNK_STATE_OFFL;
      return TRUNK_STATE_OFFL;
   }
   return TRUNK_ERROR_NO_TRUNK_POSTED;
}

int ttp_rts()
{
   if (postedTrunk)
   {
      if (postedTrunk->state == TRUNK_STATE_OFFL)
         return TRUNK_ERROR_CANNOT_RTS_AN_OFFLINE_TRUNK;

      postedTrunk->state = TRUNK_STATE_INSV;
      return TRUNK_STATE_INSV;
   }
   return TRUNK_ERROR_NO_TRUNK_POSTED;
}
