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
    int total = 0;

public:
    Word();
    Word(string word);
    bool operator<(const Word& w);
    bool operator==(const Word& w);

    void toLower();
    void removePunc();
    void stemming();//using porter2 stemming library

    string& getStr();
    vector<Document>& getDocs();
    void printDocs();
    void incrFreq(Document& doc);//given a doc, incrememnt its corresponding freq.
    vector<int>& getFrequency();
    int getDocFreq(Document& doc);//get the frequency of a specific doc for a word
    int getTotal();
    friend std::ostream& operator<< (std::ostream& out, const Word& w);
};


#endif //INC_22S_FINAL_PROJ_WORD_H
