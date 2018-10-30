#include "stdafx.h"
#include "lesson_multithreading.h"

void Lesson_multithreading::run()
{
	LOG("Hardware concurrency: " << std::thread::hardware_concurrency());
}