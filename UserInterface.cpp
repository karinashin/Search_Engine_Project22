//
// Created by 18476 on 4/23/2022.
//

#include "UserInterface.h"

UserInterface::UserInterface() {}

void UserInterface::run(const string& file)
{
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;

    bool go = true;

    string choice;
    while (choice != "1" && choice != "2"){
        cout << "Enter 1 to parse files or 2 to use persistence file: " << endl;
        cin.clear();
        cin >> choice;
        if (choice == "1"){
            cout << "parsing..." << endl;
            docReader.getFiles(file, stops);
            cout << "done!" << endl;
        }
        else if (choice == "2"){
            cout << "parsing..." << endl;
            docReader.persistenceIndex();//TODO
            cout << "done!" << endl;
        }
        else{
            cout << "Incorrect input." << endl;
        }
    }

    while (go)
    {
        cin.get();
        cout << "Search: " << endl;
        string query;
        getline(cin, query);
//        cout << "query: " << query << endl;
        start = std::chrono::high_resolution_clock::now();
        process.parseQuery(query, docReader.getWordTree(), docReader.getOrgTree(), docReader.getPersonTree(), stops);
        end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> time_in_seconds = end - start;
        cout << std::fixed << "Query Execution Time: " << time_in_seconds.count() << endl;

        displayResults();
//        cout << "displayed" << endl;

        choice = -1;
        while (choice != "0"){
            cout << "Enter the corresponding number to the article you wish to read (Enter 0 to skip): ";
            cin >> choice;
            if (choice == "0")//exit
                break;
            else if (choice == "1" || choice == "2" || choice == "3" || choice == "4" || choice == "5" || choice == "6" || choice == "7" || choice == "8" || choice == "9" || choice == "10" || choice == "11" || choice == "12" || choice == "13" || choice == "14" || choice == "15"){
                showText(process.getFinal().at(stoi(choice) - 1));
                cout << endl;
            }
            else
                cout << "Incorrect input." << endl;
        }

        choice = -1;//reset choice;
        while (choice != "0"){
            cout << "Enter 1 to search again, 2 to display search engine stats, or 0 to exit the search engine: " << endl;
            cin.get();
            cin >> choice;
            if (choice == "1"){
                process.clearFinal();//reset results
                break;
            }
            else if (choice == "2"){
                stats();
                cout << endl;
            }
            else if (choice == "0"){
                go = false;
                break;
            }
            else
                cout << "Incorrect input." << endl;
        }
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

void UserInterface::displayResults()//TODO change getFinal to getBest()
{
    if (process.getFinal().size() == 0)
        cout << "No results found" << endl;

    for (int i = 0; i < process.getFinal().size(); i++)
    {
        if (i == 15)
            break;
        cout << i + 1 << ") ";
        cout << "Title: " << process.getFinal().at(i).getTitle() << ", " << process.getFinal().at(i).getPub() << ", Date: " << process.getFinal().at(i).getDate() << endl;
        cout << "Path: " << process.getFinal().at(i).getPath() << endl;
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
    cout << "Total number of unique organizations indexed: " << docReader.getOrgTree().getCount() << endl;
    cout << "Total number of unique persons indexed: " << docReader.getPersonTree().getCount() << endl;
    getTopWords();
}

void UserInterface::getTopWords()
{

}

DocParser& UserInterface::getDocParser() { return docReader; }