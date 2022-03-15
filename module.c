
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "module.h"
#include "ci.h"
#include "pause.h"

char random_letter()
{
    return 193 + rand() % 26;
}

char random_letter_weighted()
{
    return 193 + ((rand() % 5) * (rand() % 5)) + ((rand() % 4) * (rand() % 4));
}
/**********************************************************

    sub : module_print_random()

    desc: prints a module name with phony stats

    in  : name of module

**********************************************************/
void module_print_random(char* modName)
{
    unsigned seed = 0;
    char ec[5];
//    char pAddr[9], sAddr[9];
    int  modRef;
    char sub[7];

    seed = modName[0] + modName[1] + modName[2] 
         + modName[3] + modName[4] + modName[5];

    srand(seed);

    sprintf(ec, "%c%c%02d", random_letter(), random_letter(), rand() % 100);
    modRef = rand() % 10000;

    sprintf(sub,   "%c%c%c%c", 
            random_letter(), 
            random_letter_weighted(),
            random_letter_weighted(),
            random_letter_weighted()
            );

    strcat( sub, ((rand() % 10) > 6)? "SUB" : "COM" );

    printf("\n");
    pause_long();
    printf("%-9s", ci_toUpper(modName));
    printf("ec=%s  ModRef=%d  SWAPPABLE  %s  ORIGINAL\n\n", ec, modRef, sub );
    // print "ec=$ec  ModRef=$ModRef  SWAPPABLE  $sub  ORIGINAL\n";
    printf("         protected:  address=00%04X%04X  size=%04x\n\n", rand(), rand(), rand() % 4096);
    // print "         protected:  address=$pAddr  size=$pSize\n";
      printf("         shared:     address=00%04X%04X  size=%04x\n\n", rand(), rand(), rand() % 4096);
    // print "         shared:     address=$sAddr  size=$sSize\n";
      printf("         entry: %s_I  offset=%04x  RESTART  initialized\n\n", modName, rand() % 4096);
    // print "         entry: ${modName}_I  offset=$offs  RESTART  initialized\n";
    // print "\n";
    printf("\n         NeedsInit: ***\n\n");
}