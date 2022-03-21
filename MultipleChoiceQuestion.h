#pragma once

#include<iostream> 
#include<string>
#include <vector>
#include "Question.h"
using namespace std;

class MultipleChoiceQuestion: public Question {
    public:
	    vector<string> choices;
        int correctAnswer;
        int userChoice;
        int verifyAnswer();
    };