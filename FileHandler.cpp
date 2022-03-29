#include "FileHandler.h"
#include "InputHandler.h"
#include "Index.h"
#include "Person.h"
#include <sys/stat.h>
using namespace std;

Quiz *FileHandler::getQuizFromFile(string path)
{

	Json::Value root;
	ifstream quizFile(path);
	quizFile >> root;
	Quiz *quiz = new Quiz();
	root = root["Quiz"];
	quiz->title = root["Name"].asString();
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
			vector<string> correctAnswers = InputHandler::stringToVector(question["Answer"].asString(),',');

			quiz->addQuestion(new MultiSelectQuestion(questionTitle, type, choices,allowedInputs, correctAnswers));
		}
		else if(question["Type"].asString() == "ShortAnswer")
		{
			string questionTitle = question["Title"].asString();
			QuestionType type = QuestionType::SA;
			vector<string> acceptableAnswers = InputHandler::stringToVector(question["Answer"].asString(),',');
			quiz->addQuestion(new ShortAnswerQuestion(questionTitle,type,acceptableAnswers));
		}
	}
	quizFile.close();
	return quiz;
}

Person* FileHandler::createUser(string user,string password){
	struct stat buf;
	if(stat((user+".json").c_str(), &buf) != -1){
		cout << "User already exists!" << endl;
		return nullptr;
	}
	Json::Value root;
	ofstream outputFileStream(user+".json");	
	root["user"]["name"] = user;
	root["user"]["password"] = password;
	
	Json::StreamWriterBuilder builder;
	builder["commentStyle"] = "None";
	builder["indentation"] = "  ";
	unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
    writer -> write(root,&outputFileStream);
	outputFileStream.close();
	return new Person(user,password);
}

Person* FileHandler::getUser(string user, string password){
	Json::Value root;
	ifstream readUser(user+".json");
	if(readUser.fail()){
		cout << "User does not exist!" << endl;
		return nullptr;
	}
	readUser >> root;
	readUser.close();
	if(password == root["user"]["password"].asString()){
		return new Person(root["user"]["name"].asString(),root["user"]["password"].asString());
	}else{
		cout << "Invalid password!" << endl;
		return nullptr;
	}
}


int FileHandler::addNewQuiz(Quiz* quiz,string quizPath){
    try{

        Json::Value root;
        ifstream QuizIndex("QuizIndex.json");
        QuizIndex >> root;

        if(root["Quizes"][to_string(quiz->quizCode)].isNull()){

        }else{
            cout << "Would you like to overwrite the index?" << endl;
            string input;
            do{
                cin >> input;
            }while(input != "y" && input != "Y" && input != "n" && input != "N");
            if(input == "N" || input == "n"){
                cout << "[Fail] Adding to index failed" << endl;
                QuizIndex.close();
                return 0;
            }
        }
        

        root["Quizes"][to_string(quiz->quizCode)]["QuizCode"] = quiz->quizCode;
        root["Quizes"][to_string(quiz->quizCode)]["QuizTitle"] = quiz->title;
        root["Quizes"][to_string(quiz->quizCode)]["QuizPath"] = quizPath;

        QuizIndex.close();

        Json::StreamWriterBuilder builder;
        builder["commentStyle"] = "None";
        builder["indentation"] = "  ";
        unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
        ofstream outputFileStream("QuizIndex.json");
        writer -> write(root,&outputFileStream);
        cout << "[Success] Adding to index success" << endl;

        outputFileStream.close();

    }catch(exception){
        cout << "[Fail] Adding to index failed" << endl;
        return 0;
    }
    return 1;
}