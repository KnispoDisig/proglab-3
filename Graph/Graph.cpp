//
// Created by fell2 on 12/9/2020.
//

#include "Graph.h"

bool isNull(unsigned int n) {
    return n == 0;
}

Graph::Graph() {
    nodeNames = new LinkedListSequence<string>();
    matrix = new LinkedListSequence<SparseSeq<unsigned int> *>();
}

//Graph::Graph(Sequence<SparseSeq<unsigned int> *> *matrix) {
//    this->matrix = new LinkedListSequence<SparseSeq<unsigned int> *>();
//    nodeNames = new LinkedListSequence<string>();
//
//    for (int i = 0; i < matrix->getLength(); i++) {
//        SparseSeq<unsigned int> *copySeq = new SparseSeq<unsigned int>(*(matrix->get(i)));
//        this->matrix->prepend(copySeq);
//
//        nodeNames->prepend(to_string(i));
//    }
//}

int Graph::nodeCount() {
    return this->matrix->getLength();
}

void Graph::addNode(string node) {
    if (!nodeNames->contains(node)) {
        nodeNames->prepend(node);

        for (int i = 0; i < matrix->getLength(); i++) {
            matrix->get(i)->prepend(0);
        }

        SparseSeq<unsigned int> *addedLine = new SparseSeq<unsigned int>(matrix->getLength() + 1, 0, isNull);
        matrix->prepend(addedLine);
    } else {
        throw invalid_argument("there is node in graph with such name already");
    }
}

void Graph::removeNode(string node) {
    if (nodeCount() != 0) {
        if (nodeNames->contains(node)) {
            int nodeIndex = nodeNames->indexOf(node);
            nodeNames = nodeNames->deleteItem(nodeIndex);

            matrix = matrix->deleteItem(nodeIndex);

            for (int i = 0; i < matrix->getLength(); i++) {
                matrix->set(i, matrix->get(i)->deleteItem(nodeIndex));
            }
        }
    }
}

void Graph::addEdge(string node1, string node2, unsigned int weight) {
    if (nodeNames->contains(node1) && nodeNames->contains(node2)) {
        if (this->hasEdge(node1, node2)) {
            throw invalid_argument("Edge already exists!");
        } else if (weight == 0) {
            throw invalid_argument("weight == 0");
        } else {
            int x = nodeNames->indexOf(node1);
            int y = nodeNames->indexOf(node2);
            matrix->get(x)->set(y, weight);
        }
    } else {
        throw invalid_argument("No such nodes in graph");
    }
}

void Graph::removeEdge(string node1, string node2) {
    if (nodeNames->contains(node1) && nodeNames->contains(node2) && this->hasEdge(node1, node2)) {
        int x = nodeNames->indexOf(node1);
        int y = nodeNames->indexOf(node2);

        SparseSeq<unsigned int> *newRow = new SparseSeq<unsigned int>(*matrix->get(x));
        newRow->set(y, 0);
        matrix->set(x, newRow);
    } else {
        throw std::exception();
    }
}

bool Graph::hasEdge(string node1, string node2) {
    int x = nodeNames->indexOf(node1);
    int y = nodeNames->indexOf(node2);

    return matrix->get(x)->get(y) != 0;
}

string Graph::nodeName(int index) {
    return nodeNames->get(index);
}

unsigned int Graph::getEdgeWeight(int x, int y) {
    return matrix->get(x)->get(y);
}

bool Graph::hasNode(string node) {
    return this->nodeNames->contains(node);
}

Sequence<string> *Graph::listOfNodes() {
    Sequence<string> *result = new LinkedListSequence<string>();
    for (int i = 0; i < nodeCount(); i++) {
        result->prepend(nodeName(i));
    }

    return result;
}

Sequence<string> *Graph::getNeighbours(string nodeName) {
    if (nodeNames->contains(nodeName)) {
        Sequence<string> *result = new LinkedListSequence<string>();
        int index = nodeNames->indexOf(nodeName);

        SparseSeq<unsigned int> *neighbours = matrix->get(index);

        for (int i = 0; i < neighbours->getLength(); i++) {
            if (neighbours->get(i) != 0) {
                result->prepend(nodeNames->get(i));
            }
        }

        return result;
    } else {
        throw std::exception();
    }
}


