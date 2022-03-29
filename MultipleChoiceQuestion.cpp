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