#pragma once

#ifndef SESSIONHANDLER_H
#define SESSIONHANDLER_H

#include "Person.h"

class SessionHandler{
    public:
        static SessionHandler* shared_instance();
        void setUser(Person*);
        Person* getUser();
    private:
        Person* loggedInUser;
};

#endif