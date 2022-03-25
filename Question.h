#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "QuestionType.h"

class Question
{
public:
	Question(string, QuestionType);
	// Question() = delete;
	// Question(const Question &) = delete;
	// Question(Question &&) = default;
	virtual ~Question();
	std::string question;
	QuestionType type;
	virtual int verifyAnswer();
	virtual void printQuestion();
};