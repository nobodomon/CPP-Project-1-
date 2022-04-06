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
#include <ctime>
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
    time_t curr_time;
	tm * curr_tm;
	char attemptDate[100];
	string attemptID;
	time(&curr_time);
	curr_tm = localtime(&curr_time);
	
    strftime(attemptDate, 50, "%m%d%y%H%M%S", curr_tm);
	//QuizCode/Month/Day/Year/Hour/Min/Sec
	attemptID = to_string(quizCode).append(attemptDate);
	QuizAttempt* attempt = new QuizAttempt(attemptID,this->quizCode,totalScore,this->Questions.size());
	attempt->writeFile();
}
