# Makefile for sortnames program
#
# GPR2 UE1, UE2
#
# if13b076 - Linda Spindler
# if13b070 - K Kollmann
#
# make all -> create executable program 'sortnames' (use Option -g)
# make = make all
# make clean -> delete all files created during program creation
# make dist -> make release archive (using tar) containing a sub dir named
# like program + version no. (sortnames-1.1) with all necessary files
# (all program files and input files etc. but no executables)
# make distclean -> delete all files that aren't needed anymore
#
CC=gcc
CFLAGS = -g -Wall -Werror -O -std=c99

all: sortnames
sortnames: sortnames.o
	${CC} ${CFLAGS} -o sortnames sortnames.c
sortnames.o: sortnames.c
	${CC} ${CFLAGS} -c sortnames.c
dist:
	mkdir sortnames-1.1
	cp sortnames.c sortnames-1.1/
	cp *.txt sortnames-1.1/
	cp Makefile sortnames-1.1/
	tar -cvzf sortnames-1.1.tgz sortnames-1.1
distclean:
	rm sortnames-1.1.tgz
	rm -r sortnames-1.1
clean:
	rm -f sortnames.o sortnames
