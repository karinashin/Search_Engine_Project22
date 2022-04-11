#include <iostream>
#include <string>
#include <fstream>
#include "include/rapidjson/document.h"

using namespace std;
int main() {
    rapidjson::Document doc;
    ifstream stream;
    stream.open("blogs_0000001.json");
    if (stream.is_open())
        cout << "open" << endl;

    string wholeFile;
    string temp;
    while (getline(stream, temp))//not reading anything
    {
        cout << temp << endl;
        wholeFile += temp;
    }
    stream.close();
    cout << wholeFile << endl;

    doc.Parse(wholeFile.c_str());
    if (doc.IsObject()) cout << "ITS AN OBJECT" << endl;

//    string notArr = doc["root"]["entities"]["persons"][0]["name"].GetString();
    string notArr = doc["root"]["url"].GetString();
    cout << "notArr: " << notArr << endl;

//    doc["root"]["entities"]["persons"].IsObject();
//    doc["root"]["entities"]["persons"].IsArray();
//    for (auto& v : doc["root"]["entities"]["persons"].GetArray())
//        cout << "Value: " << v.GetString() << endl;
}
