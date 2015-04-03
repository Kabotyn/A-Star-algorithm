#include "node.h"

Node::Node()
{
    statusH = false;
    statusG = false;
}

Node::~Node()
{

}

void Node::setPosition(nodePosition pos) {
    position.row = pos.row;
    position.col = pos.col;
}

void Node::setPosition(int row, int col) {
    position.row = row;
    position.col = col;
}

void Node::setH(int h) {
    statusH = true;
    H = h;
}

void Node::setG(int g) {
    statusG = true;
    G = g;
}

void Node::countF() {
    F = G + H;
}

void Node::setParent(Node *p) {
    parent = p;
}

nodePosition Node::getPosition() {
    return position;
}

int Node::getF() {
    return F;
}

int Node::getH() {
    return H;
}

int Node::getG() {
    return G;
}

bool Node::getStatusH() {
    return statusH;
}

bool Node::getStatusG() {
    return statusG;
}

Node* Node::getParent() {
    return parent;
}
