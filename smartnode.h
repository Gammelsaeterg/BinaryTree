#ifndef SMARTNODE_H
#define SMARTNODE_H

#include <memory>
#include <iostream>
#include <algorithm>

namespace DuckyTools{

template <class U>
class SmartBinaryTree;

template <class T>
class SmartNode {

    friend SmartBinaryTree<T>; // Declare friend function that is allowed to see parent pointer.

private:
    SmartNode<T> *m_parent{}; // Using a normal pointer here because of circular dependancy, and it's easier to assign.

public:
    std::unique_ptr<SmartNode<T>> m_vSub{};
    std::unique_ptr<SmartNode<T>> m_hSub{};
    T m_data{};

public:
    SmartNode() {
        std::cout << "Constructed!" << std::endl;
    }


    SmartNode(const T &data) : m_data{data} {
        std::cout << "Constructed!" << std::endl;
    }
    SmartNode(const T &data, SmartNode<T> *parent) : m_data{data}, m_parent{parent} {
        std::cout << "Constructed!" << std::endl;
    }

    void insert (const T &data) {
        if (m_data <= data) {
            if (m_hSub) {
                m_hSub->insert(data);
            } else {
                m_hSub = std::make_unique<SmartNode<T>>(data, this);
            }
        } else {
            if (m_vSub) {
                m_vSub->insert(data);
            } else {
                m_vSub = std::make_unique<SmartNode<T>>(data, this);
            }
        }
    }

    void remove(const T &data) {
        // Search for the node to use

        bool left{};

        if (m_data == data) {
            // Should do the remove on the node before, not the node that shall be removed.
            // So if this is true, then this is the root.

            // Do root deletion.
        }

        if (m_data < data) {
            if (m_hSub) {
                if (m_hSub->m_data == data) {
                    // Match found, continue deleting.
                    removeLeftOrRight(false);
                } else {
                    m_hSub->remove(data);
                }
            } else {
                // The data to search for isn't in the tree. Abort.
                return;
            }
        } else {
            if (m_vSub) {
                if (m_vSub->m_data == data) {
                    // Match found, continue deleting.
                    removeLeftOrRight(true);
                } else {
                    m_vSub->remove(data);
                }
            } else {
                // The data to search for isn't in the tree. Abort.
                return;
            }
        }
    }

    SmartNode<T>* search(const T &data) {
        if (m_data == data) {
            return this;
        } else if (m_data < data) {
            if (m_hSub) {
                return m_hSub->search(data);
            } else {
                return nullptr;
            }
        } else {
            if (m_vSub) {
                return m_vSub->search(data);
            } else {
                return nullptr;
            }
        }
    }

    SmartNode<T>* findLeftSmallest() {
        if (m_vSub) {
            return m_vSub->findLeftSmallest();
        } else {
            return this;
        }
    }

    void preTrav() {
        std::cout << m_data << std::endl;

        if (m_vSub) {
            m_vSub.get()->preTrav();
        }
        if (m_hSub) {
            m_hSub.get()->preTrav();
        }
    }

    void inTrav() {
        if (m_vSub) {
            m_vSub.get()->postTrav();
        }

        std::cout << m_data << std::endl;

        if (m_hSub) {
            m_hSub.get()->postTrav();
        }
    }

    void postTrav() {
        if (m_vSub) {
            m_vSub.get()->postTrav();
        }
        if (m_hSub) {
            m_hSub.get()->postTrav();
        }

        std::cout << m_data << std::endl;
    }

    unsigned int countNodesInternal() {
        return ((m_vSub) ? m_vSub.get()->countNodesInternal() : 0)
            + ((m_hSub) ? m_hSub.get()->countNodesInternal() : 0)
            + 1;
    }

    unsigned int getDepth(unsigned int currentDepth) {
        return std::max(
                    (m_vSub) ? m_vSub.get()->getDepth(currentDepth + 1) : currentDepth,
                    (m_hSub) ? m_hSub.get()->getDepth(currentDepth + 1) : currentDepth
                        );
    }

    void printDepth(int depth) {
        std::cout << std::string{""}.append(static_cast<unsigned int >(4 * depth), ' ')
                  << m_data << std::endl;
        if (m_vSub) {
            m_vSub.get()->printDepth(depth + 1);
        }
        if (m_hSub) {
            m_hSub.get()->printDepth(depth + 1);
        }
    }

    void print() {
        if (m_vSub) {
            m_vSub.get()->print();
        }
        if (m_hSub) {
            m_hSub.get()->print();
        }
        std::cout << m_data << std::endl;
    }


    ~SmartNode() {
        std::cout << "Destructed!" << std::endl;
    }

private:
    void removeLeftOrRight(bool left) {
        /* At this point the function should be running on the parent of the
         * function that is going to be deleted, and "left" has been set to
         * either true or false.
         */

        // Figure out what deletion method and do the deletion method:
        if ((left ? m_vSub : m_hSub)->m_vSub && (left ? m_vSub : m_hSub)->m_hSub) {
            // Node that is going to be deleted has two children:
            removeWithTwoChildren();
        } else if ((left ? m_vSub : m_hSub)->m_vSub || (left ? m_vSub : m_hSub)->m_hSub) {
            // Node that is going to be deleted has 1 children:
            removeWithOneChild();
        } else {
            // Node that is going to be deleted has no children:
            removeWithNoChildren();
        }
    }

    void removeWithNoChildren(bool left) {

    }

    void removeWithOneChild(bool left) {

    }

    void removeWithTwoChildren(bool left) {

    }
};
}

#endif // SMARTNODE_H
