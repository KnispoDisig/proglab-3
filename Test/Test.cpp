//
// Created by fell2 on 12/9/2020.
//

#include "Test.h"



//AdjGraph *Test::customGraph() {
//    AdjGraph *graph = new AdjGraph();
//    graph->addNode("");
//}
void Test::success() {
    std::cout << "success\n";
}

void Test::fail() {
    std::cout << "fail\n";
}

Graph *Test::generateGraph() {
    Graph *graph = new Graph();

    graph->addNode("Moscow");
    graph->addNode("Spb");
    graph->addNode("Sochi");
    graph->addNode("Tver");
    graph->addNode("Kgd");

    graph->addEdge("Moscow", "Sochi", 1000);
    graph->addEdge("Moscow", "Spb", 500);
    graph->addEdge("Moscow", "Tver", 800);
    graph->addEdge("Sochi", "Spb", 1400);
    graph->addEdge("Moscow", "Kgd", 1500);
    graph->addEdge("Kgd", "Sochi", 1400);
    graph->addEdge("Sochi", "Moscow", 600);
    graph->addEdge("Spb", "Moscow", 800);

    return graph;
}

bool Test::graphCountNodes() {
    Graph *graph = generateGraph();
    bool test1 = generateGraph()->nodeCount() == 5;

    Graph *empty = new Graph();
    bool test2 = empty->nodeCount() == 0;

    return test1 && test2;
}

bool Test::graphAddNode() {
    Graph *graph = generateGraph();
    graph->addNode("Kemerovo");

    bool test1 = graph->nodeName(5) == "Kemerovo";


    Graph *empty = new Graph();
    empty->addNode("MSK");
    bool test2 = empty->nodeCount() == 1 && empty->nodeName(0) == "MSK";

    return test1 && test2;
}

bool Test::graphRemoveNode() {
    Graph *graph = generateGraph();
    int previousCount = graph->nodeCount();
    graph->removeNode("Moscow");
    bool test1 = previousCount == graph->nodeCount() + 1 && !graph->hasNode("Moscow");

    Graph *empty = new Graph();
    bool test2 = empty->nodeCount() == 0;
    empty->removeNode("Moscow");
    test2 = test2 && empty->nodeCount() == 0;

    return test1 && test2;
}

bool Test::graphAddEdge() {
    Graph *graph = generateGraph();
    graph->addEdge("Kgd", "Tver", 900);
    bool test1 = graph->hasEdge("Kgd", "Tver") && graph->getEdgeWeight(4, 3) == 900;

    Graph *empty = new Graph();
    bool test2;
    try {
        empty->addEdge("Moscow", "Spb", 1000);
    } catch (const std::invalid_argument& ia) {
        test2 = true;
    }

    bool test3;
    try {
        graph->addEdge("Moscow", "Kgd", 900);
    } catch (const std::invalid_argument& ia) {
        test3 = true;
    }

    bool test4;
    try {
        graph->addEdge("Spb", "Sochi", 0);
    } catch (const std::invalid_argument& ia) {
        test4 = true;
    }

    return test4 && test3 && test2 && test1;
}

bool Test::graphRemoveEdge() {
    Graph *graph = generateGraph();

    graph->removeEdge("Moscow", "Sochi");
    bool test1 = !graph->hasEdge("Moscow", "Sochi");

    bool test2;
    try {
        graph->removeEdge("Spb", "Sochi");
    } catch (...) {
        test2 = true;
    }

    return test1 && test2;
}

bool Test::graphListOfNodes() {
    Graph *graph = generateGraph();
    Sequence<string> *sequenceNames = graph->listOfNodes();

    string arrNodes[5] = {"Moscow", "Spb", "Sochi", "Tver", "Kgd"};
    Sequence<string> *nodes = new LinkedListSequence<string>(arrNodes, 5);

    bool test = true;
    for (int i = 0; i < sequenceNames->getLength(); i++) {
        if (nodes->get(i) != sequenceNames->get(i)) {
            test = false;
            break;
        }
    }

    return test;
}

bool Test::graphNodeName() {
    Graph *graph = generateGraph();

    bool test1 = graph->nodeName(0) == "Moscow" && graph->nodeName(1) == "Spb" &&
            graph->nodeName(2) == "Sochi" && graph->nodeName(3) == "Tver" && graph->nodeName(4) == "Kgd";

    bool test2;
    Graph *empty = new Graph();
    try {
        string str = empty->nodeName(0);
    } catch (...) {
        test2 = true;
    }

    return test1 && test2;
}

void Test::testGraph() {
    int countAll = 7;
    int countSuccess = 0;

    std::cout << "\n*** GRAPH TESTING ***\n";

    std::cout << "graphCountNodes test:";
    check(graphCountNodes());
    std::cout << "graphAddNode test:";
    check(graphAddNode());
    std::cout << "graphRemoveNode test:";
    check(graphRemoveNode());
    std::cout << "graphAddEdge test:";
    check(graphAddEdge());
    std::cout << "graphRemoveEdge test:";
    check(graphRemoveEdge());
    std::cout << "graphListOfNodes test:";
    check(graphListOfNodes());
    std::cout << "graphNodeName test:";
    check(graphNodeName());

    countSuccess += graphCountNodes();
    countSuccess += graphAddNode();
    countSuccess += graphRemoveNode();
    countSuccess += graphAddEdge();
    countSuccess += graphRemoveEdge();
    countSuccess += graphListOfNodes();
    countSuccess += graphNodeName();

    std::cout << "______________\n";
    std::cout << countSuccess << " from " << countAll << " successful tests\n";
}

void Test::check(bool test) {
    if (test) {
        success();
    } else {
        fail();
    }
}

bool Test::undirGraphAddEdge() {
    Graph *undir = generateUndirGraph();
    undir->addEdge("Kgd", "Spb", 7);

    bool test1 = undir->hasEdge("Kgd", "Spb") && undir->hasEdge("Spb", "Kgd");

    Graph *empty = new UndirGraph();
    empty->addNode("1");
    empty->addNode("2");
    empty->addEdge("1", "2", 10);
    bool test2 = empty->hasEdge("1", "2") && empty->hasEdge("2", "1");

    return test1 && test2;
}

Graph *Test::generateUndirGraph() {
    Graph *undir = new UndirGraph();

    undir->addNode("Moscow");
    undir->addNode("Spb");
    undir->addNode("Sochi");
    undir->addNode("Tver");
    undir->addNode("Kgd");

    undir->addEdge("Moscow", "Sochi", 1000);
    undir->addEdge("Moscow", "Spb", 500);
    undir->addEdge("Moscow", "Tver", 800);
    undir->addEdge("Sochi", "Spb", 1400);
    undir->addEdge("Moscow", "Kgd", 1500);
    undir->addEdge("Kgd", "Sochi", 1400);

    return undir;
}

bool Test::undirGraphRemoveEdge() {
    Graph *undir = generateUndirGraph();
    undir->removeEdge("Moscow", "Kgd");

    bool test = !undir->hasEdge("Moscow", "Kgd") && !undir->hasEdge("Kgd", "Moscow");

    return test;
}

void Test::testUndirGraph() {
    int countAll = 2;
    int countSuccess = 0;

    countSuccess += undirGraphAddEdge();
    countSuccess += undirGraphRemoveEdge();

    std::cout << "\n*** UNDIRGRAPH TESTING ***\n";

    std::cout << "undirGraphAddEdge test:";
    check(undirGraphAddEdge());
    std::cout << "undirGraphRemoveEdge test:";
    check(undirGraphRemoveEdge());

    std::cout << "______________\n";
    std::cout << countSuccess << " from " << countAll << " successful tests\n";
}

void Test::colorizingTest() {
    UndirGraph *undirGraph = new UndirGraph();
    undirGraph->addNode("1");
    undirGraph->addNode("2");
    undirGraph->addNode("3");
    undirGraph->addNode("4");

    undirGraph->addEdge("1", "2", 1);
    undirGraph->addEdge("2", "3", 1);
    undirGraph->addEdge("2", "4", 1);
    undirGraph->addEdge("4", "3", 1);

    ColorizedGraph *coloredGraph = new ColorizedGraph(undirGraph);

    int color1 = coloredGraph->getColor("1");
    int color2 = coloredGraph->getColor("2");
    int color3 = coloredGraph->getColor("3");
    int color4 = coloredGraph->getColor("4");

    bool test = color2 != color1 && color2 != color3 && color2 != color4 && ((color1 == color4 &&
            color3 != color1) || (color1 == color3 && color4 != color1));

    if (test) {
        std::cout << "colorizing is right\n";
    } else {
        std::cout << "colorizing is wrong\n";
    }
}

void Test::launchAllTests() {
    testGraph();
    testUndirGraph();
    colorizingTest();
}



