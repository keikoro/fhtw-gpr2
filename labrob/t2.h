/*  labrob program
    t2.h

    GPR2 UE5 + UE6 + UE7

    if13b070 - K Kollmann
    if13b076 - Linda Spindler

    subclass of "robots": for robots of type 1
*/

#ifndef T2_H
#define T2_H

class t2 : public Robots {
public:
    virtual void exit_search(Robots robot, int v, int h, Mazes this_maze);
protected:

};

#endif // T1_H
