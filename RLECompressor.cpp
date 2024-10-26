#include "RLECompressor.h"


std::string RLECompressor::readFile(const std::string& filePath) {
    std::ifstream inputFile(filePath);
    if (!inputFile) {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier " << filePath << std::endl;
        return "";
    }

    std::string content((std::istreambuf_iterator<char>(inputFile)),
                         std::istreambuf_iterator<char>());
    inputFile.close();
    return content;
}

// Écrire le contenu dans un fichier
void RLECompressor::writeFile(const std::string& filePath, const std::string& content) {
    std::ofstream outputFile(filePath);
    if (!outputFile) {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier " << filePath << std::endl;
        return;
    }

    outputFile << content;
    outputFile.close();
}

std::string RLECompressor::compress(const std::string& input) {
    std::string result = "";  
    int count = 1;             

   
    for (size_t i = 1; i < input.length(); i++) {
       
        if (input[i] == input[i-1]) {

            count++; 
        } else {
            
            result += input[i - 1] + std::to_string(count);
            count = 1;  
        }
    }

    result += input[input.length() - 1] + std::to_string(count);

    return result;
}


std::string RLECompressor::decompress(const std::string& input) {
    std::string result = "";  
    
    for (size_t i = 0; i < input.length();) {

        char ch = input[i];    
        i++;  
        
        std::string countStr = "";
       
        while (i < input.length() && std::isdigit(input[i])) {

            countStr += input[i];
            i++;
        }
        
        if (countStr.empty()) {
            
            std::cerr << "Erreur : aucun nombre trouvé après le caractère '" << ch << "'." << std::endl;
            return "";
        }
        
        int count = std::stoi(countStr);   
        result += std::string(count, ch);  
    }
    
    return result;
}
