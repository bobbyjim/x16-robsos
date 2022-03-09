# x16-robsos
A small SOS emulator.

# Why?
30 years ago, I wrote a DISKUT emulator in Perl, by which I practiced
setting the ITOC field and booting the CM. I added in a few extras,
just for fun, and had a nice little fake emulator.

I'm porting this to the X16, because (a) I like the X16, and (b) I get to
practice C coding.  It helps that the X16 has a browser-based emulator.

Commands implemented:

diskut
lv 0
lf <{volume}IMAGE>

I'll add in SBF and CBF, then add RESTART and a few fun extras.
Then I hope to add a subset of TTP.
