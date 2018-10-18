#include "stdafx.h"
#include "lessonBase.h"

LessonBase::LessonBase(char* lessonName)
{
	std::cout << "start lesson: " << lessonName << "\n";
}

LessonBase::~LessonBase()
{
	std::cout << "end lesson";
}