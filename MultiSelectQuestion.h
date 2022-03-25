#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Question.h"
using namespace std;

class MultiSelectQuestion : public Question
{
public:
  MultiSelectQuestion(string, QuestionType,vector<string>,vector<string>, vector<int>);
  vector<string> choices;
  vector<int> correctAnswers;
  vector<int> userChoices;
  virtual int verifyAnswer(vector<string>);
  void printQuestion();
  void promptAnswer();
private:
  vector<string> allowedInputs;
};