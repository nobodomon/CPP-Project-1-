#include "Question.h"
#include <string>
#include <vector>
using namespace std;

class MultipleChoiceQuestion: public virtual Question {
public:
	MultipleChoiceQuestion(string question, QuestionType type, vector<string> choices, int correctAnswer):  Question(question,type){};
	~MultipleChoiceQuestion(){
		
	}
	// MultipleChoiceQuestion() = delete;
	// MultipleChoiceQuestion(const MultipleChoiceQuestion &) = delete;
	// MultipleChoiceQuestion(MultipleChoiceQuestion &&) = default;
	vector<string> choices;
	int correctAnswer;
	int userChoice;
	virtual void printQuestion(){
		cout << this->question;
		for(auto choice: choices){
			cout << choice << endl;
		}
	}
	virtual int verifyAnswer();
};