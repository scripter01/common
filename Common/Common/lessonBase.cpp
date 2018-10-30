#include "stdafx.h"
#include "lessonBase.h"

LessonBase::LessonBase(char* lessonName)
{
	LOG("LESSON: " << lessonName << "\n");
}

LessonBase::~LessonBase()
{
	LOG("\n***************************************");
}