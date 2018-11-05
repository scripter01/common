#include "stdafx.h"
#include "ThreadPool.h"

ThreadPool::ThreadPool(uint32_t threadsCount): m_done(false)
{
	const auto threadsCountMax = std::max(std::thread::hardware_concurrency(), 2U) - 1U;
	threadsCount = std::min(threadsCountMax, threadsCount);
	if (threadsCount == 0)
		threadsCount = threadsCountMax;

	for (std::uint32_t i = 0; i < threadsCount; ++i)
		m_threads.emplace_back(&ThreadPool::worker, this);
}

ThreadPool::~ThreadPool()
{
	destroy();
}

void ThreadPool::worker()
{
	while (!m_done)
	{
		std::unique_ptr<ThreadTask> task(nullptr);
		if (m_workQueue.waitPop(task))
			task->run();
	}
}

void ThreadPool::destroy()
{
	m_done = true;
	m_workQueue.invalidate();
	for (auto& thread : m_threads)
	{
		if (thread.joinable())
			thread.join();
	}
}

void ThreadPool::addTask(ThreadTask* task)
{
	std::unique_ptr<ThreadTask> ptr(task);
	m_workQueue.push(std::move(ptr));
}