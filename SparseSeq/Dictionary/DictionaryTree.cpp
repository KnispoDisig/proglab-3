//
// Created by fell2 on 12/9/2020.
//

#include <iostream>
#include "DictionaryTree.h"

template<class Key, class Value>
DictionaryTree<Key, Value>::DictionaryTree(Key k, Value v) {
    selfKey = k;
    value = v;
    left = nullptr;
    right = nullptr;
}

template<class Key, class Value>
bool DictionaryTree<Key, Value>::isEmpty() {
    return this == nullptr;
}

template<class Key, class Value>
void DictionaryTree<Key, Value>::add(Key k, Value val) {
    if (this->selfKey > k) {
        if (this->left->isEmpty()) {
            this->left = new DictionaryTree<Key, Value>(k, val);
        } else {
            this->left->add(k, val);
        }
    } else if (this->selfKey < k) {
        if (this->right->isEmpty()) {
            this->right = new DictionaryTree<Key, Value>(k, val);
        } else {
            this->right->add(k, val);
        }
    } else {
        std::cout << "Key " << k << " already exist\n\n";
    }
}

template<class Key, class Value>
bool DictionaryTree<Key, Value>::contains(Key key) {
    DictionaryTree<Key, Value> *temp = this;

    if (temp == nullptr) {
        return false;
    }

    if (temp->selfKey == key) {
        return true;
    } else if (temp->selfKey > key) {
        return temp->left->contains(key);
    } else {
        return temp->right->contains(key);
    }

}

template<class Key, class Value>
bool DictionaryTree<Key, Value>::isLeaf() {
    return this->left == nullptr && this->right == nullptr;
}

template<class Key, class Value>
Value DictionaryTree<Key, Value>::get(Key key) {
    if (this->contains(key)) {
        DictionaryTree<Key, Value> *temp = this;

        if (temp->selfKey == key) {
            return temp->value;
        } else if (temp->selfKey > key) {
            return temp->left->get(key);
        } else {
            return temp->right->get(key);
        }
    } else {
        throw std::exception();
    }
}

template<class Key, class Value>
bool DictionaryTree<Key, Value>::hasLeft() {
    return this->left != nullptr;
}

template<class Key, class Value>
Sequence<std::pair<Key, Value>> *DictionaryTree<Key, Value>::toSeq() {
    return this->thread("NLR");
}

template<class Key, class Value>
bool DictionaryTree<Key, Value>::hasRight() {
    return this->right != nullptr;
}

template<class Key, class Value>
int DictionaryTree<Key, Value>::size() {
    return this->toSeq()->getLength();
}

template<class Key, class Value>
DictionaryTree<Key, Value> *DictionaryTree<Key, Value>::unitedWith(DictionaryTree<Key, Value> *tree1) {
    if (this->isEmpty()) {
        return tree1;
    }
    if (tree1->isEmpty()) {
        return this;
    }

    bool this_is_Node = rand() > (RAND_MAX / 2);

    if (this_is_Node) {
        DictionaryTree<Key, Value> *tree = this->right->unitedWith(tree1);
        this->right = tree;
        return this;
    } else {
        DictionaryTree<Key, Value> *tree = this->unitedWith(tree1->left);
        tree1->left = tree;
        return tree1;
    }
}

template<class Key, class Value>
bool DictionaryTree<Key, Value>::containsNullValue(bool (*isNull)(Value)) {
    Sequence<std::pair<Key, Value>> *sequenceTree = this->toSeq();

    for (int i = 0; i < sequenceTree->getLength(); i++) {
        if (isNull((sequenceTree->get(i)).second)) {
            return true;
        }
    }

    return false;
}

template<class Key, class Value>
Sequence<Key> *DictionaryTree<Key, Value>::keyList() {
    Sequence<std::pair<Key, Value>> *sequenceTree = this->toSeq();
    Sequence<Key> *keyList = new LinkedListSequence<Key>();

    for (int i = 0; i < sequenceTree->getLength(); i++) {
        keyList->prepend(sequenceTree->get(i).first);
    }

    return keyList;
}

template<class Key, class Value>
void DictionaryTree<Key, Value>::updateValue(Key key, Value newValue) {
    if (this->contains(key)) {
        if (this->selfKey == key) {
            this->value = newValue;
        } else if (this->selfKey > key) {
            this->left->updateValue(key, newValue);
        } else {
            this->right->updateValue(key, newValue);
        }

    } else {
        std::cout << "There's no such key\n";
        throw std::exception();
    }
}

template<class Key, class Value>
Sequence<std::pair<Key, Value>> *DictionaryTree<Key, Value>::thread(std::string order) {
    if (order.size() != 3 && !(order.find('L') != std::string::npos &&
                               order.find('R') != std::string::npos && order.find('N') != std::string::npos)) {
        std::cout << "INVALID ORDER: invalid order for threading, use L, N, R parameters\n";
        throw std::exception();
    }

    Sequence<std::pair<Key, Value>> *sequenceTree = new LinkedListSequence<std::pair<Key, Value>>();

    if (this->isLeaf()) {
        std::pair<Key, Value> item;
        item.first = this->selfKey;
        item.second = this->value;
        sequenceTree->prepend(item);
        return sequenceTree;
    }

    for (int i = 0; i < 3; i++) {
        if (order[i] == 'N') {
            std::pair<Key, Value> item;
            item.first = this->selfKey;
            item.second = this->value;
            sequenceTree->prepend(item);
        } else if (order[i] == 'L' && this->hasLeft()) {
            sequenceTree = sequenceTree->concat(this->left->thread(order));
        } else if (order[i] == 'R' && this->hasRight()) {
            sequenceTree = sequenceTree->concat(this->right->thread(order));
        }
    }

    return sequenceTree;
}

template<class Key, class Value>
DictionaryTree<Key, Value> *DictionaryTree<Key, Value>::minTree() {
    DictionaryTree<Key, Value> *temp = this;

    if (temp->hasLeft()) {
        while (temp->hasLeft()) {
            temp = temp->left;
        }
        return temp;
    } else {
        return this;
    }
}

template<class Key, class Value>
DictionaryTree<Key, Value> *DictionaryTree<Key, Value>::getTreeByKey(Key key) {
    if (this->contains(key)) {
        DictionaryTree<Key, Value> *ptr = this;

        while (ptr->selfKey != key) {
            if (ptr->selfKey > key) {
                ptr = ptr->left;
            } else {
                ptr = ptr->right;
            }
        }

        return ptr;
    } else {
        return nullptr;
    }
}

template<class Key, class Value>
void DictionaryTree<Key, Value>::remove(Key key) {
    if (this->contains(key)) {
        DictionaryTree<Key, Value> *target = this->getTreeByKey(key);
        DictionaryTree<Key, Value> *parent = this->getParent(key);
        bool isLeftChild = parent != nullptr && parent->hasLeft() && parent->left->selfKey == target->selfKey;   // является ли target левым ребенком parent'а

        if (target->isLeaf()) {
            if (parent != nullptr) {
                if (isLeftChild) {
                    parent->left = nullptr;
                } else {
                    parent->right = nullptr;
                }
                delete target;
            } else {
                delete this;
            }
        } else if (target->hasLeft() != target->hasRight()) {
            if (parent != nullptr) {
                if (target->hasLeft()) {
                    if (isLeftChild) {
                        parent->left = target->left;
                    } else {
                        parent->right = target->left;
                    }
                } else {
                    if (isLeftChild) {
                        parent->left = target->right;
                    } else {
                        parent->right = target->right;
                    }
                }
            } else {
                DictionaryTree<Key, Value> *separatedTree;
                if (target->hasLeft()) {
                    separatedTree = this->left;
                    this->left = nullptr;
                } else {
                    separatedTree = this->right;
                    this->right = nullptr;
                }

                Sequence<std::pair<Key, Value>> *sepTreeSequence = separatedTree->thread("NLR");
                this->selfKey = sepTreeSequence->get(0).first;
                this->value = sepTreeSequence->get(0).second;

                for (int i = 1; i < sepTreeSequence->getLength(); i++) {
                    this->add(sepTreeSequence->get(i).first, sepTreeSequence->get(i).second);
                }
            }
        } else {
            DictionaryTree<Key, Value> *replacingNode = target->right->minTree();
            Key replacingKey = replacingNode->selfKey;
            Value replacingVal = replacingNode->value;

            this->remove(replacingKey);
            target->selfKey = replacingKey;
            target->value = replacingVal;
        }
    } else {
        std::cout << "No such key in the tree\n";
        throw std::exception();
    }
}

template<class Key, class Value>
DictionaryTree<Key, Value> *DictionaryTree<Key, Value>::getParent(Key key) {
    if (this->contains(key)) {
        if (this->selfKey == key) {
            return nullptr;
        } else {
            DictionaryTree<Key, Value> *ptr1 = this;
            DictionaryTree<Key, Value> *ptr2;

            while (ptr1->selfKey != key) {
                ptr2 = ptr1;

                if (ptr1->selfKey > key) {
                    ptr1 = ptr1->left;
                } else {
                    ptr1 = ptr1->right;
                }
            }

            return ptr2;
        }
    } else {
        std::cout << "No such key in the tree\n";
        throw std::exception();
    }
}
