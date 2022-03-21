#include <string>
#include <iostream>
#include <fstream>
#include "json.h"
#include "Quiz.h"
#include "MultipleChoiceQuestion.h"
#include "MultiSelectQuestion.h"
using namespace std;

class FileHandler {
	public:
		static Quiz getQuizFromFile() {
			cout << "Enter quiz file name";
			string path;
			cin >> path;
			Json::Value root;
			ifstream quizFile(path);
			quizFile >> root;
			Quiz quiz;
			root = root["Quiz"];
			quiz.quizCode = root["ID"].asInt();
			int numOfQuestions = root["NumberOfQns"].asInt();
			for(int n = 0;n<numOfQuestions;n++){
				string q = "Q"+to_string(n+1);
				Json::Value question = root[q];
				if(question["Type"].asString() == "MCQ"){
					unique_ptr<MultipleChoiceQuestion> mcqPtr;
					MultipleChoiceQuestion mcq;
					int numOfOptions = question["NumberOfOptions"].asInt();
					mcq.question = question["Title"].asString();
					mcq.type = QuestionType::MCQ;
					for(int qn = 0;qn<numOfOptions;qn++){
						Json::Value option;
						mcq.choices.push_back(option[to_string(qn+1)].asString());
					}
					mcq.correctAnswer = question["Answer"].asInt();
					quiz.Questions.push_back(&mcq);
				}else if(question["Type"].asString() == "MultiSelect"){
					MultiSelectQuestion msq;
					int numOfOptions = question["NumberOfOptions"].asInt();
					msq.question = question["Title"].asString();
					msq.type = QuestionType::MSQ;
					for(int qn = 0;qn<numOfOptions;qn++){
						Json::Value option;
						msq.choices.push_back(option[to_string(qn+1)].asString());
					}
					size_t pos = 0;
					string rawAnswer = question["Answer"].asString();
					string token;
					while((pos = rawAnswer.find(",")) != string::npos){
						token = rawAnswer.substr(0,pos);
						msq.correctAnswers.push_back(stoi(token));
						rawAnswer.erase(0,pos+string(",").length());
					}
					quiz.Questions.push_back(&msq);
				}else{

				}
			}
			quizFile.close();
			return quiz;
		};
};