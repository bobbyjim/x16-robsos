SOURCES = main.c boot.c ci.c ckt.c common.c diskut.c module.c pause.c restart.c trk.c ttp.c volumes.c 
PROGRAM = MAPCI

CC65_TARGET = cx16

CC	= cl65 
CFLAGS 	= --cpu 65c02 -t $(CC65_TARGET) --create-dep $(<:.c=.d) -Ors 
LDFLAGS	= -t $(CC65_TARGET) -m $(PROGRAM).map
OBJDIR  = .obj

#############################################
OBJECTS = $(SOURCES:%.c=$(OBJDIR)/%.o)

.SUFFIXES: 
all: $(PROGRAM)

ifneq (($MAKECMDGOALS),clean)
-include $(SOURCES:.c=.d)
endif

clean:
	$(RM) $(OBJECTS) $(SOURCES:.c=.d) $(PROGRAM) $(PROGRAM).map

.PHONY: all clean

$(PROGRAM): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $^

$(OBJECTS): $(OBJDIR)/%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<


