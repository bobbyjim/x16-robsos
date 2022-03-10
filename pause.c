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
   // pause_jiffies( rand() % 25 );
}

void pause_long()
{
   // pause_jiffies( rand() % 250 );
}