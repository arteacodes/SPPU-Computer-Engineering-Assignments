#include <bits/stdc++.h>
using namespace std;

// a node of the huffman tree
struct Node {
    char data;
    int freq;
    Node *left;
    Node *right;

    Node (char d, int f) {
        left = right = NULL;
        data = d;
        freq = f;
    }
};

// for comparison of 2 heap nodes (structs)
struct compare {
    bool operator() (Node* left, Node* right) {
        return left->freq > right->freq;
    }
};

// prints huffman codes from root of the tree
void printCodes(Node *root, string str) {
    if (!root)
        return;
    
    if (root->data != '$')
        cout << root->data << ": " << str << endl;

    printCodes(root->left, str + "0");
    printCodes(root->right, str + "1");
}

// main function to build the Huffman Tree
void huffmanTree(vector<char>& data, vector<int>& freq, int size) {
    struct Node *left, *right, *top;

    // create a min-heap and insert all characters in data[]
    priority_queue<Node*, vector<Node*>, compare> minHeap;

    for (int i = 0; i < size; i++) {
        minHeap.push(new Node(data[i], freq[i]));
    }

    // iterate while size of heap is not 1
    while (minHeap.size() != 1) {
        // extract 2 minimum frequency items from the heap
        left = minHeap.top();
        minHeap.pop();

        right = minHeap.top();
        minHeap.pop();

        // create new parent node with frequency = sum of frequencies of the 2 extracted nodes
        int frequencySum = left->freq + right->freq;
        top = new Node('$', frequencySum);

        // make the 2 nodes as left and right child of this parent node, and add it to minheap
        top->left = left;
        top->right = right;
        minHeap.push(top);
    }

    printCodes(minHeap.top(), "");
}

int main() {
    int size;
    cout << "Enter the number of characters: ";
    cin >> size;

    vector<char> data(size);
    vector<int> freq(size);

    cout << "Enter the characters: ";
    for (int i = 0; i < size; i++) {
        cin >> data[i];
    }

    cout << "Enter the frequencies of the characters: ";
    for (int i = 0; i < size; i++) {
        cin >> freq[i];
    }

    huffmanTree(data, freq, size);

    return 0;
}
