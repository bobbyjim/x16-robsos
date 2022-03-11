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
