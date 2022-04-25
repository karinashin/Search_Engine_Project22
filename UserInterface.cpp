//
// Created by 18476 on 4/23/2022.
//

#include "UserInterface.h"

UserInterface::UserInterface() {}

void UserInterface::run(const string& file)
{
    bool run = true;

    cout << "Enter 1 to parse files or 2 to use persistence file: " << endl;
    int choice;
    cin >> choice;
    if (choice == 1){
        cout << "parsing..." << endl;
        docReader.getFiles(file, stops);
        cout << "done!" << endl;
    }
    else{
        cout << "parsing..." << endl;
        docReader.persistenceIndex();//TODO
        cout << "done!" << endl;
    }

    while (run)
    {
        cout << "Search: " << endl;
        string query;
        cin >> query;
        process.parseQuery(query, docReader.getWordTree(), docReader.getOrgTree(), docReader.getPersonTree(), stops);
        displayResults();
        choice = -1;
        while (choice != 0){
            cout << "Enter the corresponding number to the article you wish to read (Enter 0 to search new term): " << endl;
            cin >> choice;
            if (choice != 0)
                showText(process.getFinal().at(choice - 1));
            cout << endl;
        }

        cout << "Enter 1 if you would like to search again, 2 to display search engine stats, or 0 to exit the search engine: " << endl;
        cin >> choice;
        if (choice == 2){
            stats();
            cout << endl;
        }
        else if (choice == 0)
            run = false;
    }
}

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

void UserInterface::displayResults()
{
    for (int i = 0; i < 15 || i < process.getFinal().size(); i++)
    {
        cout << "Title: " << process.getFinal().at(i).getTitle() << ", " << process.getFinal().at(i).getPub() << ", Date: " << process.getFinal().at(i).getDate() << endl;
    }
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