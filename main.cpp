#include <iostream>
#include <iomanip>
#include "Matrix/AdjMatrix.h"
#include "Sequence/Sequence.h"
#include "Graph/Graph.h"
#include "Graph/UndirGraph.h"
#include "Graph/ColoredGraph.h"

void printMatrix(AdjMatrix *matrix) {
    for (int j = 0; j < matrix->getSize(); j++) {
        for (int i = 0; i < matrix->getSize(); i++) {
            unsigned int elem = matrix->get(i, j);
            std::cout << std::setw(3) << elem << " ";
        }
        std::cout << "\n";
    }
}

void printIntSeq(Sequence<int> *seq) {
    for (int i = 0; i < seq->getLength(); i++) {
        std::cout << seq->get(i) << " ";
    }
    std::cout << "\n";
}


int main() {
    Graph *graph = new UndirGraph();
    graph->addNode("Moscow");
    graph->addNode("SPB");
//    graph->addNode("Anapa");
    graph->addNode("BCHT");

    graph->addEdge("Moscow", "SPB", 1000);
    graph->addEdge("Moscow", "BCHT", 3500);
//    graph->addEdge("SPB", "Anapa", 2000);
//    graph->addEdge("BCHT", "Anapa", 4000);
//    graph->addEdge("Moscow", "Anapa", 1000);
    graph->addEdge("BCHT", "SPB", 100);

    ColoredGraph *coloredGraph = new ColoredGraph(graph);

    coloredGraph->printColors();
}
