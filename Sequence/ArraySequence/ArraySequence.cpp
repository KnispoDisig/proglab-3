//
// Created by fell2 on 12/5/2020.
//

#include "ArraySequence.h"
#include "DynamicArray/DynamicArray.cpp"

template<class T>
ArraySequence<T>::ArraySequence(T *items, int count) {
    this->array = new DynamicArray<T>(items, count);
}

template<class T>
ArraySequence<T>::ArraySequence() {
    this->array = new DynamicArray<T>();
}

template<class T>
ArraySequence<T>::ArraySequence(const ArraySequence<T> &arraySequence) {
    T* temp = new T[arraySequence.getLength()];
    for (int i = 0; i < arraySequence.getLength(); i++) {
        temp[i] = arraySequence.get(i);
    }
    array = new DynamicArray<T>(temp, arraySequence.getLength());
}

template<class T>
int ArraySequence<T>::getLength() const {
    return this->array->getSize();
}

template<class T>
T ArraySequence<T>::getFirst() const {
    return this->array->get(0);
}

template<class T>
T ArraySequence<T>::getLast() const {
    return this->array->get(this->getLength() - 1);
}

template<class T>
T ArraySequence<T>::get(const int i) const {
    return this->array->get(i);
}

template<class T>
Sequence<T> *ArraySequence<T>::getSubsequence(const int startIndex, const int endIndex) const {
    const int arraySize = endIndex - startIndex + 1;
    DynamicArray<T> *newArray = this->array->getSubArray(startIndex, endIndex);

    return new ArraySequence(newArray->getItems(), arraySize);
}

template<class T>
void ArraySequence<T>::append(T item) {
    this->array->resize(this->getLength() + 1);
    for (int i = this->getLength() - 1; i > 0; i--) {
        this->array->set(i, this->array->get(i - 1));
    }
    this->array->set(0, item);
}

template<class T>
void ArraySequence<T>::prepend(T item) {
    this->array->resize(this->getLength() + 1);
    this->array->set(this->getLength() - 1, item);
}

template<class T>
void ArraySequence<T>::insertAt(const int index, T value) {
    this->array->resize(this->getLength() + 1);
    for (int i = this->getLength() - 2; i >= index; i--) {
        this->array->set(i + 1, this->array->get(i));
    }
    this->array->set(index, value);
}

template<class T>
Sequence<T> *ArraySequence<T>::concat(Sequence<T> *sequence) {
    const int arraySize = this->getLength() + sequence->getLength();
    T *tempArray = new T[arraySize];
    int j = 0;

    for (int i = 0; i < this->getLength(); i++) {
        tempArray[j] = this->array->get(i);
        j++;
    }
    for (int i = 0; i < sequence->getLength(); i++) {
        tempArray[j] = sequence->get(i);
        j++;
    }

    return new ArraySequence(tempArray, arraySize);
}

//template<class T>
//void ArraySequence<T>::print() {
//    this->array->print();
//}

template<class T>
void ArraySequence<T>::set(int index, T value) {
    this->array->set(index, value);
}

template<class T>
bool ArraySequence<T>::contains(T item) {
    for (int i = 0; i < this->getLength(); i++) {
        if (this->get(i) == item) {
            return true;
        }
    }

    return false;
}

template<class T>
int ArraySequence<T>::indexOf(T item) {
    if (this->contains(item)) {
        for (int i = 0; i < array->getSize(); i++) {
            if (array->get(i) == item) {
                return i;
            }
        }
    } else {
        throw std::exception();
    }
}

template<class T>
Sequence<T> *ArraySequence<T>::deleteItem(int index) {
    int newArr[this->getLength() - 1];
    for (int i = 0; i < this->getLength(); i++) {
        if (i != index) {
            newArr[i] = this->get(i);
        }
    }

    return new ArraySequence<T>(newArr, this->getLength() - 1);
}

