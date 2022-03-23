#pragma once

#include<iostream> 
#include<string>
#include <vector>
#include "Question.h"
using namespace std;

class MultiSelectQuestion: public Question {
    public:
	    vector<string> choices;
        vector<int> correctAnswers;
        vector<int> userChoices;
		virtual int verifyAnswer();
    };