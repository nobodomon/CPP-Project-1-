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

ostream &operator << (ostream &out, const MultiSelectQuestion* msq)
{
    out << "[Multi Select Question]" << msq->question << endl;
    int optionNo = 1;
    for (auto &choice : msq->choices)
    {
        out << "[" + to_string(optionNo) + "] " << choice << endl;
        optionNo++;
    }
    return out;
}

istream &operator >> (istream &in, MultiSelectQuestion* msq)
{
    vector<string> inputs;
    do
    {
        inputs.clear();
        string rawInput;
        cout << "Your answer: ";
        in >> rawInput;
        inputs = InputHandler::stringToVector(rawInput, ',');
    } while (InputHandler::verifyMSQInput(inputs, msq->getAllowedInputs()) == 0);
    msq->userChoice = inputs;
    if (msq->verifyAnswer(inputs))
    {
        cout << "Correct!" << endl;
        msq->score = 1;
    }
    else
    {
        cout << "Wrong!" << endl;
    }
    return in;
}

vector<string> MultiSelectQuestion::getAllowedInputs(){
    return this->allowedInputs;
}

vector<string> MultiSelectQuestion::getChoices(){
    return this->choices;
}
void MultiSelectQuestion::setChoices(vector<string> choices){
    this->choices = choices;
}
vector<string> MultiSelectQuestion::getCorrectAnswers(){
    return this->correctAnswers;
}
void MultiSelectQuestion::setCorrectAnswers(vector<string> correctAnswer){
    this->correctAnswers = correctAnswer;
}

vector<string> MultiSelectQuestion::getUserChoice(){
    return this->userChoice;
}

void MultiSelectQuestion::setUserChoice(vector<string> userChoice){
    this->userChoice = userChoice;
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
    } while (InputHandler::verifyMSQInput(inputs, this->allowedInputs) == 0);
    this->userChoice = inputs;
    if (verifyAnswer(inputs))
    {
        cout << "Correct!" << endl;
        this->score = 1;
    }
    else
    {
        cout << "Wrong!" << endl;
    }
}

int MultiSelectQuestion::verifyAnswer(vector<string> inputs)
{
    int counter = 0;
    for (auto &input : inputs)
    {
        for (auto &answer : this->correctAnswers)
        {
            if (input == answer)
            {
                counter++;
                break;
            }
        }
    }
    if (counter == this->correctAnswers.size())
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
