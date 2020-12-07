//
// Created by fell2 on 12/7/2020.
//

#include "UndirGraph.h"

UndirGraph::UndirGraph() {
    matrix = new AdjMatrix(0);
    nodeNames = new LinkedListSequence<string>();
}

void UndirGraph::addEdge(string node1, string node2, unsigned int weight) {
    if (nodeNames->contains(node1) && nodeNames->contains(node2)) {
        if (this->hasEdge(node1, node2)) {
            throw invalid_argument("Edge already exists!");
        } else {
            int x = nodeNames->indexOf(node1);
            int y = nodeNames->indexOf(node2);

            matrix->set(x, y, weight);
            matrix->set(y, x, weight);
        }
    } else {
        throw invalid_argument("No such nodes in graph");
    }
}

void UndirGraph::removeEdge(string node1, string node2) {
    if (nodeNames->contains(node1) && nodeNames->contains(node2) && this->hasEdge(node1, node2)) {
        int x = nodeNames->indexOf(node1);
        int y = nodeNames->indexOf(node2);

        matrix->set(x, y, 0);
        matrix->set(y, x, 0);
    }
}
