#include "FileHandler.h"
#include "InputHandler.h"
#include "Index.h"
#include "Person.h"
#include <sys/stat.h>
#include <filesystem>
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
	root["user"]["attempts"] = Json::arrayValue;
	Json::StreamWriterBuilder builder;
	builder["commentStyle"] = "None";
	builder["indentation"] = "  ";
	unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
    writer -> write(root,&outputFileStream);
	outputFileStream.close();
	return new Person(user,password);
}

Person* FileHandler::getUser(string user, string password){
	vector<QuizAttempt*> attempts;
	Json::Value root;
	if(!checkIfFileExist(user+".json")){
		cout << "User does not exist!" << endl;
		return nullptr;
	}
	
	ifstream readUser(user+".json");
	readUser >> root;
	readUser.close();

	if(password == root["user"]["password"].asString()){
		Json::Value attemptsArray = root["user"]["attempts"];
		for(Json::Value::ArrayIndex i = 0; i != attemptsArray.size(); i++){
			auto curr = attemptsArray[i];
			attempts.push_back(new QuizAttempt(curr["AttemptID"].asString(),curr["QuizCode"].asInt(),curr["Score"].asInt(),curr["TotalQns"].asInt()));
		}
		return new Person(root["user"]["name"].asString(),root["user"]["password"].asString(),attempts);
	}else{
		cout << "Invalid password!" << endl;
		return nullptr;
	}
}

int FileHandler::createQuizIndexFile(){
	try{
		Json::Value root;
		root["Quizes"] = Json::arrayValue;
		Json::StreamWriterBuilder builder;
		builder["commentStyle"] = "None";
		builder["indentation"] = "  ";
		unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
		ofstream outputFileStream("QuizIndex.json");
		writer -> write(root,&outputFileStream);
		cout << "[Success] Creating new index success" << endl;

		outputFileStream.close();
		return 1;
	}catch(exception){
		cout << "Error creating new index!";
		return 0;
	}
}


int FileHandler::addNewQuiz(Quiz* quiz,string quizPath){
    try{
        Json::Value root;
        ifstream QuizIndex("QuizIndex.json");
		if(QuizIndex.fail()){
			QuizIndex.close();
			createQuizIndexFile();
        	ifstream QuizIndex("QuizIndex.json");
        	QuizIndex >> root;
		}else{
			QuizIndex >> root;
		}
		
		Json::Value newIndexEntry;

		newIndexEntry["QuizCode"] = quiz->quizCode;
		newIndexEntry["QuizTitle"] = quiz->title;
		newIndexEntry["QuizPath"] = quizPath;

		for(Json::Value::ArrayIndex i = 0; i != root["Quizes"].size(); i++){
			if(root["Quizes"][i]["QuizCode"].asInt() == quiz->quizCode){
				cout << "Would you like to overwrite the index?" << endl;
				string input;
				do{
					cin >> input;
				}while(input != "y" && input != "Y" && input != "n" && input != "N");
				if(input == "N" || input == "n"){
					cout << "[Fail] Adding to index failed" << endl;
					QuizIndex.close();
					return 0;
				}else{
					root["Quizes"][i] = newIndexEntry;
					cout << "[Success] Overwriting completed" << endl;
					QuizIndex.close();
					return 1;
				}
			}
		}
        

        root["Quizes"].append(newIndexEntry);

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

vector<Index*> FileHandler::getIndexes(){
	Json::Value root;
	ifstream quizIndex("QuizIndex.json");
	quizIndex >> root;
	vector<Index*> index;
	for(Json::Value::ArrayIndex i = 0; i < root["Quizes"].size(); i++){
		Json::Value curr = root["Quizes"][i];
		index.push_back(new Index(curr["QuizCode"].asInt(),curr["QuizTitle"].asString(),curr["QuizPath"].asString()));
	}
	return index;
}

Index* FileHandler::getIndexByKey(string in, vector<Index*> index){
	for(int i = 0; i < index.size();i++){
		if(index[i] == in){
			return index[i];
		}
	}
	return nullptr;
}


bool FileHandler::checkIfFileExist(string path){
	
	ifstream readUser(path);
	if(readUser.fail()){
		readUser.close();
		return false;
	}else{
		readUser.close();
		return true;
	}
}

bool FileHandler::checkIfValidFile(string path,FileType fileType){
	filesystem::path filePath = path;
	if(filePath.extension() != ".json"){
		throw(string("Invalid file!"));
		return false;
	}
	if(checkIfFileExist(path) == false){
		throw(string("File does not exist!"));
		return false;
	}
	Json::Value root;
	ifstream file(filePath);
	file >> root;
	file.close();
	if(fileType == FileType::INDEX && !root["Quizes"].isNull()){
		return true;
	}
	if(fileType == FileType::USER && !root["user"].isNull()){
		return true;
	}
	if(fileType == FileType::QUIZ && !root["Quiz"].isNull()){
		return true;
	}
	throw(string("Invalid file!"));
	return false;
}