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

int main()
{
	string input;
	cout << "Welcome to Quizzo how may I help you today?" << endl;
	while (input != "exit")
	{
		Quiz* readQuiz = FileHandler::getQuizFromFile();
		//cout << "Quiz code " << readQuiz->quizCode << endl;
		QuestionType currType;
		//vector<unique_ptr<Question>> questions = readQuiz.Questions;
		int i = 0;
		vector<Question*>:: iterator iter;
		for (iter = readQuiz->Questions.begin(); iter != readQuiz->Questions.end(); iter++)
		{
			//cout << i << endl;
			if(MultipleChoiceQuestion* mcq = dynamic_cast<MultipleChoiceQuestion*>(readQuiz->Questions[i]); mcq != nullptr){
				//cout << "MCQ Casted" << endl;
				mcq->printQuestion();
				mcq->promptAnswer();
			}else if(MultiSelectQuestion* msq = dynamic_cast<MultiSelectQuestion*>(readQuiz->Questions[i]); msq != nullptr){
				//cout << "MSQ Casted" << endl;
				msq->printQuestion();
				msq->promptAnswer();
			}else if(ShortAnswerQuestion* saq = dynamic_cast<ShortAnswerQuestion*>(readQuiz->Questions[i]); saq != nullptr){
				saq->printQuestion();
				saq->promptAnswer();
			}
			//currType = qn->type;
			//cout << qn.question << endl;
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
	cout << "Goodbye!" << endl;
	return 1;
}