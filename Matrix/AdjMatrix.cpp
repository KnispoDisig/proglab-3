//
// Created by fell2 on 12/5/2020.
//

#include "AdjMatrix.h"

AdjMatrix::AdjMatrix(int size) {
    if (size >= 0) {
        this->size = size;

        Sequence<unsigned int> *rows;   // нулевая строка
        unsigned int arr[size];
        for (int i = 0; i < size; i++) {
            arr[i] = 0;
        }
        rows = new LinkedListSequence<unsigned int>(arr, size);

        matrix = reinterpret_cast<Sequence<Sequence<unsigned int> *> *>(new LinkedListSequence<LinkedListSequence<unsigned int> *>());
        for (int i = 0; i < size; i++) {
            matrix->prepend(rows);
        }
    } else {
        throw std::invalid_argument("size of matrix is less than 0");
    }
}

unsigned int AdjMatrix::get(int x, int y) {
    if (x >= 0 && y >= 0) {
        return matrix->get(x)->get(y);
    } else {
        throw std::invalid_argument("negative arguments x or y");
    }
}

void AdjMatrix::set(int x, int y, unsigned int value, bool hasSelfEdge) {
    if (x >= 0 && y >= 0) {
        if (!hasSelfEdge) {
            if (x != y) {
                Sequence<unsigned int> *copy = matrix->get(x);
                Sequence<unsigned int> *newRow = new LinkedListSequence<unsigned int>();
                for (int i = 0; i < copy->getLength(); i++) {
                    newRow->prepend(copy->get(i));
                }
                newRow->set(y, value);

                matrix->set(x, newRow);
            }
        } else {
            Sequence<unsigned int> *copy = matrix->get(x);
            Sequence<unsigned int> *newRow = new LinkedListSequence<unsigned int>();
            for (int i = 0; i < copy->getLength(); i++) {
                newRow->prepend(copy->get(i));
            }
            newRow->set(y, value);

            matrix->set(x, newRow);
        }
    } else {
        throw std::invalid_argument("negative arguments x or y");
    }
}

int AdjMatrix::getSize() {
    return this->size;
}

void AdjMatrix::addLayer() {
    Sequence<Sequence<unsigned int> *> *newMatrix = reinterpret_cast<Sequence<Sequence<unsigned int> *> *>(new LinkedListSequence<LinkedListSequence<unsigned int> *>());
    for (int i = 0; i < size; i++) {
        Sequence<unsigned int> *copyRow = new LinkedListSequence<unsigned int>();
        Sequence<unsigned int> *rowPointer = matrix->get(i);
        for (int j = 0; j < size; j++) {
            copyRow->prepend(rowPointer->get(j));
        }
        copyRow->prepend(0);
        newMatrix->prepend(copyRow);
    }

    unsigned int nulArr[size + 1];
    for (int i = 0; i < size + 1; i++) {
        nulArr[i] = 0;
    }

    newMatrix->prepend(new LinkedListSequence<unsigned int>(nulArr, size + 1));

    matrix = newMatrix;
    this->size++;
}

AdjMatrix::AdjMatrix(const AdjMatrix &adjMatrix) {
    matrix = reinterpret_cast<Sequence<Sequence<unsigned int> *> *>(new LinkedListSequence<LinkedListSequence<unsigned int> *>());
    size = adjMatrix.size;

    for (int i = 0; i < adjMatrix.size; i++) {
        Sequence<unsigned int> *rowPointer = adjMatrix.matrix->get(i);
        Sequence<unsigned int> *newRow = new LinkedListSequence<unsigned int>();
        for (int j = 0; j < adjMatrix.size; j++) {
            newRow->prepend(rowPointer->get(j));
        }
        matrix->prepend(newRow);
    }
}

void AdjMatrix::deleteLayer(int index) {
    if (this->getSize() == 0) {
        return;
    }

    if (index < 0 || index >= this->getSize()) {
        throw std::out_of_range("index out of range");
    }

    Sequence<Sequence<unsigned int> *> *newMatrix = reinterpret_cast<Sequence<Sequence<unsigned int> *> *>(new LinkedListSequence<LinkedListSequence<unsigned int> *>());
    for (int i = 0; i < this->getSize(); i++) {
        if (i != index) {
            Sequence<unsigned int> *rowPtr = matrix->get(i);
            Sequence<unsigned int> *newRow = new LinkedListSequence<unsigned int>();
            for (int j = 0; j < rowPtr->getLength(); j++) {
                if (j != index) {
                    newRow->prepend(rowPtr->get(j));
                }
            }
            newMatrix->prepend(newRow);
        }
    }

    this->matrix = newMatrix;
    this->size--;
}
