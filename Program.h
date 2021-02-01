#ifndef UNTITLED_PROGRAM_H
#define UNTITLED_PROGRAM_H

#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
#define TEN 10

using namespace std;


class Program {
public:
    struct Node {
        char letter;
        int frequency;
        Node *left, *right;
    };
    Node* getNode(char letter, int frequency, Node* left, Node* right){
        Node* node = new Node();
        node->letter = letter;
        node->frequency = frequency;
        node->left = left;
        node->right = right;
        return node;
    }

    struct order{
        bool operator()(Node* l, Node* r){
            return l->frequency > r->frequency;
        }
    };

    void encode(Node* root, string encoding,unordered_map<char, string> &huffman){
        if (root == nullptr){
            return;
        }

        if (!root->left && !root->right) {
            huffman[root->letter] = encoding;
        }
        encode(root->left, encoding + "0", huffman);
        encode(root->right, encoding + "1", huffman);
    }

    void print(Node* root, string encoding,unordered_map<char, string> &huffman){
        if (root == nullptr)
            return;
        if (!root->left && !root->right) {
            huffman[root->letter] = encoding;
        }

    }

    void printTree(Node *root,unordered_map<char, string> &huffman, int number,ofstream& fout){
        if (root == NULL){
            return;
        }

        number += TEN;

        printTree(root->right,huffman, number,fout);
        fout<<"tree";

        for (int i = TEN; i < number; i++){
            fout<<"-";
        }

        if(!root->letter){
            fout<<"|";
        }

        fout<<root->letter<<endl;

        printTree(root->left,huffman, number,fout);
    }


    void decode(Node* root, int &index, string decoding,ofstream& fout){
        if (root == nullptr) {
            return;
        }

        if (!root->left && !root->right)
        {
            fout << root->letter;
            return;
        }

        index++;
        if (decoding[index] =='0')
            decode(root->left, index, decoding,fout);
        else
            decode(root->right, index, decoding,fout);
    }

    void createHuffmanTree(string text,ofstream& fout){

        unordered_map<char, int> frequency;

        for (char letter: text) {
            frequency[letter]++;
        }

        priority_queue<Node*, vector<Node*>, order> priorityQueue;

        for (auto branch: frequency) {
            priorityQueue.push(getNode(branch.first, branch.second, nullptr, nullptr));
        }

        while (priorityQueue.size() != 1){
            Node *left = priorityQueue.top(); priorityQueue.pop();
            Node *right = priorityQueue.top();	priorityQueue.pop();
            int total = left->frequency + right->frequency;
            priorityQueue.push(getNode('\0', total, left, right));
        }

        Node* root = priorityQueue.top();

        unordered_map<char, string> huffman;
        encode(root, "", huffman);

        for (auto branch: huffman) {
            fout << "Codes-"<<branch.first <<" "<< branch.second<<endl;
        }

        string encoding = "";
        for (char ch: text) {
            encoding += huffman[ch];
        }

        fout << "EncodedString-" << encoding <<endl;
        cout<<encoding<<endl;

        int index = -1;
        fout << "DecodedString-";
        while (index < (int)encoding.size() - 2) {
            decode(root, index, encoding,fout);
        }
        fout<<endl;

        printTree(root,huffman,0,fout);
    }
};


#endif //UNTITLED_PROGRAM_H
