//
// Created by WU on 2021/7/19.
//

#ifndef MYSTL_AVL_H
#define MYSTL_AVL_H

#include <queue>
#include <iostream>

namespace wfs {
    template<class T>
    struct TreeNode {
        T value;
        int cnt;
        TreeNode* left, *right;
        TreeNode(T val):value(val), cnt(1), left(nullptr), right(nullptr){}
    };
//实现上有个小技巧：因为旋转点要满足两个条件，第一个是平衡因子绝对值大于1，第二个是要离插入点最近，满足第二个我一开始想的是记录每个点的平衡因子，但是每次插入都要更新
//显然不切实际，所以一种隐式满足第二个条件的方法就是递归调用_insert的时候。总是从下到上返回的，第一个满足第一个条件的位置自然就是离插入点最近的
//关于树节点递归调用的时候，子树的根节点会因为旋转而发生改变，传入的参数是指针（是一种值传递），再函数中修改指针指向的节点是没有意义的，需要返回新的根节点（或者旧的）
//然后赋值给上层调用的老根节点才行
    template<class T>
    class AVLTree {
    protected:
        TreeNode<T> *root;
        TreeNode<T>* _find(T val, TreeNode<T>* node) {
            if (node) {
                if (node->value == val) {
                    return node;
                }
                if (val < node->value && node->left) return _find(val, node->left);
                if (val > node->value && node->right) return _find(val, node->right);
            }
            return nullptr;
        }
        int _height(TreeNode<T>* node) {
            if (!node) return 0;
            int l = _height(node->left);
            int r = _height(node->right);
            return l > r ? l+1 : r+1;
        }
        TreeNode<T>* _right_rotate(TreeNode<T>* node) {
            TreeNode<T>* new_node = node->left;
            node->left = new_node->right;
            new_node->right = node;
            return new_node;
        }

        TreeNode<T>* _left_rotate(TreeNode<T>* node) {
            TreeNode<T>* new_node = node->right;
            node->right = new_node->left;
            new_node->left = node;
            return new_node;
        }
        TreeNode<T>* _insert(T val, TreeNode<T>* node) {
            if (val < node->value) {
                if (node->left) node->left = _insert(val, node->left);
                else node->left = new TreeNode<T>(val);
                if (_height(node->left) - _height(node->right) >= 2) {//l
                    if (val < node->left->value) {//ll
                        node = _right_rotate(node);
                    }
                    else { //lr
                        node->left = _left_rotate(node->left);
                        node = _right_rotate(node);
                    }
                }
            }
            else {
                if (node->right) node->right = _insert(val, node->right);
                else node->right = new TreeNode<T>(val);
                if (_height(node->right) - _height(node->left) >= 2) {//r
                    if (val < node->right->value) {//rl
                        node->right = _right_rotate(node->right);
                        node = _left_rotate(node);
                    }
                    else { //rr
                        node = _left_rotate(node);
                    }
                }
            }
            return node;
        }
        void destroy() {

        }
    public:
        AVLTree() {
            root = nullptr;
        }
        AVLTree(T val) {
            root = new TreeNode<T>(val);
        }
        void insert(T val) {
            TreeNode<T>* node = _find(val, root);
            if (node) {
                node->cnt++;
                return;
            }
            if (root) root = _insert(val,  root);
            else root = new TreeNode<T>(val);

        }

        int count(T val) {
            TreeNode<T>* t = _find(val, root);
            return t->cnt;
        }
        void printTree() {
            if (!root) return;
            std::queue<TreeNode<T>*> q;
            q.push(root);
            while (!q.empty()) {
                int sz = q.size();
                for (int i = 0; i < sz; ++i) {
                    TreeNode<T>* node = q.front();
                    std::cout << node->value << " ";
                    if (node->left != NULL) q.push(node->left);
                    if (node->right != NULL) q.push(node->right);
                    q.pop();
                }
                std::cout << std::endl;
            }
        }



        ~AVLTree() {
            destroy();
        }
    };
}

#endif //MYSTL_AVL_H
