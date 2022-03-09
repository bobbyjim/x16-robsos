5 DIM A0$(10)
10 DIM A1
15 DATA "CC      ", "CMC     ", "IOD     "
20 DATA "NET     ", "PM      ", "CCS     "
25 DATA "LNS     ", "TRKS    ", "EXT     "
30 DATA "APPL"
35 A1$ = "\X93  "
40 FOR X=0 TO 9
45    READ A0$(X)
50    A1$ = A1$ + A0$(X)
55 NEXT
60 COLOR 15,0 :REM LTGREY ON BLACK
65 REM ------------------------------------------------
70 REM
75 REM   MAIN LOOP
80 REM
85 REM ------------------------------------------------
90 ? A1$
