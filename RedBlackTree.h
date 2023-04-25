#include <string>
#include <vector>
#include <set>
#include <queue>
#ifndef REDBLACKTREE_REDBLACKTREE_H
#define REDBLACKTREE_REDBLACKTREE_H

#endif //REDBLACKTREE_REDBLACKTREE_H

class rbTree {
    struct node {
        //each node has the word itself its score and a vector to store words with the same score
        int score;
        std::string word;
        std::vector<std::string> duplicates;
        //r = false, b = true
        bool black;
        node* left;
        node* right;
        node* parent;
        node(int s,std::string& w);
    };
    private:
        node* root;
        void Balance(node* n);
        node* getSibling(node* p);
        void rotateLeft(node* n);
        void rotateRight(node* n);
    public:
        rbTree();
        void insert(int s, std::string& w);
        void search(std::string& w, std::vector<std::pair<std::string, int>>& r);
        int value(std::string& w);
        ~rbTree();
};
