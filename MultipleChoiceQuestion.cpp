#include "Question.h"
#include <string>
#include <vector>
using namespace std;

class MultipleChoiceQuestion: public Question {
public:
	vector<string> choices;
	int correctAnswer;
	int userChoice;
	int verifyAnswer() {
		if (userChoice == correctAnswer){
			return 1;
		}
		else {
			return 0;
		}
	}
};