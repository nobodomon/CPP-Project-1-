#include "Person.h"

Person::Person(string name,string password){
    this->name = name;
    this->password = password;
};

Person::Person(string name,string password, vector<QuizAttempt*> attempts){
    this->name = name;
    this->password = password;
    this->quizAttempts = attempts;
};

vector<QuizAttempt*> Person::getAttempts(){
    return this->quizAttempts;
}