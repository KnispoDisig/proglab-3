//
// Created by fell2 on 12/5/2020.
//

#ifndef PROGLAB3_ADJMATRIX_H
#define PROGLAB3_ADJMATRIX_H

#include "../Sequence/Sequence.h"
#include "../Sequence/LinkedListSequence/LinkedListSequence.cpp"

class AdjMatrix {
private:
    Sequence<Sequence<unsigned int> *> *matrix;
    int size;

public:
    explicit AdjMatrix(int size);

    AdjMatrix(const AdjMatrix &adjMatrix);

    unsigned int get(int x, int y);

    void set(int x, int y, unsigned int value, bool hasSelfEdge = false);

    int getSize();

    void addLayer();

    void deleteLayer(int index);
};


#endif //PROGLAB3_ADJMATRIX_H
