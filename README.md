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
        bsy
        rts
        offl
        trunks (to get a list of trunks)

"help" is not an actual DMS SOS command.  I added it because I forget 
command syntax.

# Trunks
The trunks are all completely randomly generated.  Don't expect them to make
much sense at all.

There are 64 trunks, randomly generated.  There are likely some very wrong
strings in there.

## Trunk Maintenance
Minimal and buggy. You can offline, bsy, or rts a posted trunk.
It won't let you rts an offl trunk -- bsy it first.  It won't tell you this.

You can use the first 6 characters of a CLLI when posting a trunk; e.g.
you can POST DAL360 instead of POST DAL360ICDTGS or whatever it is.
