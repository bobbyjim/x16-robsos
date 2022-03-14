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
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "volumes.h"
#include "ci.h"
#include "pause.h"

VolumeStringHeaders*    stringHeaders;
VolumeEntry*            targetentry;
Volume*                 volume;
int i, j;

char org[]  = { 'O', 'I', 'I', 'O' };
char rec[]  = { ' ', 'F', 'V', ' ' };
char itoc[] = { ' ', 'Y' };
char open[] = { ' ', 'Y' };
char old[]  = { ' ', 'Y' };
char vld[]  = { ' ', 'Y' };

char tmpname[20];
char tmptype[4];

Volume* volumes_find(char *vol)
{
    int chosen = -1;

    setBank(BANK_VOLUMES);
    stringHeaders = ((VolumeStringHeaders*)(0xa000));
    volume = ((Volume*)(0xa400));

    for(i=0; i<7; ++i)
        if (!strcmp(vol, volume[i].hdr.volumeName) )
           chosen = i;

    if (chosen == -1)
       return 0;

    return &(volume[chosen]);
}

VolumeEntry* volumes_findEntry(char *volName, char *bootfile)
{
    volume = volumes_find( volName );
    if (!volume)
    {
        //printf( "Volume %s either unavailable or does not exist on node CM.\n", volName);
        return 0;
    }

    for(j=0; j<volume->hdr.totalFiles; ++j)
    {
        targetentry = &(volume->entry[j]);
        if (!strcmp(targetentry->fileName, bootfile))
           return targetentry;
    }

    //printf( "Volume %s either unavailable or does not exist on node CM.\n", bootfile);
    return 0;
}

int volumes_list()
{
    setBank(BANK_VOLUMES);
    stringHeaders = ((VolumeStringHeaders*)(0xa000));
    volume = ((Volume*)(0xa400));

    pause();
    puts("\nVolumes found on the node CM:\n"
         "\n-----------------------------\n");
    pause();
    printf("\n%s\n", stringHeaders->title1_1);
    pause();
    printf("\n%s\n", stringHeaders->title1_2);
    pause();
    printf("\n%s\n", stringHeaders->title1_3);

    j=0;
    for(i=0; i<7; ++i)
    {           
        unsigned long totalBlocks = (volume[i].hdr.totalBlocks << 8) * 100L + 614239;

        pause();

        if (volume[i].hdr.volumeName[0] == 0)
           break;

        ++j;
        ci_inputToUpper( volume[i].hdr.volumeName, tmpname );
        ci_inputToUpper( volume[i].hdr.volumeType, tmptype );

//              S00DIMAGE             STD    1433439     252850    10     0     6     252850
        printf("\n%-21s %-4s %9lu %10lu %5u %5u %5u %10lu\n", 
            tmpname,
            tmptype,
            totalBlocks,
            volume[i].hdr.freeBlocks,
            volume[i].hdr.totalFiles,
            volume[i].hdr.openFiles,
            volume[i].hdr.itocFiles,
            volume[i].hdr.largestFreeSegment
        );
    }
    printf("\n\nTotal number of volumes found on node CM: %d\n\n", j);
    return j;
}

void volumes_listfiles(char *vol)
{
    VolumeEntry entry;
    int chosen = -1;

    setBank(BANK_VOLUMES);
    stringHeaders = ((VolumeStringHeaders*)(0xa000));
    volume = ((Volume*)(0xa400));

    for(i=0; i<7; ++i)
        if (!strcmp(vol, volume[i].hdr.volumeName) )
           chosen = i;

    ci_toUpper(vol);

    if (chosen == -1)
    {
       printf("\nVolume %s either unavailable or does not exist on node CM.\n", vol);
       return;
    }

    pause();
    printf("\nFile information for volume %s:\n", vol);
    pause();
    printf("\n%s\n", stringHeaders->title2_1);
    pause();
    printf("\n%s\n", stringHeaders->title2_2);
    pause();
    printf("\n%s\n", stringHeaders->title2_3);
    pause();
    printf("\n%s\n", stringHeaders->title2_4);
    pause();
    printf("\n%s\n", stringHeaders->title2_5);
    pause();
    printf("\n%s\n", stringHeaders->title2_6);
    pause();
    printf("\n%s\n", stringHeaders->title2_7);
    pause();
    
    for(j=0; j<volume[chosen].hdr.totalFiles; ++j)
    {
        entry = volume[chosen].entry[j];
        ci_inputToUpper(entry.fileName, tmpname);
 
        pause();
        printf("\n%-31s %c %c %c %c %c %c    0  %4u %9lu %7lu %ld\n",
            tmpname,
            org[ (int)entry.org ],
            rec[ (int)entry.rec ],
            itoc[ (int)entry.itoc ],
            open[ (int)entry.open ],
            old[ (int)entry.old ],
            vld[ (int)entry.vld ],
//                 0,
            entry.maxRecLen * 64 - 4,
            entry.numOfRecordsInFile * 2L,
            entry.numOfRecordsInFile * 4L,
            entry.lastModifyDate + 930000L
        );  
    }
    puts("");
}