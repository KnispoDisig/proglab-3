//
// Created by fell2 on 12/8/2020.
//

#include "ColorizedGraph.h"

bool intIsNull(unsigned int n) {
    return n == 0;
}

bool boolIsNull(bool b) {
    return !b;
}

ColorizedGraph::ColorizedGraph(UndirGraph *graph) {
    // матрица та же самая
    matrix = new LinkedListSequence<SparseSeq<unsigned int> *>();
    for (int i = 0; i < graph->nodeCount(); i++) {
        SparseSeq<unsigned int> *row = new SparseSeq<unsigned int>(graph->nodeCount(), 0, intIsNull);
        for (int j = 0; j < graph->nodeCount(); j++) {
            row->set(j, graph->getEdgeWeight(i, j));
        }

        matrix->prepend(row);
    }

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
    Sequence<SparseSeq<bool> *> *binMatrix = convertToBinaryMatrix(matrix);
    int n = binMatrix->getLength();

    // начало самого алгоритма
    for (int i = 0; i < binMatrix->getLength(); i++) {                          // i будем считать строкой
        if (excludedNodes->contains(i)) {                                       // если вершина уже покрашена, то пропускаем
            continue;
        } else {
            Sequence<bool> *row_i = binMatrix->get(i)->toSeq();                 // получаем i-ю строку

            Sequence<int> *listOfUnicolorous = new LinkedListSequence<int>();   // список вершин одного цвета
            listOfUnicolorous->prepend(i);
            excludedNodes->prepend(i);                                          // вершина i теперь вычеркнута

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

                Sequence<bool> *row_j = binMatrix->get(indexNotNeighbour)->toSeq();

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

bool ColorizedGraph::hasAllOnes(Sequence<bool> *sequence) {
    for (int i = 0; i < sequence->getLength(); i++) {
        if (!sequence->get(i)) {
            return false;
        }
    }

    return true;
}

Sequence<bool> *ColorizedGraph::binaryAdding(Sequence<bool> *seq1, Sequence<bool> *seq2) {
    if (seq1->getLength() == seq2->getLength()) {
        Sequence<bool> *binSum = new LinkedListSequence<bool>();

        for (int i = 0; i < seq1->getLength(); i++) {
            binSum->prepend(seq1->get(i) || seq2->get(i));
        }

        return binSum;
    } else {
        throw std::invalid_argument("seq1.length != seq2.length");
    }
}

Sequence<SparseSeq<bool> *> *ColorizedGraph::convertToBinaryMatrix(Sequence<SparseSeq<unsigned int> *> *matrix) {
    Sequence<SparseSeq<bool> *> *binMatrix = new LinkedListSequence<SparseSeq<bool> *>();

    for (int i = 0; i < matrix->getLength(); i++) {
        SparseSeq<bool> *row = new SparseSeq<bool>(matrix->getLength(), false, boolIsNull);
        for (int j = 0; j < matrix->getLength(); j++) {
            if (i == j) {
                row->set(j, true);
            } else {
                row->set(j, matrix->get(i)->get(j) > 0);
            }
        }

        binMatrix->prepend(row);
    }

    return binMatrix;
}

int ColorizedGraph::getColor(string node) {
    if (nodeNames->contains(node)) {
        for (int i = 0; i < coloredNodes->getLength(); i++) {
            if (coloredNodes->get(i)->contains(node)) {
                return i + 1;
            }
        }
    } else {
        return -1;
    }
}

Sequence<Sequence<string> *> *ColorizedGraph::getColoredNodes() {
    return this->coloredNodes;
}
