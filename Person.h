#pragma once

#include <string>
#include <vector>
#include "QuizAttempt.h"
using namespace std;
class Person {
public:
	Person(string name,string password){
		this->name = name;
		this->password = password;
	}
	string name;
	string password;
	vector<QuizAttempt*> quizAttempts;
};