#include <string>
#include "Question.h"
#include <vector>
class Quiz {
	public:
		int quizCode;
		std::string title;
		std::vector<Question*> Questions;

		void readFile() {};
};