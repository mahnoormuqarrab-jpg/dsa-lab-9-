#include <iostream>
#include <string>
using namespace std;
struct Node {
    string word;
    int freq;
    Node *left, *right;
    Node(string w) { word = w; freq = 1; left = right = NULL; }
};
class WordBST {
    Node* root;
    int uniqueWords;
    int totalWords;
    // insert a word, or increase its count if it already exists
    Node* insert(Node* node, string w) {
        if (node == NULL) {
            uniqueWords++;
            return new Node(w);
        }
        if (w < node->word) node->left = insert(node->left, w);
        else if (w > node->word) node->right = insert(node->right, w);
        else node->freq++;
        return node;
    }
    void alphabetical(Node* node) {
        if (node == NULL) return;
        alphabetical(node->left);
        cout << node->word << " : " << node->freq << endl;
        alphabetical(node->right);
    }
    // print only the words that have exactly this frequency
    void printWithFreq(Node* node, int f) {
        if (node == NULL) return;
        printWithFreq(node->left, f);
        if (node->freq == f)
            cout << node->word << " : " << node->freq << endl;
        printWithFreq(node->right, f);
    }
    int maxFreq(Node* node) {
        if (node == NULL) return 0;
        int m = node->freq;
        int l = maxFreq(node->left);
        int r = maxFreq(node->right);
        if (l > m) m = l;
        if (r > m) m = r;
        return m;
    }
public:
    WordBST() { root = NULL; uniqueWords = 0; totalWords = 0; }
    // make the word lowercase, then insert it
    void addWord(string w) {
        for (int i = 0; i < w.length(); i++)
            w[i] = tolower(w[i]);
        totalWords++;
        root = insert(root, w);
    }
    // read the paragraph and pull out each word (letters only)
    void readText(string text) {
        string word = "";
        for (int i = 0; i < text.length(); i++) {
            if (isalpha(text[i])) {
                word += text[i];
            } else if (word != "") {
                addWord(word);
                word = "";
            }
        }
        if (word != "") addWord(word);
    }
    void displayAlphabetical() {
        cout << " Alphabetical " << endl;
        alphabetical(root);
    }
    // go from the highest frequency down to 1
    void displayByFrequency() {
        cout << " By Frequency " << endl;
        for (int f = maxFreq(root); f >= 1; f--)
            printWithFreq(root, f);
    }
    void findMostFrequentWord() {
        int m = maxFreq(root);
        cout << " Most Frequent Word " << endl;
        printWithFreq(root, m);
    }
    void summary() {
        cout << " Summary " << endl;
        cout << "Unique words: " << uniqueWords << endl;
        cout << "Total words: " << totalWords << endl;
    }
};
int main() {
    string text = "The quick brown fox jumps over the lazy dog. The fox is quick and smart.";
    WordBST tree;
    tree.readText(text);
    tree.displayAlphabetical();
    cout << endl;
    tree.displayByFrequency();
    cout << endl;
    tree.findMostFrequentWord();
    cout << endl;
    tree.summary();
    return 0;
}