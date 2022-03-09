/*

    MAPCI
    Copyright (C) 2021 Robert Eaglestone

    This file is part of Traveller-Trader.
        
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
#include <cbm.h>
#include <peekpoke.h>

#include "common.h"

#define LOGICAL_FILE_NUM        1
#define IGNORE_LFN              0
#define SD_CARD                 8
#define EMULATOR_FILE_SYSTEM    8
#define HOST_FILE_SYSTEM        1
#define SA_IGNORE_HEADER        0
#define LOAD_FLAG               0

void setBank(byte bank)
{
   POKE(0x9f61, bank);
   POKE(0x0000, bank);
}

void hr(byte color)
{
   int x=81;
   cbm_k_bsout(color);
   while(--x)
   {
      cbm_k_bsout(HORIZ_BAR);
   }
   cbm_k_bsout(0x0d);
   toDefaultColor();
}

void toDefaultColor()
{
   cbm_k_bsout(GREEN); 
}

void loadFile(char* name, byte bankNum)
{  
   cbm_k_setnam(name);
   cbm_k_setlfs(IGNORE_LFN,EMULATOR_FILE_SYSTEM,SA_IGNORE_HEADER);
   setBank(bankNum);
   cbm_k_load(LOAD_FLAG, 0xa000);
}

void loadFileAtB800(char* name, byte bankNum)
{
   cbm_k_setnam(name);
   cbm_k_setlfs(IGNORE_LFN,EMULATOR_FILE_SYSTEM,SA_IGNORE_HEADER);
   setBank(bankNum);
   cbm_k_load(LOAD_FLAG, 0xb800);
}

void down(byte count)
{
   for(;count>0;--count) cbm_k_bsout(17);
}

void left(byte count)
{
   for(;count>0;--count) cbm_k_bsout(157);
}

char pressReturnAndClear()
{
   char c;

   cputsxy(3,58,"press <return> to continue");
   c = cgetc();
   clrscr();
   return c;
}

