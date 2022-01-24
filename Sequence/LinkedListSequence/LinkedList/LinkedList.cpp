//
// Created by fell2 on 12/5/2020.
//

#include <iostream>
#include "LinkedList.h"
#include <stdexcept>

template<typename T>
LinkedList<T>::LinkedList(T *items, int count) {
    if (count > 0) {
        this->head = new Element;
        Element *temp = this->head;

        for (int i = 0; i < count - 1; i++) {
            temp->value = items[i];
            temp->next = new Element;
            temp = temp->next;
        }
        temp->value = items[count - 1];
        temp->next = nullptr;
    }
}

template<typename T>
LinkedList<T>::LinkedList() {
    this->head = nullptr;
    this->count = 0;
}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T> &list) {
    if (list.head == nullptr) {
        count = 0;
        head = nullptr;
    } else {
        count = list.count;
        head = new Element;

        Element *temp1 = head;
        Element *temp2 = list.head;

        while (temp2->next != nullptr) {
            temp1->value = temp2->value;
            temp1->next = new Element;
            temp2 = temp2->next;
            temp1 = temp1->next;
        }
        temp1->value = temp2->value;
        temp1->next = nullptr;
    }
}

template<typename T>
T LinkedList<T>::getFirst() {
    if (this->head == nullptr) {
        throw std::out_of_range("IndexOutOfRange");
    }
    return this->head->value;
}


template<typename T>
T LinkedList<T>::getLast() {
    if (this->head == nullptr) {
        throw std::out_of_range("IndexOutOfRange");
    }

    Element *temp = this->head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    return temp->value;
}

template<typename T>
T LinkedList<T>::get(int index) {
    if (index < 0) {
        throw std::out_of_range("IndexOutOfRange");
    }
    if (this->head == nullptr) {
        throw std::out_of_range("IndexOutOfRange");
    }
    Element *temp = this->head;

    for (int i = 0; i < index; i++) {
        if (temp->next == nullptr) {
            throw std::out_of_range("IndexOutOfRange");
        }
        temp = temp->next;
    }
    return temp->value;
}

template<typename T>
LinkedList<T> *LinkedList<T>::getSubList(int startIndex, int endIndex) {
    if (startIndex >= this->count || startIndex < 0 || endIndex >= this->count || endIndex < 0 ||
        startIndex > endIndex) {
        throw std::out_of_range("IndexOutOfRange");
    }

    const int subArraySize = endIndex - startIndex + 1;
    T *subArray = new T[subArraySize];
    Element *temp = this->head;
    int k = 0;

    for (int i = 0; i < endIndex + 1; i++) {
        if (i >= startIndex) {
            subArray[k] = temp->value;
            k++;
        }
        temp = temp->next;
    }

    return new LinkedList(subArray, subArraySize);
}

template<typename T>
int LinkedList<T>::getLength() {
    int length = 0;
    Element *temp = this->head;

    while (temp != nullptr) {
        length++;
        temp = temp->next;
    }

    return length;
}

template<typename T>
void LinkedList<T>::append(T item) {
    Element *newElem = new Element;
    newElem->value = item;
    newElem->next = this->head;
    this->head = newElem;

    count++;
}

template<typename T>
void LinkedList<T>::prepend(T item) {
    Element *newElem = new Element;
    newElem->value = item;
    newElem->next = nullptr;

    if (this->head != nullptr) {
        Element *temp = this->head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newElem;
    } else {
        this->head = newElem;
    }

    count++;
}

template<typename T>
void LinkedList<T>::insertAt(int index, T item) {
    if (index <= 0 || index >= this->getLength()) {
        throw std::out_of_range("IndexOutOfRange");
    }

    Element *newElem = new Element;
    newElem->value = item;

    if (this->head != nullptr) {
        if (this->head->next != nullptr) {
            Element *temp1 = this->head, *temp2 = this->head->next;
            for (int i = 0; i < index - 1; i++) {
                temp1 = temp1->next;
                temp2 = temp2->next;
            }
            temp1->next = newElem;
            newElem->next = temp2;
        } else {
            this->prepend(item);
        }
    } else {
        newElem->next = nullptr;
        this->head = newElem;
    }
}

template<typename T>
LinkedList<T> *LinkedList<T>::concat(LinkedList<T> *list) {
    Element *temp = this->head;
    T *elemArray = new T[this->getLength() + list->getLength()];
    int i = 0;

    while (temp != nullptr) {
        elemArray[i] = temp->value;
        i++;
        temp = temp->next;
    }
    temp = list->head;
    while (temp != nullptr) {
        elemArray[i] = temp->value;
        i++;
        temp = temp->next;
    }

    return new LinkedList(elemArray, this->getLength() + list->getLength());
}

template<typename T>
T *LinkedList<T>::getItems() {
    if (this->head == nullptr) {
        return nullptr;
    }

    Element *temp = this->head;
    T *items = new T[this->count];
    int i = 0;

    while (temp != nullptr) {
        items[i] = temp->value;
        temp = temp->next;
        i++;
    }

    return items;
}

template<typename T>
void LinkedList<T>::set(int index, T value) {
    if (index < this->getLength()) {
        Element *temp = this->head;
        for (int i = 0; i < index; i++) {
            temp = temp->next;
        }
        temp->value = value;
    }
}
