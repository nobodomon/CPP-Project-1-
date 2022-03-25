#include "MultiSelectQuestion.h"
#include "InputHandler.h"
using namespace std;

MultiSelectQuestion::MultiSelectQuestion(string question, QuestionType type, vector<string> choices, vector<string> allowedInputs, vector<int> correctAnswer)
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
    while (InputHandler::verifyMSQInput(inputs,this->allowedInputs) == 0 || inputs.size() == 0)
    {
        inputs.clear();
        string rawInput;
        size_t pos = 0;
        string token;
        cout << "Your answer: ";
        cin >> rawInput;
        cout << endl;
        if(rawInput.length() == 1){
            rawInput + ',';
        }
        while ((pos = rawInput.find(",")) != string::npos)
        {
            token = rawInput.substr(0, pos);
            inputs.push_back(token);
            rawInput.erase(0, pos + string(",").length());
        }
    }
    if(verifyAnswer(inputs)){
        cout << "Correct!" << endl;
    }else{
        cout << "Wrong!" << endl;
    }
}

int MultiSelectQuestion::verifyAnswer(vector<string> inputs)
{
    int counter = 0;
    for(auto &input : inputs){
        for(auto &answer: correctAnswers){
            if(input == to_string(answer)){
                counter++;
            }
        }
    }
    if(counter == correctAnswers.size()){
        return 1;
    }else{
        return 0;
    }
}
