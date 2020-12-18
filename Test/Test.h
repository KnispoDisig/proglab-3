//
// Created by fell2 on 12/9/2020.
//

#ifndef PROGLAB3_TEST_H
#define PROGLAB3_TEST_H

#include "../Graph/ColorizedGraph.h"
#include "../SparseSeq/SparseSeq.h"

class Test {
// auxiliary functions
private:
    static void success();

    static void fail();

    static void check(bool test);

    static Graph *generateGraph();

    static Graph *generateUndirGraph();

// test Graph
private:
    static bool graphCreating();

    static bool graphCountNodes();

    static bool graphAddNode();

    static bool graphRemoveNode();

    static bool graphAddEdge();

    static bool graphRemoveEdge();

    static bool graphListOfNodes();

    static bool graphNodeName();

public:

    static void testGraph();

// test UndirGraph
private:
    static bool undirGraphAddEdge();

    static bool undirGraphRemoveEdge();

public:
    static void testUndirGraph();

// test ColoredGraph
public:
    static void colorizingTest();


public:
    static void launchAllTests();
};


#endif //PROGLAB3_TEST_H
