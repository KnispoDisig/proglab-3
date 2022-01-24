//
// Created by fell2 on 12/9/2020.
//

#include <exception>
#include <iostream>
#include "Dictionary.h"

template<class Key, class Value>
Dictionary<Key, Value>::Dictionary() {
    this->dictionaryTree = nullptr;
}

template<class Key, class Value>
Dictionary<Key, Value>::Dictionary(const Dictionary<Key,Value> &dictionary) {
    Sequence<std::pair<Key, Value>> *sequenceTree = dictionary.dictionaryTree->thread("NLR");

    dictionaryTree = new DictionaryTree<Key, Value>(sequenceTree->get(0).first, sequenceTree->get(0).second);

    for (int i = 1; i < sequenceTree->getLength(); i++) {
        dictionaryTree->add(sequenceTree->get(i).first, sequenceTree->get(i).second);
    }
}

template<class Key, class Value>
Sequence<std::pair<Key, Value>> *Dictionary<Key, Value>::listOfPairs() {
    if (this->isEmpty()) {
        return new LinkedListSequence<std::pair<Key, Value>>();
    } else {
        return dictionaryTree->thread("LNR");
    }
}

template<class Key, class Value>
bool Dictionary<Key, Value>::isEmpty() {
    return dictionaryTree == nullptr;
}

template<class Key, class Value>
Value Dictionary<Key, Value>::get(Key key) {
    if (this->isEmpty()) {
        throw std::exception();
    } else {
        return dictionaryTree->get(key);
    }
}

template<class Key, class Value>
void Dictionary<Key, Value>::add(Key key, Value val) {
    if (this->isEmpty()) {
        dictionaryTree = new DictionaryTree<Key, Value>(key, val);
    } else {
        dictionaryTree->add(key, val);
    }
}

template<class Key, class Value>
bool Dictionary<Key, Value>::contains(Key key) {
    if (this->isEmpty()) {
        return false;
    } else {
        return dictionaryTree->contains(key);
    }
}

template<class Key, class Value>
bool Dictionary<Key, Value>::containsNullValue(bool (*isNull)(Value)) {
    if (this->isEmpty()) {
        return false;
    } else {
        return dictionaryTree->containsNullValue(isNull);
    }
}

template<class Key, class Value>
int Dictionary<Key, Value>::getCount() {
    if (this->isEmpty()) {
        return 0;
    } else {
        return dictionaryTree->size();
    }
}

template<class Key, class Value>
Dictionary<Key, Value> *Dictionary<Key, Value>::concat(Dictionary<Key, Value> *dictionary) {
    if (this->isEmpty()) {
        return dictionary;
    }
    if (dictionary->isEmpty()) {
        return this;
    }

    Sequence<std::pair<Key, Value>> *listOfCommonPairs = dictionaryTree->unitedWith(dictionary->dictionaryTree)->thread("NLR");
    Dictionary<Key, Value> *newDictionary = new Dictionary<Key, Value>();

    for (int i = 0; i < listOfCommonPairs->getLength(); i++) {
        Key key = listOfCommonPairs->get(i).first;
        Value value = listOfCommonPairs->get(i).second;
        newDictionary->add(key, value);
    }

    return newDictionary;
}

template<class Key, class Value>
void Dictionary<Key, Value>::updateValue(Key key, Value newValue) {
    if (this->isEmpty()) {
        std::cout << "Dictionary is empty\n";
        throw std::exception();
    } else {
        dictionaryTree->updateValue(key, newValue);
    }
}

template<class Key, class Value>
Sequence<Key> *Dictionary<Key, Value>::keyList() {
    if (this->isEmpty()) {
        return new LinkedListSequence<Key>();
    } else {
        return dictionaryTree->keyList();
    }
}

template<class Key, class Value>
void Dictionary<Key, Value>::remove(Key key) {
    if (this->isEmpty()) {
        std::cout << "Empty dictionary\n";
        throw std::exception();
    } else {
        dictionaryTree->remove(key);
    }
}
