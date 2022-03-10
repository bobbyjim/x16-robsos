
#include <stdio.h>

#include "diskut.h"
#include "ci.h"
#include "volumes.h"
#include "boot.h"

#define     ELSIF       else if

extern char ciInputBuffer[80];
extern char ciLowerBuffer[80];
extern int i1, i2;
extern char c1[80], c2[20], c3[20];

void diskut_run()
{
    if ( 1 == sscanf(ciLowerBuffer, " lv %d", &i1))
    {
        volumes_list();
    }
    ELSIF ( 1 == sscanf(ciLowerBuffer, " lf %s", c1)
         || 1 == sscanf(ciLowerBuffer, " listfl %s", c1))
    {
        volumes_listfiles(c1);
    }
    ELSIF ( 4 == sscanf(ciLowerBuffer, " sbf %s %s %d %d", c1, c2, &i1, &i2)
         || 4 == sscanf(ciLowerBuffer, " setbootfl %s %s %d %d", c1, c2, &i1, &i2))
    {
        boot_sbf( c1, c2, i1 );
    }
    ELSIF ( 3 == sscanf(ciLowerBuffer, " cbf %s %s %s", c1, c2, c3)
         || 3 == sscanf(ciLowerBuffer, " clearbootfl %s %s %s", c1, c2, c3))
    {
        boot_cbf( c1, c2 );
    }
}
