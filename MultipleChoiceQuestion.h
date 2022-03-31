#pragma once

#ifndef MULTIPLECHOICEQUESTION_H
#define MULTIPLECHOICEQUESTION_H

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
  friend ostream& operator <<(ostream&, const MultipleChoiceQuestion*);
  friend istream& operator >>(istream&, MultipleChoiceQuestion*);
  vector<string> choices;
  int correctAnswer;
  string userChoice;
  virtual int verifyAnswer(string);
  void printQuestion() const;
  void promptAnswer();
  vector<string> getAllowedInputs();
private:
  vector<string> allowedInputs;
};

#endif