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
labrob.o: labrob.cpp checkuserinput.cpp mazes_findentrance.cpp mazes_dummyprint.cpp mazes_dummyprint.cpp mazes_iswall.cpp t1_exitsearch.cpp t2_exitsearch.cpp robots_stepforward.cpp robots_stepforward_v2.cpp robots_turnleft.cpp
	${CC} ${CFLAGS} -c labrob.cpp
mazes_findentrance.o: mazes_findentrance.cpp
	${CC} ${CFLAGS} -c checkuserinput.cpp
mazes_dummyprint.o: mazes_dummyprint.cpp
	${CC} ${CFLAGS} -c mazes_dummyprint.cpp
mazes_iswall.o: mazes_iswall.cpp
	${CC} ${CFLAGS} -c mazes_iswall.cpp
t1_exitsearch.o: t1_exitsearch.cpp
	${CC} ${CFLAGS} -c t1_exitsearch.cpp
t2_exitsearch.o: t2_exitsearch.cpp
	${CC} ${CFLAGS} -c t2_exitsearch.cpp
robots_stepforward.o: robots_stepforward.cpp
	${CC} ${CFLAGS} -c robots_stepforward.cpp
robots_stepforward_v2.o: robots_stepforward_v2.cpp
	${CC} ${CFLAGS} -c robots_stepforward_v2.cpp
robots_turnleft.o: robots_turnleft.cpp
	${CC} ${CFLAGS} -c robots_turnleft.cpp

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
