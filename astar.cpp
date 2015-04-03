#include "astar.h"
#include <QDebug>
#include <algorithm>

AStar::AStar(int r, int c, int sr, int sc, int er, int ec) {
    setSize(r, c); // init size of field

    setStartEnd(sr, sc, er, ec); // init start and end node

}

void AStar::setSize(int r, int c) {
    rows = r;
    cols = c;

    // allocate memory, creat 2D array rows*cols
    allNodes = new Node*[rows];
    for(int i = 0; i < rows; ++i)
        allNodes[i] = new Node[cols];
}

void AStar::setStartEnd(int startR, int startC, int endR, int endC) {
    // set values to start and end nodes. init two necessary points

    start = &allNodes[startR][startC];
    end = &allNodes[endR][endC];

    start->setPosition(startR, startC);
    end->setPosition(endR, endC);

    start->setG(0);
    start->setH(countDistance(start->getPosition(), end->getPosition()));
    start->countF();
    start->setParent(NULL);

    current = start;

    end->setG(countDistance(start->getPosition(), end->getPosition()));
    end->setH(0);
    end->countF();
    end->setParent(NULL);

    openList.push_back(current); // initializa openList with start node

}

void AStar::setObstacle(int r, int c) {
    closeList.push_back(&allNodes[r][c]);
}

AStar::~AStar()
{
    delete allNodes;    // releae memory
}

// return minimum distance from start to end
int AStar::countDistance(nodePosition startNode, nodePosition endNode) {

    // integer distance between each node. In diagonal is 14 (sqrt 2 * 10) in normal it is 1 * 10;
    // multiply by 10 because we want to have an integer value
    int diagonalVal = 14, normalVal = 10;

    if(startNode.col == endNode.col && startNode.row == endNode.row) {
        // start = end
        return 0; // distance is 0

    } else if(startNode.col == endNode.col) {
        // same column, calculate only distance in a row
        return abs(startNode.row - endNode.row) * normalVal;

    } else if(startNode.row == endNode.row) {
        // same row, calculate distance in col
        return abs(startNode.col - endNode.col) * normalVal;

    } else {
        // we have some diagonal movement neccessary
        int diaginalIteration = 0, rowStep = 1, colStep = 1;

        // determine of the sing of step (go up or down or left or right)
        if(startNode.row > endNode.row)
            rowStep *= -1;
        if(startNode.col > endNode.col)
            colStep *= -1;

        do {
            // count how many diagonal movement we do
            ++diaginalIteration;

            // calculate "new" start position
            startNode.col += colStep;
            startNode.row += rowStep;
        } while(startNode.col != endNode.col && startNode.row != endNode.row); // do it as lon as we will be in the sam row or column

        // recurency, use this function to calculate te distans in the same row or column
        // plus distance in diagonal steps
        return countDistance(startNode, endNode) + (diaginalIteration * diagonalVal);
    }

}

std::list<nodePosition> AStar::find() {
    std::list<Node *> neighbourOfCurrent;
    std::list<Node *>::iterator niterator, findCloseIterator, findOpernIterator;

    Node *tempNode;

    int newG;
    do {
        current = findLowestFinOpenList();
        if(current == NULL)
            break;
        openList.remove(current);
        closeList.push_back(current);

        neighbourOfCurrent.clear();
        neighbourOfCurrent = findNeighboursOfCurrent();
        for(niterator = neighbourOfCurrent.begin(); niterator != neighbourOfCurrent.end(); ++niterator) {
            tempNode = *niterator;
            // find if neighbur is in closeList
            findCloseIterator = std::find(closeList.begin(), closeList.end(), tempNode);
            if(findCloseIterator != closeList.end()) {
                // yep, there is neighbour in close list
                continue;
            } else {
                // nope there is no neighbour in closeList

                findOpernIterator = std::find(openList.begin(), openList.end(), tempNode);
                newG = current->getG() + countDistance(current->getPosition(), tempNode->getPosition()); // new G for this neighbour

                if(findOpernIterator != openList.end()) {
                    // neighbour is in open list, so we nieed to update distance from start node (if needed)
                    if(tempNode->getStatusG() == false || newG < tempNode->getG()) {
                        tempNode->setG(newG);
                        tempNode->countF();
                        tempNode->setParent(current);
                    }
                } else {
                    // ther is no neighbour in open list, so we nieed to add it
                    tempNode->setG(newG);
                    tempNode->countF();
                    tempNode->setParent(current);
                    openList.push_back(tempNode);
                }

            }

        }

    } while(current != end);


   return route(end);

}

std::list<nodePosition> AStar::route(Node *e) {
    std::list<nodePosition> path;

    if(e->getParent() == NULL) {
        return path;
    }

    path.push_front(e->getPosition());

    while(e->getPosition().col != start->getPosition().col ||
            e->getPosition().row != start->getPosition().row) {

        e = e->getParent();
        path.push_front(e->getPosition());

    }
    return path;

}

Node* AStar::findLowestFinOpenList() {
    // if there are more than one lowest F, choose one with lowest H
    std::list<Node *>::iterator listIterator;

    if(openList.empty())
        return NULL;

    Node *tempNode, *lowestNode;
    int lowestFValue = 999999;
    int lowestHValue = 999999;


    // iterator goes on evry list item and check if it is minimum
    for(listIterator = openList.begin(); listIterator!= openList.end(); ++listIterator) {
        tempNode = *listIterator ;

        // std:min_element
        if( (tempNode->getF() < lowestFValue) ||
                ( tempNode->getF() == lowestFValue &&
                  tempNode->getH() < lowestHValue ) ) {
            lowestFValue = tempNode->getF();
            lowestHValue = tempNode->getH();
            lowestNode = *listIterator;
        }
    }

    return lowestNode;
}

// selectin all neighbours of current node
std::list<Node *> AStar::findNeighboursOfCurrent() {
    std::list<Node *> neighbours;
    Node *n;

    nodePosition currentPos = current->getPosition();

    int maxCol = currentPos.col+1, minCol = currentPos.col - 1,
            maxRow = currentPos.row+1, minRow = currentPos.row -1;

    // check if is in the edge
    if(currentPos.col == 0) {
        // first column
        minCol = currentPos.col;
    } else if(currentPos.col == (cols-1)) {
        // last column
        maxCol = currentPos.col;
    }

    if(currentPos.row == 0) {
        // first row
        minRow = currentPos.row;
    } else if(currentPos.row == (rows-1)) {
        // last row
        maxRow = currentPos.row;
    }

    for(int r = minRow; r <= maxRow; r++) {
        for(int c = minCol; c <= maxCol; c++) {
            if(currentPos.row == r && currentPos.col == c) {
                continue;
            }

            // create new neigbour
            n = &allNodes[r][c];

            if(n->getStatusH() == false) { // First use of that element
                n->setPosition(r, c);
                n->setH(countDistance(n->getPosition(), end->getPosition()));
            }

            neighbours.push_back(n);
            //qDebug() << n->getG() << allNodes[r][c].getG();
        }
    }

    return neighbours;

}
