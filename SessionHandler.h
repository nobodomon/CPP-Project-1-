#pragma once

#ifndef SESSIONHANDLER_H
#define SESSIONHANDLER_H

#include "Person.h"

class SessionHandler{
    public:
        static SessionHandler &shared_instance() {
            static SessionHandler sessionHandler;
            return sessionHandler;
        }
        Person* loggedInUser;
    private:
        SessionHandler(){}
};

#endif