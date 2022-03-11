
#include <stdio.h>
#include <string.h>

#include "boot.h"
#include "volumes.h"
#include "ci.h"

VolumeEntry* entry;
Volume*      vol;

void boot_sbf(char* volName, char* bootfile, int num)
{
   entry = volumes_findEntry(volName, bootfile);

   if (entry)
   {
       num %= 15;
       entry->bootnum = num;
       entry->itoc    = 1;

       printf( "File %s in volume $volume has been registered in the\n\n"
               "Image Table Of Contents for %s\n\n" 
               "as entry number %d.\n\n",
               ci_toUpper(bootfile),
               ci_toUpper(volName),
               num
       );
   }
   else
   {
       printf( "Volume %s either unavailable or does not exist on node CM.\n", bootfile);
   }
}

void boot_cbf(char* volName, char* node)
{
   int i;
   int volumeType = VOLUME_TYPE_CM;

   if (!strcmp("ms", node) || !strcmp("MS", node))
      volumeType = VOLUME_TYPE_MS;

   strcat(volName, "image");
   vol = volumes_find(volName);

   if (vol)
   {
       if (! ci_confirm("\nThe ITOC will be emptied."))
          return;

       for(i=0; i<vol->hdr.totalFiles; ++i)
          if (vol->entry[i].org == volumeType)
             vol->entry[i].itoc = 0;

       printf("The whole Image Table Of Contents for %s\n\n"
              "on %s has been cleared.\n\n",
               ci_toUpper(node),
               ci_toUpper(volName)
        );
   }
   else
   {
       printf( "Volume %s either unavailable or does not exist on node CM.\n", ci_toUpper(volName));
   }
}
