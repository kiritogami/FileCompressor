#include "huffmanCompressor.h"

int main() {
    Huffman huffman;
    
    string inputFile = "input.txt";
    string compressedFile = "compressed.huff";
    string outputFile = "output.txt";

    cout << "Compression en cours..." << endl;
    huffman.compress(inputFile, compressedFile);
    cout << "Compression terminée !" << endl;

    cout << "Décompression en cours..." << endl;
    huffman.decompress(compressedFile, outputFile);
    cout << "Décompression terminée !" << endl;

    return 0;
}
