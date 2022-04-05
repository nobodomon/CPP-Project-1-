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
        friend bool operator == (const Index*,string in);
};

#endif