//
// Created by Karina Shin on 4/9/2022.
//

#ifndef INC_22S_FINAL_PROJ_DOCUMENT_H
#define INC_22S_FINAL_PROJ_DOCUMENT_H

#include <string>

using namespace std;
class Document {
private:
    string title;
    string publication;
    string date;
    string filePath;

public:
    Document(string file);
    Document(string t, string p, string d, string f);

    string getTitle();
    string getPub();
    string getDate();
    string getPath();
};


#endif //INC_22S_FINAL_PROJ_DOCUMENT_H
