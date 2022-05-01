//
// Created by Karina Shin on 4/23/2022.
//

#include "StopWord.h"

StopWord::StopWord()
{
    ifstream stop;//make the stop words AVL tree
    stop.open("stopWords.txt");
    if (stop.is_open())
        cout << "OPened stops" << endl;
    string curr;
    while (getline(stop, curr))//make an avl tree of stop words
    {
        string s = curr.substr(0, curr.length()-1);//cut off end char
        stops.insert(s);
    }
}
bool StopWord::isStopWord(string& str)
{
    return stops.contains(str);//if str is in the avl tree, its a stop word
}