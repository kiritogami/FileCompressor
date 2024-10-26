#include "huffmanCompressor.h" 
#include "RLECompressor.h"

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

    std::string text = "aaabbbccccdddddd";

    RLECompressor rle;  

    // Test de la compression
    std::string compressedText = rle.compress(text);
    std::cout << "Texte compressé (RLE) : " << compressedText << std::endl;

    // Test de la décompression
    std::string decompressedText = rle.decompress(compressedText);
    std::cout << "Texte décompressé : " << decompressedText << std::endl;



    return 0;
}
