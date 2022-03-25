#include <string>
#include <vector>
#include <iostream>
using namespace std;

class InputHandler{
    public:
        static int verifyMCQInput(string, vector<string>);
        static int verifyMSQInput(vector<string>, vector<string>);
        static vector<string> stringToVector(string, char);
};