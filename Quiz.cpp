#include "Quiz.h"
using namespace std;


int Quiz::addQuestion(Question* questionToAdd){
    try{
        this->Questions.push_back(questionToAdd);
        return 1;
    }catch(exception){
        return 0;
    }
}

void Quiz::readFile()
{
}
