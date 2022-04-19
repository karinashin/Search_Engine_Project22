//
// Created by Karina Shin on 4/19/2022.
//

#ifndef INC_22S_FINAL_PROJ_QUERYPROCESSOR_H
#define INC_22S_FINAL_PROJ_QUERYPROCESSOR_H

#include <string>
#include <vector>
#include "Document.h"

class QueryProcessor {
private:
    string query;
    vector<Document> finalIndex;

public:
    void parseQuery(string& query);//parse query
    void setUnion(vector<Document>& a, vector<Document>& b);//OR keyword
    void intersection(vector<Document>& a, vector<Document>& b);//AND keyword
    void complement(vector<Document>& a, vector<Document>& b);//set subtraction
};


#endif //INC_22S_FINAL_PROJ_QUERYPROCESSOR_H
