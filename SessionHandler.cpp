#include "SessionHandler.h"
#include <iostream>
using namespace std;

static SessionHandler* s_SharedSession = nullptr;

SessionHandler* SessionHandler::shared_instance()
{
    if (!s_SharedSession)
    {
        s_SharedSession = new SessionHandler();
        if (!s_SharedSession)
        {
            cout << "FATAL: Not enough memory" << endl;
        }
    }
    return s_SharedSession;
}

void SessionHandler::setUser(Person* person){
    this->loggedInUser = person;
}

Person* SessionHandler::getUser(){
    return loggedInUser;
}
