
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
char* state_entry_message[] = {
    "",
    "Disk utility is now active.",
    "Current MODE setting is: EXTENDED\n",
    "traver",
    "restart",
    "mapci",
    "mtc",
    "trk",
    "ttp"
};

char* prompt[] = {
    "CI",
    "DISKUT",
    "LOGUTIL",
    "TRAVER",
    "RESTART",
    "MAPCI",
    "MTC",
    "TRK",
    "TTP"
};

byte quitState[] = {
    STATE_CI,
    STATE_CI,
    STATE_CI,
    STATE_CI,
    STATE_CI,
    STATE_CI,
    STATE_MAPCI,
    STATE_MTC,
    STATE_TRK
};

char* state_help[] = {
    "\n   DISKUT\n"
    "\n   QUIT\n"
    "\n   QUIT ALL\n"
    "\n   SETLOGMSG <message text>\n",

    "\n   CBF|CLEARBOOTFL  <volume>  <CM|MS> ALL\n"
    "\n   LF|LISTFL  <(volume)IMAGE>\n"
    "\n   LV <0|1>\n"
    "\n   SBF|SETBOOTFL <(volume>IMAGE> <bootfile> <NN> 1\n",

    "\n   no help for logutil\n",
    "\n   no help for mapci\n",
    "\n   no help for mtc\n",
    "\n   no help for trk\n",
    "\n   no help for ttp\n"
};

char banner[80] = "*** SSR07BC Intl Sus Supv - NO MODULE REPLACING!!! ***";

char ciInputBuffer[80];
char ciLowerBuffer[80];
int i1, i2;
char c1[80], c2[20], c3[20];

int ci_confirm(char* msg)
{
    puts(msg);
    printf("\nPlease confirm (\"YES\", \"Y\", \"NO\", or \"N\"):\n\n>");
    ci_readLine();

    if (!strcmp(ciLowerBuffer, "y") || !strcmp(ciLowerBuffer, "yes"))
        return 1;

    return 0;
}

char* ci_toUpper(char* s)
{
    char* tmp = s;
    while(*s) *s = toupper(*s++);
    return tmp;
}

char* ci_toLower(char* s)
{
    char* tmp = s;
    while(*s) *s = tolower(*s++);
    return tmp;
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

void ci_login()
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
    if (strlen(state_entry_message[st]) > 0)
        printf("\n%s\n", state_entry_message[st]);
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
    if EQ( "help",    ciLowerBuffer ) puts(state_help[state]);
    if EQ( "quit",    ciLowerBuffer ) ci_setState(quitState[state]);
    if EQ( "quit all",ciLowerBuffer ) ci_setState(STATE_CI);
    if EQ( "diskut",  ciLowerBuffer ) ci_setState(STATE_DISKUT);
//    if EQ( "logutil", ciLowerBuffer ) ci_setState(STATE_LOGUTIL);
//    if EQ( "msg",     ciLowerBuffer ) ci_sendMsg();
//    if EQ( "restart", ciLowerBuffer ) ci_setState(STATE_RESTART);
//    if EQ( "traver",  ciLowerBuffer ) ci_setState(STATE_TRAVER);
    if (1 == sscanf( ciLowerBuffer, "setlogmsg %s", c1))
        strcpy(banner, &ciLowerBuffer[10]);
    // if ((1 == sscanf( ciLowerBuffer, "query %s", c1))
    //  || (1 == sscanf( ciLowerBuffer, "query module %s", c1)))
    //     ci_module_query(c1);

    ci_prompt();
}