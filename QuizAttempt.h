#pragma once

#ifndef QUIZATTEMPT_H
#define QUIZATTEMPT_H

#include <string>
using namespace std;

class QuizAttempt
{
public:
    QuizAttempt(string,int ,int ,int );
    string attemptID;
    int quizCode;
    int score;
    int totalQns;
    int writeFile();
    friend ostream& operator << (ostream& ,const QuizAttempt*);
};

#endif