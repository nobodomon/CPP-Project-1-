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

class FileHandler {
	public:
		static Quiz* getQuizFromFile(string);
		static int addNewQuiz(Quiz*, string );
		static Person* createUser(string,string);
};