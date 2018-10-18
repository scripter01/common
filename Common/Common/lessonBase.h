#ifndef LESSON_BASE_H
#define LESSON_BASE_H

class LessonBase
{
public:
	LessonBase(char* lessonName);
	virtual ~LessonBase();

	virtual void run() = 0;
};

#endif //LESSON_BASE_H