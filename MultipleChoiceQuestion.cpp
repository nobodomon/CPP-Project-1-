#include "MultipleChoiceQuestion.h"
#include "InputHandler.h"
using namespace std;

MultipleChoiceQuestion::MultipleChoiceQuestion(string question, QuestionType type, vector<string> choices, vector<string> allowedInputs, int correctAnswer)
	: Question(question, type)
{
	this->question = question;
	this->type = type;
	this->choices = choices;
	this->allowedInputs = allowedInputs;
	this->correctAnswer = correctAnswer;
}

MultipleChoiceQuestion::~MultipleChoiceQuestion()
{
}

vector<string> MultipleChoiceQuestion::getAllowedInputs(){
	return this->allowedInputs;
}

ostream& operator << (ostream& out, const MultipleChoiceQuestion* mcq){
	out << "[MCQ]" << mcq->question << endl;
	int optionNo = 1;
	for(auto &choice: mcq->choices){
		out << "[" + to_string(optionNo) + "] " <<  choice << endl;
		optionNo++;
	}
	return out;
}

istream& operator >> (istream& in, MultipleChoiceQuestion* mcq){
	string input;
	do{

		cout << "Your answer: "; 
		in >> input; cout << endl;
	}while(InputHandler::verifyMCQInput(input,mcq->getAllowedInputs()) == 0);
	mcq->userChoice = input;
	if(mcq->verifyAnswer(input)){
		cout << "Correct" << endl;
		mcq->score = 1;
	}else{
		cout << "Wrong!" << endl;
	}
	return in;
}

void MultipleChoiceQuestion::printQuestion() const
{
	//cout << "Printing MCQ question" << endl;
	cout << this->question << endl;
	int optionNo = 1;
	for (auto &choice : this->choices)
	{
		cout << "[" + to_string(optionNo) + "] " <<  choice << endl;
		optionNo++;
	}
}

void MultipleChoiceQuestion::promptAnswer(){
	string input;
	do{

		cout << "Your answer: "; cin >> input; cout << endl;
	}while(InputHandler::verifyMCQInput(input,this->allowedInputs) == 0);
	this->userChoice = input;
	if(verifyAnswer(input)){
		cout << "Correct" << endl;
		this->score = 1;
	}else{
		cout << "Wrong!" << endl;
	}
}

int MultipleChoiceQuestion::verifyAnswer(string input)
{
	if(input == to_string(this->correctAnswer)){
		return 1;
	}else{
		return 0;
	}
}