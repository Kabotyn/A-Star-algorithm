#ifndef SPACEPROBE_H
#define SPACEPROBE_H

#include <astar.h>
#include <string>
#include <vector>

class SpaceProbe
{
public:
    SpaceProbe(int p_N, int p_startR, int p_startC, int p_endR, int p_endC);
    ~SpaceProbe();

    void setSpaceSize(int p_N);   // set N (space size)
    void showSpace();


    bool run(); // return true when found way, return false if not

private:
    int N;  // field size N*N
    int A;  // number of asteroids
    int G;  // number of gravity wells
    int F;  // number of free space
    std::string *vis;   // visualisation in text

    nodePosition start; // start node position
    nodePosition end;   // end node position

    std::vector<nodePosition> asteroids;    // positions of asteroids
    std::vector<nodePosition> gravityWells; // positions of gravity wells
    std::vector<nodePosition> allObstacles; // positions of all obstacle (space around gravity well is an obstacle)

    std::list<nodePosition> result; // result - path if empty - no path

    void countA();  // count numbers of asteroids
    void countG();  // numbers of gravity wells
    void countF();  // numbers of empty space

    void randomAsteroids();     // generate random position for asteroids;
    void randomGravityWells();  // generate random positions for gravity wells

    void prepareVis();      // prepare vis variable - put dot, S, E, G and A.
    void prepareResult();   // prepre results with the path

};

#endif // SPACEPROBE_H
