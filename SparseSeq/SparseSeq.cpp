//
// Created by fell2 on 12/9/2020.
//

#include "SparseSeq.h"

template<class T>
SparseSeq<T>::SparseSeq(Sequence<T> *seq, T null, bool (*isNull)(T), bool mapReduceOn) {
    length = seq->getLength();
    this->null = null;
    this->isNull = isNull;

    if (!mapReduceOn) {
        for (int i = 0; i < seq->getLength(); i++) {
            if (!isNull(seq->get(i))) {
                if (storage == nullptr) {
                    storage = new Dictionary<int, T>();
                }
                storage->add(i, seq->get(i));
            }
        }
    } else {
        storage = reduce<Dictionary<int, T> *>(indexing(seq), reducingFunction(isNull));
    }
}

template<class T>
template<typename Q>
Sequence<Q> *SparseSeq<T>::map(Sequence<T> *seq, std::function<Q(T)> f) {
    Sequence<Q> *newSeq = new ArraySequence<Q>();
    for (int i = 0; i < seq->getLength(); i++) {
        newSeq->prepend(f(seq->get(i)));
    }

    return newSeq->getSubsequence(1, newSeq->getLength());
}

template<class T>
template<typename Q>
Q SparseSeq<T>::reduce(Sequence<Q> *seq, std::function<Q(Q, Q)> f) {
    Q result;

    for (int i = 1; i < seq->getLength(); i++) {
        if (i == 1) {
            result = f(seq->get(i - 1), seq->get(i));
        } else {
            result = f(result, seq->get(i));
        }
    }

    return result;
}

template<class T>
SparseSeq<T>::SparseSeq(const SparseSeq<T> &seq) {
    this->storage = new Dictionary<int, T>(*seq.storage);
    this->length = seq.length;
    this->isNull = seq.isNull;
    this->null = seq.null;
}

template<class T>
Sequence<Dictionary<int, T> *> *SparseSeq<T>::indexing(Sequence<T> *seq) {
    Sequence<Dictionary<int, T> *> *result = new ArraySequence<Dictionary<int, T> *>();

    for (int i = 0; i < seq->getLength(); i++) {
        Dictionary<int, T> *dictionary = new Dictionary<int, T>();
        dictionary->add(i, seq->get(i));
        result->prepend(dictionary);
    }

    return result->getSubsequence(1, result->getLength() - 1);

}

template<class T>
std::function<Dictionary<int, T> *(Dictionary<int, T> *, Dictionary<int, T> *)>
SparseSeq<T>::reducingFunction(bool (*isNull)(T)) {
    return [isNull](Dictionary<int, T> *d1, Dictionary<int, T> *d2) {
        if (d2->containsNullValue(isNull)) {
            return d1;
        } else if (d1->containsNullValue(isNull) && !d2->containsNullValue(isNull)) {
            return d2;
        } else {
            return d1->concat(d2);
        }
    };
}

template<class T>
int SparseSeq<T>::getLength() {
    return length;
}

template<class T>
T SparseSeq<T>::get(int index) {
    T elem;
    try {
        elem = storage->get(index);
    } catch (...) {
        elem = null;
    }

    return elem;
}

template<class T>
T SparseSeq<T>::getNull() {
    return null;
}

template<class T>
void SparseSeq<T>::set(int index, T item) {
    if (index >= 0 && index < this->length) {
        if (storage->contains(index)) {
            if (!isNull(item)) {
                storage->updateValue(index, item);
            } else {
                if (storage->getCount() == 1) {
                    storage->remove(index);
                    storage = new Dictionary<int, T>();
                } else {
                    storage->remove(index);
                }
            }
        } else {
            if (!isNull(item)) {
                storage->add(index, item);
            }
        }
    } else {
        throw std::out_of_range("index out of range");
    }
}

template<class T>
Sequence<T> *SparseSeq<T>::toSeq() {
    Sequence<T> *sequence = new LinkedListSequence<T>();

    for (int i = 0; i < length; i++) {
        if (storage->contains(i)) {
            sequence->prepend(storage->get(i));
        } else {
            sequence->prepend(null);
        }
    }

    return sequence;
}

template<class T>
void SparseSeq<T>::prepend(T item) {
    length++;

    if (!isNull(item)) {
        storage->add(length - 1, item);
    }
}

template<class T>
SparseSeq<T>::SparseSeq(int length, T null, bool (*isNull)(T)) {
    this->length = length;
    this->null = null;
    this->isNull = isNull;

    this->storage = new Dictionary<int, T>();
}

template<class T>
SparseSeq<T> *SparseSeq<T>::deleteItem(int index) {
    if (index >= 0 && index < length) {
        SparseSeq<T> *result = new SparseSeq<T>(length - 1, this->null, this->isNull);

        int j = 0;
        for (int i = 0; i < length; i++) {
            if (i != index) {
                result->set(j, this->get(i));
                j++;
            }
        }
        return result;
    } else {
        throw std::out_of_range("index out of range");
    }

}

template<class T>
bool SparseSeq<T>::contains(T item) {
    Sequence<int> *keyList = storage->keyList();

    if (!isNull(item)) {
        for (int i = 0; i < keyList->getLength(); i++) {
            if (storage->get(keyList->get(i)) == item) {
                return true;
            }
        }

        return false;
    } else {
        return keyList->getLength() < length;
    }
}

template<class T>
Sequence<int> *SparseSeq<T>::notNullIndices() {
    return storage->keyList();
}

