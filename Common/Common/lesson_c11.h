#ifndef LESSON_C11_H
#define LESSON_C11_H

#include "lessonBase.h"

// Списки инициализации
struct SimpleStruct
{
	int i;
	float f;
};

// Списки инициализации
class SequenceClass
{
public:
	SequenceClass(std::initializer_list<SimpleStruct> list);
	
private:
	void print();

private:
	std::vector<SimpleStruct> m_vec;
};

// Лямбда - функции и выражения
class SortedIntVector
{
public:
	SortedIntVector();
	void insert(int number);
	void print() const;

private:
	std::vector<int> m_vec;
	int m_valueMax;
};


class Lesson_c11: public LessonBase
{
public:
	Lesson_c11();

	void run();
};

#endif //LESSON_C11