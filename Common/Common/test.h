#ifndef TEST_H
#define TEST_H

#include "lessonBase.h"

class Test : public LessonBase
{
public:
	Test() : LessonBase("Test") {};
	void run();
};

#endif //TEST_H
