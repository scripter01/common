#include "stdafx.h"
#include "ThreadTask.h"

ThreadFuncTask::ThreadFuncTask(std::function<void()> func):
	m_func(func) 
{}

void ThreadFuncTask::executeFunc()
{
	if (m_func != nullptr)
		m_func();
}

void ThreadFuncTask::run()
{
	ThreadTask::run();
	executeFunc();
}