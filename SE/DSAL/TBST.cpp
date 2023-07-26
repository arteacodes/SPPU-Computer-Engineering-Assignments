/*
Create an inordered threaded binary search tree. Perform inorder, preorder traversals without recursion and deletion of a node. Analyze time and space complexity of the algorithm.
*/

#include <iostream>
using namespace std;

class Node
{
    int data;
    Node* left;
    Node* right;
    bool lbit;
    bool rbit;
    // 1 = child exists, 0 = thread exists

    public:
    Node() {
        data = 0;
        left = NULL;
        right = NULL;
        lbit = 0;
        rbit = 0;
    }

    Node(int d) {
        data = d;
        left = NULL;
        right = NULL;
        lbit = 0;
        rbit = 0;
    }

    friend class TBST;
};


class TBST
{
    Node *head, *root;

    public:
    TBST() {
        head = NULL;
        root = NULL;
    }

    Node* getRoot() {
        return root;
    }

    void insert(int);
    void inorder();
    void preorder();
    bool search(int, Node*&, Node*&);
    void del(Node*&, Node*&);
};


void TBST::insert(int d)
{
    if (root == NULL) {
        head = new Node(-99);
        head->right = head;

        root = new Node(d);
        head->left = root;
        head->lbit = 1;
        root->left = head;
        root->right = head;

        return;
    }
    else {
        Node* parent = root;
        Node* temp = new Node(d);
        while (true) {
            if (d == parent->data) {
                cout<<"\nNode already exists.";
                delete temp;
                temp = NULL;
                return;
            }
            
            else if (d > parent->data) {
                if (parent->rbit == 1)
                    parent = parent->right;
                else {
                    temp->right = parent->right;
                    temp->left = parent;
                    parent->right = temp;
                    parent->rbit = 1;
                    break;
                }
            }
        
            else {
                if (parent->lbit == 1)
                    parent = parent->left;
                else {
                    temp->left = parent->left;
                    temp->right = parent;
                    parent->left = temp;
                    parent->lbit = 1;
                    break;
                }
            }
        }
    }
}


void TBST::inorder() {
    Node* temp = root;
    cout<<"\nInorder: ";

    // find leftmost node
    while (temp->lbit == 1)
        temp = temp->left;

    while (temp != head) {
        cout<<temp->data<<" ";

        // if thread exists, find directly
        if (temp->rbit == 1) {
            temp = temp->right;
            while (temp->lbit == 1)
                temp = temp->left;
        }
        // else go to leftmost child in right subtree
        else {
            temp = temp->right;
        }
    }
}


void TBST::preorder() {
    Node* temp = root;
    bool flag = 0; //decides to print or not based on if next temp is a child or thread
    cout<<"\nPreorder: ";

    while (temp != head) {
        if (flag == 0) {
            cout<<temp->data<<" ";
        }

        if (flag==0 && temp->lbit==1) {
            temp = temp->left;
        }
        else {
            if (temp->rbit == 1)
				flag = 0;
			else
				flag = 1;
            temp = temp->right;
        }
    }
}


bool TBST::search(int key, Node* &curr, Node* &parent) {
    while (curr!=head) {
        if (key == curr->data) {
            return true;
        }
        else {
            parent = curr;
            if (key < curr->data)
                curr = curr->left;
            else
                curr = curr->right;
        }
    }
    return false;
}


void TBST::del(Node* &t, Node* &p) {
    // case 1 - both children exist
    if (t->lbit==1 && t->rbit==1) {
        // traverse to leftmost element of right subtree 
        // to find inorder successor
        Node *sc = t->right;
        p = t;
        while (sc->lbit == 1) {  
            p = sc;
            sc = sc->left;
        }
        t->data = sc->data;
        t = sc;
    }

    // case 2 - leaf node (both threads exist)
    if (t->lbit==0 && t->rbit==0) {
        // if node is left child
        if (p->left == t) {
            p->left = t->left;
            p->lbit = 0;
        }
        // if node is right child
        else {
            p->right = t->right;
            p->rbit = 0;
        }
        delete t;
    }

    // case 3 - left child, right thread
    if (t->lbit==1 && t->rbit==0) {

        Node* temp = t->left;  // store child

        if (p->left == t) {  // if node is left child
            p->left = temp;
        }
        else {
            p->right = temp;
        }

        // largest element in left subtree
        while (temp->rbit == 1) {
            temp = temp->right;
        }
        temp->right = t->right;
        delete t;
    }

    // case 4 - right child, left thread
    if (t->rbit==1 && t->lbit==0) {
        
        Node* temp = t->right;  // store child
        
        if (p->left == t) {
            p->left = temp;
        }
        else {
            p->right = temp;
        }

        // smallest element in right subtree
        while (temp->lbit == 1) {
            temp = temp->left;
        }
        temp->left = t->left;
        delete t;
    }
}


int main() {
    TBST t;
    int ch, k, n;
    char ans = 'y';
    Node *curr, *parent;

    do
    {
        cout<<"\n1. Insert\n2. Inorder\n3. Preorder\n4. Delete\nEnter choice: ";
        cin>>ch;

        switch(ch) 
        {
            case 1:
            cout<<"\nEnter no. of values: ";
            cin>>n;
            while (n!=0) {
                cout<<"Enter data: ";
                cin>>k;
                t.insert(k);
                n--;
            }
            break;

            case 2:
            t.inorder();
            break;

            case 3:
            t.preorder();
            break;

            case 4:
            cout<<"Enter value to delete: ";
            cin>>k;
            curr = t.getRoot();
            parent = NULL;
            if (t.search(k, curr, parent)) {
                t.del(curr, parent);
                cout<<k<<" deleted.";
            }
            else {
                cout<<k<<" not found.";
            }
            break;

            default:
            cout<<"\nInvalid choice!";
            break;
        }

        cout<<"\nContinue? (y/n): ";
        cin>>ans;

    } while (ans == 'y' || ans == 'Y');
}