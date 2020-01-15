PROGRAM = box_pusher
CC      = gcc
CFLAGS  = -Wall
LDLIBS  = -lglut -lGLU -lGL
SOURCES		= main.c game.c	draw.c	

$(PROGRAM): $(SOURCES)
	$(CC) $^ -o $(PROGRAM) $(LDLIBS) $(CFLAGS)

.PHONY: beauty clean dist

beauty:
	-indent -kr -nut main.c
	-rm *~ *BAK

clean:
	-rm *.o $(PROGRAM) *core

dist: clean
	-tar -chvj -C .. -f ../$(PROGRAM).tar.bz2 $(PROGRAM)
