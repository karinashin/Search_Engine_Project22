//
// Created by Karina Shin on 4/9/2022.
//

#include "DocParser.h"

void DocParser::parse(const string& filename) {
    cout << "parse function" << endl;
    //TODO parse for org and person, put unique ones into avl tree
    //parse main text
    rapidjson::Document doc;

    //for every file in the folder
    ifstream stream;
    stream.open(filename);
    if (stream.is_open())
        cout << "open" << endl;

    string wholeFile;
    string temp;
    while (getline(stream, temp))//not reading anything
        wholeFile += temp;

    stream.close();

    doc.Parse(wholeFile.c_str());
    if (!doc.IsObject()) cout << "somethings wrong" << endl;

    //make Document object for current file
//    string title = doc["title"].GetString(); TODO add back later
//    string pub = doc["thread"]["published"].GetString();
//    string date;
    Document currDoc(filename);

    string text = doc["text"].GetString();
    cout << "text: " << text << endl;

    int space = text.find(" ");
    while (space != -1)
    {
        Word curr(text.substr(0, space));
        curr.toLower();//remove caps
        if (curr.isStopWord())
            break;//don't add to tree
        curr.removePunc();//remove punctuation
        curr.stemming();//perform stemming

        //put unique words into the avl tree
        if (!words.contains(curr)){//if the word is not already in the tree/new unique word
            words.insert(curr);
        }
        curr.incrFreq(currDoc);//index document
    }
}

void DocParser::getFiles(const string& directory)
{
    for (const auto & entry : fs::recursive_directory_iterator(directory)){
        if (entry.is_regular_file()) {
            if (entry.path().extension().string() == ".json") {
                string filename = entry.path().c_str();
                parse(filename);
            }
        }
    }
}

DSAVLTree<Word>& DocParser::getWordTree() { return words; }
DSAVLTree<Word>& DocParser::getOrgTree() { return orgs; }
DSAVLTree<Word>& DocParser::getPersonTree() { return people; }
