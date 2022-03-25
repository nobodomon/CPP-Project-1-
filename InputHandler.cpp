#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include "InputHandler.h"
using namespace std;

int InputHandler::verifyMCQInput(string input, vector<string> allowedInputs)
{
    if(input.length() == 0){
        cout << "Invalid input!" << endl;
        return 0;
    }
    for (auto &allowed : allowedInputs)
    {
        if (input == allowed)
        {
            return 1;
        }
    }
    cout << "Invalid input!" << endl;
    return 0;
}

int InputHandler::verifyMSQInput(vector<string> inputs, vector<string>allowedInputs){
    int counter = 0;
    if(inputs.size() == 0){
        cout << "Invalid input!" << endl;
        return 0;
    }
    for(auto &input: inputs){
        for(auto &allowed: allowedInputs){
            if(input == allowed){
                counter++;
            }
        }
    }
    if(counter == inputs.size()){
        return 1;
    }else{
        cout << "Invalid input!" << endl;
        return 0;
        
    }
}

vector<string> InputHandler::stringToVector(string rawInput, char delim){
    vector<string> input;
    stringstream rawInputStream(rawInput);
    while(rawInputStream.good()){
        string token;
        getline(rawInputStream,token,delim);
        input.push_back(token);
    }
    return input;
}