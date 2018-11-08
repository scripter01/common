#include "stdafx.h"
#include "ThreadPool.h"

void waitSec(const int sec)
{
	for (int i = 0; i < sec; i++)
	{
		LOG("THREAD: " << std::this_thread::get_id() << " WAIT: " << i + 1 << "/" << sec);
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}

class WaitThreadTask: public ThreadTask
{
public:
	WaitThreadTask(const uint32_t step): m_stepCount(step)
	{}

	void run()
	{
		waitSec(m_stepCount);
	}

private:
	const int m_stepCount;
};

int main()
{
	ThreadPool threadPool;
	threadPool.addTask(new WaitThreadTask(10));
	threadPool.addTask(new WaitThreadTask(5));
	threadPool.addTask(new ThreadFuncTask([]()
	{
		waitSec(6);
	}));

	while (true){}
	return 1;
}