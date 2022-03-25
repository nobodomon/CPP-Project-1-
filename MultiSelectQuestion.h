#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Question.h"
using namespace std;

class MultiSelectQuestion : public Question
{
public:
  MultiSelectQuestion(string, QuestionType,vector<string>,vector<string>,vector<string>);
  vector<string> choices;
  vector<string> correctAnswers;
  vector<int> userChoices;
  virtual int verifyAnswer(vector<string>);
  void printQuestion();
  void promptAnswer();
private:
  vector<string> allowedInputs;
};