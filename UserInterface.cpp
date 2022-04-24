//
// Created by 18476 on 4/23/2022.
//

#include "UserInterface.h"

UserInterface::UserInterface() {}

void UserInterface::clearIndex()
{
    words.deleteTree(words.getRoot());
    orgs.deleteTree(orgs.getRoot());
    persons.deleteTree(persons.getRoot());
    //TODO also erase contents of persistence file?
}

void UserInterface::parseDocs(const string& direct)
{
    std::cout << "parsing documents..." << std::endl;
    docReader.getFiles(direct, stops);
    std::cout << "done parsing!" << std::endl;
}

void UserInterface::persistentIndex()
{

}

void UserInterface::enterQuery(string& query)
{
    process.parseQuery(query, stops);
}

void UserInterface::stats()
{

}

DocParser& UserInterface::getDocParser() { return docReader; }