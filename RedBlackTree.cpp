#include "RedBlackTree.h"

rbTree::node::node(int s,std::string& w) {
    score = s;
    word = w;
    black = false;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
}

rbTree::rbTree() {
    root = nullptr;
}

void rbTree::insert(int s, std::string& w) {
    //if root is null insert a new node, change color to black
    node *n = nullptr;
    if(root == nullptr) {
        root = new node(s, w);
        n = root;
    }
    else {
        node *current = root;
        while (current != nullptr) {
            //compare current score with score trying to insert, if less than inserted score move right
            if (current->score < s) {
                if (current->right == nullptr) {
                    current->right = new node(s, w);
                    n = current->right;
                    current->right->parent = current;
                    current = nullptr;
                } else {
                    current = current->right;
                }
            }
                //compare current score with score trying to insert, if greater than inserted move left
            else if (current->score > s) {
                if (current->left == nullptr) {
                    current->left = new node(s, w);
                    n = current->left;
                    current->left->parent = current;
                    current = nullptr;
                } else {
                    current = current->left;
                }
            } else if (current->score == s){
                //to deal with duplicate scores of words store them in vector associated with each node
                current->duplicates.push_back(w);
                //return afterwards since the list doesn't need balancing
                return;
            }
        }
    }
    Balance(n);
}

//algorithm for balancing found in slides for red black tress
void rbTree::Balance(node *n) {
    //if at root of tree change the color to black
    if(n->parent == nullptr) {
        n->black = true;
        return;
    }
    //if inserted nodes parent was black nothing to do
    if(n->parent->black) {
        return;
    }
    //get the parent, uncle, and grandparent
    node* parent = n->parent;
    node* grandparent = parent->parent;
    node* uncle = getSibling(parent);
    //if the uncle is red, flip colors
    if(uncle != nullptr && !uncle->black) {
        parent->black = true;
        uncle->black = true;
        grandparent->black = false;
        //then call balance on the grandparent after flipping colors
        Balance(grandparent);
        return;
    }
    //if the tree is right left unbalanced
    //change the parent and current node pointers to account for color swap after rotation
    if(n == parent->right && parent == grandparent->left) {
        rotateLeft(parent);
        n = parent;
        parent = n->parent;
    }
    //if the tree is left right unbalanced
    else if(n ==  parent->left && parent == grandparent->right){
        rotateRight(parent);
        n = parent;
        parent = n->parent;
    }
    parent->black = true;
    grandparent->black = false;
    //either final step of a two-step rotation or the only rotation necessary
    if(n == parent->left) {
        rotateRight(grandparent);
    }
    else{
        rotateLeft(grandparent);
    }
}

rbTree::node* rbTree::getSibling(node* p) {
    if(p->parent->score > p->score) {
        //if the parents score is greater than the currents nodes score, the sibling will be on the right
        return p->parent->right;
    }
    else {
        //the sibling is to the left of the current nodes parent
        return p->parent->left;
    }
}

void rbTree::rotateLeft(node *n) {
    //standard left rotation
    node* grandchild = n->right->left;
    node* newParent = n->right;
    newParent->left =  n;
    n->right = grandchild;
    //if-else to reassign parent pointers, also accounts for if rotation node is the root
    if(n == root) {
        root = newParent;
        newParent->parent = nullptr;
        n->parent = newParent;
    }
    else {
        newParent->parent = n->parent;
        //reassign n's parent to point to either have a right or left child depending on newParents score
        if(newParent->score > n->parent->score) {
            n->parent->right = newParent;
        }
        else {
            n->parent->left = newParent;
        }
        n->parent = newParent;
    }
}

void rbTree::rotateRight(node *n) {
    //standard right rotation
    node* grandchild = n->left->right;
    node* newParent = n->left;
    newParent->right = n;
    n->left = grandchild;
    //if-else to reassign parent pointers, also accounts for if rotation node is the root
    if(n == root) {
        root = newParent;
        newParent->parent = nullptr;
        n->parent = newParent;
    }
    else {
        newParent->parent = n->parent;
        //reassign n's parent to point to either have a right or left child depending on newParents score
        if(newParent->score > n->parent->score) {
            n->parent->right = newParent;
        }
        else {
            n->parent->left = newParent;
        }
        n->parent = newParent;
    }
}

void rbTree::search(std::string &w, std::vector<std::pair<std::string, int>>& r) {
    node* current = root;
    int s = value(w);
    while(current != nullptr) {
        //if score searching for is greater than current nodes score move right
        if(s > current->score) {
            current = current->right;
        }
        else if(s < current->score) {
            current = current->left;
        }
        else if(s == current->score) {
            //once found check if letters match, using a set to compare
            std::set<char> check(w.begin(), w.end());
            std::set<char> toCompare(current->word.begin(), current->word.end());
            if(toCompare == check) {
                r.push_back(std::make_pair(current->word, current->score));
            }
            //check if there are duplicates
            if(!current->duplicates.empty()) {
                for(int i = 0; i < current->duplicates.size(); i++) {
                    //make a set for the word in duplicate
                    std::set<char> c(current->duplicates.at(i).begin(), current->duplicates.at(i).end());
                    if(check == c) {
                        r.push_back(std::make_pair(current->duplicates.at(i), current->score));
                    }
                }
                return;
            }
        }
    }
}

int rbTree::value(std::string &w) {
    int sum = 0;
    for (int i = 0; i < w.size(); i++) {
        if (w.at(i) == 'A') {
            sum += 1;
        } else if (w.at(i) == 'E') {
            sum += 1;
        } else if (w.at(i) == 'I') {
            sum += 1;
        } else if (w.at(i) == 'O') {
            sum += 1;
        } else if (w.at(i) == 'U') {
            sum += 1;
        } else if (w.at(i) == 'L') {
            sum += 1;
        } else if (w.at(i) == 'N') {
            sum += 1;
        } else if (w.at(i) == 'S') {
            sum += 1;
        } else if (w.at(i) == 'T') {
            sum += 1;
        } else if (w.at(i) == 'R') {
            sum += 1;
        } else if (w.at(i) == 'D') {
            sum += 2;
        } else if (w.at(i) == 'G') {
            sum += 2;
        }  else if (w.at(i) == 'B') {
            sum += 3;
        } else if (w.at(i) == 'C') {
            sum += 3;
        } else if (w.at(i) == 'M') {
            sum += 3;
        } else if (w.at(i) == 'P') {
            sum += 3;
        } else if (w.at(i) == 'F') {
            sum += 4;
        } else if (w.at(i) == 'H') {
            sum += 4;
        } else if (w.at(i) == 'V') {
            sum += 4;
        } else if (w.at(i) == 'W') {
            sum += 4;
        } else if (w.at(i) == 'Y') {
            sum += 4;
        } else if (w.at(i) == 'K') {
            sum += 5;
        } else if (w.at(i) == 'J') {
            sum += 8;
        } else if (w.at(i) == 'X') {
            sum += 8;
        } else if (w.at(i) == 'Q') {
            sum += 10;
        } else if (w.at(i) == 'Z') {
            sum += 10;
        }
    }
    return sum;
}

rbTree::~rbTree() {
    std::queue<node*> q;
    q.push(root);
    while(!q.empty()) {
        int size = q.size();
        for(int i = 0; i < size; i++) {
            if(q.front()->left != nullptr) {
                q.push(q.front()->left);
            }
            if(q.front()->right != nullptr) {
                q.push(q.front()->right);
            }
            delete q.front();
            q.pop();
        }
    }
    root = nullptr;
}

