#include "Quiz.h"
#include "Question.h"
#include "MultipleChoiceQuestion.h"
#include "MultiSelectQuestion.h"
#include "ShortAnswerQuestion.h"
#include <memory>
#include <fstream>
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
	vector<Question *>::iterator iter;
	for (iter = this->Questions.begin(); iter != this->Questions.end(); iter++)
	{
		// cout << i << endl;
		if (MultipleChoiceQuestion *mcq = dynamic_cast<MultipleChoiceQuestion *>(this->Questions[i]); mcq != nullptr)
		{
			// cout << "MCQ Casted" << endl;
			mcq->printQuestion();
			mcq->promptAnswer();
		}
		else if (MultiSelectQuestion *msq = dynamic_cast<MultiSelectQuestion *>(this->Questions[i]); msq != nullptr)
		{
			// cout << "MSQ Casted" << endl;
			msq->printQuestion();
			msq->promptAnswer();
		}
		else if (ShortAnswerQuestion *saq = dynamic_cast<ShortAnswerQuestion *>(this->Questions[i]); saq != nullptr)
		{
			saq->printQuestion();
			saq->promptAnswer();
		}
		i++;
	}
	cout << "-Quiz end-" << endl;
}
