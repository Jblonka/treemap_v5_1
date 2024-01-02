// C++ Aufgabe Treemap V5 part 1 - treemap_node, alias treemap::node
// Autor: Hartmut Schirmacher, BHT Berlin

#pragma once

#include <memory>

namespace my
{

    // this is the template for a node in the treemap's tree
    // please note that the node does not need to know anything about the treemap itself (or about the iterator, later)
    template <typename K, typename T>
    class treemap_node
        : public std::enable_shared_from_this<treemap_node<K, T>>
    {

    public:
        // aloas to shorten things
        using node = treemap_node<K, T>;
        using node_ptr = std::shared_ptr<node>;

        // public attributes
        std::pair<K, T> value_;
        std::weak_ptr<node> up_;
        node_ptr left_, right_;

        treemap_node(K key, T mapped, node_ptr up)
            : value_(std::make_pair(key, mapped)), up_(up), left_(), right_()
        {
        }

        // try to insert new (key,mapped) node in tree, return (new node, true)
        // if key already in tree, do not overwrite, just return (existing node, false)
        std::pair<node_ptr, bool> insert(K key, T mapped);

        // find node with the given key, and return pointer to it. return nullptr if not found
        std::shared_ptr<node> find(K key)
        {
            // TODO, this is dummy code!
            return nullptr;
        }

    }; // class treemap_node

    template <typename K, typename T>
    std::pair<typename treemap_node::node_ptr, bool>
    treemap_node<K,T>::insert(K key, T mapped)
    {
        // if (key == value_.first)
        // { // key is current node
        //     return std::make_pair(shared_from_this(), false);
        // }
        // else if (key < value_.first)
        // { // key is smaller than current node
        //     if (left_ == nullptr)
        //     { // left child is empty
        //         left_ = std::make_shared<node>(key, mapped, shared_from_this());
        //         return std::make_pair(left_, true);
        //     }
        //     else
        //     {                                      // left child is not empty
        //         return left_->insert(key, mapped); // recursive call
        //     }
        // }
        // else
        // { // key is bigger than current node
        //     if (right_ == nullptr)
        //     { // right child is empty
        //         right_ = std::make_shared<node>(key, mapped, shared_from_this());
        //         return std::make_pair(right_, true);
        //     }
        //     else
        //     {                                       // right child is not empty
        //         return right_->insert(key, mapped); // recursive call
        //     }
        // }
    }

} // my::