/*

    MAPCI
    Copyright (C) 2021 Robert Eaglestone

    This file is part of MAPCI

    MAPCI is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    MAPCI is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with MAPCI.  If not, see <https://www.gnu.org/licenses/>.

*/

#include <cbm.h>
#include <peekpoke.h>
#include <conio.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>


#include "common.h"
#include "trk.h"
#include "ckt.h"
#include "ttp.h"
#include "ci.h"
#include "volumes.h"


#define  PROMPT               cprintf("\r%u %c", _heapmemavail(), '>')

void init()
{
   trk_initTrunks(); 
}

void main() 
{
   bgcolor(COLOR_BLACK);
   textcolor(COLOR_GRAY3);
   clrscr();

   loadFile("trkmem.bin", 1);
   loadFile("volumes.bin", 2);
  
   cbm_k_setnam("pet-case.bin");
   cbm_k_setlfs(0,8,0);
   cbm_k_load(2, 0x0f800);

   init();
   login();

   for(;;)
   {
      ci_run();
      ci_readLine();
   }
}

