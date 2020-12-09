//
// Created by fell2 on 12/8/2020.
//

#ifndef PROGLAB3_COLOREDGRAPH_H
#define PROGLAB3_COLOREDGRAPH_H

#include "Graph.h"

class ColoredGraph : public Graph {
private:
    Sequence<Sequence<string> *> *coloredNodes;

    AdjMatrix *convertToBinaryMatrix(AdjMatrix *adjMatrix);

    // adding seq2 to seq1
    Sequence<unsigned int> *binaryAdding(Sequence<unsigned int> *seq1, Sequence<unsigned int> *seq2);

    bool hasAllOnes(Sequence<unsigned int> *sequence);

public:
    explicit ColoredGraph(Graph *graph);

    void printColors();
};


#endif //PROGLAB3_COLOREDGRAPH_H
