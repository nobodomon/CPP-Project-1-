#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Question.h"
using namespace std;

class MultipleChoiceQuestion : public virtual Question
{
public:
  MultipleChoiceQuestion(string, QuestionType, vector<string>, int);
  ~MultipleChoiceQuestion()
  {
  }
  // MultipleChoiceQuestion() = delete;
  // MultipleChoiceQuestion(const MultipleChoiceQuestion &) = delete;
  // MultipleChoiceQuestion(MultipleChoiceQuestion &&) = default;
  vector<string> choices;
  int correctAnswer;
  int userChoice;
  virtual int verifyAnswer();
  virtual void printQuestion(){};
};