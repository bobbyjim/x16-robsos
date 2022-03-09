/*

    MAPCI
    Copyright (C) 2021 Robert Eaglestone

    This file is part of MAPCI.
        
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

#ifndef _common_h_
#define _common_h_

#define HORIZ_BAR       0xc0
#define VERT_BAR        0xdd

#define TO_BACKGROUND	0x01

#define RVS_ON          18
#define RVS_OFF         146

#define BLACK		    0x90
#define WHITE		    0x05
#define RED             0x1c
#define GREEN           0x1e
#define BLUE            0x1f
#define AMBER           0x81
#define LTRED           0x96
#define LTGREEN         0x99
#define LTBLUE          0x9a
#define YELLOW          0x9e
#define LTGREY		    155
#define PURPLE		    156
#define CYAN		    159

typedef unsigned char byte;
typedef unsigned int  word;

void setBank(byte bank);

void hr(byte color);
void toDefaultColor();
void loadFile(char* name, byte bankNum);
void loadFileAtB800(char* name, byte bankNum);
void down(byte count);
void left(byte count);
char pressReturnAndClear();

#endif
