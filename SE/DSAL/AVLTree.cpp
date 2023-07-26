/*
A Dictionary stores keywords & its meanings. Provide facility for adding new keywords, deleting keywords, updating values of any entry. Provide facility to display whole data sorted in
ascending/descending order. Also find how many maximum comparisons may require for finding any keyword. Use Height balance tree and find the complexity for finding a keyword.
*/

#include <iostream>
#include <queue>
using namespace std;

class Node {
    int data;
    int height = 1;
    Node* left;
    Node* right;

    public: 
    friend class AVL;
};


class AVL
{
    public:
    Node* root;

    AVL() {
        root = NULL;
    }

    int height(Node* node) {
        if (node == NULL)
            return 0;

        return node->height;
    }

    void updateHeight(Node* node) {
        node->height = 1 + max(height(node->left), height(node->right));
    }

    int bf(Node* node) {
        if (node == NULL)
            return 0;
        
        return (height(node->left) - height(node->right));
    }

    Node* LL(Node* node) {
        Node* newroot = node->left;
        newroot->right = node;
        node->left = NULL;

        updateHeight(node);
        updateHeight(newroot);

        return newroot;
    }

    Node* RR(Node* node) {
        Node* newroot = node->right;
        newroot->left = node;
        node->right = NULL;

        updateHeight(node);
        updateHeight(newroot);
    }

    Node* LR(Node* node) {
        node->left = RR(node->left);
        return LL(node);
    }

    Node* RL(Node* node) {
        node->right = LL(node->right);
        return RR(node);
    }

    Node* balance(Node* node) {
        if (bf(node) == 2) {
            if (bf(node->left) < 0) {
                node = LR(node);
            }
            else {
                node = LL(node);
            }
        }
        else if (bf(node) == -2) {
            if (bf(node->right) > 0) {
                node = RL(node);
            }
            else {
                node = RR(node);
            }
        }

        updateHeight(node);
        return node;
    }

    void inorder(Node* root) {
        if (root) {
            inorder(root->left);
            cout<<root->data<<" ";
            inorder(root->right);
        }
    }


    Node* insertSubtree(Node* curr, int d) {
        if (curr == NULL) {
            Node* newnode = new Node();
            newnode->data = d;
            return newnode;
        }

        if (d < curr->data)
            curr->left = insertSubtree(curr->left, d);
        else if (d > curr->data)
            curr->right = insertSubtree(curr->right, d);
        else {
            curr->data = d;
            return curr;
        }
        return balance(curr);
    }


    void insert(int d) {
        root = insertSubtree(root, d);
    }

    void showInorder() {
        cout<<"\nInorder: ";
        inorder(root);
    }

    void bfs() {
        queue<Node*> q;
        q.push(root);
        cout<<"\nBFS: ";

        while(!q.empty()) {
            Node* temp = q.front();
            q.pop();

            cout<<temp->data<<" ";

            if (temp->left != NULL)
                q.push(temp->left);
            if (temp->right != NULL) 
                q.push(temp->right);
        }
    }

    Node* search( int data ) {
        Node *curr = root;
        while( curr != nullptr ) {
            if( data > curr->data )
                curr = curr->right;
            else if( data < curr->data )
                curr = curr->left;
            else
                return curr;
        }
        return nullptr;
    }
};



int main() {
    AVL tree;
    
    tree.insert(10);
    cout<<"\ninserted";
    tree.insert(50);
    cout<<"\ninserted";
    tree.insert(100);
    cout<<"\ninserted";
    tree.insert(25);
    tree.insert(75);
    tree.insert(85);
    
    tree.bfs();
    tree.showInorder();
    
    // tree.insert(175, "7");
    // tree.insert(65, "8");
    // tree.insert(85, "9");
    
    // tree.BFS();
    // tree.inorder();
    
    return 0;
}