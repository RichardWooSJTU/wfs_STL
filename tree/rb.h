//
// Created by WU on 2021/7/20.
//

#ifndef MYSTL_RB_H
#define MYSTL_RB_H

#include "../iterator/rbtree_iterator.h"
#include "../memory/construct.h"

namespace wfs {
    template<class Key, class Compare>
    class rb_tree {
    protected:
        typedef __rb_tree_node<Key> tree_node;
        typedef size_t size_type;
        typedef rb_tree<Key, Compare> self;
        typedef Key value_type;
        typedef Key* pointer;
        typedef Key& reference_type;

    protected:
        size_type node_count;
        tree_node * header;
        allocator<tree_node> allocator;
        Compare compare_obj;
        tree_node * get_node() {return allocator.allocate();}
        void put_node(tree_node * p) {allocator.deallocate(p, sizeof(tree_node));}
    public:
        typedef __rb_tree_iterator<value_type , reference_type , pointer> iterator;
    protected:
        void __right_rotate(tree_node * node) {
            tree_node * new_node = node->left;
            node->left = new_node->right;
            new_node->right = node;
            new_node->parent = node->parent;
            node->parent = new_node;
        }
        void __left_rotate(tree_node * node) {
            tree_node * new_node = node->right;
            node->right = new_node->left;
            new_node->left = node;
            new_node->parent = node->parent;
            node->parent = new_node;
        }
    public:
        iterator begin() {return header->left;}
        iterator end() {return header;}//迭代器加法保证会回到header
        void init() {
            header = get_node();
            header->color = false;
            header->parent = nullptr;
            header->left = header;
            header->right = header;
        }
        rb_tree(const Compare& cmp = Compare()):node_count(0),  compare_obj(cmp) {
            init();
        }
        ~rb_tree() {
            //这里也应该把整个树delete掉
            iterator beg = begin();
            while (beg != end()) {
                destroy(beg.node);
                put_node(beg.node);
                ++beg;
            }
            put_node(header);
        }

        std::pair<iterator, bool> insert_unique(const Key& key) {
            tree_node * p = header, * x = header->parent;
            while (x != nullptr) {
                if (x->key == key) return std::pair<iterator, bool>(iterator(header->right), false);

                //由上而下进行插入前旋转
                if (x->left && x->right && x->left->color == false && x->right->color == false) {
                    //先反色
                    x->color = false;
                    x->left->color = x->right->color = true;
                    if (x == header->parent){
                        x->color = true;
                        continue;
                    }
                    //再判断是否影响了规则
                    if (p->color == false) {
                        //影响了，走三种状况,而且p必然不可能是root因为root必然是true
                        tree_node * g = p->parent, * gg = g -> parent;
                        tree_node * s;//叔叔
                        if (p == g->left) s = g->right;
                        else s = g->left;
                        //其实这里s也就是叔叔不可能是红色，是的话在上层的判断中就已经没了
                        if ((s && s->color) || !s) {
                            if (p == g->left && x == p->left) {
                                __right_rotate(g);
                                p->color = !p->color;
                                g->color = !g->color;
                                if (gg->parent == g) gg->parent = p;
                                else if (gg->left == g) gg->left = p;
                                else if (gg->right == g) gg->right = p;
                            }
                            else if (p == g->right && x == p->right) {
                                __left_rotate(g);
                                p->color = !p->color;
                                g->color = !g->color;
                                if (gg->parent == g) gg->parent = p;
                                else if (gg->left == g) gg->left = p;
                                else if (gg->right == g) gg->right = p;
                            }
                            else if (p == g->left && x == p->right) {
                                __left_rotate(p);
                                __right_rotate(g);
                                x->color = !x->color;
                                g->color = !g->color;
                                if (gg->parent == g) gg->parent = x;
                                else if (gg->left == g) gg->left = x;
                                else if (gg->right == g) gg->right = x;
                            }
                            else if (p == g->right && x == p->left) {
                                __right_rotate(p);
                                __left_rotate(g);
                                x->color = !x->color;
                                g->color = !g->color;
                                if (gg->parent == g) gg->parent = x;
                                else if (gg->left == g) gg->left = x;
                                else if (gg->right == g) gg->right = x;

                            }
                        }
                    }
                    //这里可以保证走到x这里它的孩子全是黑色
                }
                p = x;
                bool comp = compare_obj(key, x->key);
                x = comp ? x->left : x->right;
            }
            //到这里x = null, p就是插入点的父亲，现在唯一遗漏的情况是 p是叶子了 p是红的 p的兄弟是肯定没有的
            if (x == header->parent) {
                //根节点
                header->parent = get_node();
                x = header->parent;
                construct(&(x->key), key);
                x->color = true;
                x->parent = header;
                x->left = nullptr;
                x->right = nullptr;
                header->left = x;
                header->right = x;
                ++node_count;
                iterator iter = iterator(x);
                return std::pair<iterator, bool>(iter, true);
            }
            if (compare_obj(key, p->key)) {
                p->left = get_node();
                x= p->left;
                if (p == header->left) header->left = x;
            } else {
                p->right = get_node();
                x= p->right;
                if (p == header->right) header->right = x;
            }
            construct(&(x->key), key);
            x->color = false;
            x->parent = p;
            x->left = nullptr;
            x->right = nullptr;
            if (!p->color) {
                tree_node * g = p->parent, * gg = g -> parent;
                if (p == g->left && x == p->left) {
                    __right_rotate(g);
                    p->color = !p->color;
                    g->color = !g->color;
                    if (gg->parent == g) gg->parent = p;
                    else if (gg->left == g) gg->left = p;
                    else if (gg->right == g) gg->right = p;
                }
                else if (p == g->right && x == p->right) {
                    __left_rotate(g);
                    p->color = !p->color;
                    g->color = !g->color;
                    if (gg->parent == g) gg->parent = p;
                    else if (gg->left == g) gg->left = p;
                    else if (gg->right == g) gg->right = p;
                }
                else if (p == g->left && x == p->right) {
                    __left_rotate(p);
                    __right_rotate(g);
                    x->color = !x->color;
                    g->color = !g->color;
                    if (gg->parent == g) gg->parent = x;
                    else if (gg->left == g) gg->left = x;
                    else if (gg->right == g) gg->right = x;
                }
                else if (p == g->right && x == p->left) {
                    __right_rotate(p);
                    __left_rotate(g);
                    x->color = !x->color;
                    g->color = !g->color;
                    if (gg->parent == g) gg->parent = x;
                    else if (gg->left == g) gg->left = x;
                    else if (gg->right == g) gg->right = x;

                }
            }
            ++node_count;
            iterator iter = iterator(x);
            return std::pair<iterator, bool>(x, true);
        }
    };
}

#endif //MYSTL_RB_H
