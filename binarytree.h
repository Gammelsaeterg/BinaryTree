#ifndef BINARYTREE_H
#define BINARYTREE_H

namespace DuckyTools {
template <class T>
class BTree;
}

#include "treenode.h"
#include <vector>

namespace DuckyTools {
template <class T>
class BTree {
private:
    unsigned int count{0};
public:
    Node<T>* root{nullptr};
    BTree() {

    }

    void insert(const T &data) {
        if (root == nullptr) {
            root = new Node<T>{data};
            count++;
        } else {
            root->insert(data);
            /*
            if (data < root->m_data) {
                if (root->m_vSub == nullptr) {
                    root->m_vSub = new Node<T>{data};
                    count++;
                } else {
                    root->m_vSub->insert(data);
                }
            } else {
                if (root->m_hSub == nullptr) {
                    root->m_hSub = new Node<T>{data};
                    count++;
                } else {
                    root->m_hSub->insert(data);
                }
            }
            */
        }
    }

    void remove(T data) {
        // Search for the node you want to remove
        Node<T>* nodeToDelete{search(data)};
        if (nodeToDelete != nullptr) {

            Node<T>* parentNode{nullptr};
            if (nodeToDelete->m_parent != nullptr) {
               parentNode = nodeToDelete->m_parent;
            } else {
               // If the parent doesn't exist, it
               // must mean that this is the root node.
            }

            // Find the nodes right, most left node. This will be the new tree-root.
            Node<T>* newBase = nodeToDelete->m_hSub->findMostLeft();
            // Also find the parent of that node.
            Node<T>* overBase = newBase->m_parent;

            // Set the parents left to the root-nodes right
            overBase->m_vSub = newBase->m_hSub;
            // Set the left for the deleted node to be the left for the root-node.
            newBase->m_vSub = nodeToDelete->m_vSub;
            // Set the right for the deleted node to be the right for the root-node.
            newBase->m_hSub = nodeToDelete->m_hSub;
        } else {
            // cannot find the node to delete. Abort
        }


    }

    void intrav() {
        if (root != nullptr)
            root->intrav();
    }

    Node<T>* search(const T &data, Node<T>* &parent) {
        if (root != nullptr) {
            root->search(data, parent);
        }
    }

    std::vector<T> toVector() {
        std::vector<T> v{};
        if (root != nullptr)
            root->addToVector(v);
        return v;
    }
};
}

#endif // BINARYTREE_H
