#include "InputHandler.h"
using namespace std;

int InputHandler::verifyMCQInput(string input, vector<string> allowedInputs)
{
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