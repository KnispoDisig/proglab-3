//
// Created by fell2 on 12/7/2020.
//

#include "UndirGraph.h"


UndirGraph::UndirGraph() {
    matrix = new LinkedListSequence<SparseSeq<unsigned int> *>();
    nodeNames = new LinkedListSequence<string>();
}

void UndirGraph::addEdge(string node1, string node2, unsigned int weight) {
    if (nodeNames->contains(node1) && nodeNames->contains(node2)) {
        if (this->hasEdge(node1, node2)) {
            throw invalid_argument("Edge already exists!");
        } else if (weight == 0) {
            throw invalid_argument("weight == 0");
        } else {
            int x = nodeNames->indexOf(node1);
            int y = nodeNames->indexOf(node2);
            matrix->get(x)->set(y, weight);
            matrix->get(y)->set(x, weight);
        }
    } else {
        throw invalid_argument("No such nodes in graph");
    }
}

void UndirGraph::removeEdge(string node1, string node2) {
    if (nodeNames->contains(node1) && nodeNames->contains(node2) && this->hasEdge(node1, node2)) {
        int x = nodeNames->indexOf(node1);
        int y = nodeNames->indexOf(node2);

        SparseSeq<unsigned int> *newRow1 = new SparseSeq<unsigned int>(*matrix->get(x));
        newRow1->set(y, 0);
        matrix->set(x, newRow1);

        SparseSeq<unsigned int> *newRow2 = new SparseSeq<unsigned int>(*matrix->get(y));
        newRow2->set(x, 0);
        matrix->set(y, newRow2);
    }
}
