#pragma once 

#ifndef SHORTANSWERQUESTION_H
#define SHORTANSWERQUESTION_H

#include <iostream>
#include <string>
#include <vector>
#include "Question.h"
using namespace std;

class ShortAnswerQuestion : public Question{
    public:
    ShortAnswerQuestion(string, QuestionType,vector<string> acceptableAnswers);
    friend ostream& operator <<(ostream&, const ShortAnswerQuestion*);
    friend istream& operator >>(istream&, ShortAnswerQuestion*);
    vector<string> acceptableAnswers;
    string userChoice;
    virtual int verifyAnswer(string);
    void printQuestion();
    void promptAnswer();
};

#endif