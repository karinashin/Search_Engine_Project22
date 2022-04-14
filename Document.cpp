//
// Created by Karina Shin on 4/9/2022.
//

#include "Document.h"
Document::Document(string file)
{
    title = "";
    publication = "";
    date = "";
    filePath = file;
}

Document::Document(string t, string p, string d, string f)
{
    title = t;
    publication = p;
    date = d;
    filePath = f;
}

bool Document::operator==(const Document& d)
{
    return filePath == d.filePath;//if they have the same path, they're the same doc
}

string Document::getTitle() { return title; }
string Document::getPub() { return publication; }
string Document::getDate() { return date; }
string Document::getPath() { return filePath; }