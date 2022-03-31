#include "ShortAnswerQuestion.h"
#include "InputHandler.h"
using namespace std;

ShortAnswerQuestion::ShortAnswerQuestion(string question, QuestionType type, vector<string> acceptableAnswers)
    : Question(question, type)
{
    this->question = question;
    this->type = type;
    this->acceptableAnswers = acceptableAnswers;
}

ostream& operator << (ostream& out, const ShortAnswerQuestion* saq){
	out << "[Short Answer Question]" << saq->question << endl;
	return out;
}

istream& operator >> (istream& in, ShortAnswerQuestion* saq){
    string input;
    cout << "Your answer: ";
    in >> input;
    saq->userChoice = input;
    if(saq->verifyAnswer(input)){
        cout << "Correct!" << endl;
        saq->score = 1;
    }else{
        cout << "Wrong!" << endl;
    }
	return in;
}

void ShortAnswerQuestion::printQuestion(){
    cout << this->question << endl;
}

void ShortAnswerQuestion::promptAnswer(){
    string input;
    cout << "Your answer: ";
    cin >> input;
    this->userChoice = input;
    if(verifyAnswer(input)){
        cout << "Correct!" << endl;
        this->score = 1;
    }else{
        cout << "Wrong!" << endl;
    }
}

int ShortAnswerQuestion::verifyAnswer(string input){
    for(auto &answer: acceptableAnswers){
        if(answer == input){
            return 1;
        }
    }
    return 0;
}