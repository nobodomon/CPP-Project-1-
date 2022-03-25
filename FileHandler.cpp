#include "FileHandler.h"
using namespace std;

Quiz *FileHandler::getQuizFromFile()
{
	cout << "Enter quiz file name" << endl;
	string path;
	cin >> path;
	Json::Value root;
	ifstream quizFile(path);
	quizFile >> root;
	Quiz *quiz = new Quiz();
	root = root["Quiz"];
	quiz->quizCode = root["ID"].asInt();
	int numOfQuestions = root["NumberOfQns"].asInt();
	for (int n = 0; n < numOfQuestions; n++)
	{
		string q = "Q" + to_string(n + 1);
		Json::Value question = root[q];
		if (question["Type"].asString() == "MCQ")
		{
			int numOfOptions = question["NumberOfOptions"].asInt();
			string questionTitle = question["Title"].asString();
			QuestionType type = QuestionType::MCQ;
			vector<string> choices;
			vector<string> allowedInputs;
			Json::Value option = question["Options"];
			for (int qn = 0; qn < numOfOptions; qn++)
			{
				// cout << option[to_string(qn + 1)].asString();
				choices.push_back(option[to_string(qn + 1)].asString());
				allowedInputs.push_back(to_string(qn + 1));
			}
			int correctAnswer = question["Answer"].asInt();
			quiz->addQuestion(new MultipleChoiceQuestion(questionTitle, type, choices, allowedInputs, correctAnswer));
			// quiz->Questions.emplace_back(unique_ptr<Question>(new MultipleChoiceQuestion(questionTitle,type,choices,correctAnswer)));
		}
		else if (question["Type"].asString() == "MultiSelect")
		{
			int numOfOptions = question["NumberOfOptions"].asInt();
			string questionTitle = question["Title"].asString();
			QuestionType type = QuestionType::MSQ;
			vector<string> choices;
			vector<string> allowedInputs;
			Json::Value option = question["Options"];
			for (int qn = 0; qn < numOfOptions; qn++)
			{
				choices.push_back(option[to_string(qn + 1)].asString());
				allowedInputs.push_back(to_string(qn + 1));
			}
			size_t pos = 0;
			string rawAnswer = question["Answer"].asString();
			string token;
			vector<int> correctAnswers;
			while ((pos = rawAnswer.find(",")) != string::npos)
			{
				token = rawAnswer.substr(0, pos);
				correctAnswers.push_back(stoi(token));
				rawAnswer.erase(0, pos + string(",").length());
			}
			quiz->addQuestion(new MultiSelectQuestion(questionTitle, type, choices,allowedInputs, correctAnswers));
		}
		else if(question["Type"].asString() == "ShortAnswer")
		{
			string questionTitle = question["Title"].asString();
			QuestionType type = QuestionType::SA;
			size_t pos = 0;
			string rawAnswer = question["Answer"].asString();
			string token;
			vector<string> acceptableAnswers;
			while ((pos = rawAnswer.find(",")) != string::npos)
			{
				token = rawAnswer.substr(0, pos);
				acceptableAnswers.push_back(token);
				rawAnswer.erase(0, pos + string(",").length());
			}
			quiz->addQuestion(new ShortAnswerQuestion(questionTitle,type,acceptableAnswers));
		}
	}
	quizFile.close();
	return quiz;
}