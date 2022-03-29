#include <string>
#include "Question.h"

Question::Question(string question, QuestionType type)
{
    this->question = question;
    this->type = type;
    this->score = 0;
}

Question::~Question()
{

}

void Question::printQuestion(){
    cout << this->question;
}

int Question::verifyAnswer()
{
	return 1;
}
