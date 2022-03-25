// CPP-Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "FileHandler.h"
#include "Quiz.h"
#include "Question.h"
#include "MultipleChoiceQuestion.h"
#include "MultiSelectQuestion.h"
#include "ShortAnswerQuestion.h"
using namespace std;

void printMenu();
void open();
void detectInputIntent(string input);

int main()
{
	string input;
	cout << "Welcome to Quizzo how may I help you today?" << endl;
	printMenu();
	while (input != "exit")
	{
		cin >> input; cout << endl;
		detectInputIntent(input);
	}
	cout << "Goodbye!" << endl;
	return 1;
}

void printMenu()
{
	cout << "Commands:" << endl;
	cout << "open - open a quiz and start attempting" << endl;
	cout << "info - Displays your info" << endl;
}

void open()
{
	Quiz *readQuiz = FileHandler::getQuizFromFile();
	// cout << "Quiz code " << readQuiz->quizCode << endl;
	QuestionType currType;
	// vector<unique_ptr<Question>> questions = readQuiz.Questions;
	int i = 0;
	vector<Question *>::iterator iter;
	for (iter = readQuiz->Questions.begin(); iter != readQuiz->Questions.end(); iter++)
	{
		// cout << i << endl;
		if (MultipleChoiceQuestion *mcq = dynamic_cast<MultipleChoiceQuestion *>(readQuiz->Questions[i]); mcq != nullptr)
		{
			// cout << "MCQ Casted" << endl;
			mcq->printQuestion();
			mcq->promptAnswer();
		}
		else if (MultiSelectQuestion *msq = dynamic_cast<MultiSelectQuestion *>(readQuiz->Questions[i]); msq != nullptr)
		{
			// cout << "MSQ Casted" << endl;
			msq->printQuestion();
			msq->promptAnswer();
		}
		else if (ShortAnswerQuestion *saq = dynamic_cast<ShortAnswerQuestion *>(readQuiz->Questions[i]); saq != nullptr)
		{
			saq->printQuestion();
			saq->promptAnswer();
		}
		// currType = qn->type;
		// cout << qn.question << endl;
		//  else if (currType == QuestionType::MSQ)
		//  {
		//  	cout << qn.question << endl;
		//  	for (auto option:qn.choices)
		//  	{
		//  		cout << option << endl;
		//  	}
		//  }
		i++;
	}
	cout << "-Quiz end-" << endl;
}

void detectInputIntent(string input){
	if(input == "open"){
		open();
	}else{
		cout << "Invalid option!" << endl;
		printMenu();
	}
}