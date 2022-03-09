
#include <stdio.h>

#include "diskut.h"
#include "ci.h"
#include "volumes.h"

#define     ELSIF       else if

extern char ciInputBuffer[80];
extern char ciLowerBuffer[80];
extern int i1, i2;
extern char c1[20], c2[20];

void diskut_run()
{
    if ( 1 == sscanf(ciLowerBuffer, " lv %d", &i1))
    {
        volumes_list();
    }
    ELSIF ( 1 == sscanf(ciLowerBuffer, " lf %s", c1)
         || 1 == sscanf(ciLowerBuffer, " listfl %s", c1))
    {
        volumes_find(c1);
//        printf("\nVolume %s either unavailable for does not exist on node CM.\n", c1);
    }
    ELSIF ( 4 == sscanf(ciLowerBuffer, " sbf %s %s %d %d", c1, c2, &i1, &i2)
         || 4 == sscanf(ciLowerBuffer, " setbootfl %s %s %d %d", c1, c2, &i1, &i2))
    {
        ci_toUpper(c1);
        ci_toUpper(c2);
    }
    ELSIF ( 4 == sscanf(ciLowerBuffer, " cbf %s %s %d %d", c1, c2, &i1, &i2)
         || 4 == sscanf(ciLowerBuffer, " clearbootfl %s %s %d %d", c1, c2, &i1, &i2))
    {
        ci_toUpper(c1);
        ci_toUpper(c2);
    }
}