#pragma once

#include <string>
#include <vector>
#include "QuizAttempt.h"
using namespace std;
class Person {
public:
	Person(string,string);
	Person(string,string, vector<QuizAttempt*>);
	string name;
	string password;
	vector<QuizAttempt*> getAttempts();
private:
	vector<QuizAttempt*> quizAttempts;
};