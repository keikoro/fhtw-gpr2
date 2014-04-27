/*
# gridsever for vehicle_grid_server program
#
# GPR2 UE4


Status
 - No implementation of message queues and named pipes yet (so everything
	happens in this program)
 - height and width of the grid are entered (by scanf), the grid is 
	calculated and drawn
 - a two-dimensinal 26x2 array is created and filled with '0'
 - the user is asked to enter a letter twice. The letter is given fixed coordinates
	both times, they're saved in the 26x2 array. If the second letter is the same as the first
	there is an error message.
 - I've been writing 'car' instead of 'vehicle'
*/


#include <stdio.h>

int main()
{

    // Creating the grid; reaidng in the numbers if done with scanf instead of getop for now.
    int grid_horizontal, grid_vertical;
    printf("Number of rows? ");
    scanf("%d", &grid_horizontal);
    printf("Number of columns? ");
    scanf("%d", &grid_vertical);
/*
 The actual matrix, borders included, is thus grid_horizontal+2 x grid_vertical+2
 The index of the matrix goes from 0 to grid_horizontal+1 and from 0 to grid_vertical+1
 The index of for the field the cars can travel through goes from 1 to grid_horizonzal, and from 1 to grid_vertical
*/
    char grid [grid_horizontal+2][grid_vertical+2];

// The following two for loops are for drawing the borders
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

// The following loop fills the rest of the grid with '.' (I don't think you can do this without a loop?)
    for(int i=1; i<=grid_horizontal; i++)
    {
        for(int j=1; j<=grid_vertical; j++)
            grid[i][j] = '.';
    }

/*
    Printing the grid
*/
    for(int i=0; i<=grid_horizontal+1; i++)
    {
        for(int j=0; j<=grid_vertical+1; j++)
            printf("%c", grid[i][j]);
        printf("\n");
    }


/*
 Matrix for saving the coordinates of the (up to) 26 cars
 2 rows, 26 cols.
*/
    int cars [2][26];
    for(int i=0; i<=1; i++)
    {
        for(int j=0; j<=25; j++)
            cars[i][j]= 0;
    }

	printf("Current Matrix:\n");
    for(int i=0; i<=1; i++)
    {
        for(int j=0; j<=25; j++)
            printf("%d", cars[i][j]);
        printf("\n");
    }


    // Starting a car by chosing its letter (A-Z); user is asked to enter a letter
    char car_letter;
    printf("Which car? (A-Z)?\n");
    scanf(" %c", &car_letter);



/*
 The initial coordinates for the car (here just fixed at [2][2], needs to be randomised)
 are saved at the index corresponding to the letter (0 for A, 1 for B etc)
 by calculating the ASCII-number - 65
 This information should be entered by the client, then sent to the server
*/
    cars[0][car_letter-65] = 2;
    cars[1][car_letter-65] = 2;

    for(int i=0; i<=1; i++) // printing the current matrix for easy debugging
    {
        for(int j=0; j<=25; j++)
            printf("%d", cars[i][j]);
        printf("\n");
    }


    // Starting a car by chosing its letter (A-Z), again, user entry
    // needs to come from the client later 
    printf("Which car? (A-Z)?\n");
    scanf(" %c", &car_letter);


// Checks if this letter is already in use, prints message acordingly
    if( (cars[0][car_letter-65] == 0) && (cars[1][car_letter-65]==0) )
    {
        printf("Registration OK. Start position: 3,3.\n"); // Start position just set at '3', needs to be randomised
            cars[0][car_letter-65] = 3;
            cars[1][car_letter-65] = 3;
    }
    else printf("Registration FAILED (letter already exists)\n");

    for(int i=0; i<=1; i++) // printing the current matrix for easy debugging
    {
        for(int j=0; j<=25; j++)
            printf("%d", cars[i][j]);
        printf("\n");
    }

/*
 For loop goes through the cars matrix, seaches for coordinates that are not [0][0], and writes the corresponding letter
 into the grid matrix.
 The conversion back from index (which is an int from 0 to 25) back to the corresponding letter
 is done with a switch statement, because I don't think there's another sure way of doing it.
 Posive effect is never having to search for a letter in a list. We're going through the whole 26 long
 array though.
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


/*
    Printing the grid
*/
    for(int i=0; i<=grid_horizontal+1; i++)
    {
        for(int j=0; j<=grid_vertical+1; j++)
            printf("%c", grid[i][j]);
        printf("\n");
    }



    return 0;
}

