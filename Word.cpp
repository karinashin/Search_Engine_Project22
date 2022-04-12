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

void Word::toLower()
{
    for (int i = 0; i < str.length(); i++)
        tolower(str.at(i));
}

void Word::removePunc()
{
    string buffer;//no punc string
    for (int i = 0; i < str.length(); ++i)
    {
        if (str.at(i) != '.' && str.at(i) != '!' && str.at(i) != '?' && str.at(i) != ',' && str.at(i) != ';' && str.at(i) != ':' && str.at(i) != '\"')//only add if its a letter
            buffer += str.at(i);
    }
    str = buffer;
}

bool Word::isStopWord()
{
    ifstream stop;
    stop.open("stopWords.txt");
    string curr;
    while (getline(stop, curr))//go through entire list of stop words
    {
        if (curr == str)//the current string is a stop word
            return true;
    }
    return false;
}

string Word::getStr() { return str; }
vector<Document> Word::getDocs() { return docs; }
vector<int> Word::getFrequency() { return frequency; }
int Word::getTotal() { return total; }