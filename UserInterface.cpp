//
// Created by Karina Shin on 4/23/2022.
//

#include "UserInterface.h"

UserInterface::UserInterface() {}

void UserInterface::run(const string& file)
{
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;

    bool go = true;

    string choice;
//    while (choice != "1" && choice != "2"){
//        cout << "Enter 1 to parse files or 2 to use persistence file: " << endl;
//        cin.clear();
//        cin >> choice;
//        if (choice == "1"){
//            cout << "parsing..." << endl;
//            start = std::chrono::high_resolution_clock::now();
//            docReader.getFiles(file, stops);
//            end = std::chrono::high_resolution_clock::now();
//            std::chrono::duration<double> time_in_seconds = end - start;
//            cout << std::fixed << "Parsing Time: " << time_in_seconds.count() << endl;
//            cout << "done!" << endl;
//        }
//        else if (choice == "2"){
//            cout << "parsing..." << endl;
//            docReader.persistenceIndex();//TODO
//            cout << "done!" << endl;
//        }
//        else{
//            cout << "Incorrect input." << endl;
//        }
//    }

    //Parse documents
    cout << "parsing..." << endl;
    start = std::chrono::high_resolution_clock::now();
    docReader.getFiles(file, stops);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time_in_seconds = end - start;
    cout << std::fixed << "Parsing Time: " << time_in_seconds.count() << endl;
    cout << "done!" << endl;

    while (go)
    {
        cin.get();
        cout << "Search: " << endl;
        string query;
        getline(cin, query);
        start = std::chrono::high_resolution_clock::now();
        process.parseQuery(query, docReader.getWordTree(), docReader.getOrgTree(), docReader.getPersonTree(), stops);
        end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> time_in_seconds = end - start;
        cout << std::fixed << "Query Execution Time: " << time_in_seconds.count() << endl;

        displayResults();

        choice = -1;
        while (choice != "0"){
            cout << "Enter the corresponding number to the article you wish to read (Enter 0 to skip): ";
            cin >> choice;
            if (choice == "0")//exit
                break;
            else if (choice == "1" || choice == "2" || choice == "3" || choice == "4" || choice == "5" || choice == "6" || choice == "7" || choice == "8" || choice == "9" || choice == "10" || choice == "11" || choice == "12" || choice == "13" || choice == "14" || choice == "15"){
                if (stoi(choice) > 0 && stoi(choice) <= process.getBest().size()){
                    showText(process.getBest().at(stoi(choice) - 1));
                    cout << endl;
                }
                else
                    cout << "Incorrect input." << endl;
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
}

void UserInterface::displayResults()//with ranking
{
    if (process.getBest().size() == 0)
        cout << "No results found" << endl;

    for (int i = 0; i < process.getBest().size(); i++)
    {
        if (i == 15)
            break;
        cout << i + 1 << ") ";
        cout << "Title: " << process.getBest().at(i).getTitle() << ", " << process.getBest().at(i).getPub() << ", Date: " << process.getBest().at(i).getDate() << endl;
        cout << "Path: " << process.getBest().at(i).getPath() << endl;
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

void UserInterface::topWordsHelper(Node<Word>* n)
{
    if (n != nullptr){
        topWordsHelper(n->getLeft());
        frequency.push_back(n->getData().getTotal());
        all.push_back(n->getData());
        topWordsHelper(n->getRight());
    }
}

void UserInterface::getTopWords()//go through tree and get the frequency of each word (in order)
{
    topWordsHelper(docReader.getWordTree().getRoot());
    vector<Word> top;//top 25 words
    //result: total frequency for each doc

    //get the top 25 most frequent words
    cout << "Top 25 Most Frequent Words: " << endl;
    for (int n = 0; n < 25; n++){
        int highest = frequency.at(0);
        int index = 0;
        if (n > frequency.size())//less than 25 total words
            break;
        for (int i = 1; i < frequency.size(); i++)//find the next highest freq
        {
            if (frequency.at(i) > highest){//get highest freq
                highest = frequency.at(i);
                index = i;
            }
        }
        cout << all.at(index) << ": " << frequency.at(index) << endl;
        frequency.erase(frequency.begin() + index);
        all.erase(all.begin() + index);
    }
}

DocParser& UserInterface::getDocParser() { return docReader; }

QueryProcessor& UserInterface::getQueryProcessor() { return process; }