#pragma once

#ifndef INDEX_H
#define INDEX_H

#include <string>
#include <iostream>
using namespace std;


class Index{
    public:
        Index(int, string, string);
        int quizCode;
        string quizTitle;
        string quizPath;
        friend ostream& operator << (ostream&, const Index*);
        template<typename T>
        friend bool operator == (const Index*,T);
};

#endif