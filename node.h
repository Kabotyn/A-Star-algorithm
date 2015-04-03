#ifndef NODE_H
#define NODE_H

struct nodePosition {
    int row;
    int col;
};

/* This class is a node type. Evry node is an object of this class, it provides
 * necessary variables (with setters and getters) like positions, H value G value etc.
 **/
class Node {

public:
    Node();
    ~Node();

    void setPosition(nodePosition);     // set position for current node
    void setPosition(int row, int col); // set possition from two integers
    void setH(int h);   // set H value for current node - distance to the end
    void setG(int g);   // set G - distance to start
    void setParent(Node *); // set Parent node
    void countF();      // add H to G and put in F

//    void openNode(); // TODO - moze jendna funkcja do otwierania wezła?

    nodePosition getPosition(); // return position in struct
    int getH(); // return H
    int getF(); // return F
    int getG(); // return G
    bool getStatusH();  // return statusH (if was set return true)
    bool getStatusG();  // as above but for G

    Node* getParent();  // return pointer to parent node

private:
    nodePosition position; // row and col

    int H; // distance to the end node (do not count the obstacles)
    int G; // distance from start node with awarness of obstacles
    int F; // F + G
    nodePosition parentPosition;

    bool statusH; // if H was settet true, if not false
    bool statusG; // as above but G

    Node *parent;   // pointer to parent node


};

#endif // NODE_H
