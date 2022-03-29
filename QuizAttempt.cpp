#include "QuizAttempt.h"
#include "SessionHandler.h"
#include "Person.h"
#include "json.h"
#include <string>
#include <iostream>
#include <fstream>
#include <memory>
using namespace std;

QuizAttempt::QuizAttempt(string attemptID, int quizCode, int score, int totalQns)
{
    this->attemptID;
    this->quizCode = quizCode;
    this->score = score;
    this->totalQns = totalQns;
}

int QuizAttempt::writeFile()
{
    SessionHandler handler = SessionHandler::shared_instance();
    cout << "Writing to " + handler.loggedInUser->name;
    Json::Value root;
    ifstream userFile(handler.loggedInUser->name + ".json");
    userFile >> root;
    userFile.close();
    ofstream outputFileStream(handler.loggedInUser->name + ".json");
    root["user"]["attempts"][attemptID]["QuizCode"] = quizCode;
    root["user"]["attempts"][attemptID]["Score"] = score;
    root["user"]["attempts"][attemptID]["TotalQns"] = totalQns;

    Json::StreamWriterBuilder builder;
    builder["commentStyle"] = "None";
    builder["indentation"] = "  ";
    unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
    writer->write(root, &outputFileStream);
    
    cout << "[Success] Adding attempt to user file success" << endl;
    outputFileStream.close();
    return 1;
}
