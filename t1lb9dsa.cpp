#include <iostream>
#include <stack>
using namespace std;
struct Node {
    int key;
    Node *left, *right;
    Node(int k) { key = k; left = right = NULL; }
};
// insert a key into the BST
Node* insert(Node* root, int key) {
    if (root == NULL) return new Node(key);
    if (key < root->key) root->left = insert(root->left, key);
    else if (key > root->key) root->right = insert(root->right, key);
    return root;
}
// inorder traversal (gives sorted order)
void inorder(Node* root) {
    if (root == NULL) return;
    inorder(root->left);
    cout << root->key << " ";
    inorder(root->right);
}
// find predecessor and successor of a key
void findPredSucc(Node* root, int key) {
    Node* pred = NULL;
    Node* succ = NULL;
    Node* cur = root;
    while (cur != NULL) {
        if (key < cur->key) {
            succ = cur;
            cur = cur->left;
        } else if (key > cur->key) {
            pred = cur;
            cur = cur->right;
        } else {
            // key found: predecessor is the max of left subtree
            if (cur->left != NULL) {
                pred = cur->left;
                while (pred->right != NULL) pred = pred->right;
            }
            // successor is the min of right subtree
            if (cur->right != NULL) {
                succ = cur->right;
                while (succ->left != NULL) succ = succ->left;
            }
            break;
        }
    }
    if (pred != NULL) cout << "Predecessor of " << key << ": " << pred->key << endl;
    else cout << "Predecessor of " << key << ": none" << endl;
    if (succ != NULL) cout << "Successor of " << key << ": " << succ->key << endl;
    else cout << "Successor of " << key << ": none" << endl;
}
// range query - recursive version
int comparisonsRec = 0;
void rangeRecursive(Node* root, int low, int high) {
    if (root == NULL) return;
    comparisonsRec++;
    if (root->key > low)                 // left side may have valid keys
        rangeRecursive(root->left, low, high);
    comparisonsRec += 2;
    if (root->key >= low && root->key <= high)
        cout << root->key << " ";
    comparisonsRec++;
    if (root->key < high)                // right side may have valid keys
        rangeRecursive(root->right, low, high);
}
// range query - iterative version (using a stack)
int rangeIterative(Node* root, int low, int high) {
    int comparisons = 0;
    stack<Node*> s;
    Node* cur = root;
    while (cur != NULL || !s.empty()) {
        while (cur != NULL) {
            comparisons++;
            if (cur->key >= low) {
                s.push(cur);
                cur = cur->left;
            } else {
                cur = cur->right;        // too small, skip left side
            }
        }
        if (s.empty()) break;
        cur = s.top();
        s.pop();
        comparisons++;
        if (cur->key > high) break;      // too big, stop
        cout << cur->key << " ";
        cur = cur->right;
    }
    return comparisons;
}
int main() {
    int arr[] = {50, 30, 70, 20, 40, 60, 80, 35, 45, 65, 85};
    Node* root = NULL;
    for (int i = 0; i < 11; i++)
        root = insert(root, arr[i]);
    cout << "Inorder: ";
    inorder(root);
    cout << endl << endl;
    findPredSucc(root, 40);
    cout << endl;
    cout << "Range [30, 70] recursive: ";
    rangeRecursive(root, 30, 70);
    cout << endl;
    cout << "Range [30, 70] iterative: ";
    int comparisonsIter = rangeIterative(root, 30, 70);
    cout << endl << endl;
    cout << "Comparisons (recursive): " << comparisonsRec << endl;
    cout << "Comparisons (iterative): " << comparisonsIter << endl;
    return 0;
}