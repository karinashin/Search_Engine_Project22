//
// Created by Karina Shin on 4/9/2022.
//

#ifndef INC_22S_FINAL_PROJ_DOCPARSER_H
#define INC_22S_FINAL_PROJ_DOCPARSER_H

#include <iostream>
#include <fstream>
#include <dirent.h>
#include <filesystem>
#include <vector>
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
    DSAVLTree<string> stops;

public:
    DocParser();
    void parse(const string& filename);//parse the documents and create 3 AVLTrees
    void getFiles(const string& directory);//returns filenames for traversal through directory
    vector<Document>& findIndex(Word& obj);//return the document index of a given Word object
    bool isStopWord(string& str);

    vector<Document>& findWordIndex(Word& w);
    vector<Document>& findOrgIndex(Word& org);
    vector<Document>& findPersonIndex(Word& p);

    DSAVLTree<Word>& getWordTree();
    DSAVLTree<Word>& getOrgTree();
    DSAVLTree<Word>& getPersonTree();
};


#endif //INC_22S_FINAL_PROJ_DOCPARSER_H
