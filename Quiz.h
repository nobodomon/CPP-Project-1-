#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "Question.h"

class Quiz
{
public:
    int quizCode;
    std::string title;
    std::vector<Question*> Questions;
    void readFile();
    int addQuestion(Question*);
};