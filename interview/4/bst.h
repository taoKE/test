#pragma once

class BSTNode{
    private:
        BSTNode * left, * right;

    public:
        BSTNode(BSTNode * l = NULL, BSTNode * r = NULL) left(l), right(r){}
        
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
};

class BST{
    private:
        BSTNode * root;

    public:
        BST(BSTNode * r) : root(r){}
        
        BSTNode * getRoot(){
            return root;
        }
};
