//
// Created by Karina Shin on 4/19/2022.
//

#include "QueryProcessor.h"

QueryProcessor::QueryProcessor(){}

void QueryProcessor::parseQuery(string& q, DSAVLTree<Word>& words, DSAVLTree<Word>& orgs, DSAVLTree<Word>& people, StopWord& stop)//parse query
{
    this->query = q;
//    std::cout << "NEW QUERY: " << query << std::endl;
    int space;
    while (space != -1)
    {
        space = query.find(" ");//for first word
        Word curr(query.substr(0, space));
        curr.toLower();
        cout << curr.getStr() << endl;
        if (specialStopCheck(stop, curr.getStr()))
            continue;//skip stop words

        if (curr.getStr() == "and" || curr.getStr() == "or"){
            if (curr.getStr() == "and"){//perform corresponding set operation
//                std::cout << "intersection" << std::endl;
                intersection(parseAndOr(), words);
            }
            else{
//                std::cout << "union" << std::endl;
                setUnion(parseAndOr(), words);
            }
        }
        else if (curr.getStr() == "not"){
            query = query.substr(space + 1);//cut off operator
            space = query.find(" ");
            Word word1;
            if (space != -1){//not at the end of the line
                word1 = query.substr(0, space);
                query = query.substr(space + 1);
            }
            else{//reached end of line
                word1 = query;//second word is rest of query
                query = "";//empty query
            }
            word1.stemming();
//            std::cout << word1 << std::endl;
//            std::cout << "complement" << std::endl;
            if (words.contains(word1))
                complement(words.find(words.getRoot(), word1).getDocs());
            else
                cout << word1.getStr() << " is not found." << endl;
//            complement(words.find(words.getRoot(), word1)->getData().getDocs());
        }
        else if (curr.getStr() == "org"){
            query = query.substr(space + 1);//cut off operator
            Word org(findPersonOrg());
//            std::cout << "org intersection" << std::endl;
            if (orgs.contains(org))
                addPersonOrg(orgs.find(orgs.getRoot(), org).getDocs());
            else
                cout << org.getStr() << " is not found." << endl;
//            addPersonOrg(orgs.find(orgs.getRoot(), org)->getData().getDocs());
        }
        else if (curr.getStr() == "person"){
            query = query.substr(space + 1);//cut off operator KEEP
//            cout << "query: " << query << endl;
            Word person(findPersonOrg());
//            std::cout << "person intersection" << std::endl;
            if (people.contains(person))
                addPersonOrg(people.find(people.getRoot(), person).getDocs());//index has to include only those that have this person
            else
                cout << person.getStr() << " is not found." << endl;
            //addPersonOrg(people.find(people.getRoot(), person)->getData().getDocs());
        }
        else{//just a term
            Word term(curr);
            term.stemming();
            if (words.contains(term))
                addTerm(words.find(words.getRoot(), term).getDocs());
            else
                cout << term.getStr() << " is not found." << endl;
//            addTerm(words.find(words.getRoot(), term)->getData().getDocs());
            query = query.substr(space + 1);
        }
        space = query.find(" ");//to check if youve reached the end of the query
    }

    rankIndex();
}

vector<Word> QueryProcessor::parseAndOr()
{
    bool check = true;
    vector<Word> args;//words to "and" or "or" together

    int space = query.find(" ");
    query = query.substr(space + 1);//cut off operator
//    cout << "query: " << query << endl;
    while (check)
    {
        Word word;
        space = query.find(" ");
//        cout << space << endl;
        if (space != -1){//not at the end of the line
            if (query.substr(0, space) != "AND" && query.substr(0, space) != "OR" && query.substr(0, space) != "NOT" && query.substr(0, space) != "PERSON" && query.substr(0, space) != "ORG")
            {//if its not a key word
                word = query.substr(0, space);
                word.stemming();
                args.push_back(word);
                query = query.substr(space + 1);
            }
            else
                break;//reached a key word
        }

        else{//reached end of line
            word = query;//word is rest of query
            query = "";//empty query
            word.stemming();
            args.push_back(word);
            break;
        }
    }

    return args;
}

Word QueryProcessor::findPersonOrg()//operator is already removed from query
{
    int count = 0;
    int space = query.find(" ");
    string curr;// = query.substr(0, space);
    string name = "";// = curr;//first word

    while ((curr != "AND" && curr != "OR" && curr != "NOT" && curr != "ORG" && curr != "PERSON") || space != -1)
    {
        if (space != -1){//not at the end of the line
            curr = query.substr(0, space);
            query = query.substr(space + 1);
        }
        else{//reached end of line
            curr = query;//second word is rest of query
            query = "";//empty query
            if (count != 0)
                name += " ";
            name += curr;
            break;
        }
        cout << curr << endl;
        if (count != 0)
            name += " ";
        name += curr;
        space = query.find(" ");
        count++;
    }
//    cout << "Name: " << name << endl;
    Word person(name);

    return person;
}

//void QueryProcessor::intersection(vector<Document>& a, vector<Document>& b)//AND keyword
//{
//    //AND a and b together and add to the final index, no duplicates
//    //only add if the document is in both a and b
//    std::cout << "intersection" << std::endl;
//
//    for (int i = 0; i < a.size(); i++)
//    {
//        vector<Document>::iterator it = find(b.begin(), b.end(), a.at(i));//look for each element of a in b
//        if (it != b.end())//doc exits in b
//        {
//            vector<Document>::iterator finalIt = find(finalIndex.begin(), finalIndex.end(), *it);
//            if (finalIt == finalIndex.end())//if the doc is NOT in the final index, add it
//                finalIndex.push_back(*it);
//        }
//    }
//}

void QueryProcessor::setUnion(vector<Word> a, DSAVLTree<Word>& tree)//OR keyword
{
    for (int i = 0; i < a.size(); i++)//for every word object in the OR operator
    {
//        cout << a.at(i).getStr() << endl;
        vector<Document> temp;
        if (tree.contains(a.at(i)))
            temp = tree.find(tree.getRoot(), a.at(i)).getDocs();
        else{
            cout << a.at(i).getStr() << " is not found." << endl;
            continue;
        }
//        vector<Document> temp = tree.find(tree.getRoot(), a.at(i))->getData().getDocs();
        for (int d = 0; d < temp.size(); d++)//for every doc in the Word objects index
        {
            vector<Document>::iterator it = find(finalIndex.begin(), finalIndex.end(), temp.at(d));
            if (it == finalIndex.end()){//if the doc is NOT in the final index, add it
                finalIndex.push_back(temp.at(d));
            }
        }
    }
}

void QueryProcessor::intersection(vector<Word> a, DSAVLTree<Word>& tree)//AND keyword
{//TODO Doesn't work
    //a holds the words in the intersection
//    for (int i = 0; i < a.size(); i++)
//        cout << a.at(i).getStr() << endl;

//    bool check = true;
    vector<Document> temp;
    for (int i = 0; i < a.size(); i++){//find the first word in a that is in the tree
        if (tree.contains(a.at(i))){
            temp = tree.find(tree.getRoot(), a.at(i)).getDocs();
            cout << "a: " << a.at(i).getStr() << endl;
            break;
        }
        else{
            cout << a.at(i).getStr() << " is not found." << endl;
        }
    }

    cout << "temp: " << temp.size() << endl;

//    vector<Document> temp = tree.find(tree.getRoot(), a.at(0))->getData().getDocs();
    for (int i = 0; i < temp.size(); i++)//for each doc of the first word (Word)
    {
        bool check = true;
        vector<Document>::iterator it;
        for (int j = 0; j < a.size(); j++){//check if the doc is in every other docs index (a.at(j))
            //need to have a check for if a.at(j) is the same as temp?
            vector<Document> other = tree.find(tree.getRoot(), a.at(j)).getDocs();
            cout << "a.at(j) " << a.at(j).getStr() << endl;
            cout << "a.at(j).getSize() " << other.size() << endl;
//            vector<Document> other = tree.find(tree.getRoot(), a.at(j))->getData().getDocs();
            it = find(other.begin(), other.end(), temp.at(i));//look for each element of a in b
            if (it == other.end())//doc does NOT exit in another words index
            {
                cout << "false" << endl;
                check = false;
                break;//don't add doc to final index
            }
        }
        if (check){//if the doc is in all word's indexes
            vector<Document>::iterator finalIt = find(finalIndex.begin(), finalIndex.end(), *it);
            if (finalIt == finalIndex.end()){//if the doc is NOT in the final index, add it
                finalIndex.push_back(*it);
                cout << "added to final" << endl;
            }
        }
    }
}

void QueryProcessor::addTerm(vector<Document>& a)
{
//    cout << "size: " << a.size() << endl;
    for (int i = 0; i < a.size(); i++)
    {
        vector<Document>::iterator finalIt = find(finalIndex.begin(), finalIndex.end(), a.at(i));
        if (finalIt == finalIndex.end()){//if the doc is NOT in the final index, add it
            finalIndex.push_back(a.at(i));
//            cout << "added new " << endl;
        }
    }
}

void QueryProcessor::complement(vector<Document>& a)//delete set a from finalIndex set
{
    for (int i = 0; i < a.size(); i++)
    {
        vector<Document>::iterator it = find(finalIndex.begin(), finalIndex.end(), a.at(i));
        if (it != finalIndex.end())//doc of a exists in final
            finalIndex.erase(it);//remove that index from final
    }
}

void QueryProcessor::addPersonOrg(vector<Document>& a)//remove any docs from final that don't include the person/org
{//i think it works?
    //if finalIndex already has values, remove any docs that don't contain person/org
    //else: query only has person/org keywords, just add the files that contain the person/org
    if (finalIndex.size() > 0)
    {
        for (int i = 0; i < finalIndex.size(); i++)
        {//get person/org document index list from doc parser (a), each file in finalIndex should be in the person/orgs index
            vector<Document>::iterator it = find(a.begin(), a.end(), finalIndex.at(i));
            if (it == a.end()){//doc of final index does NOT exist in person/org doc list
                finalIndex.erase(finalIndex.begin() + i);//remove the file that doens't contain person/org
                i--;//account for file lost
            }
        }
    }
    else{//finalIndex doesn't have any other values in it
        for (int i = 0; i < a.size(); i++)
        {
            vector<Document>::iterator it = find(finalIndex.begin(), finalIndex.end(), a.at(i));
            if (it == finalIndex.end())//doc of a does NOT exist in final
                finalIndex.push_back(a.at(i));//add files with person/org
        }
    }
}

void QueryProcessor::rankIndex()
{
    //TODO
}

bool QueryProcessor::specialStopCheck(StopWord& stop, string& word)
{
    if (word == "AND" || word == "OR" || word == "NOT")//exclude key words
        return false;
    else if (stop.isStopWord(word))
        return true;
    return false;
}

void QueryProcessor::clearFinal()
{
    finalIndex.erase(finalIndex.begin(), finalIndex.end());
}

vector<Document>& QueryProcessor::getFinal() { return finalIndex; }
