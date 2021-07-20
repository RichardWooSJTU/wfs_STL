//
// Created by WU on 2021/7/20.
//

#ifndef MYSTL_RBTREE_ITERATOR_H
#define MYSTL_RBTREE_ITERATOR_H
#include <bits/stl_iterator_base_types.h>
#include "../my_allocator.h"
namespace wfs {
    template<class Key>//我觉得这里应该使用key的类型啊 value不应该是找到key之后用hashtable去找的么
    struct __rb_tree_node{ //这里用两层的目的就是前面的指针结构实际上是和类型无关的，无需放在template里
        typedef __rb_tree_node* base_ptr;

        bool color; //red is false and black is true
        base_ptr parent;
        base_ptr left;
        base_ptr right;
        static base_ptr min(base_ptr x) {
            while (x->left) x = x->left;
            return x;
        }

        static base_ptr max(base_ptr x) {
            while (x->right) x = x->right;
            return x;
        }
        Key key;
    };
    template<class Key, class Ref, class Ptr>
    struct __rb_tree_iterator {
        typedef std::bidirectional_iterator_tag iterator_category;
        typedef ptrdiff_t difference_type;
        typedef Key value_type;
        typedef Ref reference;
        typedef Ptr pointer;
        typedef __rb_tree_node<Key> tree_node;
        typedef __rb_tree_iterator<Key, Ref, Ptr> self;

        tree_node *node;

        __rb_tree_iterator(){}
        __rb_tree_iterator(tree_node * x){node = x;}
        __rb_tree_iterator(const self& it) {node = it.node;}

        reference operator*() const {return node->key;}
        self& operator++(){
            //中序遍历 左链入栈的思想
            if (node->right) {
                node = node->right;
                while (node->left) node = node -> left;
            }
            else {
                tree_node * p = node->parent;
                while (node == p->right) {
                    node = p;
                    p = node->parent;
                }
                //此时左链的父节点就是我们需要找的，需要考虑的特殊情况是现在如果node是根节点的话，其父节点是head，如果root又没有右节点，head的右节点会指向root
                if (node->right != p) node = p;
            }
            return *this;
        }

        self operator++(int) {
            self tmp = *this;
            operator++();
            return tmp;
        }

        self& operator--() {
            //右链入栈
            if (node -> color == false && node->parent->parent == node) node = node->right;//指向最大节点处
            else if (node->left) {
                node = node ->left;
                while (node->right) node = node->right;
            }
            else {
                tree_node * p = node->parent;
                while (node == p->left) {
                    node = p;
                    p = node->parent;
                }
                node = p;
            }
            return *this;
        }

        self operator--(int) {
            self tmp = *this;
            operator--();
            return tmp;
        }

        bool operator!=(const self& ri) {
            return this->node != ri.node;
        }


    };
}

#endif //MYSTL_RBTREE_ITERATOR_H
