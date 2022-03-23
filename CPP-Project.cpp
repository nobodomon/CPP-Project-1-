// CPP-Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "FileHandler.cpp"
#include "Quiz.h"
#include "Question.h"
#include "MultipleChoiceQuestion.h"
#include "MultiSelectQuestion.h"
using namespace std;

int main()
{
	string input;
	printf("Welcome to Quizzo how may I help you today?");
	while (input != "exit")
	{
		Quiz* readQuiz = FileHandler::getQuizFromFile();
		FileHandler* handler = new FileHandler;
		cout << "Quiz code " << readQuiz->quizCode << endl;
		QuestionType currType;
		//vector<unique_ptr<Question>> questions = readQuiz.Questions;
		int i = 0;
		vector<unique_ptr<Question>> questions = readQuiz->Questions;
		for (auto &qn : questions)
		{
			//currType = qn->type;
			//cout << qn.question << endl;
			if (MultipleChoiceQuestion* mcq = dynamic_cast<MultipleChoiceQuestion*>(qn.get()); mcq != nullptr)
			{
				cout << mcq->question << endl;
				mcq->printQuestion();
			}
			// else if (currType == QuestionType::MSQ)
			// {
			// 	cout << qn.question << endl;
			// 	for (auto option:qn.choices)
			// 	{
			// 		cout << option << endl;
			// 	}
			// }
			i++;
		}
	}
}