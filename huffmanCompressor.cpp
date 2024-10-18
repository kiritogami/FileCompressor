#include "huffmanCompressor.h"


void Huffman::buildTree(string text) {
    
    unordered_map<char, int> freq;
    for (int i = 0; i < text.length(); i++) {

        freq[text[i]]++;
    }

    priority_queue<Node*, vector<Node*>, Compare> p;
    for (auto pair : freq) {

        p.push(new Node(pair.first, pair.second));
    }

    while (p.size() > 1) {

        Node* left = p.top(); p.pop();
        Node* right = p.top(); p.pop();

        Node* newNode = new Node('\0', left->freq + right->freq);

        newNode->left = left;
        newNode->right = right;

        p.push(newNode);
    }

    root = p.top();
    generateCodes(root, "");
}


void Huffman::generateCodes(Node* node, string code) {

    if (!node) return;

    if (node->ch != '\0') {

        huffmanCodes[node->ch] = code;
        reverseCodes[code] = node->ch;
    }

    generateCodes(node->left, code + "0");
    generateCodes(node->right, code + "1");
}


void Huffman::writeBinaryFile(string filename, string encodedText) {

    ofstream file(filename, ios::binary);

    int textSize = encodedText.size();
    char buffer[sizeof(textSize)];
    std::memcpy(buffer, &textSize, sizeof(textSize));
    file.write(buffer, sizeof(buffer)); 

    bitset<8> bits;
    int count = 0;
    for (char bit : encodedText) {

        bits[7 - count] = (bit == '1');
        count++;
        if (count == 8) {

            char byte = static_cast<char>(bits.to_ulong());  
            file.write(&byte, sizeof(byte));  
            bits.reset();
            count = 0;
        }
    }

    if (count > 0) {

        char byte = static_cast<char>(bits.to_ulong()); 
        file.write(&byte, sizeof(byte));  
    }

    file.close();
}


string Huffman::readBinaryFile(string filename) {

    ifstream file(filename, ios::binary);
    
    
    char sizeBuffer[sizeof(int)];
    file.read(sizeBuffer, sizeof(int));
    int textSize = 0;

    for (int i = 0; i < sizeof(int); ++i) {

        textSize |= (static_cast<unsigned char>(sizeBuffer[i]) << (8 * (sizeof(int) - 1 - i)));
    }

    
    string binaryText;
    char byte;

    while (file.read(&byte, sizeof(byte))) {
        bitset<8> bits(static_cast<unsigned char>(byte));
        binaryText += bits.to_string();
    }

    return binaryText.substr(0, textSize);
}


void Huffman::compress(string inputFile, string outputFile) {
    ifstream file(inputFile);
    if (!file) {
        cerr << "Erreur : Impossible d'ouvrir " << inputFile << endl;
        return;
    }

    string text((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();

    buildTree(text);
    string encodedText;
    for (char c : text) {
        encodedText += huffmanCodes[c];
    }

    writeBinaryFile(outputFile, encodedText);
}


void Huffman::decompress(string inputFile, string outputFile) {
    string encodedText = readBinaryFile(inputFile);

    ofstream file(outputFile);
    if (!file) {
        cerr << "Erreur : Impossible d'ouvrir " << outputFile << endl;
        return;
    }

    string temp;
    for (char bit : encodedText) {
        temp += bit;
        if (reverseCodes.find(temp) != reverseCodes.end()) {
            file << reverseCodes[temp];
            temp = "";
        }
    }

    file.close();
}
