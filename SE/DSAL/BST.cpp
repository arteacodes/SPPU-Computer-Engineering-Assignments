/*
Beginning with an empty binary search tree. Construct the binary search tree by inserting the values in given order. After constructing binary search tree perform following operations:
1) Insert a new node
2) Find numbers of node in longest path
3) Minimum and maximum data value found in tree
4) Change a tree so that the roles of the left and right pointers are swapped at every node
5)Search an element
*/

#include <iostream>
using namespace std;

#define size 10

class Node
{
    Node* left;
    int key;
    string value;
    Node* right;

    Node(int k, string v) {
        key = k;
        value = v;
        left = NULL;
        right = NULL;
    }

    friend class BST;
};


class BST
{
    Node* root;

    public:
    BST() {
        root = NULL;
    }

    //void create();
    void insert();
    void del(int);
    Node* remove(Node*, int);
    void traversal();
    void inorder(Node*);
    void preorder(Node*);
    void postorder(Node*);
    void search(int);
    void showSwapped();
    void swap(Node*);
    void showHeight();
    int height(Node*);
    void minmax();
    Node* min(Node*);
    Node* max(Node*);
};


void BST::insert()
{
    Node *curr, *temp;
    int k;
    string v;

    cout<<"\nEnter key: ";
    cin>>k;
    cout<<"Enter value: ";
    cin>>v;
    curr = new Node(k,v);

    if (root == NULL) {
        root = curr;
    }
    else {
        temp = root;
        while (true) {
            if (curr->key <= temp->key) {
                if (temp->left == NULL) {
                    temp->left = curr;
                    break;
                }
                else {
                    temp = temp->left;
                }
            }
            else {
                if (temp->right == NULL) {
                    temp->right = curr;
                    break;
                }
                else {
                    temp = temp->right;
                }
            }
        }
    }
}


void BST::del(int key) {
    remove(root, key);
}


Node* BST::remove(Node *r, int key) {
    Node *temp;

    if (r == NULL)
        return r;

    if (key < r->key)    
        r->left = remove(r->left, key);
    
    else if (key > r->key)
        r->right = remove(r->right, key);

    else {
        // leaf node
        if (r->left == NULL && r->right == NULL) {
            return NULL;
        }
        // node with right child
        else if (r->left == NULL) {
            temp = r->right;
            delete r;
            return temp;
        }
        // node with left child
        else if (r->right == NULL) {
            temp = r->left;
            delete r;
            return temp;
        }
        temp = min(r->right);  // inorder successor is smallest in right subtree
        r->key = temp->key;
        r->value = temp->value;
        r->right = remove(r->right, temp->key);
    }
    return r;
}


void BST::traversal() {
    cout<<"\nInorder: ";
    inorder(root);
    cout<<"\nPreorder: ";
    preorder(root);
    cout<<"\nPostorder: ";
    postorder(root);
}


void BST::inorder(Node* root) {
    if (root == NULL)
        return;
    inorder(root->left);
    cout<<"["<<root->key<<":"<<root->value<<"] ";
    inorder(root->right);
}


void BST::preorder(Node* root) {
    if (root == NULL)
        return;
    cout<<"["<<root->key<<":"<<root->value<<"] ";
    preorder(root->left);
    preorder(root->right);
}


void BST::postorder(Node* root) {
    if (root == NULL)
        return;
    postorder(root->left);
    postorder(root->right);
    cout<<"["<<root->key<<":"<<root->value<<"] ";
}


void BST::search(int key) {
    Node *temp = root;
    bool found = false;

    while (temp != NULL) {
        if (key == temp->key) {
            found = true;
            break;
        }
        else {
            if (key < temp->key)
                temp = temp->left;
            else
                temp = temp->right;
        }
    }

    if (found) {
        cout<<"\nFound! ["<<temp->key<<":"<<temp->value<<"]";
    }
    else {
        cout<<"\nNot Found!";
    }
}


void BST::showSwapped() {
    swap(root);
    cout<<"\nTraversal after swapping:";
    traversal();
}


void BST::swap(Node* root) {
    Node *curr = root;
    if (curr == NULL)
        return;
    
    swap(curr->left);
    swap(curr->right);

    Node *temp = curr->left;
    curr->left = curr->right;
    curr->right = temp;
}


void BST::minmax() {
    Node *minkey = min(root);
    Node *maxkey = max(root);
    cout<<"\nMinimum: ["<<minkey->key<<":"<<minkey->value<<"]";
    cout<<"\nMaximum: ["<<maxkey->key<<":"<<maxkey->value<<"]";
}


Node* BST::min(Node* root) {
    Node *temp = root;

    while (temp && temp->left != NULL) {
        temp = temp->left;
    }

    return temp;
}


Node* BST::max(Node* root) {
    Node *temp = root;

    while (temp && temp->right != NULL) {
        temp = temp->right;
    }

    return temp;
}


void BST::showHeight() {
    cout<<"Height = "<<height(root);
}


int BST::height(Node* root) {
    if (root == NULL)
        return 0;
    int l = height(root->left);
    int r = height(root->right);
    if (l > r)
        return (1 + height(root->left));
    else
        return (1 + height(root->right));
}


int main() {
    BST t;
    int ch, k;
    char ans = 'y';

    do
    {
        cout<<"\n1. Insert\n2. Traverse\n3. Search\n4. Height\n5. Min/Max\n6. Swap\n7. Delete\nEnter choice: ";
        cin>>ch;

        switch(ch) 
        {
            case 1:
            t.insert();
            break;

            case 2:
            t.traversal();
            break;

            case 3:
            cout<<"\nEnter key to search: ";
            cin>>k;
            t.search(k);
            break;

            case 4:
            t.showHeight();
            break;

            case 5:
            t.minmax();
            break;
            
            case 6:
            t.showSwapped();
            break;

            case 7:
            cout<<"\nEnter key to delete: ";
            cin>>k;
            t.del(k);
            break;

            default:
            cout<<"\nInvalid choice!";
            break;
        }

        cout<<"\nContinue? (y/n): ";
        cin>>ans;

    } while (ans == 'y' || ans == 'Y');
}