#ifndef ASTAR_H
#define ASTAR_H

#include <math.h>
#include <list>
#include "node.h"

class AStar
{
public:

    /* r - number of rows
     * c - number of cols
     * sr - row of start node
     * sc - col of start node
     * er - row of start node
     * ec - col of start node
     */
    AStar(int r, int c, int sr, int sc, int er, int ec);
    ~AStar();

    std::list<nodePosition> find();    // start searching a shortest way
    void setSize(int r, int c); // set number of rows and cols
    void setStartEnd(int startR, int startC, int endR, int endC);   // set start and end node position
    void setObstacle(int r, int c); // put point r c in closeList (as a obstacle)

private:
    int cols; // number of cols
    int rows; // number of rows

    int countDistance(nodePosition startNode, nodePosition endNode); // cout distance between two nodes

    Node *start, *end, *current; // pointer to start, end and current node

    Node **allNodes; // my pointer to 2D array with nodes. above *start and *end are pointer to specific element in this array

    std::list<Node *> openList;     // list with open nodes
    std::list<Node *> closeList;    // list with closed and visited nodes

    Node* findLowestFinOpenList();   // find Node in OpenList with the lowest F.

    std::list<Node *> findNeighboursOfCurrent();    // function return all neighbours of current node

    std::list<nodePosition> route(Node *e); // return a rout from end node to the start node
};

#endif // ASTAR_H
