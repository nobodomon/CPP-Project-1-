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
#include "SessionHandler.h"
using namespace std;

void printMenu();
void registerUser();
void login();
void open();
void load();
void detectInputIntent(string input);
SessionHandler* handler = SessionHandler::shared_instance();
int main()
{
	string input;
	printMenu();
	while (input != "exit")
	{
		cin >> input; cout << endl;
		detectInputIntent(input);
	}
	return 1;
}

void printGreeting(){
	if(handler->getUser() != nullptr){
		cout << "Welcome back " + handler->getUser()->name + ". how may I help you today?" << endl;
	}else{
		cout << "Welcome to Quizzo how may I help you today?" << endl;
	}
}

void printMenu()
{
	cout << "Commands:" << endl;
	if(handler->getUser() == nullptr){
		cout << "[register] - Create a new user" << endl;
		cout << "[login] - Login to existing user" << endl;
	}else{
		cout << "[getinfo] - Load your userdata" << endl;
		cout << "[load] - Add a new quiz into the index" << endl;
		cout << "[open] - Open a quiz and start attempting" << endl;
		cout << "[info] - Displays your info" << endl;
		cout << "[logout] - logout from current user" << endl;
	}
	cout << "[exit] - Exit the program" << endl;
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
	if(readPerson != nullptr){
		handler->setUser(readPerson);
		printGreeting();
		//cout << readPerson->name << endl;
	}
}

void login(){
	cout << "Enter name: " << endl;
	string name;
	cin >> name;
	cout << "Enter password: " << endl;
	string password;
	cin >> password;
	Person* loggedInUser = FileHandler::getUser(name,password);
	if(loggedInUser != nullptr){
		cout << "Logged in successfully as " + name << endl;
		handler->setUser(loggedInUser);
		printGreeting();
	}
	
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
	if(input == "exit"){
		
		cout << "Goodbye!" << endl;
		return;
	}
	if (handler->getUser() != nullptr)
	{
		if (input == "open")
		{
			open();
			printMenu();
		}
		else if (input == "load")
		{
			load();
			printMenu();
		}else if(input == "logout"){
			handler->setUser(nullptr);
			printMenu();
		}else{
			cout << "Invalid option!" << endl;
			printMenu();
		}
	}
	else
	{
		if(input == "register"){
			registerUser();
			printMenu();
		}else if (input == "login"){
			login();
			printMenu();
		}else
		{
			cout << "Invalid option!" << endl;
			printMenu();
		}
	}
		
}