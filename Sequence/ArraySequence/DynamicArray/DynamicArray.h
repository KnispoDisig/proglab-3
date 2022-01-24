//
// Created by fell2 on 12/5/2020.
//

#ifndef PROGLAB3_DYNAMICARRAY_H
#define PROGLAB3_DYNAMICARRAY_H


template<class T>
class DynamicArray {
private:
    T *items;
    int count{};
public:
    DynamicArray();

    DynamicArray(T *items, int count);

    DynamicArray(int count);

    DynamicArray(const DynamicArray<T> &dynamicArray);

    T get(int index);

    int getSize();

    T *getItems();

    DynamicArray<T> *getSubArray(int startIndex, int endIndex);

    void set(int index, T value);

    void resize(int newSize);

    ~DynamicArray() = default;
};


#endif //PROGLAB3_DYNAMICARRAY_H
