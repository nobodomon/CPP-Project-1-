#include "Question.h"
#include <string>
#include <vector>
using namespace std;

class MultipleSelectQuestion: public Question {
public:
	vector<string> choices;
	vector<int> correctAnswers;
	vector<int> userChoices;
	int verifyAnswer() {
        return 1;
	}
};