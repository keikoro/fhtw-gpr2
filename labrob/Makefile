# Makefile for labrob program
#
# GPR2 UE5 + UE6 + UE7
#
# if13b076 - Linda Spindler
# if13b070 - K Kollmann
#
# make all -> create executable cpp program 'labrob' (use Option -g)
# make = make all
# make clean -> delete all files created during program creation
# make dist -> make release archive (using tar) containing a sub dir named
# like program + version no. with all necessary files
# (all program files and input files etc. but no executables)
# make distclean -> delete all files that aren't needed anymore
#
CC=g++
CFLAGS = -g -Wall -Werror -O

all: labrob
# TODO: uncomment once checkuserinput is merged into labrob again.
# labrob: labrob.o
# 	${CC} ${CFLAGS} -o labrob labrob.cpp
# labrob.o: labrob.cpp
# 	${CC} ${CFLAGS} -c labrob.cpp

# start checkuserinput -- TODO: remove later on
labrob: labrob.o
	${CC} ${CFLAGS} -o labrob labrob.cpp
labrob.o: labrob.cpp checkuserinput.cpp mazes_findentrance.cpp mazes_dummyprint.cpp
	${CC} ${CFLAGS} -c labrob.cpp
mazes_findentrance.o: mazes_findentrance.cpp
	${CC} ${CFLAGS} -c checkuserinput.cpp
mazes_dummyprint.o: mazes_dummyprint.cpp
	${CC} ${CFLAGS} -c mazes_dummyprint.cpp
# stop checkuserinput -- TODO: remove later on

dist:
	mkdir labrob_kollmann_spindler
	cp labrob.cpp labrob_kollmann_spindler/
	cp labrob.cpp labrob_kollmann_spindler/
	cp *.h labrob_kollmann_spindler/
	cp Makefile labrob_kollmann_spindler/
	tar -cvzf labrob_kollmann_spindler.tgz labrob_kollmann_spindler
distclean:
	rm labrob_kollmann_spindler.tgz
	rm -r labrob_kollmann_spindler
clean:
	rm -f labrob.o labrob
# remove dSYM dir created on Mac due to g++ -g flag
	@rm -f -r labrob.dSYM
