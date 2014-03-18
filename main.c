#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include "writefiles.c"
#include "readfiles.c"


int main(int argc, char *argv[])
{
    // FILE *fp;
    // int i;

    readfiles(argc, argv);
    writefiles(argc, argv);

    return 0;
}
