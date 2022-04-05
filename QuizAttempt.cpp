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
    this->attemptID = attemptID;
    this->quizCode = quizCode;
    this->score = score;
    this->totalQns = totalQns;
}

int QuizAttempt::writeFile()
{
    SessionHandler* handler = SessionHandler::shared_instance();
    cout << "Writing to " + handler->getUser()->name << endl;
    Json::Value root;
    ifstream userFile(handler->getUser()->name + ".json");
    userFile >> root;
    userFile.close();
    ofstream outputFileStream(handler->getUser()->name + ".json");
    Json::Value attempt;
    attempt["AttemptID"] = attemptID;
    attempt["QuizCode"] = quizCode;
    attempt["Score"] = score;
    attempt["TotalQns"] = totalQns;

    root["user"]["attempts"].append(attempt);

    Json::StreamWriterBuilder builder;
    builder["commentStyle"] = "None";
    builder["indentation"] = "  ";
    unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
    writer->write(root, &outputFileStream);
    
    cout << "[Success] Adding attempt to user file success" << endl;
    outputFileStream.close();
    handler->updateUser();
    return 1;
}

ostream& operator << (ostream& out, const QuizAttempt* attempt){
    out << "[" <<  attempt->attemptID << "] " << attempt->quizCode << endl;
    out << attempt->score << "/" << attempt->totalQns << endl;
    return out;
}
