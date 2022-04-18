#include <iostream>
#include <string>
#include <fstream>
#include "include/rapidjson/document.h"
#include "DocParser.h"
#include "DSAVLTree.h"
#include "Word.h"

using namespace std;
int main(int argc, char** argv) {
    DocParser parse;
    cout << "parsing..." << endl;
    parse.getFiles(argv[1]);
    cout << "done!" << endl;
//    cout << parse.getWordTree().getRoot()->getData().getStr() << endl;
//    cout << parse.getWordTree().getCount();
    Word w("investors");
    w.stemming();
//    if (parse.getWordTree().contains(w)){
//        cout << "true" << endl;
//        parse.getWordTree().find(parse.getWordTree().getRoot(), w).printDocs();
//    }
    parse.getWordTree().find(parse.getWordTree().getRoot(), w).printDocs();

    //data folder took 1:45 4/17
//    DSAVLTree<Word> tree;
//    Word a("a");
//    Word z("z");
//    Word b("b");
//    tree.insert(a);
//    tree.insert(z);
//    tree.insert(b);
//    Word check("b");
//    if (tree.contains(check))
//        cout << "true";

//    rapidjson::Document doc;
//    ifstream stream;
//    stream.open("blogs_0000001.json");
//    if (stream.is_open())
//        cout << "open" << endl;
//
//    string wholeFile;
//    string temp;
//    while (getline(stream, temp))//not reading anything
//    {
//        cout << temp << endl;
//        wholeFile += temp;
//    }
//    stream.close();
//    cout << wholeFile << endl;
//
//    doc.Parse(wholeFile.c_str());
//    if (doc.IsObject()) cout << "ITS AN OBJECT" << endl;
//
////    string notArr = doc["root"]["entities"]["persons"][0]["name"].GetString();
//    string notArr = doc["url"].GetString();
//    cout << "notArr: " << notArr << endl;
//
//    doc["entities"]["persons"].IsObject();
//    doc["entities"]["persons"].IsArray();
//    for (auto& v : doc["entities"]["persons"].GetArray())
//        cout << "Value: " << v["name"].GetString() << endl;
}
