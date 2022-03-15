use strict;
use warnings;

srand();

#
#
#  Randomly generate a pile of trunks.
#
#
my @state     = qw/iNsV cbSY mANb sYSb istB offl fbAR hAcf/;
my @trunks    = qw/dal dal ean ean  imt  onl  ont  mgp/;
my @direction = qw/2w   og   ic   2w/;
my @line      = qw/dt   dp   /;
my @select    = qw/ls   gs   go   ls/;
my @card      = qw/dtc  dtci gwc  xpm/;

#
#  Create file and print strings (128 bytes)
#
open my $out, '>', 'TRKMEM.BIN';
print $out pack 'xx';
print $out pack 'A4x', $_ for @state;       # 3 bits,  40 bytes
print $out pack 'A3x', $_ for @trunks;      # 3 bits,  32 bytes
print $out pack 'A2x', $_ for @direction;   # 2 bits,  12 bytes
print $out pack 'A2x' , $_ for @line;       # 1 bit,   12 bytes
print $out pack 'A2x', $_ for @select;      # 2 bits,  12 bytes
print $out pack 'A4x', $_ for @card;        # 2 bits,  20 bytes
#                                                 ---------
#                                                 128 bytes

my %prefixByTrunkType = ();
my $prefix = 200;

for my $memvar (0..63) 
{
     #         CLLI            CKT  SGroup   DTC/I  MEMVAR    State
     # DAL220TWDTGS             1    0        DTC   0  1  1   CBsy

   my $ttyp = int($memvar/8); # rand(@trunks));      # 3 bits
   my $tdir = int(rand(@direction));   # 2 bits 
   my $tlin = int(rand(@line));        # 1 bit 
   my $tsel = int(rand(@select));      # 2 bits 
   #my $prefix = sprintf( "%d%d%d", int(rand(9)+1), int(rand(10)), int(rand(10)));
   $prefix += 10 if $prefixByTrunkType{ $ttyp }->{ $prefix };

   $prefixByTrunkType{ $ttyp }->{ $prefix } = 1;

   my $shortclli = $trunks[ $ttyp ]
                 . $prefix;

   my $clli = $shortclli
            . $direction[ $tdir ]
            . $line[ $tlin ]
            . $select[ $tsel ];

   $clli =~ s/2w/tw/;

   my $ckt    = 1+int(rand(2));        # 3 bits?
   my $sgroup = int(rand(24)+1);       # 5 bits

   my $stateindex = int(rand(@state)); # 3 bits
   my $dtc    = int(rand(3));          # 3 bits
   my $memvar1 = int(rand(2));	      # 2 bits

   my $memvar2 = int($memvar /16);     # 4 bits
   my $memvar3 = ($memvar % 16);       # 4 bits

   my $state = $state[ $stateindex ]; 


   printf("%12s  typ %d dir %d lin %d sel %d   sgp %2d ckt   %d st %d dtc %d mv %d   %2d %d\n",
         $clli,
         $ttyp,
         $tdir,
         $tlin,
         $tsel,
         $sgroup,
         $ckt,
         $stateindex,
         $dtc,
         $memvar1,
         $memvar2,
         $memvar3
   );

   my $searchUID = $ttyp + $tdir * 8 + $tlin * 32 + $tsel * 64;

   print $out pack 'C',    $searchUID;
   print $out pack 'A12x', $clli;
   print $out pack 'C',    $ttyp + $tdir * 8 + $tlin * 32 + $tsel * 64;
   print $out pack 'C',    $sgroup     + $ckt * 32;
   print $out pack 'C',    $stateindex + $dtc * 8 + $memvar1 * 64;
   print $out pack 'C',    $memvar2    + $memvar3 * 16;
   print $out pack 'C',    0;                                          # alarm + severity
   print $out pack 'x13';                                              # padding to 32b
}
close $out;

# ean (eant) = equal access network trunk
# dal  = direct access line
# ont (onat) = off network access trunk
# onl (onal) = off network access line
# imt        = inter-machine trunk

#       CLLI       EXTRKNM SGRP               MEMVAR   STATE ALARM  SEV
#                  (ckt #?)
__DATA__
DAL220TWDTGS             1    0        DTC   0  1  1   CBsy   2GC      
DAL220TWDTGS             2    0        DTC   1  1  1   ISTb   2GC    M 
DAL221TWDTLS             1    0        DTC   0  1  2   OffL   2GC   *C*
DAL221TWDTLS             2    0        DTC   1  1  2   ManB    .     
DAL222TWDTLS             1    0        DTC   0  1  3   SysB    .     
DAL223TWDTLS             1    0        DTC   0  1  4   InSv    .     
DAL224TWDTGS             1    0        DTC   0  3  1   InSv    .     
DAL224TWDTGS             2    0        DTC   1  3  1   InSv    .     
DAL225OGDTGS             1    0       DTCI   0  5  1   InSv    .     
DAL226OGDTGO             1    0       DTCI   0  6  1   InSv    .     
DAL227OGDTLS             1    0       DTCI   0  7  8   InSv    .     
DAL228TWDTLS             1    0        DTC   0  6  1   InSv    .     
DAL229TWDTLS             1    0        DTC   0  6 17   InSv    .     
DAL230TWDPGS             1    0        DTC   0  7  1   InSv    .     
DAL231TWDTLS             1    0        DTC   0  3  2   InSv    .     
DAL231TWDTLS             2    0        DTC   1  3  2   InSv    .     
DAL232TWDPLS             1    0        DTC   1  7  1   InSv    .     
DAL233TWDTGO             1    0        DTC   0  3  7   InSv    .     
DAL234TWDTLS             1    0        DTC   0  4 22   InSv    .     
DAL236TWDTGO             1    0        DTC   0  8  1   InSv    .     
DAL237TWDTLS             1    0        DTC   1  8  1   InSv    .     
DAL238TWDTLS             1    0        DTC   0  8  9   InSv    .     
DAL239TWDTGS             1    0        DTC   0  4  2   InSv    .     
DAL240TWDTLS             1    0        DTC   1  7 15   InSv    .     
DAL241TWDTGO             1    0        DTC   0  3  8   InSv    .     
DAL245TWDTGS             1    0        DTC   1  4  2   InSv    .     
DAL247TWDTLS             1    0        DTC   0  4  7   InSv    .     
DAL248TWDTLS             1    0        DTC   0  5  2   InSv    .     
DAL255TWDTGS             1    0        DTC   1  5  2   InSv    .     
DAL257TWDTLS             1    0        DTC   0  5  8   InSv    .     
DAL258TWDTGS             1    0        DTC   0  6  2   InSv    .     
DAL265TWDTGS             1    0        DTC   1  6  2   InSv    .     
DAL267TWDTLS             1    0        DTC   0  6  3   InSv    .     
DAL268TWDTGS             1    0        DTC   0  7  2   InSv    .     
DAL271TWDTGS             1    0        DTC   0  4 15   InSv    .     
DAL272TWDTLS             1    0        DTC   0  4 16   InSv    .     
DAL273TWDTGS             1    0        DTC   0  4 17   InSv    .     
DAL274TWDTLS             1    0        DTC   0  4 18   InSv    .     
DAL275TWDTGS             1    0        DTC   1  7  2   InSv    .     
DAL276TWDTGS             1    0        DTC   0  4 24   InSv    .     
DAL277TWDTLS             1    0        DTC   1  5 11   InSv    .     
DAL278TWDTGS             1    0        DTC   0  8  2   InSv    .     
DAL279TWDTLS             1    0        DTC   1  8  2   InSv    .     
MG36C7IBN2W              0    0        GWC   1  8  8   InSv    .
EANT670
ONAT
ONAL

