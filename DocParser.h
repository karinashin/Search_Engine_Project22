//
// Created by Karina Shin on 4/9/2022.
//

#ifndef INC_22S_FINAL_PROJ_DOCPARSER_H
#define INC_22S_FINAL_PROJ_DOCPARSER_H

#include "DSAVLTree.h"
#include "Word.h"

class DocParser {
private:
    DSAVLTree<Word> words;
    DSAVLTree<Word> orgs;
    DSAVLTree<Word> people;

public:
    void parse();//TODO add arg
};


#endif //INC_22S_FINAL_PROJ_DOCPARSER_H
