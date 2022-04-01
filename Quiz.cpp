#include "Quiz.h"
#include "Question.h"
#include "MultipleChoiceQuestion.h"
#include "MultiSelectQuestion.h"
#include "ShortAnswerQuestion.h"
#include "QuizAttempt.h"
#include <memory>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <algorithm> // for copy
#include <iterator> // for ostream_iterator
using namespace std;


int Quiz::addQuestion(Question* questionToAdd){
    try{
        this->Questions.push_back(questionToAdd);
        return 1;
    }catch(exception){
        return 0;
    }
}

void Quiz::startQuiz()
{
    
	int i = 0;
	int totalScore = 0;
	vector<Question *>::iterator iter;
	for (iter = this->Questions.begin(); iter != this->Questions.end(); iter++)
	{
		// cout << i << endl;
		if (MultipleChoiceQuestion *mcq = dynamic_cast<MultipleChoiceQuestion *>(this->Questions[i]); mcq != nullptr)
		{
			// cout << "MCQ Casted" << endl;
			cout << mcq;
			cin >> mcq;
			totalScore += mcq->score;
		}
		else if (MultiSelectQuestion *msq = dynamic_cast<MultiSelectQuestion *>(this->Questions[i]); msq != nullptr)
		{
			// cout << "MSQ Casted" << endl;
			cout << msq;
			cin >> msq;
			totalScore += msq->score;
		}
		else if (ShortAnswerQuestion *saq = dynamic_cast<ShortAnswerQuestion *>(this->Questions[i]); saq != nullptr)
		{
			cout << saq;
			cin >> saq;
			totalScore += saq->score;
		}
		i++;
	}
	cout << "-Quiz end-" << endl;
	//Find attemptID
    vector<string> strNum;
	string attemptID;
    srand(time(0));  // Initialize random number generator.
    for(int i=0;i<10;i++)
    {
        strNum.push_back(to_string(rand()%10));
    } 
    for(auto & elem : strNum)
    {
        attemptID = attemptID.append(elem);
    }
	QuizAttempt* attempt = new QuizAttempt(attemptID,this->quizCode,totalScore,this->Questions.size());
	attempt->writeFile();
}
