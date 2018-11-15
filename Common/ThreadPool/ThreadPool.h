#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include "ThreadTaskQueue.h"
#include "ThreadTask.h"

class ThreadPool
{
public:
	ThreadPool(uint32_t threadsCount = 0);
	~ThreadPool();

	void addTask(ThreadTask* task);
	void addTask(std::unique_ptr<ThreadTask>& task);

private:
	ThreadPool(const ThreadPool& rhs) = delete;
	ThreadPool& operator=(const ThreadPool& rhs) = delete;

	void worker();
	void destroy();

private:
	std::atomic_bool m_done;
	ThreadTaskQueue<std::unique_ptr<ThreadTask>> m_workQueue;
	std::vector<std::thread> m_threads;
};

#endif //THREAD_POOL_H