#pragma once

#include<iostream> 
#include<string>
#include <vector>
#include "QuestionType.h"
using namespace std;

class Question {
	public:
		std::string question;
		QuestionType type;
		int verifyAnswer();
};