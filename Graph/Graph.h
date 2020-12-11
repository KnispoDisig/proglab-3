//
// Created by fell2 on 12/9/2020.
//

#ifndef PROGLAB3_GRAPH_H
#define PROGLAB3_GRAPH_H

#include <string>
#include "../SparseSeq/SparseSeq.cpp"

using namespace std;

class Graph {
protected:
    Sequence<string> *nodeNames;

    Sequence<SparseSeq<unsigned int> *> *matrix;

public:
    Graph();

    explicit Graph(Sequence<SparseSeq<unsigned int> *> *matrix);

    int nodeCount();

    void addNode(string node);

    void removeNode(string node);

    virtual void addEdge(string node1, string node2, unsigned int weight);

    virtual void removeEdge(string node1, string node2);

    bool hasEdge(string node1, string node2);

    Sequence<string> *listOfNodes();

    unsigned int getEdgeWeight(int x, int y);

    void print();    // удалить в конце !!!

    string nodeName(int index);

};


#endif //PROGLAB3_GRAPH_H
