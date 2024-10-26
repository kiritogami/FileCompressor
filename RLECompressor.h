#ifndef RLECOMPRESSOR_H
#define RLECOMPRESSOR_H

#include <string>
#include <iostream>
#include <fstream> 
#include <iterator>  
#include <string>  

class RLECompressor {

    public :
        std::string compress(const std::string& input);
        std::string decompress(const std::string& input);
        std::string readFile(const std::string& filePath);
        void writeFile(const std::string& filePath, const std::string& content);
    };

#endif 
