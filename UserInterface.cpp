//
// Created by 18476 on 4/23/2022.
//

#include "UserInterface.h"

UserInterface::UserInterface()
{
    ifstream stop;//make the stop words AVL tree
    stop.open("stopWords.txt");
    string curr;
    while (getline(stop, curr))//make an avl tree of stop words
    {
        string s = curr.substr(0, curr.length()-1);//cut off end char
        stops.insert(s);
    }
}

void UserInterface::clearIndex()
{
    words.deleteTree(words.getRoot());
    orgs.deleteTree(orgs.getRoot());
    persons.deleteTree(persons.getRoot());
    //TODO also erase contents of persistence file?
}

void UserInterface::parseDocs(string& direct)
{
    std::cout << "parsing documents..." << std::endl;
    docReader.parse(direct);
    std::cout << "done parsing!" << std::endl;
}

void UserInterface::persistentIndex()
{

}

void UserInterface::enterQuery(string& query)
{
    process.parseQuery(query);
}

void UserInterface::stats()
{

}