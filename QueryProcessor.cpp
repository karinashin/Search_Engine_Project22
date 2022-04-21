//
// Created by Karina Shin on 4/19/2022.
//

#include "QueryProcessor.h"

QueryProcessor::QueryProcessor(){}
QueryProcessor::QueryProcessor(DSAVLTree<Word>& w, DSAVLTree<Word>& o, DSAVLTree<Word>& p)
{
//    words = w;//TODO error
//    orgs = o;
//    people = p;
}

void QueryProcessor::parseQuery(string& query)//parse query
{
    std::cout << "NEW QUERY: " << query << std::endl;
    int space;
    while (space != -1)
    {
        space = query.find(" ");
        string curr = query.substr(0, space);

        if (curr == "AND" || curr == "OR"){//2 arg operators
            query = query.substr(space + 1);//cut off operator
            space = query.find(" ");
            Word word1(query.substr(0, space));//guaranteed to have first word
            std::cout << word1.getStr() << std::endl;
            query = query.substr(space + 1);//cut off operator
            space = query.find(" ");//find next word
            Word word2;
            if (space != -1){//not at the end of the line
                word2 = query.substr(0, space);
                query = query.substr(space + 1);
            }//second word
            else{//reached end of line
                word2 = query;//second word is rest of query
                query = "";//empty query
            }
            std::cout << word2.getStr() << std::endl;

            if (curr == "AND"){//perform corresponding set operation
                std::cout << "intersection" << std::endl;
//                intersection(words.find(words.getRoot(), word1).getDocs(), words.find(words.getRoot(), word2).getDocs());
            }
            else{
                std::cout << "union" << std::endl;
//                setUnion(words.find(words.getRoot(), word1).getDocs(), words.find(words.getRoot(), word2).getDocs());
            }
        }
        else if (curr == "NOT"){
            query = query.substr(space + 1);//cut off operator
            space = query.find(" ");
            Word word1;
            if (space != -1){//not at the end of the line
                word1 = query.substr(0, space);
                query = query.substr(space + 1);
            }//second word
            else{//reached end of line
                word1 = query;//second word is rest of query
                query = "";//empty query
            }
            std::cout << word1 << std::endl;
            std::cout << "complement" << std::endl;
//            complement(words.find(words.getRoot(), word1).getDocs());
        }
        else if (curr == "ORG"){
            query = query.substr(space + 1);//cut off operator
            space = query.find(" ");
            Word org;
            if (space != -1){//not at the end of the line
                org = query.substr(0, space);
                query = query.substr(space + 1);
            }//second word
            else{//reached end of line
                org = query;//second word is rest of query
                query = "";//empty query
            }
            std::cout << org << std::endl;
            std::cout << "org intersection" << std::endl;
//            intersection(finalIndex, orgs.find(orgs.getRoot(), org).getDocs());
            //org.getDocs() returns index where this org appears
        }
        else if (curr == "PERSON"){
            query = query.substr(space + 1);//cut off operator
            space = query.find(" ");
            Word person;
            if (space != -1){//not at the end of the line
                person = query.substr(0, space);
                query = query.substr(space + 1);
            }//second word
            else{//reached end of line
                person = query;//second word is rest of query
                query = "";//empty query
            }
            std::cout << person << std::endl;
            std::cout << "person intersection" << std::endl;
//            intersection(finalIndex, people.find(people.getRoot(), person).getDocs());
        }
        else{//just a term
            Word term(curr);
            std::cout << term << std::endl;
            std::cout << "standard union" << std::endl;
//            setUnion(finalIndex, words.find(words.getRoot(), term).getDocs());
            query = query.substr(space + 1);
            space = query.find(" ");
        }
    }
}

void QueryProcessor::setUnion(vector<Document>& a, vector<Document>& b)//OR keyword
{
    std::cout << "union" << std::endl;
}

void QueryProcessor::intersection(vector<Document>& a, vector<Document>& b)//AND keyword
{
    std::cout << "intersection" << std::endl;
}

void QueryProcessor::complement(vector<Document>& a)//delete set a from finalIndex set
{
    std::cout << "complement" << std::endl;
}