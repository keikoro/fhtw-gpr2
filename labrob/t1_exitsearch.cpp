/*  labrob program
    t2_exitsearch.cpp

    GPR2 UE5 + UE6 + UE7
    if13b070 - K Kollmann
    if13b076 - Linda Spindler

    Search function for robots of type 1.
    Type 1 robots try to find their way through the maze
    by always turning right.
*/

using namespace std;

void t1::exit_search(Robots thisrobot, Mazes thismaze)
{
    thisrobot.step_counter = 0;

    // thisrobot.h // x coordinate;
    // thisrobot.v // y coordinate;
    // thisrobot.direction // direction the robot is currently facing;

    cout << endl << "X: " << thisrobot.h << " Y: " << thisrobot.v << endl << endl
    << "facing: " << thisrobot.direction << endl << endl;

    thisrobot = step_forward(thisrobot);
    thisrobot.step_counter++;

    cout << endl << "X: " << thisrobot.h << " Y: " << thisrobot.v << endl << endl
    << "facing: " << thisrobot.direction << endl << endl;

    thisrobot = step_forward(thisrobot);
    thisrobot.step_counter++;

    cout << endl << "X: " << thisrobot.h << " Y: " << thisrobot.v << endl << endl
    << "facing: " << thisrobot.direction << endl << endl;

    cout << "steps: " << thisrobot.step_counter << endl << endl;

}
