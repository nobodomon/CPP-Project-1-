#pragma once

#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <string>
#include <iostream>
#include <fstream>
#include <memory>
#include "json.h"
#include "Quiz.h"
#include "MultipleChoiceQuestion.h"
#include "MultiSelectQuestion.h"
#include "ShortAnswerQuestion.h"
#include "Person.h"
#include "Index.h"

class FileHandler {
	public:
		static Quiz* getQuizFromFile(string);
		static Person* createUser(string,string);
		static Person* getUser(string, string);

		static int createQuizIndexFile();
		static int addNewQuiz(Quiz*, string );
		static vector<Index*> getIndexes();

		static Index* getIndexByKey(string,vector<Index*>);
};

#endif