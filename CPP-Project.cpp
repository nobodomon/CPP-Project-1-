// CPP-Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "FileHandler.h"
#include "Quiz.h"
#include "Question.h"
#include "Index.h"
#include "MultipleChoiceQuestion.h"
#include "MultiSelectQuestion.h"
#include "ShortAnswerQuestion.h"
#include "Person.h"
using namespace std;

void printMenu();
void registerUser();
void open();
void load();
void detectInputIntent(string input);

int main()
{
	string input;
	cout << "Welcome to Quizzo how may I help you today?" << endl;
	printMenu();
	while (input != "exit")
	{
		cin >> input; cout << endl;
		detectInputIntent(input);
	}
	cout << "Goodbye!" << endl;
	return 1;
}

void printMenu()
{
	cout << "Commands:" << endl;
	cout << "getinfo - Load your userdata" << endl;
	cout << "load - Add a new quiz into the index" << endl;
	cout << "open - Open a quiz and start attempting" << endl;
	cout << "info - Displays your info" << endl;
	cout << "exit - Exit the program" << endl;
}

void registerUser(){
	cout << "Enter name: " << endl;
	string name;
	cin >> name;
	string password;
	string confirmPassword;
	do{
		cout << "Enter a password" << endl;
		cin >> password;
		cout << "Confirm password" << endl;
		cin >> confirmPassword;
	}while(password != confirmPassword);

	Person * readPerson = FileHandler::createUser(name,password);
	cout << readPerson->name << endl;
}

void open()
{	
	cout << "Enter quiz file name" << endl;
	string path;
	cin >> path;
	Quiz *readQuiz = FileHandler::getQuizFromFile(path);
	readQuiz->startQuiz();
}

void load(){
	string filePath;
	cout << "Adding new quiz into index" << endl;	
	cout << "Enter quiz file name" << endl;
	string path;
	cin >> path;
	Quiz *quiz = FileHandler::getQuizFromFile(path);
	FileHandler::addNewQuiz(quiz,path);
}

void detectInputIntent(string input){
	if(input == "register"){
		registerUser();
		printMenu();
	}else if(input == "open"){
		open();
		printMenu();
	}else if(input == "load"){
		load();
		printMenu();
	}
	else{
		cout << "Invalid option!" << endl;
		printMenu();
	}
}