/*  labrob program
    checkuserinput.cpp

    GPR2 UE5 + UE6 + UE7
    if13b070 - K Kollmann
    if13b076 - Linda Spindler

	Function for checking the user's input.
	Part of labrob program.

	labrob program:
    Program for sending robots through mazes with different kinds of
    search algorithms and printing statistics about the robots' performances.
    (When all robots have found their way from the entrance to the
    labyrinth to its exit, a table containing information on how many
    steps it took each robot to reach the exit is printed out.)

    Usage:
    labrob path_to_maze [-t1] [–t2] [–t3]...[-tN] [-h]

    With:
    -t1-tN being used for the robot type (if no type is specified, t1 is used)
    -h being used for printing a usage message
*/

using namespace std;

void checkuserinput (int argc, char *argv[]) {

string programname = argv[0];
string helpmsg = "Usage: labrob path_to_maze [-t1] [–t2] [–t3]...[-tN] [-h]";

int getflags;
char *robot_type=NULL;
std::vector<int> robot_numbers;
int robot_number;

//    string *robot = new string();
string *maze = new string();

// print all arguments
// std::cout << "argc: " << argc << std::endl;
// for (int i = 0; i < argc; ++i)
//     std::cout << "argv: "<< argv[i] << std::endl;

while ((getflags = getopt(argc, (char **)argv, "t::h")) != -1) {

    switch(getflags) {
        case 'h':
            cout << helpmsg << endl; // prints help message
            exit(EXIT_FAILURE);
            break;
        case 't':
            robot_type=optarg;
            // print robot number
            cout << "the robot number is " << robot_type << endl;
			if (robot_type != NULL)
			{
				int robot_number = 1;
				sscanf(robot_type, "%d", &robot_number);

				robot_numbers.push_back (robot_number);
			}
			else
			{
                cout << "Option t missing"  << endl << helpmsg << endl;
				exit(EXIT_FAILURE);
			}
			break;
    }
}

if (argc < optind+1) /* wrong nb of options */
{
	cout << "Too few options!" << endl << helpmsg << endl;
	exit(EXIT_FAILURE);
}

*maze = argv[optind];

cout << "All the arguments in an int vector: ";
for(std::vector<int>::iterator i=robot_numbers.begin();
	i != robot_numbers.end(); i++)
{
	robot_number = *i;
	cout << robot_number << "   ";
}
cout << endl;
}
