#pragma once

class BSTNode{
    public:
        BSTNode * left, * right;

        int value;

    public:
        BSTNode(int _value, BSTNode * l = NULL, BSTNode * r = NULL): left(l), right(r), value(_value){}

/*        
        void setLeft(BSTNode * l) {
            left = l;
        }
        
        void setRight(BSTNode * r) {
            right = r;
        }

        BSTNode * getLeft() {
            return left;
        }

        BSTNode * getRight() {
            return right;
        }
        
        */

        void add(int v) {
            if(this->value < v) {
                if(this->right == NULL) {
                    this->right = new BSTNode(v);
                } else this->right->add(v);
            } else {
                if(this->left == NULL) {
                    this->left = new BSTNode(v);
                } else this->left->add(v);
            }
        }
};

class BST{
    private:
        BSTNode * root;

        void destruct(BSTNode * node){
            if(node->left == NULL && node->right == NULL) {
                delete node;
            } else {
                if(node->left != NULL) destruct(node->left);
                if(node->right != NULL) destruct(node->right);
                delete node;
            }

        }

    public:
        BST(BSTNode * r = NULL) : root(r){}
        
        ~BST(){
            destruct(root);
        }

        BSTNode * getRoot(){
            return root;
        }

        void setRoot(BSTNode * r) {
            root = r;
        }

        void insert(int i) {
            root->add(i);
        }
};
