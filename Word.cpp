//
// Created by Karina Shin on 4/9/2022.
//

#include "Word.h"

Word::Word(string word)
{
    str = word;
}

bool Word::operator<(const Word& w)
{
    //TODO organize by str?
}

void Word::sort()
{
    //TODO
}

string Word::getStr() { return str; }
vector<Document> Word::getDocs() { return docs; }
vector<int> Word::getFrequency() { return frequency; }
int Word::getTotal() { return total; }