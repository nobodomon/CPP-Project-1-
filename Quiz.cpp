#include <string>
#include <memory>
#include "Question.h"
#include <vector>
using namespace std;
class Quiz
{
public:
	int quizCode;
	std::string title;
	std::vector<unique_ptr<Question>> Questions;
	virtual void printQuestion(){}
	void readFile(){};
};