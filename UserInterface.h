//
// Created by Karina Shin on 4/23/2022.
//

#ifndef INC_22S_FINAL_PROJ_USERINTERFACE_H
#define INC_22S_FINAL_PROJ_USERINTERFACE_H

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
    int totalArticle;//total number of articles indexed
//    DSAVLTree<Word> words;
//    DSAVLTree<Word> orgs;
//    DSAVLTree<Word> persons;

public:
    UserInterface();
    void clearIndex();//delete every tree
    void parseDocs(const string& direct);//parse all documents
    void enterQuery(string& query);
    void displayResults();
    void showText(Document& d);
    void stats();
    DocParser& getDocParser();//used to access word/org/person avl trees
};


#endif //INC_22S_FINAL_PROJ_USERINTERFACE_H
