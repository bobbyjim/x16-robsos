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
#include <time.h>
#include <stdlib.h>

#include "pause.h"

void pause_jiffies(unsigned jiffies)
{
   clock_t now = clock();
   while(clock() < now + jiffies) {}
}

void pause()
{
   pause_jiffies( rand() % 25 );
}

void pause_long()
{
   pause_jiffies( rand() % 250 );
}

void pause_short()
{
   pause_jiffies( (rand() % 5)  *  (rand() % 5));
}
