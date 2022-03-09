
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "ci.h"
#include "pause.h"
#include "common.h"
#include "diskut.h"

#define     EQ(s1,s2)       (!strcmp(s1,s2))

byte cycle = 1;
byte state = STATE_CI;
char* entry_message[] = {
    "",
    "Disk utility is now active.",
    "Current MODE setting is: EXTENDED\n",
    "",
    "",
    ""
};

char* prompt[] = {
    "CI",
    "DISKUT",
    "LOGUTIL",
    "MAPCI",
    "MTC",
    "TTP"
};

byte quitState[] = {
    STATE_CI,
    STATE_CI,
    STATE_CI,
    STATE_CI,
    STATE_MAPCI,
    STATE_MTC
};

char banner[60] = "*** SSR07BC Intl Sus Supv - NO MODULE REPLACING!!! ***";

char ciInputBuffer[80];
char ciLowerBuffer[80];
int i1, i2;
char c1[20], c2[20];

char* ci_toUpper(char* s)
{
    while(*s) *s = toupper(*s++);
    return s;
}

char* ci_toLower(char* s)
{
    while(*s) *s = tolower(*s++);
    return s;
}

char* ci_inputToLower(char* in, char* out)
{
    while(*in) *out++ = tolower(*in++);
    *out = 0; // end of string
    return out;
}

char* ci_inputToUpper(char* in, char* out)
{
    while(*in) *out++ = toupper(*in++);
    *out = 0; // end of string
    return out;
}

void login()
{
    pause();    
    puts("\nInitializing cmap\n");
    puts("Attemping to connect to '.map-x25.250b.bnrrich-dms'\n");
    pause_long();
    puts("Connected to 'hc1.map-x25.250b.bnrrich-dms'\n");
    puts("  via gateway 47.166.64.77 and link crchh898-0\n");
    puts("  as device T019336\n");

    pause_long();
    puts("\n\nEnter username and password\n");
    puts("OR   log on automatically by pressing RETURN\n");
    i1 = cgetc();
    _randomize();

    printf("Trying cmap%02d\n\n", 1 + rand() % 20);
    pause_long();
    puts("Break key is ^b (Control-b). Type 'help' for assistance\n");
}

int ci_readLine()
{
   if (!fgets(ciInputBuffer, sizeof(ciInputBuffer), stdin))
   {
      return 0;
   }
   ciInputBuffer[strlen(ciInputBuffer)-1] = '\0'; // chop newline
   ci_inputToLower(ciInputBuffer, ciLowerBuffer);
   return 1;    
}

void ci_prompt()
{
    if (cycle)
    {
        printf("\n95/11/03 10:03 %s\n", banner);
        printf("\n%s:\n", prompt[state]);
    }
    printf("\n>");
    cycle = 1 - cycle;
}

void ci_setState(byte st)
{
    state = st;
    cycle = 1; // reset
    if (entry_message[st][0] > 0)
        printf("\n%s\n", entry_message[st]);
}

void ci_run()
{
    switch(state)
    {
        case STATE_DISKUT:
            diskut_run();
            break;
        
        case STATE_LOGUTIL:
            break;
        
        case STATE_MAPCI:
            break;
        
        case STATE_MTC:
            break;

        case STATE_TTP:
            break;

        default:
            break;
    }

//    printf("[%s]\n", ciLowerBuffer);
    if EQ( "quit",    ciLowerBuffer ) ci_setState(quitState[state]);
    if EQ( "diskut",  ciLowerBuffer ) ci_setState(STATE_DISKUT);
    if EQ( "logutil", ciLowerBuffer ) ci_setState(STATE_LOGUTIL);

    ci_prompt();
}