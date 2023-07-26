/*
Beginning with an empty binary tree, Construct binary tree by inserting the values in the order given.
After constructing a binary tree perform following operations on it:
1) Perform in order / pre order and post order traversal
2) Change a tree so that the roles of the left and right pointers are swapped at every node
3) Find the height of tree 
4) Copy this tree to another [operator=]
5) Count number of leaves, number of internal nodes.
6) Erase all nodes in a binary tree.
(implement both recursive and non-recursive methods)
*/


#include <iostream>
#include <queue>
#include <stack>
using namespace std;


class Node 
{
    int data;
    Node *left;
    Node *right;

    public:
    Node() {
        data = 0;
        left = NULL;
        right = NULL;
    }

    Node(int d) {
        data = d;
        left = NULL;
        right = NULL;
    }

    friend class BT;
};


class BT
{
    Node *root;
    queue<Node*> q;

    public:
    BT() {
        root = NULL;
    }

    // recursive
    void create();
    Node* insert();

    void traverse();
    void inorder(Node*);
    void preorder(Node*);
    void postorder(Node*);

    void showSwapped();
    void swap(Node*);

    void showHeight();
    int height(Node*);

    void showCount();
    int leaf(Node*);
    int internal(Node*);

    void erase();
    void del(Node*);


    // iterative
    void itr_create();
    void itr_insert(int);

    void itr_inorder();
    void itr_preorder();
    void itr_postorder();

    void itr_del();


    // overloaded operator and method to copy tree;
    void operator = (BT b2);
    Node* copy(Node*);

    Node* getroot() {
        return root;
    }

    void setroot(Node* r) {
        root = r;
    }
};


void BT::create() {
    root = insert();
}


Node* BT::insert() {
    int d;
    cout<<"Enter data (-1 if none): ";
    cin>>d;

    //root = new Node(d);

    if (d == -1) {
        return NULL;
    }
    else {
        Node *t = new Node(d);

        cout<<"Left child of "<<d<<": ";
        t->left = insert();

        cout<<"Right child of "<<d<<": ";
        t->right = insert();

        return t;
    }
}


void BT::traverse() {
    cout<<"\nInorder: ";
    inorder(root);
    cout<<"\nPreorder: ";
    preorder(root);
    cout<<"\nPostorder: ";
    postorder(root);
}


void BT::inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        cout<<root->data<<" ";
        inorder(root->right);
    }
}


void BT::preorder(Node* root) {
    if (root == NULL)
        return;
    cout<<root->data<<" ";
    preorder(root->left);
    preorder(root->right);
}


void BT::postorder(Node* root) {
    if (root == NULL)
        return;
    postorder(root->left);
    postorder(root->right);
    cout<<root->data<<" ";
}


void BT::showSwapped() {
    swap(root);
    cout<<"\nTree swapped.";
}


void BT::swap(Node* root) {
    Node* curr = root;
    if (curr == NULL)
        return;

    swap(curr->left);
    swap(curr->right);

    Node* temp = curr->left;
    curr->left = curr->right;
    curr->right = temp;
}


void BT::showHeight() {
    cout<<"\nHeight = "<<height(root);
}


int BT::height(Node *root) {
    if (root == NULL)
        return 0;

    int l = height(root->left);
    int r = height(root->right);

    if (l > r) 
        return (1 + l);
    else
        return (1 + r);
}


void BT::showCount() {
    cout<<"\nLeaf Nodes = "<<leaf(root);
    cout<<"\nInternal Nodes = "<<internal(root);
}


int BT::leaf(Node *root) {
    if (root == NULL)
        return 0;

    if (root->left == NULL && root->right == NULL)
        return 1;  // leaf node
    else
        return (leaf(root->left) + leaf(root->right));
}


int BT::internal(Node *root) {
    if (root == NULL || (root->left == NULL && root->right == NULL))
        return 0;

    return (1 + internal(root->left) + internal(root->right));
}


void BT::erase() {
    del(root);
    cout<<"\nTree Erased.";
}


void BT::del(Node *root) {
    if (root) {
        del(root->left);
        del(root->right);
        cout<<"\nDeleting "<<root->data;
        delete root;
    }
}


// ***** ITERATIVE METHODS *****

void BT::itr_create()
{
    int n, d;
    cout<<"Enter number of values: ";
    cin>>n;

    for (int i=0; i<n; i++) {
        cout<<"Enter data: ";
        cin>>d;
        itr_insert(d);
    }
}


void BT::itr_insert(int d) {
    if (d == -1)
        return;

    if (root == NULL) {
        root = new Node(d);
        return;
    }

    Node* temp;
    q.push(root);

    while (!q.empty()) {
        temp = q.front();
        q.pop();

        if (temp->left) {
            q.push(temp->left);
        }
        else {
            temp->left = new Node(d);
            return;
        }

        if (temp->right) {
            q.push(temp->right);
        }
        else {
            temp->right = new Node(d);
            return;
        }
    }
}


void BT::itr_inorder() {
    stack<Node*> s;
    Node *temp = this->root;

    cout<<"\nInorder: ";
    while (!s.empty() || temp!=NULL) {
        if (temp!=NULL) {
            s.push(temp);
            temp = temp->left;
        }
        else {
            temp = s.top();
            s.pop();
            cout<<temp->data<<" ";
            temp = temp->right;
        }
    }
}


void BT::itr_preorder() {
    stack<Node*> s;
    Node *temp = root;
    s.push(temp);

    cout<<"\nPreorder: ";
    while (!s.empty()) {
        if (temp!=NULL) {
            cout<<temp->data<<" ";
            if (temp->right != NULL) {
                s.push(temp->right);
            }

            if (temp->left != NULL) {
                temp = temp->left;
            }
            else {
                temp = s.top();
                s.pop();
            }
        }
    }
}


void BT::itr_postorder() {
    stack<Node*> s1;  // holds child
    stack<Node*> s2;  // holds parent

    cout<<"\nPostorder: ";

    Node *temp = root;
    Node *ptr = NULL;
    
    s1.push(temp);
    while (!s1.empty()) {
        if (temp!=NULL) {
            temp = s1.top();
            s1.pop();
            s2.push(temp);
        }
        ptr = s2.top();
        if (ptr->left != NULL) 
            s1.push(ptr->left);
        if (ptr->right != NULL)
            s1.push(ptr->right);
    }

    while (!s2.empty()) {
        cout<<s2.top()->data<<" ";
        s2.pop();
    }
}


void BT::itr_del() {
    if (root == NULL)
        return;

    Node *temp;
    q.push(root);

    while (!q.empty()) {
        temp = q.front();
        cout<<"\n"<<temp->data;
        q.pop();
        
        if (temp->left)
            q.push(temp->left);
        else 
            temp = temp->left;
        
        if (temp->right)
            q.push(temp->right);
        else
            temp = temp->right;
        
        cout<<"\nDeleting "<<temp->data;
        delete temp;
    }
}


void BT::operator=(BT bt) {
    this->root = bt.copy(bt.getroot());
}


Node* BT::copy(Node* root) {
    Node* temp = NULL;

    if (root==NULL) {
        return NULL;
    }
    else {
        temp = new Node(root->data);
        temp->left = copy(root->left);
        temp->right = copy(root->right);
    }

    return temp;
}


int main() {
    BT t;
    BT copytree;
    int ch;
    char ans = 'y';

    do
    {
        cout<<"\n1. Recursive Insert\n2. Iterative Insert\n3. Recursive Traverse\n4. Iterative Traversal\n5. Height\n6. Swap\n7. Count\n8. Copy Tree\n9. Delete\nEnter choice: ";
        cin>>ch;

        switch(ch) 
        {
            case 1:
            t.create();  
            break;

            case 2:
            t.itr_create();
            break;

            case 3:
            t.traverse();
            break;

            case 4:
            t.itr_inorder();
            t.itr_preorder();
            t.itr_postorder();
            break;

            case 5:
            t.showHeight();
            break;

            case 6:
            t.showSwapped();
            break;

            case 7:
            t.showCount();
            break;

            case 8:
            copytree = t;
            cout<<"\nTraversal of copied tree: ";
            copytree.traverse();
            break;

            case 9:
            t.erase();
            break;

            default:
            cout<<"\nInvalid choice!";
            break;
        }

        cout<<"\nContinue? (y/n): ";
        cin>>ans;

    } while (ans == 'y');
}