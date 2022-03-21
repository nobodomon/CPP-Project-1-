#pragma once

#include<iostream> 
#include<string>
#include <vector>
#include "Question.h"
using namespace std;

class Quiz {
public:
    int quizCode;
    std::string title;
    std::vector<Question*> Questions;

    void readFile() {};
};