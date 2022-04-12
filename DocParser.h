//
// Created by Karina Shin on 4/9/2022.
//

#ifndef INC_22S_FINAL_PROJ_DOCPARSER_H
#define INC_22S_FINAL_PROJ_DOCPARSER_H

#include <iostream>
#include <fstream>
#include <dirent.h>
#include <filesystem>
#include <sys/stat.h>
#include "DSAVLTree.h"
#include "Word.h"
#include "include/rapidjson/document.h"

using namespace std;
namespace fs = std::filesystem;

class DocParser {
private:
    DSAVLTree<Word> words;
    DSAVLTree<Word> orgs;
    DSAVLTree<Word> people;

public:
    void parse(const string& filename);
    void getFiles(const string& directory);
};


#endif //INC_22S_FINAL_PROJ_DOCPARSER_H
