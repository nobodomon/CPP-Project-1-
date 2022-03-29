#include "MultiSelectQuestion.h"
#include "InputHandler.h"
using namespace std;

MultiSelectQuestion::MultiSelectQuestion(string question, QuestionType type, vector<string> choices, vector<string> allowedInputs, vector<string> correctAnswer)
    : Question(question, type)
{
    this->question = question;
    this->type = type;
    this->choices = choices;
    this->allowedInputs = allowedInputs;
    this->correctAnswers = correctAnswer;
}

void MultiSelectQuestion::printQuestion()
{
    cout << this->question << endl;
    int optionNo = 1;
    for (auto &choice : choices)
    {
        cout << "[" + to_string(optionNo) + "] " << choice << endl;
        optionNo++;
    }
}

void MultiSelectQuestion::promptAnswer()
{
    vector<string> inputs;
    do
    {
        inputs.clear();
        string rawInput;
        cout << "Your answer: ";
        cin >> rawInput;
        inputs = InputHandler::stringToVector(rawInput, ',');
    }while(InputHandler::verifyMSQInput(inputs,this->allowedInputs) == 0);
    this->userChoice = inputs;
    if(verifyAnswer(inputs)){
        cout << "Correct!" << endl;
        this->score = 1;
    }else{
        cout << "Wrong!" << endl;
    }
}

int MultiSelectQuestion::verifyAnswer(vector<string> inputs)
{
    int counter = 0;
    for(auto &input : inputs){
        for(auto &answer: this->correctAnswers){
            if(input == answer){
                counter++;
                break;
            }
        }
    }
    if(counter == this->correctAnswers.size()){
        return 1;
    }else{
        return 0;
    }
}
