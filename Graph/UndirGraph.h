//
// Created by fell2 on 12/7/2020.
//

#ifndef PROGLAB3_UNDIRGRAPH_H
#define PROGLAB3_UNDIRGRAPH_H

#include "Graph.h"

class UndirGraph : public Graph {
public:
    UndirGraph();

    void addEdge(string node1, string node2, unsigned int weight) override;

    void removeEdge(string node1, string node2) override;
};


#endif //PROGLAB3_UNDIRGRAPH_H
