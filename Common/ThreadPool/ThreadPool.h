#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include "ThreadTaskQueue.h"

class ThreadTask
{
public:
	virtual ~ThreadTask() = default;
	virtual void run() = 0;
};

class ThreadPool
{
	ThreadPool(uint32_t threadsCount = 0);
	~ThreadPool();

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