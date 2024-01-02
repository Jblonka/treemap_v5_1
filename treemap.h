// C++ Aufgabe Treemap V5 part 1 - treemap class, uses treempap_node 
// Autor: Hartmut Schirmacher, BHT Berlin

#pragma once

// other includes
#include <memory>
#include <iostream>
#include <utility>
#include <tuple>
#include "treemap_node.h"

// forward declarations

namespace my {
    template<typename K, typename T>
    class treemap;
}

template<typename KK, typename TT>
void swap(my::treemap<KK,TT>& lhs, my::treemap<KK,TT>& rhs);

namespace my {

/*
 * class treemap<K,T>
 * represents an associative container (dictionary) with unique keys
 * implemented by a binary search tree
 * - no balancing, no remove/erase operations 
 * - no separate comparison operators, relies on K::operator==(), K::operator<(), etc.
 */
template<typename K, typename T>
class treemap 
{

public:

    // public type aliases
    using key_type = K;
    using mapped_type = T;  
    using value_type = std::pair<K, T>;

public:

    // construct empty map
    treemap();

    // number of keys in map
    size_t size() const;

    // how often is the element contained in the map?
    // (for this type of container, can only return 0 or 1)
    size_t count(const K&) const;

    // random read/write access to value by key
    T& operator[](const K&);

    // delete all (key,value) pairs in map 
    void clear();

    // used for copy&move - declared in global namespace, not in my::
    template<typename KK, typename TT>
    friend void ::swap(treemap<KK,TT>& , treemap<KK,TT>& );

protected:

    // the node type is only used internally - do not show publicly!
    using node = my::treemap_node<K, T>; // from treemap_node.h
    using node_ptr = std::shared_ptr<node>; // for passing around pointers to nodes internally (!) 

    // class attributes
    node_ptr root_;
    size_t count_;

    // add a new (key, value) pair into the tree
    // returns pair, consisting of:
    // - pointer to node containing the (key, value) pair
    // - bool
    //   - true if element was inserted;
    //   - false if key was already in map (will not overwrite existing value)
    std::pair<node_ptr,bool> insert_(const K&, const T&);

    // find element with specific key. returns nullptr if not found.
    node_ptr find_(const K&) const;

};


template<typename K, typename T>
treemap<K,T>::treemap()
    : root_(), count_(0)
{
}

template<typename K, typename T>
void
treemap<K,T>::clear()
{
    root_.reset();
    count_ = 0;
}

// random write access to value by key
// if key is not in map, insert new (key, T()) 
template<typename K, typename T>
T&
treemap<K,T>::operator[](const K& key)
{
    // TODO this is dummy code
    // static T dummy;
    // return dummy;
    if(count_ == 0 || find_(key) == nullptr) {
        insert_(key, T());
        count_++;
    }
    return find_(key)->value_.second;
}

// number of elements in map (nodes in tree)
template<typename K, typename T>
size_t
treemap<K,T>::size() const
{
    return count_;
}

// add a new element into the tree
// returns:
// - pointer to element
// - true if element was inserted; false if key was already in map
// template<typename K, typename T>
// std::pair<typename treemap<K,T>::node_ptr,bool>
// treemap<K,T>::insert_(const K& key, const T& mapped)
// {
//     if(count_ == 0) {   // empty tree
//         root_ = std::make_shared<node>(key, mapped, nullptr);
//         return std::make_pair(root_, true);
//     }
//     else if(root_->value_.first == key) {   // root is key
//         return std::make_pair(root_, false);
//     }
//     else if(root_->value_.first < key) {    // key is bigger than root
//         if(root_->right_ == nullptr) {    // right child is empty
//             root_->right_ = std::make_shared<node>(key, mapped, root_);
//             return std::make_pair(root_->right_, true);
//         }
//         else {  // right child is not empty
//             return insert_(root_->right_->value_.first, mapped);    // recursive call
//         }
//     }
//     else {  // key is smaller than root
//         if(root_->left_ == nullptr) {   // left child is empty
//             root_->left_ = std::make_shared<node>(key, mapped, root_);
//             return std::make_pair(root_->left_, true);
//         }
//         else {  // left child is not empty
//             return insert_(root_->left_->value_.first, mapped); // recursive call
//         }
//     }
// }

template<typename K, typename T>
std::pair<typename treemap<K,T>::node_ptr,bool>
treemap<K,T>::insert_(const K& key, const T& mapped)
{
    if(count_ == 0) {   // empty tree
        root_ = std::make_shared<node>(key, mapped, nullptr);
        return std::make_pair(root_, true);
    }

    node_ptr current = root_;
    while(true) {
        if(current->value_.first == key) {   // current is key
            return std::make_pair(current, false);
        }
        else if(current->value_.first < key) {    // key is bigger than current
            if(current->right_ == nullptr) {    // right child is empty
                current->right_ = std::make_shared<node>(key, mapped, current);
                return std::make_pair(current->right_, true);
            }
            else {  // right child is not empty
                current = current->right_;    // move to right child
            }
        }
        else {  // key is smaller than current
            if(current->left_ == nullptr) {   // left child is empty
                current->left_ = std::make_shared<node>(key, mapped, current);
                return std::make_pair(current->left_, true);
            }
            else {  // left child is not empty
                current = current->left_; // move to left child
            }
        }
    }
}

// find element with specific key. returns end() if not found.
// template<typename K, typename T>
// typename treemap<K,T>::node_ptr
// treemap<K,T>::find_(const K& key) const
// {
//     // TODO this is dummy code
//     if(count_ != 0 && root_ != nullptr) {
//         if(root_->value_.first == key) {
//             return root_;
//         }
//         else if(root_->value_.first < key) {
//             return find_(root_->right_->value_.first);
//         }
//         else {
//             return find_(root_->left_->value_.first);
//         }
//     }
//     return nullptr;
//     // return end();
// }

template<typename K, typename T>
typename treemap<K,T>::node_ptr
treemap<K,T>::find_(const K& key) const
{
    node_ptr current = root_;
    while (current != nullptr) {    // while current is not empty
        if (current->value_.first == key) { // if current is key
            return current;
        } else if (current->value_.first < key) {   // if current is smaller than key
            current = current->right_;
        } else {    // if current is bigger than key
            current = current->left_;
        }
    }
    return nullptr;
}

// how often is the element contained in the map?
template<typename K, typename T>
size_t
treemap<K,T>::count(const K& key) const
{
    return find_(key) == nullptr? 0 : 1;
}

} // namespace my


// swap contents of two trees
// this is defined in the global namespace, for reasons... (see StackOverflow)
template<typename KK, typename TT>
void
swap(my::treemap<KK,TT>& lhs, my::treemap<KK,TT>& rhs)
{
    std::swap(lhs.root_, rhs.root_);
    std::swap(lhs.count_, rhs.count_);
}
