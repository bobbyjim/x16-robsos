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

#include <conio.h>

#include "common.h"
#include "trk.h"
#include "ci.h"

void main() 
{
   bgcolor(COLOR_BLACK);
   textcolor(COLOR_GRAY3);
   clrscr();

   common_loadFile("trkmem.bin", 1);
   common_loadFile("volumes.bin", 2);
  
   cbm_k_setnam("pet-case.bin");
   cbm_k_setlfs(0,8,0);
   cbm_k_load(2, 0x0f800);

   trk_initTrunks();
   ci_login();

   for(;;)
   {
      ci_run();
      ci_readLine();
   }
}

