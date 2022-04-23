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

class UserInterface {
private:
    DocParser docReader;
    QueryProcessor process;

    DSAVLTree<Word> words;
    DSAVLTree<Word> orgs;
    DSAVLTree<Word> persons;
    DSAVLTree<string> stops;

public:
    UserInterface();
    void clearIndex();//delete every tree
    void parseDocs(string& direct);//parse all documents
    void persistentIndex();//read in persistence file to index words
    void enterQuery(string& query);
    void stats();
};


#endif //INC_22S_FINAL_PROJ_USERINTERFACE_H
