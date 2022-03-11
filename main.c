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

