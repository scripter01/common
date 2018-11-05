#include "stdafx.h"
#include "ThreadPool.h"

std::mutex g_mtxLog;
#define LOG(a) { std::lock_guard<std::mutex> lock(g_mtxLog); std::cout << a << std::endl; }

class WaitThreadTask: public ThreadTask
{
public:
	WaitThreadTask(const uint32_t step): m_stepCount(step)
	{}

	void run()
	{
		for (int i = 0; i < m_stepCount; i++)
		{
			LOG("THREAD: " << std::this_thread::get_id() << " WAIT: " << i + 1 << "/" << m_stepCount);
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
	}

private:
	const int m_stepCount;
};

int main()
{
	ThreadPool threadPool;
	threadPool.addTask(new WaitThreadTask(3));
	threadPool.addTask(new WaitThreadTask(4));
	system("pause");
	return 1;
}