#include <string>
#include "QuestionType.h"

class Question {
	public:
		Question(string question, QuestionType type){};
		virtual ~Question(){};
		std::string question;
		QuestionType type;
		virtual int verifyAnswer();
};