//
// Created by Karina Shin on 4/9/2022.
//

#include "Document.h"
//Document::Document(string file, string id)
//{
//    title = "";
//    publication = "";
//    date = "";
//    filePath = file;
//    uuid = id;
//}

Document::Document(string t, string p, string d, string f, string id)
{
    title = t;
    publication = p;
    date = d;
    filePath = f;
    uuid = id;
}

bool Document::operator==(const Document& d)
{
    return filePath == d.filePath;//if they have the same path, they're the same doc
}

string& Document::getTitle() { return title; }
string& Document::getPub() { return publication; }
string& Document::getDate() { return date; }
string& Document::getPath() { return filePath; }
string& Document::getID() { return uuid; }