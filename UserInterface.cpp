//
// Created by 18476 on 4/23/2022.
//

#include "UserInterface.h"

UserInterface::UserInterface() {}

void UserInterface::clearIndex()
{
    docReader.getWordTree().deleteTree(docReader.getWordTree().getRoot());
    docReader.getOrgTree().deleteTree(docReader.getOrgTree().getRoot());
    docReader.getPersonTree().deleteTree(docReader.getPersonTree().getRoot());
    //TODO also erase contents of persistence file?
}

void UserInterface::parseDocs(const string& direct)
{
    std::cout << "parsing documents..." << std::endl;
    docReader.getFiles(direct, stops);
    std::cout << "done parsing!" << std::endl;
}

void UserInterface::enterQuery(string& query)
{
    process.parseQuery(query, docReader.getWordTree(), docReader.getOrgTree(), docReader.getPersonTree(), stops);
}

void UserInterface::displayResults()
{

}

void UserInterface::showText(Document& d)
{
    rapidjson::Document doc;

    ifstream stream;
    stream.open(d.getPath());

    string wholeFile;
    string temp;
    while (getline(stream, temp))
        wholeFile += temp;
    stream.close();

    doc.Parse(wholeFile.c_str());
    if (!doc.IsObject()) cout << "somethings wrong" << endl;

    string text = doc["text"].GetString();
    cout << text << endl;
}

void UserInterface::stats()
{
    //do not parse more than once (doubles numDocs)
    //only call stats once you have parsed the documents
    cout << "Search Engine stats:" << endl;
    cout << "Total number of articles indexed: " << docReader.getNumDocs() << endl;
    cout << "Total number of unique words indexed: " << docReader.getWordTree().getCount() << endl;
}

DocParser& UserInterface::getDocParser() { return docReader; }