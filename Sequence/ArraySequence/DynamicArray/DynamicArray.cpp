//
// Created by fell2 on 12/5/2020.
//

#include "DynamicArray.h"
#include <iostream>

template<class T>
DynamicArray<T>::DynamicArray(T *items, int count) {
    this->count = count;
    this->items = new T[count];
    for (int i = 0; i < count; i++) {
        this->items[i] = items[i];
    }
}

template<class T>
DynamicArray<T>::DynamicArray(int count) {
    this->items = new T[count]();
    this->count = count;
}

template<class T>
DynamicArray<T>::DynamicArray(const DynamicArray<T> &dynamicArray) {
    count = dynamicArray.count;
    items = new T[dynamicArray.count];
    for (int i = 0; i < this->count; i++) {
        items[i] = dynamicArray.items[i];
    }
}

template<class T>
DynamicArray<T>::DynamicArray() {
    this->count = 1;
    this->items = new T[this->count]();
}

template<class T>
int DynamicArray<T>::getSize() {
    return this->count;
}

template<class T>
T *DynamicArray<T>::getItems() {
    return this->items;
}

template<class T>
T DynamicArray<T>::get(int index) {
    return this->items[index];
}

template<class T>
void DynamicArray<T>::resize(int newSize) {
    T *temp = new T[newSize];
    int size = (newSize < this->count) ? newSize : this->count;

    for (int i = 0; i < size; i++) {
        temp[i] = this->items[i];
    }

    this->count = newSize;
    delete this->items;
    this->items = temp;
}

template<class T>
void DynamicArray<T>::set(int index, T value) {
    this->items[index] = value;
}

template<class T>
DynamicArray<T> *DynamicArray<T>::getSubArray(int startIndex, int endIndex) {
    if (startIndex >= this->count || startIndex < 0 || endIndex >= this->count || endIndex < 0 ||
        startIndex > endIndex) {
        throw std::out_of_range("IndexOutOfRange");
    }

    const int arraySize = endIndex - startIndex + 1;
    T *array = new T[arraySize];
    int j = 0;

    for (int i = startIndex; i < endIndex + 1; i++) {
        array[j] = this->items[i];
        j++;
    }

    return new DynamicArray(array, arraySize);
}