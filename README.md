# x16-robsos
A small SOS emulator.

# Why?
30 years ago, I wrote a DISKUT emulator in Perl, by which I practiced
setting the ITOC field and booting the CM. I added in a few extras,
just for fun, and had a nice little fake emulator.

I'm porting this to the X16, because (a) I like the X16, and (b) I get to
practice C coding.  It helps that the X16 has a browser-based emulator.

Commands implemented:

     help 
     quit
     quit all
     setlogmsg
     restart warm|cold|reload
     diskut
        lv 0
        lf|listfl <{volume}IMAGE>
        sbf|setbootfl
        cbf|clearbootfl
     mapci;mtc;trks;ttp
        post <CLLI>
        trunks (to get a list of trunks)

"help" is not an actual DMS SOS command.  I added it because I forget 
command syntax.

# Plans
I hope to add a subset of TTP functionality, where you can post, bsy, offline,
and rts trunks.
