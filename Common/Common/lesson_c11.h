#ifndef LESSON_C11_H
#define LESSON_C11_H

#include "lessonBase.h"

// Списки инициализации
struct SimpleStruct
{
	int i;
	float f;
};

class SequenceClass
{
public:
	SequenceClass(std::initializer_list<SimpleStruct> list);
	
private:
	void print();

private:
	std::vector<SimpleStruct> m_vec;
};

class Lesson_c11: public LessonBase
{
public:
	Lesson_c11();

	void run();
};

#endif //LESSON_C11