#include <iostream>
#include "Graph/ColoredGraph.h"
//#include "SparseSeq/SparseSeq.cpp"

//void printMatrix(AdjMatrix *matrix) {
//    for (int j = 0; j < matrix->getSize(); j++) {
//        for (int i = 0; i < matrix->getSize(); i++) {
//            unsigned int elem = matrix->get(i, j);
//            std::cout << std::setw(3) << elem << " ";
//        }
//        std::cout << "\n";
//    }
//}
void line() {
    for (int i = 0; i < 20; i++) {
        std::cout << "_";
    }
    std::cout << "\n";
}

void printIntSeq(Sequence<int> *seq) {
    for (int i = 0; i < seq->getLength(); i++) {
        std::cout << seq->get(i) << " ";
    }
    std::cout << "\n";
}

bool intIsNull(int n) {
    return n == 0;
}


int main() {
    UndirGraph *graph = new UndirGraph();
    graph->addNode("MSK");
    graph->addNode("SPB");
    graph->addEdge("MSK", "SPB", 10);

    graph->addNode("ANP");
    graph->addNode("BCH");
    graph->addEdge("ANP", "BCH", 20);
    graph->addEdge("ANP", "MSK", 70);
    graph->addEdge("MSK", "BCH", 1);

    graph->print();
    line();

    ColoredGraph *colored = new ColoredGraph(graph);
    std::cout << colored->getColor("BCH") << "\n";
    colored->printColors();

}
