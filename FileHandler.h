#include <string>
#include <iostream>
#include <fstream>
#include <memory>
#include "json.h"
#include "Quiz.h"
#include "MultipleChoiceQuestion.h"
#include "MultiSelectQuestion.h"
#include "ShortAnswerQuestion.h"

class FileHandler {
	public:
		static Quiz* getQuizFromFile();
};