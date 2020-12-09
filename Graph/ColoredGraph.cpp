//
// Created by fell2 on 12/8/2020.
//

#include "ColoredGraph.h"

AdjMatrix *ColoredGraph::convertToBinaryMatrix(AdjMatrix *adjMatrix) {
    AdjMatrix *newMatrix = new AdjMatrix(*adjMatrix);

    for (int i = 0; i < this->nodeCount(); i++) {
        for (int j = 0; j < this->nodeCount(); j++) {
            if (newMatrix->get(i, j) != 0 || i == j) {
                newMatrix->set(i, j, 1, true);
            }
        }
    }

    return newMatrix;
}


ColoredGraph::ColoredGraph(Graph *graph) {
    // матрица та же самая
    matrix = new AdjMatrix(*graph->getAdjMatrix());

    // имена нодов те же самые
    nodeNames = new LinkedListSequence<string>();
    for (int i = 0; i < graph->nodeCount(); i++) {
        nodeNames->prepend(graph->nodeName(i));
    }

    // список списков интов; индекс этого списка - цвет, элемент - список вершин, отвечающих этому цвету
    Sequence<Sequence<int> *> *coloredNums = reinterpret_cast<Sequence<Sequence<int> *> *>(new LinkedListSequence<LinkedListSequence<int> *>());

    // исключенные вершины (вершины, которые уже покрашены в какой-то цвет)
    Sequence<int> *excludedNodes = new LinkedListSequence<int>();

    // бинарная матрица с единицами на главной диагонали (матрица смежности без весов)
    AdjMatrix *adjMatrix = convertToBinaryMatrix(matrix);

    // начало самого алгоритма
    for (int i = 0; i < adjMatrix->getSize(); i++) {        // i будем считать строкой
        if (excludedNodes->contains(i)) {                   // если вершина уже покрашена, то пропускаем
            continue;
        } else {
            Sequence<unsigned int> *row_i = new LinkedListSequence<unsigned int>();   // получаем i-ю строку
            for (int j = 0; j < adjMatrix->getSize(); j++) {
                row_i->prepend(adjMatrix->get(i, j));
            }

            Sequence<int> *listOfUnicolorous = new LinkedListSequence<int>();   // список вершин одного цвета
            listOfUnicolorous->prepend(i);
            excludedNodes->prepend(i);                                      // вершина i теперь покрашена

            while (!hasAllOnes(row_i)) {
                int indexNotNeighbour = -1;
                for (int j = i + 1; j < row_i->getLength(); j++) {
                    if (row_i->get(j) == 0 && !excludedNodes->contains(j)) {
                        indexNotNeighbour = j;
                        break;
                    }
                }

                if (indexNotNeighbour == -1) {
                    break;
                }

                listOfUnicolorous->prepend(indexNotNeighbour);
                excludedNodes->prepend(indexNotNeighbour);

                Sequence<unsigned int> *row_j = new LinkedListSequence<unsigned int>();
                for (int j = 0; j < adjMatrix->getSize(); j++) {
                    row_j->prepend(adjMatrix->get(indexNotNeighbour, j));
                }

                row_i = binaryAdding(row_i, row_j);            // прибавляем побитово к i-й строке j-ю
            }

            // на этом моменте listOfUnicolorous уже полностью проинициализирован, следовательно можно добавлять его в coloredNums
            coloredNums->prepend(listOfUnicolorous);
        }
    }

    coloredNodes = reinterpret_cast<Sequence<Sequence<std::__cxx11::string> *> *>(new LinkedListSequence<LinkedListSequence<string> *>());
    for (int i = 0; i < coloredNums->getLength(); i++) {
        Sequence<string> *unicolorousSeq = new LinkedListSequence<string>();
        for (int j = 0; j < coloredNums->get(i)->getLength(); j++) {
            unicolorousSeq->prepend(this->nodeName(coloredNums->get(i)->get(j)));
        }
        coloredNodes->prepend(unicolorousSeq);
    }

}

bool ColoredGraph::hasAllOnes(Sequence<unsigned int> *sequence) {
    for (int i = 0; i < sequence->getLength(); i++) {
        if (sequence->get(i) == 0) {
            return false;
        }
    }

    return true;
}

Sequence<unsigned int> *ColoredGraph::binaryAdding(Sequence<unsigned int> *seq1, Sequence<unsigned int> *seq2) {
    if (seq1->getLength() == seq2->getLength()) {
        Sequence<unsigned int> *binSum = new LinkedListSequence<unsigned int>();

        for (int i = 0; i < seq1->getLength(); i++) {
            binSum->prepend(seq1->get(i) || seq2->get(i));
        }

        return binSum;
    } else {
        throw std::invalid_argument("seq1.length != seq2.length");
    }
}

void ColoredGraph::printColors() {
    for (int i = 0; i < coloredNodes->getLength(); i++) {
        std::cout << (i + 1) << " color: \n";
        for (int j = 0; j < coloredNodes->get(i)->getLength(); j++) {
            std::cout << "- " << coloredNodes->get(i)->get(j) << "\n";
        }
        std::cout << "\n";
    }
}
