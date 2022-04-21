//
// Created by Karina Shin on 4/9/2022.
//

#ifndef INC_22S_FINAL_PROJ_WORD_H
#define INC_22S_FINAL_PROJ_WORD_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "Document.h"
#include "porter2_stemmer.h"
#include "DSAVLTree.h"

using namespace std;
class Word {
private:
    string str;
    vector<Document> docs;//documents word appears in
    vector<int> frequency;//frequency for each doc word appears in
//    DSAVLTree<string> stops;//stop words
    int total = 0;

public:
    Word();
    Word(string word);
//    Word& operator=(const Word& w);//SEG FAULT
    bool operator<(const Word& w);
    bool operator==(const Word& w);

    void sort();//sorts documents by index (doc with largest freq. goes first)
    void toLower();
    void removePunc();
//    bool isStopWord();
    void stemming();//using porter2 stemming library

    string& getStr();
    vector<Document>& getDocs();
    void printDocs();
    void incrFreq(Document& doc);//given a doc, incrememnt its corresponding freq.
    vector<int>& getFrequency();
    int getTotal();
    friend std::ostream& operator<< (std::ostream& out, const Word& w);
};


#endif //INC_22S_FINAL_PROJ_WORD_H
