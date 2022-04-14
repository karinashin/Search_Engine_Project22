//
// Created by Karina Shin on 4/9/2022.
//

#ifndef INC_22S_FINAL_PROJ_WORD_H
#define INC_22S_FINAL_PROJ_WORD_H

#include <string>
#include <vector>
#include <fstream>
#include "Document.h"
#include "porter2_stemmer.h"

using namespace std;
class Word {
private:
    string str;//DSString?
    vector<Document> docs;//documents word appears in
    vector<int> frequency;//frequency for each doc word appears in
    int total = 0;

public:
    Word();
    Word(string word);
    void sort();//sorts documents by index (doc with largest freq. goes first)
    bool operator<(const Word& w);
    bool operator==(const Word& w);
    void toLower();
    void removePunc();
    bool isStopWord();
    void stemming();//using porter2 stemming library

    string getStr();
    vector<Document> getDocs();
    void incrFreq(Document& doc);//given a doc, incrememnt its corresponding freq.
    vector<int> getFrequency();
    int getTotal();
};


#endif //INC_22S_FINAL_PROJ_WORD_H
