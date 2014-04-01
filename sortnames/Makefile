# Makefile for sortnames program
#
# make all -> create executable program 'sortnames' (use Option -g)
# make = make all
# make clean -> delete all files created during program creation
# make dist -> make release archive (tar) containing a sub directory with
# ... name of tool and version no. + all programs and files (sortnames-1.1)
# make distclean -> delete all files that aren't needed anymore
#
CC=gcc
CFLAGS = -g -Wall -Werror -O -std=c99

all: sortnames
sortnames: sortnames.o
	${CC} ${CFLAGS} -o sortnames sortnames.c
sortnames.o: sortnames.c readandsort.c writefiles.c checkstdin.c
	${CC} ${CFLAGS} -c sortnames.c
dist:
	mkdir sortnames-1.1
	cp *.c sortnames-1.1/
	cp *.n sortnames-1.1/
	cp Makefile sortnames-1.1/
	tar -cvzf sortnames-1.1.tgz sortnames-1.1
distclean:
	rm sortnames-1.1.tgz
	rm -r  sortnames-1.1
clean:
	rm -f sortnames.o sortnames
