#include <iostream>
#include <string>
#include <fstream>
#include "include/rapidjson/document.h"
#include "DocParser.h"

using namespace std;
int main(int argc, char** argv) {
    string input = "subset";
    DocParser parse;
    parse.getFiles(input);

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
