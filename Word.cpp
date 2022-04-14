//
// Created by Karina Shin on 4/9/2022.
//

#include "Word.h"

Word::Word()
{
    str = "";
}
Word::Word(string word)
{
    str = word;
}

bool Word::operator<(const Word& w)
{
    //TODO organize by str?
}

bool Word::operator==(const Word& w)
{
    return str == w.str;//if theyre the same string, theyre the same word
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

void Word::stemming()
{
    Porter2Stemmer::trim(str);//TODO error undefined reference
    Porter2Stemmer::stem(str);
}

string Word::getStr() { return str; }
vector<Document> Word::getDocs() { return docs; }

void Word::incrFreq(Document& doc)
{
    for (int i = 0; i < docs.size(); i++){
        if (docs.at(i) == doc){//found doc
            frequency.at(i)++;//increment corresponding freq for existing doc
            return;
        }
    }
    //if function didn't return, no doc was found
    docs.push_back(doc);//add new doc to word's index
    frequency.push_back(1);//frequency that corresponds to the current doc
}

vector<int> Word::getFrequency() { return frequency; }
int Word::getTotal() { return total; }