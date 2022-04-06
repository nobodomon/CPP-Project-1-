#pragma once 

#ifndef SHORTANSWERQUESTION_H
#define SHORTANSWERQUESTION_H

#include <iostream>
#include <string>
#include <vector>
#include "Question.h"
using namespace std;

class ShortAnswerQuestion : public Question{
    private:
    vector<string> acceptableAnswers;
    string userChoice;
    public:
    ShortAnswerQuestion(string, QuestionType,vector<string> acceptableAnswers);
    friend ostream& operator <<(ostream&, const ShortAnswerQuestion*);
    friend istream& operator >>(istream&, ShortAnswerQuestion*);
    virtual int verifyAnswer(string);
    void printQuestion();
    void promptAnswer();
    vector<string> getAcceptableAnswers();
    void setAcceptableAnswers(vector<string>);
    string getUserChoice();
    void setUserChoice(string);
};

#endif