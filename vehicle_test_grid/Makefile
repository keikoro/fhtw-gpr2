# Makefile for vehicle_grid_server program
#
# GPR2 UE4
#
# if13b076 - Linda Spindler
# if13b070 - K Kollmann
#
# make all:
# creates executable programs 'gridserver', 'vehicleclient', 'griddisplay'
# (using option -g)
#
# make clean:
# delete all files created during program creation
#
# make dist
# make release archive (using tar) containing a sub dir named
# like program + version no. (sortnames-1.1) with all necessary files
# (all program files and input files etc. but no executables)
# make distclean -> delete all files that aren't needed anymore
#
CC=gcc
CFLAGS = -g -Wall -Werror -O -std=c99 -D_XOPEN_SOURCE

all: gridserver vehicleclient griddisplay

gridserver: gridserver.o
	${CC} ${CFLAGS} -o gridserver gridserver.c
gridserver.o: gridserver.c
	${CC} ${CFLAGS} -c gridserver.c
vehicleclient: vehicleclient.o
	${CC} ${CFLAGS} -o vehicleclient vehicleclient.c
vehicleclient.o: vehicleclient.c
	${CC} ${CFLAGS} -c vehicleclient.c
griddisplay: griddisplay.o
	${CC} ${CFLAGS} -o griddisplay griddisplay.c
griddisplay.o: griddisplay.c
	${CC} ${CFLAGS} -c griddisplay.c

dist:
	mkdir UE4_kollmann_spindler
	cp *.c UE4_kollmann_spindler/
	cp Makefile UE4_kollmann_spindler/
	tar -cvzf UE4_kollmann_spindler.tgz UE4_kollmann_spindler
distclean:
	rm UE4_kollmann_spindler.tgz
	rm -r UE4_kollmann_spindler

clean:
	rm -f gridserver.o gridserver
	rm -f vehicleclient.o vehicleclient
	rm -f griddisplay.o griddisplay
# removing dSYM dirs on Mac
	@rm -r -f gridserver.dSYM
	@rm -r -f vehicleclient.dSYM
	@rm -r -f griddisplay.dSYM
