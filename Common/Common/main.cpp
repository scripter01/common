#include "stdafx.h"
#include "lesson_c11.h"
#include "lesson_bits.h"

template <typename T>
void startLesson()
{
	T lesson;
	lesson.run();
}

int main()
{
	startLesson<Lesson_c11>();
	startLesson<Lesson_bits>();
	return 1;
}