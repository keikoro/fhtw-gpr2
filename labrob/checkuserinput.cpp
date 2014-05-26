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

void checkuserinput (int argc, char *argv[], string *mazefile) {

    string helpmsg = "Usage: labrob path_to_maze [-t1] [–t2] [–t3]...[-tN] [-h]";

    int getflags;
    int thisrobot;
    vector<int> robot_numbers;
    // string *maze = NULL;

    //    string *robot = new string();
    string bla = "bli";
    *mazefile = bla;
    cout << "inner function mazepath print: " << *mazefile << endl;


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
                    /* below for debugging -- TODO: remove later on */
                }
                else
                {
                    if (isdigit(*optarg))
                    {
                        sscanf(optarg, "%d", &thisrobot);
                        robot_numbers.push_back(thisrobot);
                        /* below for debugging -- TODO: remove later on */
                        // cout << "robot " << thisrobot << endl;
                    }
                    else
                    {
                        cout << "invalid argument: " << optarg << endl;
                        cout << helpmsg << endl;
                        exit(EXIT_FAILURE);
                    }
                }
                break;
            /*  unknown option used */
            case '?':
                cout << "invalid option: " << optarg << endl
                << helpmsg << endl;
                exit(EXIT_FAILURE);
                break;
        }
    }

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
            // maze file == argv[optind]
            // check for valid file here!
            *mazefile = string(argv[optind]);
            cout << "inner function mazepath print no. 2: " << mazefile << endl;

            // cout << "path to maze file:" << endl << *mazefile << endl;
        }
        else
        {
            cout << "no maze file was provided!" << endl << helpmsg << endl;
        }
    }

    // *maze = argv[optind];
}
