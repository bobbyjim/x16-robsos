use strict;
use warnings;

$/ = undef;

open my $in, '<:raw', 'CHARGEN.BIN';
my $content = <$in>;
close $in;

my @data = unpack 'C*', $content; # on bytes I hope

print "Bytes read: ", scalar(@data), "\n";

#
#  I don't know what this one does.
#
# open my $out, '>', 'CHARGEN-FONT.BIN';
# print $out pack 'CC', 0x00, 0xe8;
# print $out pack 'C*', @data[0x00..0x7ff];
# close $out;

#
#  This one does it, but backwards I think
#
# open my $out2, '>', 'PET-CASE.BIN';
# print $out2 pack 'CC', 0x00, 0xe8;
# print $out2 pack 'C*', @data[0x800..0xfff]; 
# close $out2;

#
#  This one corrects the backwards PET-CASE.BIN.
#
open my $out3, '>', 'PETFONT3.BIN';
print $out3 pack 'CC', 0x00, 0xe8;
print $out3 pack 'C*', @data[0xc00..0xfff], @data[0x800..0xbff];
close $out3;
