#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Question.h"
using namespace std;

class MultipleChoiceQuestion : public virtual Question
{
public:
  MultipleChoiceQuestion(string, QuestionType, vector<string>, vector<string>, int);
  ~MultipleChoiceQuestion();
  // MultipleChoiceQuestion() = delete;
  // MultipleChoiceQuestion(const MultipleChoiceQuestion &) = delete;
  // MultipleChoiceQuestion(MultipleChoiceQuestion &&) = default;
  vector<string> choices;
  int correctAnswer;
  int userChoice;
  virtual int verifyAnswer(string);
  void printQuestion() const;
  void promptAnswer();
private:
  vector<string> allowedInputs;
};