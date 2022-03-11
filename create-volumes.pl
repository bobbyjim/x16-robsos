use strict;
use autodie;

open my $out, '>', 'VOLUMES.BIN';
print $out '..';  # two throwaway bytes.

#
#  One RAM bank contains all Volume data.  It is organized like so:
#
#      1K of string header data.
#      Seven volumes of 1K each.
#
#  The String Header Data is here:

print $out pack 'Z77', 'name                 type      total       free total  open  itoc    largest';
print $out pack 'Z80', '                              blocks     blocks files files files  free segment';
print $out pack 'Z79', '------------------------------------------------------------------------------';
print $out pack 'Z30', '(note:  1 block = 512 bytes )';
print $out pack 'Z80', '-------------------------------------------------------------------------------';
print $out pack 'Z80', 'file name                       o r i o o v file   max    num of    file   last';
print $out pack 'Z80', '                                r e t p l l code   rec   records    size modify';
print $out pack 'Z80', '                                g c o e d d        len        in      in   date';
print $out pack 'Z73', '                                    c n                     file  blocks';
print $out pack 'Z80', '-------------------------------------------------------------------------------';
print $out pack 'x285';  # rest of 1k

#  Each Volume is 1K in size, and consists of one HEADER, and thirty-one ENTRIES.
#
#     The HEADER is a 32-byte structure.
#     Next comes 31 ENTRIES, each in a 32 byte structure.

$/ = /\n\n/;  # split on empty line
my @volume = <DATA>;

foreach (@volume)
{
    s/\n$//; # final newline
    my ($volume, @entry) = split /\n/;
    my ($name, $type, $totalBlocks, $freeBlocks, $totalFiles, $openFiles, $itocFiles, $largestFreeSegment) 
       = split /\s+/, $volume;

    # print volume header
    print $out pack 'Z16', $name;
    print $out pack 'Z4',  $type;
    print $out pack 'C',   (($totalBlocks - 614239)/100) >> 8;
    print $out pack 'V',   $freeBlocks;
    print $out pack 'V',   $largestFreeSegment;
    print $out pack 'C',   $totalFiles;
    print $out pack 'C',   $itocFiles;
    print $out '-';   # spare byte

    # print files
    foreach (@entry[0..30])
    {
        s/\n$//; # final newline
        my ($filename, $flags, $zero, $maxRecordLength, $numOfRecordsInFile, $fileSizeInBlocks, $lastModifyDate)
           = split /\s+/;
        my ($org, $rec, $itoc) = split /\./, $flags;

        # print "filename: $filename\n";
        # print "- flags: $flags\n";
        # print "- max record length: $maxRecordLength\n";
        # print "- num of records in file: $numOfRecordsInFile\n";
        # print "- file size in blocks: $fileSizeInBlocks\n";
        # print "- last modified: $lastModifyDate\n\n";

        $org = 0 unless $org;
        $org = 1 if $filename =~ /_CM$/; # $org eq 'I' 
        $org = 2 if $filename =~ /_MS$/;
        $org = 3 if $org eq 'O';

        $filename =~ s/\x5f/\xa4/g; # underscore to PETSCII underscore
        $filename =~ s/\s*$//;      # trim
        #$filename = lc $filename;

        $rec = 0 unless $rec;
        $rec = 4 if $rec eq 'F';
        $rec = 8 if $rec eq 'V';

        $itoc = 0 unless $itoc;
        $itoc = 16 if $itoc eq 'Y';

        $flags = $org + $rec + $itoc;

        if ($maxRecordLength > 0)
        {
           $maxRecordLength += 4;
           $maxRecordLength = int($maxRecordLength/64);
#           print "max record length: $maxRecordLength\n";
        }

        my $bootnum = $itoc? 1 : 0;

        $lastModifyDate    -= 930000 if $filename;
        #print STDERR "last modified date: $lastModifyDate\n";

        $numOfRecordsInFile = int($numOfRecordsInFile/2);

        print $out pack 'Z25', $filename;
        print $out pack 'v',   $lastModifyDate;
        print $out pack 'v',   $numOfRecordsInFile; # 2 bytes!
        print $out pack 'C',   $flags;
        print $out pack 'C',   $bootnum;
        print $out pack 'C',   $maxRecordLength;
    }
}

close $out;

__DATA__
S00DIMAGE             STD    1433439     599839    10     0     6     252850
PURE_SS7_DTC0_MS                I.F            0  1020      6697   13394 951128
PURE_SS7_DTC0_CM                I.F            0  1020     65556  131112 951128
IDDD_GWY02_300_CM               I.F.Y          0  1020     58210  116420 960126
300_250B_NEW_MS                 I.F.Y          0  1020      6762   13524 951205
SSR06_ALL_MS                    I.F.Y          0  1020      6697   13394 951115
300_250B_NEW_CM                 I.F            0  1020     60095  120190 951205
FF_M06_012496_MS                I.F            0  1020      6762   13524 960124
SSR06BC_CM                      I.F.Y          0  1020     65686  131372 950704
FF_M06_012496_CM                I.F            0  1020     66141  132282 960124
SSR07BC_CM                      I.F            0  1020     67432  134864 951015

S00DPMLOAD            STD     614239     578713    19     0     0     558676
XPM04160                        O.F            0  2044       585    1170 930706
DTCI0673075K                    O.F            0  8188       631    1262 950407
DTC565FKK                       O.F            0  4092       512    1024 930319
SPMHJD                          O.F            0  1020      1238    2476 990105
DTC6224ZOL                      O.F            0  1020      1227    2454 930616
SPM03061KZ                      O.F            0   508      1244    2488 980922
DTC64662556XBQ                  O.F            0  8188      1001    2002 970118
DTCI4517317I                    O.F            0  4092      1364    2728 971024
DTC401869316                    O.F            0  2044       926    1852 970812
DTCI459501R                     O.F            0   508       795    1590 930610
XPM516436032AX                  O.F            0   252       698    1396 940122
XPM013044X                      O.F            0   252       843    1686 940801
ZPMZI                           O.F            0  1020      1027    2054 930301
ZPM922017                       O.F            0   252      1217    2434 930330
SPM57099528J                    O.F            0  2044       663    1326 990410
DTC36196691VBD                  O.F            0  1020       994    1988 970921
XPM822175687A                   O.F            0   252      1332    2664 931116
DTC40199LP                      O.F            0    64       844    1688 930522
DTCI463571806X                  O.F            0  4092       622    1244 950811

S01DIMAGE             STD    1433439     761074    10     0     6     252850
300_250B_MS                     I.F.Y          0  1020      6762   13524 960125
FF_LISTAB_MS                    I.F.Y          0  1020      6697   13394 960125
GWY02AF_CM                      I.F.Y          0  1020     57170  114340 960125
FF_LISTAB_CM                    I.F.Y          0  1020     66271  132542 960125
GWY02AE_CM                      I.F            0  1020     56274  112548 960108
DONT_DELETE_ANY_FF_LOADS        O.V            0     1         1     255 950805
FF_M05_011796_MS                I.F            0  1020      6762   13524 960117
FF_M03_100495_MS                I.F.Y          0  1020      6567   13134 951004
FF_M03_100495_CM                I.F.Y          0  1020     63411  126822 951004
FF_M05_011796_CM                I.F            0  1020     66141  132282 960117

S01DPMLOAD            STD     614239     603921     5     0     0     562901
XPM68253MQ                      O.F            0  1020      1300    2600 960607
DTCI86147WWA                    O.F            0   252       572    1144 930627
SPM231895422J                   O.F            0  4092       663    1326 930614
DTCI41190070T                   O.F            0  1020      1236    2472 990307
DTC41439NFJ                     O.F            0   128      1388    2776 990905

S02DIMAGE             STD    1433439     978327     6     0     1     784631
MCI14AQ_CM                      I.F            0  1020      7412   14824 971010
MCI14AQ_MS                      I.F            0  1020    106082  212164 971010
MCI14AO_250A_MS                 I.F.Y          0  1020      7412   14824 971015
MCI14AO_250A_CM                 I.F            0  1020    105627  211254 971015
DONTERASE08ADDAT                O.V            0   128         0     255 970829
VPNDS                           O.F            0    80     10478    1791 970429

S02DPMLOAD            STD     614239     579637    16     0     0     557794
SPM59                           O.F            0  8188      1457    2914 950226
ZPM4008                         O.F            0  2044      1364    2728 980516
SPM7046                         O.F            0  4092      1276    2552 930329
XPM925KHE                       O.F            0   508       614    1228 980009
ZPM2CPE                         O.F            0  2044      1082    2164 930726
ZPM112158BMX                    O.F            0   128       727    1454 931115
DTCI663Z                        O.F            0  4092       969    1938 931125
DTC59U                          O.F            0    64       824    1648 990606
SPM916BRT                       O.F            0  2044      1226    2452 950423
ZPM541438                       O.F            0  8188       921    1842 931026
XPM998782YR                     O.F            0  4092       896    1792 960729
DTC02390X                       O.F            0   508      1033    2066 930510
SPM4239KS                       O.F            0  2044      1476    2952 931124
DTCI372334                      O.F            0  2044      1476    2952 981025
XPM181                          O.F            0  2044       573    1146 960822
DTC6626LGB                      O.F            0   508      1387    2774 970622
