#pragma once

#ifndef MULTISELECTQUESTION_H
#define MULTISELECTQUESTION_H

#include <iostream>
#include <string>
#include <vector>
#include "Question.h"
using namespace std;

class MultiSelectQuestion : public Question
{
public:
  MultiSelectQuestion(string, QuestionType,vector<string>,vector<string>,vector<string>);
  
  friend ostream& operator <<(ostream&, const MultiSelectQuestion*);
  friend istream& operator >>(istream&, MultiSelectQuestion*);
  virtual int verifyAnswer(vector<string>);
  void printQuestion();
  void promptAnswer();
  vector<string> getAllowedInputs();
  vector<string> getChoices();
  void setChoices(vector<string>);
  vector<string> getCorrectAnswers();
  void setCorrectAnswers(vector<string>);
  vector<string> getUserChoice();
  void setUserChoice(vector<string>);

private:
  vector<string> allowedInputs;
  vector<string> choices;
  vector<string> correctAnswers;
  vector<string> userChoice;
};

#endif