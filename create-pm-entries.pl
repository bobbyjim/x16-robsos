=pod
I barely remember peripheral module image names.

We had XPM, SPM, DTC, and DTCI.  PDTC apparently also existed.

   P130703020091AMA                O.F            0  2048      4182   16892 130730

This example is kind of bogus, because the total size is not an even multiple of
the record count... and it's not 2:1 like on the other volume lists I have.

   DTC01
   DTCI01
   XPM004AL
   SPMWHATEVER

I can't really recall the nomenclature.  So I'll make things up.

Sizes were typically small.  The volume it's on shows 125 files, which suggests an 
"average" file size of 500K.  Also on the S01DPMLOAD volume, there are 444 files. If
we assume half of them are "documentation" files of no size, then the "average" size
is also around 500K, or 1000 blocks give or take.
=cut

my $volume = shift || 's00dpmload';


my @name_prefix = qw/dtc dtci xpm spm zpm/;
my @org = qw/i o/;
my @rec = qw/f v/;

my $totalBlocksUsed = 0;
my $fileCount = int(rand(31));

my @fileList = ();

for (1..$fileCount)
{
    my $maxRecLen = int(rand(8));   
    my $records   = 500 + int(rand(1000));
    my $blocks    = 2 * $records;
    $totalBlocksUsed += $blocks;

    push @fileList, sprintf("%-16s                O.F            0 %5d    %6d %7d %s\n",
       buildName(),
       2 ** ($maxRecLen + 6),
       $records,
       $blocks,
       buildDate()
    );
}

my $totalBlocks = 614239; # for a PM Disk
my $blocksFree  = $totalBlocks - $totalBlocksUsed;
my $largestFreeSegment = $blocksFree - int(rand($blocksFree / $fileCount));

printf "%-21s std %10d %10d %5d     0     0 %10d\n",
    uc $volume,
    $totalBlocks,
    $blocksFree,
    $fileCount,
    $largestFreeSegment;

print @fileList;

sub buildName
{
    my $name = $name_prefix[ rand(@name_prefix) ];

    $name .= int(rand(10)) for 1..int(rand(10));
    $name .= chr(int(rand(26)+65)) for 1..int(rand(4));

    return lc $name;
}

sub buildDate()
{
    # let's be nostalgic
    my $date = sprintf "9%d%02d%02d",
        int(rand(10)),
        int(rand(12)),
        int(rand(31));

    return $date;
}