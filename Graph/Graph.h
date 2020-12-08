//
// Created by fell2 on 12/5/2020.
//

#ifndef PROGLAB3_GRAPH_H
#define PROGLAB3_GRAPH_H

#include "../Matrix/AdjMatrix.h"
using namespace std;

class Graph {
protected:
    Sequence<string> *nodeNames;

    AdjMatrix *matrix;
public:
    Graph();

    explicit Graph(AdjMatrix *matrix);

    int nodeCount();

    void addNode(string node);

    void removeNode(string node);

    virtual void addEdge(string node1, string node2, unsigned int weight);

    virtual void removeEdge(string node1, string node2);

    bool hasEdge(string node1, string node2);

    Sequence<string> *listOfNodes();

    void print();

    string nodeName(int index);

    AdjMatrix *getAdjMatrix();

};


#endif //PROGLAB3_GRAPH_H
