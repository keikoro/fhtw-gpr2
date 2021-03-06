/*  vehicle_grid_server program
    gridserver.c

    GPR2 UE4

    if13b070 - K Kollmann
    if13b076 - Linda Spindler


Status
 -  IMPORTANT: right now, 'KEY' for the message queue is set 87,
    and queues are not automatically deleted when the program ends.
	This means that there's an error message if the program is run
	twice in a row, because the queue already exists.

 -  Height and width of the grid are entered (now with getopt),
    the grid is calculated and drawn
 -  A two-dimensional 2x26 array is created and filled with '0's
 -  First implementation of a message queue: the server starts,
	a client enters a letter (A-Z),
    the message is sent to the server, who saves the letter in a local
    variable, saves the coordinates of the letter in the 2x26 matrix,
    and waits for new input.
    The client program ends after that one message
 -  Doesn't deal with collision: the coordinates are random, if there is
	already a letter on the random spot, the current letter gets overwritten
 -	If the same letter if is sent twice by the client,
	there is an error message; at this time, the message is desplayed on
	the gridserver terminal, it needs to be moved to the client.
 -  2x26 array and grid are printed a few times on the gridserver.c terminal
 -  I've been writing 'car' instead of 'vehicle'
 -  Error messages are blindly copied from the lecture notes

*/
#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <signal.h>


// defines for the message queue
#define PERM 0660
#define KEY 87
#define MAX_DATA 255


// typedef for the structure used for messages
typedef struct
{
    long mType;
    char mText[MAX_DATA];
} message_t;


char *program_name=NULL;


// error message to print when the parameters for main () are incorrect
void print_usage()
{
   fprintf(stderr,"Usage: %s [-x NUM] [-y NUM]\n",program_name);
   exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    int c;
    int error=0;
    char *x_axis=NULL;
    char *y_axis=NULL;
    program_name=argv[0];

    while( (c = getopt(argc, argv, "x:y:")) != EOF )
    {
        switch( c )
        {
            case 'x':
                if (x_axis!=NULL) /* Argument used more than once */
                {
                  error=1;
                  break;
                }
                x_axis=optarg;
                printf("%s: parsing option x, argument: %s\n",program_name,x_axis);
                break;
            case 'y':
                if (y_axis!=NULL)
                {
                  error=1;
                  break;
                }
                y_axis=optarg;
                // following printf to be deleted later, but useful for debugging
                printf("%s: parsing option y, argument: %s\n",program_name,y_axis);
                break;
            case '?':
                error=1;
                break;
            default:
                assert( 0 );
        }
    }

    // print usage on error or when no options were given
    if (error || ((x_axis==NULL) || (y_axis==NULL)) )
    {
        print_usage();
    }
    //this if should check for wrong nb of options
    if (argc != (optind))
    {
        print_usage();
    }

    while (optind < argc)
    {
      printf("%s: parsing argument %s\n",program_name,argv[optind]);
      optind++;
	}
//   return EXIT_SUCCESS; (This was in the example program, is this necessary?


	/*  Matrix for saving the coordinates of the (up to) 26 cars.
		2 rows, 26 cols.
	*/
	int cars [2][26];
	for(int i=0; i<=1; i++)
	{
		for(int j=0; j<=25; j++)
			cars[i][j]= 0;
	}
        /*  Creating the grid
        */
        int grid_horizontal, grid_vertical;
        grid_horizontal = (int)strtol(x_axis, NULL, 10);
        grid_vertical = (int)strtol(y_axis, NULL, 10);
     /* Conversion from string to long int with strtol, converstion from
        long int to int by cast
     */

	printf("\n%d %d\n", grid_horizontal, grid_vertical);

	/*
		The actual matrix, borders included, is thus
		grid_horizontal+2 x grid_vertical+2. The index of the matrix goes
		from 0 to grid_horizontal+1 and from 0 to grid_vertical+1.
		The index of the field the cars can travel through goes
		from 1 to grid_horizonzal, and from 1 to grid_vertical.
	*/
	char grid [grid_horizontal+2][grid_vertical+2];

	// The following two for loops are for drawing the borders;
	// The drawing of the grid itself needs to be moved to the grid
	// client later
	for(int i=0; i<=grid_vertical+1; i++)
	{
		grid[0][i]='#';
		grid[grid_horizontal+1][i]='#';
	}
	for(int i=1; i<=grid_horizontal+1; i++)
	{
		grid[i][0]='#';
		grid[i][grid_vertical+1]='#';
	}

	/*  The following loop fills the rest of the grid with '.'
		(I don't think you can do this without a loop?) */
	for(int i=1; i<=grid_horizontal; i++)
	{
		for(int j=1; j<=grid_vertical; j++)
			grid[i][j] = '.';
	}

	// Printing the grid
	for(int i=0; i<=grid_horizontal+1; i++)
	{
		for(int j=0; j<=grid_vertical+1; j++)
			printf("%c", grid[i][j]);
		printf("\n");
	}


    message_t msg;  /* Buffer */
    int msgid = -1; /* Message Queue ID */

    /* Creating Message Queue */
    if( (msgid = msgget(KEY,PERM | IPC_CREAT | IPC_EXCL ))==-1 )
    {
        /* error handling */
        fprintf(stderr,"%s: Error creating message queue\n",program_name);
        return EXIT_FAILURE;
    }

   /* Infinite loop for receiving messages */
   while (1)
   {
        if (msgrcv(msgid,&msg,sizeof(msg)-sizeof(long), 0 , 0) == -1)
        {
            /* error handling */
            fprintf(stderr,"%s: Can't receive from message queue\n",program_name);
            return EXIT_FAILURE;
        }
        printf("Message received: %s\n",msg.mText);
        char car_letter = msg.mText[0];
        printf("Letter from the last message: %c\n", car_letter);


        printf("Current Matrix:\n");
        for(int i=0; i<=1; i++)
        {
            for(int j=0; j<=25; j++)
                printf("%d", cars[i][j]);
            printf("\n");
        }
    /*
         The initial coordinates for the first car
         (random, don't take into account collision)
         are saved at the index corresponding to the letter (0 for A, 1 for B etc)
         by calculating the ASCII-number - 65

        Checks if a letter is already in use, prints message accordingly
        These messages need to be moved to the client
    */
		int x_start, y_start;
        if( (cars[0][car_letter-65] == 0) && (cars[1][car_letter-65]==0) )
        {
			x_start = (rand() % (grid_horizontal))+1;
			y_start = (rand() % (grid_vertical))+1;
            printf("Registration OK. Start position: %d,%d\n", x_start-1, y_start-1);
			cars[0][car_letter-65] = x_start;
			cars[1][car_letter-65] = y_start;
        }
        else printf("Registration FAILED (letter already exists)\n");

        printf("Current Matrix:\n");
        for(int i=0; i<=1; i++) // printing the current matrix for easy debugging
        {
            for(int j=0; j<=25; j++)
                printf("%d", cars[i][j]);
            printf("\n");
        }


        /*
            For loop goes through the cars matrix, seaches for coordinates that
            are not [0][0], and writes the corresponding letter into the
            grid matrix.
        */
        for(int i=0; i<26; i++)
        {
            if( !((cars[0][i] == 0) && (cars[1][i]==0)) )
                switch(i)
                {
                    case 0: grid[cars[0][i]][cars[1][i]] = 'A'; break;
                    case 1: grid[cars[0][i]][cars[1][i]] = 'B'; break;
                    case 2: grid[cars[0][i]][cars[1][i]] = 'C'; break;
                    case 3: grid[cars[0][i]][cars[1][i]] = 'D'; break;
                    case 4: grid[cars[0][i]][cars[1][i]] = 'E'; break;
                    case 5: grid[cars[0][i]][cars[1][i]] = 'F'; break;
                    case 6: grid[cars[0][i]][cars[1][i]] = 'G'; break;
                    case 7: grid[cars[0][i]][cars[1][i]] = 'H'; break;
                    case 8: grid[cars[0][i]][cars[1][i]] = 'I'; break;
                    case 9: grid[cars[0][i]][cars[1][i]] = 'J'; break;
                    case 10: grid[cars[0][i]][cars[1][i]] = 'K'; break;
                    case 11: grid[cars[0][i]][cars[1][i]] = 'L'; break;
                    case 12: grid[cars[0][i]][cars[1][i]] = 'M'; break;
                    case 13: grid[cars[0][i]][cars[1][i]] = 'N'; break;
                    case 14: grid[cars[0][i]][cars[1][i]] = 'O'; break;
                    case 15: grid[cars[0][i]][cars[1][i]] = 'P'; break;
                    case 16: grid[cars[0][i]][cars[1][i]] = 'Q'; break;
                    case 17: grid[cars[0][i]][cars[1][i]] = 'R'; break;
                    case 18: grid[cars[0][i]][cars[1][i]] = 'S'; break;
                    case 19: grid[cars[0][i]][cars[1][i]] = 'T'; break;
                    case 20: grid[cars[0][i]][cars[1][i]] = 'U'; break;
                    case 21: grid[cars[0][i]][cars[1][i]] = 'V'; break;
                    case 22: grid[cars[0][i]][cars[1][i]] = 'W'; break;
                    case 23: grid[cars[0][i]][cars[1][i]] = 'X'; break;
                    case 24: grid[cars[0][i]][cars[1][i]] = 'Y'; break;
                    case 25: grid[cars[0][i]][cars[1][i]] = 'Z'; break;

                    default: printf("Something went wrong");
                }
        }

        // Printing the grid
        for(int i=0; i<=grid_horizontal+1; i++)
        {
            for(int j=0; j<=grid_vertical+1; j++)
                printf("%c", grid[i][j]);
            printf("\n");
        }
    }

	// I think I need to delete the queue again somehow, but I have no
	// idea how atm
    return 0;
}


