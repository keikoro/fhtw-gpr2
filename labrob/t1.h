/*  labrob program
    robot1.h

    GPR2 UE5 + UE6 + UE7

    if13b070 - K Kollmann
    if13b076 - Linda Spindler

    subclass of "robots": for robots of type 1
*/

#ifndef T1_H
#define T1_H

class t1 : public Robots {
public:
	virtual void exit_search(Robots thisrobot, Mazes thismaze);
protected:

};

#endif // T1_H
