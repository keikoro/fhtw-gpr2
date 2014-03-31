# Makefile for sortnames program
#
# make all -> create executable program 'sortnames' (use Option -g)
# make = make all
# make clean -> delete all files created during program creation
# make dist -> make release archive (tar) containing a sub directory with
# ... name of tool and version no. + all programs and files (sortnames-1.1)
# make distclean -> delete all files that aren't needed anymore
#

all: sortnames
sortnames: sortnames.c
	gcc -g -Wall -Werror -O -o sortnames sortnames.c
dist:
distclean:
clean:
	rm -f sortnames sortnames-1.1
