#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <queue>
#include <vector>
#include <bitset>
#include <cstring>


using namespace std;

struct Node {
    char ch;
    int freq;
    Node* left;
    Node* right;

    Node(char c, int f) {
        ch = c;
        freq = f;
        left = nullptr;
        right = nullptr;
    }
};

// Comparateur pour la file de priorité
struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

class Huffman {
public:
    void compress(string inputFile, string outputFile);
    void decompress(string inputFile, string outputFile);

private:
    void buildTree(string text);
    void generateCodes(Node* root, string code);
    void writeBinaryFile(string filename, string encodedText);
    string readBinaryFile(string filename);

    Node* root;
    unordered_map<char, string> huffmanCodes;
    unordered_map<string, char> reverseCodes;
};

#endif
