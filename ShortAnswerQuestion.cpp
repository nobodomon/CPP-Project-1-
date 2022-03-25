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

void ShortAnswerQuestion::printQuestion(){
    cout << this->question << endl;
}

void ShortAnswerQuestion::promptAnswer(){
    string input;
    cout << "Your answer: ";
    cin >> input;
    if(verifyAnswer(input)){
        cout << "Correct!" << endl;
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