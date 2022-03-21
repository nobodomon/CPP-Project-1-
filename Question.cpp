#include <string>
#include "QuestionType.h"

class Question {
	public:
		std::string question;
		QuestionType type;
		int verifyAnswer();
};