#include "stdafx.h"
#include "lesson_bits.h"
#include "lesson_c11.h"
#include "lesson_c14.h"
#include "lesson_smartPointers.h"
#include "lesson_multithreading.h"
#include "lesson_stl.h"
#include "testPlayground.h"

template <typename T>
void startLesson()
{
	T lesson;
	lesson.run();
}

int main()
{
	startLesson<Lesson_bits>();
	startLesson<Lesson_c11>();
	startLesson<Lesson_c14>();
	startLesson<Lesson_stl>();
	startLesson<Lesson_smartPointers>();
	startLesson<Lesson_multithreading>();
	startLesson<TestPlayground>();

	system("pause");	
	return 1;
}