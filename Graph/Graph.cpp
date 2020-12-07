//
// Created by fell2 on 12/5/2020.
//

#include "Graph.h"

#include <utility>

Graph::Graph() {
    matrix = new AdjMatrix(0);
    nodeNames = new LinkedListSequence<string>();
}

Graph::Graph(AdjMatrix *matrix) {
    this->matrix = new AdjMatrix(*matrix);
    nodeNames = new LinkedListSequence<string>();
    for (int i = 0; i < this->matrix->getSize(); i++) {
        nodeNames->prepend(to_string(i));
    }
}

int Graph::nodeCount() {
    return matrix->getSize();
}

void Graph::addNode(string node) {
    matrix->addLayer();
    nodeNames->prepend(std::move(node));
}

void Graph::addEdge(string node1, string node2, unsigned int weight) {
    if (nodeNames->contains(node1) && nodeNames->contains(node2)) {
        if (this->hasEdge(node1, node2)) {
            throw invalid_argument("Edge already exists!");
        } else {
            int x = nodeNames->indexOf(node1);
            int y = nodeNames->indexOf(node2);
            matrix->set(x, y, weight);
        }
    } else {
        throw invalid_argument("No such nodes in graph");
    }
}

bool Graph::hasEdge(string node1, string node2) {
    if (nodeNames->contains(node1) && nodeNames->contains(node2)) {
        int x = nodeNames->indexOf(node1);
        int y = nodeNames->indexOf(node2);

        return matrix->get(x, y) != 0;
    } else {
        throw invalid_argument("No such nodes in graph");
    }
}

void Graph::removeNode(string node) {
    int nodeIndex = nodeNames->indexOf(node);

    matrix->deleteLayer(nodeIndex);
    nodeNames = nodeNames->deleteItem(nodeIndex);
}

Sequence<string> *Graph::listOfNodes() {
    return this->nodeNames;
}

string Graph::nodeName(int index) {
    if (index >= 0 && index < nodeNames->getLength()) {
        return nodeNames->get(index);
    } else {
        throw out_of_range("Index out of range");
    }
}

void Graph::print() {
    for (int i = 0; i < nodeCount(); i++) {
        std::cout << nodeNames->get(i) << " is connected with:\n";
        for (int j = 0; j < nodeCount(); j++) {
            if (matrix->get(i, j) != 0) {
                std::cout << "- " << nodeNames->get(j) << ", weight: " << matrix->get(i, j) << "\n";
            }
        }
        std::cout << "\n";
    }
}

void Graph::removeEdge(string node1, string node2) {
    if (nodeNames->contains(node1) && nodeNames->contains(node2) && this->hasEdge(node1, node2)) {
        int x = nodeNames->indexOf(node1);
        int y = nodeNames->indexOf(node2);

        matrix->set(x, y, 0);
    }
}

