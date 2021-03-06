#ifndef TREENODE_H
#define TREENODE_H

#include <iostream>
#include <vector>

// A binary tree-node.

namespace DuckyTools {
template <class T>
class Node {

    template <class U>
    friend class BTree;

private:
    Node<T>* m_parent{nullptr};
    Node<T>* m_vSub{nullptr};
    Node<T>* m_hSub{nullptr};

    void addToVector(std::vector<T> &v) {
        if (m_vSub)
            m_vSub->addToVector(v);
        v.push_back(m_data);
        if (m_hSub) {
            m_hSub->addToVector(v);
        }
    }

    Node<T>* findMostLeft() {
        return (m_vSub != nullptr) ? m_vSub->findMostLeft() : this;
    }
public:
    T m_data{};
public:
    // Default constructor
    Node(T data = T{}, Node<T>* parent = nullptr) : m_data{data}, m_parent{parent} {
        // m_index++;
    }
    ~Node() {
        // m_index--;
    }

    void insert(const T &data) {
        if (data == m_data) {
            std::cout << "Key already in tree!" << std::endl;
            return;
        }
        if (data < m_data) {
            if (m_vSub == nullptr) {
                m_vSub = new Node<T>{data, this};
            } else {
                m_vSub->insert(data);
            }
        } else {
            if (m_hSub == nullptr) {
                m_hSub = new Node<T>{data, this};
            } else {
                m_hSub->insert(data);
            }
        }
    }

    Node<T>* search(T data) {
        if (data == m_data) {
            return this;
        }
        if (data < m_data) {
            if (m_vSub == nullptr) {
                return this;
            } else {
                return m_vSub->search(data);
            }
        } else {
            if (m_hSub == nullptr) {
                return this;
            } else {
                return m_hSub->search(data);
            }
        }
    }

    Node<T>* searchBefore(T data) {
        if (m_vSub != nullptr) {
            if (m_vSub->m_data == data) {
                return this;
            }
        }
        if (m_hSub != nullptr) {
            if (m_hSub->m_data == data) {
                return this;
            }
        }
        if (m_vSub != nullptr) {
            m_vSub->searchBefore(data);
        }
        if (m_hSub != nullptr) {
            m_hSub->searchBefore(data);
        }
    }

    void intrav() {
        if (m_vSub != nullptr)
            m_vSub->intrav();
        std::cout << m_data << std::endl;
        if (m_hSub != nullptr) {
            m_hSub->intrav();
        }
    }
};
}

#endif // TREENODE_H
