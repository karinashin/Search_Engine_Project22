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

//Word& Word::operator=(const Word& w)
//{
//    str = w.str;
//    docs = w.docs;
//    frequency = w.frequency;
//    total = w.total;
//}

bool Word::operator<(const Word& w)
{
    if (str < w.str)
        return true;
    return false;
}

bool Word::operator==(const Word& w)
{
    return str == w.str;//if theyre the same string, theyre the same word
}
//
//void Word::sort()
//{
//    //TODO
//}

void Word::toLower()
{
    for (int i = 0; i < str.length(); i++)
        str.at(i) = tolower(str.at(i));
}

void Word::removePunc()
{
    string buffer;//no punc string
    for (int i = 0; i < str.length(); ++i)
    {
        if (str.at(i) != '.' && str.at(i) != '!' && str.at(i) != '?' && str.at(i) != ',' && str.at(i) != ';' && str.at(i) != ':' && str.at(i) != '\"' && str.at(i) != '\n')//only add if its a letter
            buffer += str.at(i);
    }
    str = buffer;
}

void Word::stemming()
{
    Porter2Stemmer::trim(str);
    Porter2Stemmer::stem(str);
}

string& Word::getStr() { return str; }
vector<Document>& Word::getDocs() { return docs; }

void Word::printDocs()
{
    for (int i = 0; i < docs.size(); i++)
    {
//        cout << docs.at(i).getID() << endl;
        cout << docs.at(i).getPath() << endl;
    }
    cout << endl;
}

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

int Word::getDocFreq(Document& doc)
{
   for (int i = 0; i < docs.size(); i++)
   {
       if (docs.at(i) == doc)
           return frequency.at(i);//return corresponding freq. for given doc
   }
   cout << "Doc not found." << endl;
}

vector<int>& Word::getFrequency() { return frequency; }
int Word::getTotal() { return total; }
std::ostream& operator<< (std::ostream& out, const Word& w)
{
    out << w.str;
    return out;
}