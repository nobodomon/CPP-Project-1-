#pragma once

#ifndef QUESTION_H
#define QUESTION_H

#include <iostream>
#include <string>
#include <vector>
#include "QuestionType.h"

class Question
{
public:
	Question(string, QuestionType);
	virtual ~Question();
	std::string question;
	QuestionType type;
	int score;
	virtual int verifyAnswer();
	virtual void printQuestion();
};

#endif