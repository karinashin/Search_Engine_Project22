//
// Created by Karina Shin on 4/9/2022.
//

#ifndef INC_22S_FINAL_PROJ_WORD_H
#define INC_22S_FINAL_PROJ_WORD_H

#include <string>
#include <vector>
#include "Document.h"

using namespace std;
class Word {
private:
    string str;//DSString?
    vector<Document> docs;//documents word appears in
    vector<int> frequency;//frequency for each doc word appears in
    int total = 0;

public:
    Word(string word);
    void sort();//sorts documents by index (doc with largest freq. goes first)
    bool operator<(const Word& w);
    string getStr();
    vector<Document> getDocs();
    vector<int> getFrequency();
    int getTotal();
};


#endif //INC_22S_FINAL_PROJ_WORD_H
