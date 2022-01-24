//
// Created by fell2 on 12/9/2020.
//

#ifndef PROGLAB3_SPARSESEQ_H
#define PROGLAB3_SPARSESEQ_H


#include <functional>
#include "Dictionary/Dictionary.cpp"
#include "../Sequence/ArraySequence/ArraySequence.cpp"

template<class T>
class SparseSeq {
private:
    Dictionary<int, T> *storage = nullptr;
    int length{};
    T null;
    bool (*isNull)(T);

    template<typename Q>
    Sequence<Q> *map(Sequence<T> *seq, std::function<Q(T)> f);

    template<typename Q>
    Q reduce(Sequence<Q>* seq, std::function<Q(Q, Q)> f);

    // работает как map, только именно для данной задачи
    // мы не можем использовать map, так как map предполагает
    // что функция, передаваемая в качестве параметра является чистой, что в данной задаче не может быть реализовано
    // вследствие необходимости знать индекс элемента в последовательности
    Sequence<Dictionary<int, T>*> *indexing(Sequence<T> *seq);

    static std::function<Dictionary<int, T>*(Dictionary<int, T>*, Dictionary<int, T>*)> reducingFunction(bool (*isNull)(T));

public:

    SparseSeq(Sequence<T> *seq, T null, bool (*isNull)(T), bool mapReduceOn = false);

    SparseSeq(const SparseSeq<T> &seq);

    SparseSeq(int length, T null, bool (*isNull)(T));   // вектор длины length заполненный нулями

    int getLength();

    T get(int index);

    void set(int index, T item);

    SparseSeq<T> *deleteItem(int index);

    bool contains(T item);

    void prepend(T item);

    Sequence<int> *notNullIndices();

    Sequence<T> *toSeq();

    T getNull();
};


#endif //PROGLAB3_SPARSESEQ_H
