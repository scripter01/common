#include "stdafx.h"
#include "lessonBase.h"

LessonBase::LessonBase(char* lessonName)
{
	std::cout << "start lesson: " << lessonName << "\n\n";
}

LessonBase::~LessonBase()
{
	std::cout << "\nend lesson\n\n";
}