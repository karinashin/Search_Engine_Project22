//
// Created by Karina Shin on 4/23/2022.
//

#ifndef INC_22S_FINAL_PROJ_USERINTERFACE_H
#define INC_22S_FINAL_PROJ_USERINTERFACE_H

#include <iostream>
#include <chrono>
#include "DocParser.h"
#include "QueryProcessor.h"
#include "DSAVLTree.h"
#include "Word.h"
#include "Document.h"
#include "StopWord.h"
#include "include/rapidjson/document.h"

using namespace std;

class UserInterface {
private:
    DocParser docReader;
    QueryProcessor process;
    StopWord stops;

public:
    UserInterface();
    void run(const string& file);//run search engine
    void clearIndex();//delete every tree
    void parseDocs(const string& direct);//parse all documents
    void displayResults();
    void showText(Document& d);
    void stats();
    void getTopWords();//prints out top 25 most frequent words
    DocParser& getDocParser();//used to access word/org/person avl trees
};


#endif //INC_22S_FINAL_PROJ_USERINTERFACE_H
