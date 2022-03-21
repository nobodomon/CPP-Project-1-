// CPP-Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "FileHandler.cpp"
#include "Quiz.h"
#include "MultipleChoiceQuestion.h"
#include "MultiSelectQuestion.h"
using namespace std;

int main()
{
	string input;
	printf("Welcome to Quizzo how may I help you today?");
	while (input != "exit")
	{
		Quiz readQuiz = FileHandler::getQuizFromFile();
		cout << "Quiz code " << readQuiz.quizCode << endl;
		Question currQuestion;
		QuestionType currType;
		for (auto qn : readQuiz.Questions)
		{
			currType = qn->type;
			cout << qn->question << endl;
			if (currType == QuestionType::MCQ)
			{
				cout << qn->question << endl;
				MultipleChoiceQuestion* mcq = dynamic_cast<MultipleChoiceQuestion*>(qn);
				for (auto option:qnPtr.get()->choices)
				{
					cout << option << endl;
				}
			}
			else if (currType == QuestionType::MSQ)
			{
				cout << qn->question << endl;
				for (auto option:qn->choices)
				{
					cout << option << endl;
				}
			}
		}
	}
}