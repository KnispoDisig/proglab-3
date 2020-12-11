//
// Created by fell2 on 12/8/2020.
//

#ifndef PROGLAB3_COLOREDGRAPH_H
#define PROGLAB3_COLOREDGRAPH_H

#include "UndirGraph.h"


class ColoredGraph : public UndirGraph {
private:

    Sequence<Sequence<string> *> *coloredNodes;

    static Sequence<SparseSeq<bool> *> *convertToBinaryMatrix(Sequence<SparseSeq<unsigned int> *> *matrix);

    // adding seq2 to seq1
    static Sequence<bool> *binaryAdding(Sequence<bool> *seq1, Sequence<bool> *seq2);

    static bool hasAllOnes(Sequence<bool> *sequence);

public:
    explicit ColoredGraph(UndirGraph *graph);

    int getColor(string node);

    void printColors();
};


#endif //PROGLAB3_COLOREDGRAPH_H
