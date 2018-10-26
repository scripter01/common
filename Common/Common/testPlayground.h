#ifndef TEST_PLAYGROUND_H
#define TEST_PLAYGROUND_H

#include "lessonBase.h"

class TestPlayground : public LessonBase
{
public:
	TestPlayground() : LessonBase("Test playground") {};
	void run();
};

#endif //TEST_PLAYGROUND_H
