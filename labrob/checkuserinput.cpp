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
int thisrobot;
std::vector<int> robot_numbers;
// int robot_number;

//    string *robot = new string();
string *maze = new string();

// print all arguments
// std::cout << "argc: " << argc << std::endl;
// for (int i = 0; i < argc; ++i)
//     std::cout << "argv: "<< argv[i] << std::endl;

/*  use double colon for option argument for the*/
    while ((getflags = getopt(argc, (char **)argv, "t::h")) != -1) {

        switch(getflags) {
            case 'h':
                cout << helpmsg << endl;
                exit(EXIT_FAILURE);
                break;
            case 't':
                /*  if no argument is given, use 1  */
                if (optarg == NULL)
                {
                /*  check if argument is a number  */
                    thisrobot = 1;
                    robot_numbers.push_back(thisrobot);
                    cout << "the robot number is " << thisrobot << endl; /*
                    for debugging -- TODO: remove later on */
                }
                else
                {
                    if (isdigit(*optarg))
                    {
                        sscanf(optarg, "%d", &thisrobot);
                        robot_numbers.push_back(thisrobot);
                        cout << "the robot number is " << thisrobot << endl; /*
                        for debugging -- TODO: remove later on */
                    }
                    else
                    {
                        cout << helpmsg << endl;
                        exit(EXIT_FAILURE);
                    }
                break;
                }
            /*  unknown option used */
            // case '?':
            //     cout << helpmsg << endl;
            //     exit(EXIT_FAILURE);
            //     break;
        }
    }

// cout << "optind: " << optind << endl;

    /*  there must be at least 3 argv (program name, -t, file name of maze) */
    if (sizeof(argv) < 3)
    {
        cout << "not enough options provided" << endl << helpmsg << endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        if (argv[optind])
        {
            cout << "the maze name is: "  << argv[optind] << endl;
        }
        else
        {
            cout << "no maze name was provided" << endl << helpmsg << endl;
        }
    }

        // /*  loop through file names */
        // for (int i = optind; i < argc; i++)
        // {
        //      cout << argv[i] << endl;
        // }

    *maze = argv[optind];

// cout << "All the arguments in an int vector: ";
// for(std::vector<int>::iterator i=robot_numbers.begin();
// 	i != robot_numbers.end(); i++)
// {
// 	robot_number = *i;
// 	cout << robot_number << "   ";
// }
// cout << endl;
// }

}
