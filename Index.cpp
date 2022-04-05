#include "Index.h"
#include "Quiz.h"
#include "json.h"
#include <memory>
#include <fstream>
#include <iostream>
using namespace std;

Index::Index(int quizCode, string quizTitle, string quizPath){
    this->quizCode = quizCode;
    this->quizTitle = quizTitle;
    this->quizPath = quizPath;
}

ostream& operator<< (ostream& out, const Index* index){
    out << "[" << index->quizCode << "] " << index->quizTitle << endl;
    out << "Path: " << index->quizPath << endl;
    return out;
}

template<typename T>
bool Index::operator==(const Index* index,T d){
    if(to_string(index->quizCode) == d){
        return true;
    }else if(index->quizPath == d){
        return true;
    }
    return false;
}
