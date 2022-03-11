

#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "restart.h"
#include "ci.h"
#include "pause.h"

extern char ciLowerBuffer[80];
extern char c1[80];

int restart_tmp_int;

void restart_run()
{
    
    if (1 != sscanf(ciLowerBuffer, "restart %s", c1))
    {
        puts("\nSyntax: RESTART RELOAD|COLD|WARM\n");
        return;
    }
    
    if (!ci_confirm("\nThis will result in a CALL PROCESSING OUTAGE\n"))
       return;

    puts("\n>\n");
    pause_long();
    // switch(c1[0])
    // {
    //     case 'r':
    //         puts("\nReloading switch\n");
    //         pause_long();
    //         break;
    //     case 'c':
    //         puts("\nCold booting switch\n");
    //         pause_mid();
    //         break;
    //     case 'w':
    //         puts("\nWarm booting switch\n");
    //         pause_mid();
    //         break;
    // }

    puts("\nDMS Released Connection.\n"
         "\nPress Any Key to Continue...\n");
    
    restart_tmp_int = cgetc();
    exit(0);
}
