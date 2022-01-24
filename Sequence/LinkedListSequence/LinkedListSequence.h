//
// Created by fell2 on 12/5/2020.
//
#pragma once
#ifndef PROGLAB3_LINKEDLISTSEQUENCE_H
#define PROGLAB3_LINKEDLISTSEQUENCE_H


#include "../Sequence.h"
#include "LinkedList/LinkedList.cpp"

template<class T>
class LinkedListSequence : public Sequence<T> {
private:
    LinkedList<T> *list;
public:
    LinkedListSequence(T *items, int count);

    LinkedListSequence();

    LinkedListSequence(const LinkedListSequence<T> &linkedList);

    int getLength() const override;

    T getFirst() const override;

    T getLast() const override;

    T get(const int i) const override;

    Sequence<T> *getSubsequence(const int startIndex, const int endIndex) const override;

    void append(T value) override;

    void prepend(T value) override;

    virtual void set(int index, T value) override;

    void insertAt(const int index, T value) override;

    Sequence<T> *concat(Sequence<T> *list) override;

    bool contains(T item) override;

    int indexOf(T item) override;

    Sequence<T> *deleteItem(int index) override;

    ~LinkedListSequence() = default;
};


#endif //PROGLAB3_LINKEDLISTSEQUENCE_H
