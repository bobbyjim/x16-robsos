#ifndef _VOLUMES_H_
#define _VOLUMES_H_

#include "common.h"

typedef struct {
        char title1_1[77];
        char title1_2[80];
        char title1_3[79];

        char title2_1[30];
        char title2_2[80];
        char title2_3[80];
        char title2_4[80];
        char title2_5[80];
        char title2_6[73];
        char title2_7[80];

        byte padding1[80];
        byte padding2[80];
        byte padding3[80];
        byte padding4[45];
} VolumeStringHeaders;

typedef struct {
          char volumeName[16];
          char volumeType[4];
          byte totalBlocks;            // <-- shift left 8 bits, multiply by 100, subtract 204961
          unsigned long freeBlocks;         
          unsigned long largestFreeSegment; 

          int totalFiles : 5;
          int padding1   : 3;

          int itocFiles  : 4 ;
          int openFiles  : 4 ;

          byte dash;

} VolumeHeader;

typedef struct {
          char fileName[17];          
          unsigned long lastModifyDate;     
          byte filler1;
          unsigned long numOfRecordsInFile; 
          byte filler2;

          int  org       :2; // 0 = no org.  1 = CM ("I").  2 = MS ("I").  3 = Other ("O")
          int  rec       :2; // "F" "V"
          int  itoc      :1; // empty or "Y"
          int  open      :1; // empty or "Y"
          int  old       :1; // empty or "Y"
          int  vld       :1; // empty or "Y"

          int  bootnum   :4;
          int  filler3   :4;
          
          byte  maxRecLen;
          byte filler4;
          byte filler5;
} VolumeEntry;

typedef struct {
    VolumeHeader hdr;
    VolumeEntry  entry[31];
} Volume;

int volumes_list();
void volumes_listfiles(char *vol);
Volume* volumes_find(char *vol);
VolumeEntry* volumes_findEntry(char *volName, char *bootfile);

#endif
