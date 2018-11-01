#include "stdafx.h"
#include "lesson_multithreading.h"

#define CONCURRENCY_ENABLED 1

#ifdef CONCURRENCY_ENABLED
#include "cvmarkersobj.h"
Concurrency::diagnostic::marker_series g_series;
#define C_SPAN(name) Concurrency::diagnostic::span c_span(g_series, _T(name));
#define C_FLAG(name) g_series.write_flag(_T(name));
#define C_MSG(name) g_series.write_message(_T(name));
#else
#define C_SPAN(name) 
#define C_FLAG(name) 
#define C_MSG(name) 
#endif

/****************************************************/
/*                        mutex                     */
/****************************************************/

void threadPrint(int pass, int& idx, const std::string& str, std::mutex* mtx)
{
	C_SPAN("threadFoo");
	for (int i = 0; i < pass; i++)
	{
		std::lock_guard<std::mutex> lock(*mtx);
		/*if (mtx)
			mtx->lock();*/

		std::cout << str;
#define COLUMN_COUNT 3
		std::cout << (idx % COLUMN_COUNT == COLUMN_COUNT - 1 ? "\n" : " ");
		idx++;

		/*if (mtx)
			mtx->unlock();*/
	}
}

void mutexTest()
{
	C_FLAG("mutex test");

	std::mutex mtx;
	const std::string strA = "aaaaaaaa";
	const std::string strB = "bbbbbbbb";
	int idx = 0;

	C_MSG("t1 and t2");
#define THREAD_ELEMENTS_COUNT 30
	std::thread t1(threadPrint, THREAD_ELEMENTS_COUNT, std::ref(idx), ref(strA), &mtx);
	std::thread t2(threadPrint, THREAD_ELEMENTS_COUNT, std::ref(idx), ref(strB), &mtx);

	if (t1.joinable())
		t1.join();
	if (t2.joinable())
		t2.join();
}

/****************************************************/
/*                condition variable                */
/****************************************************/

std::condition_variable g_cv;
std::mutex g_mtx;

#define THREAD_MAX_VALUE 999999

void threadInc(std::atomic<int>& num, std::atomic<bool>& flag)
{
	C_SPAN("threadLog");
	while (true)
	{
		std::unique_lock<std::mutex> ulock(g_mtx);

		g_cv.wait(ulock, [&]() {return flag == true;} );
		/*while (g_cv.wait_for(ulock, std::chrono::milliseconds(300), []() {return flag == true;} ) == false)
			std::cout << "thread " << std::this_thread::get_id() << " wait" << std::endl;*/

		num++;
		if (num >= THREAD_MAX_VALUE)
			return;
	}
}

void threadSignal(std::atomic<bool>& flag)
{
	C_SPAN("threadSignal");
	Sleep(1000);
	flag = true;
	LOG("SIGNAL");
	g_cv.notify_all(); 
}

void threadStatus(std::atomic<int>& a, std::atomic<int>& b)
{
	C_SPAN("threadStatus");
	while (true)
	{
		if (a > 0 || b > 0)
		{
			LOG("a: " << a << ", b: " << b);
			if (a >= THREAD_MAX_VALUE && b >= THREAD_MAX_VALUE)
				break;
		}
		Sleep(150);
	}
}

void conditionVaribaleTest()
{
	C_FLAG("condition variable test");
	std::atomic<bool> flag = false;
	std::atomic<int> a = 0;
	std::atomic<int> b = 0;
	std::thread t1(threadInc, std::ref(a), std::ref(flag));
	std::thread t2(threadInc, std::ref(b), std::ref(flag));
	std::thread tStatus(threadStatus, std::ref(a), std::ref(b));
	std::thread tSignal(threadSignal, std::ref(flag));

	t1.join();
	t2.join();
	tStatus.join();
	tSignal.join();
}

/****************************************************/
/*                       future                     */
/****************************************************/

int threadWait(int time)
{
	LOG("thread " << std::this_thread::get_id() << " wait: " << time);
	Sleep(time);
	return time;
}

int threadWaitFuture(std::future<int>& fut)
{
	const int time = fut.get();
	return threadWait(time);
}

void futureTest()
{
	C_FLAG("future test");
	{
		std::future<int> fut = std::async(threadWait, 1);
		LOG("thread end: " << fut.get());
	}
	
	{
		std::packaged_task<int(int)> tsk(threadWait);
		std::future<int> fut = tsk.get_future();
		std::thread thread(std::move(tsk), 1);
		LOG("thread end: " << fut.get());
		thread.join();
	}

	{
		const int time = 2;
		std::promise<int> prom;
		std::future<int> fut = prom.get_future();
		std::thread thread(threadWaitFuture, std::ref(fut));
		prom.set_value(time);
		thread.join();
		LOG("thread end: " << time);
	}

	{
		std::promise<int> prom;
		std::future<int> futInput = prom.get_future();

		std::packaged_task<int(std::future<int>&)> tsk(threadWaitFuture);
		std::future<int> futResult = tsk.get_future();
		std::thread thread(std::move(tsk), std::ref(futInput));

		prom.set_value(3);
		LOG("thread end: " << futResult.get());
		thread.join();
	}
}

/****************************************************/
/*                thread dependencies               */
/****************************************************/

class ThreadTask
{
public:
	virtual ~ThreadTask() {}
	virtual void run() = 0;
};

class Thread
{
public:
	Thread(ThreadTask* t) : m_finished(false), m_task(t) {}
	virtual ~Thread() {}

	void wait()
	{
		std::unique_lock<std::mutex> ulock(m_mutex);
		//m_condThisJobFinished.wait(ulock, [this] { return this->m_finished; });
		while (!m_finished)
			m_cv.wait(ulock);
	}

	void start()
	{
		std::thread thread(&Thread::runTask, this);
		thread.detach();
	}

	bool isFinished() const { return m_finished; }

private:
	void runTask()
	{
		waitDependence();
		if (m_task)
			m_task->run();
		std::unique_lock<std::mutex> ulock(m_mutex);
		m_finished = true;
		m_cv.notify_all();
	}

	virtual void waitDependence() {}

private:
	std::mutex m_mutex;
	std::condition_variable m_cv;
	bool m_finished;
	std::shared_ptr<ThreadTask> m_task;
};

class ThreadDependence : public Thread
{
public:
	ThreadDependence(ThreadTask* t) : Thread(t) {}
	void addDependence(const std::shared_ptr<Thread>& thread) { m_dependencies.push_back(thread); }

private:
	virtual void waitDependence() 
	{
		for (const auto& weakPtrThread : m_dependencies)
		{
			if (std::shared_ptr<Thread> ptrThread = weakPtrThread.lock())
				ptrThread->wait();
		}
		m_dependencies.clear();
	}

private:
	std::vector<std::weak_ptr<Thread>> m_dependencies;
};

class TaskTest: public ThreadTask
{
public:
	TaskTest(const int step) : m_stepCount(step) {}
	virtual void run()
	{
		for (int i = 0; i < m_stepCount; i++)
		{
			LOG("THREAD: " << std::this_thread::get_id() << " WAIT: " << i+1 << "/" << m_stepCount);
			Sleep(1000);
		}
	}

private:
	const int m_stepCount;
};

template<typename T>
std::shared_ptr<T> createThread(ThreadTask* task)
{
	return std::shared_ptr<T>(new T(task));
}

void threadDependenciesTest()
{
	std::shared_ptr<Thread> threadA = createThread<Thread>(new TaskTest(3));
	std::shared_ptr<Thread> threadB = createThread<Thread>(new TaskTest(2));

	std::shared_ptr<ThreadDependence> thread— = createThread<ThreadDependence>(new TaskTest(1));
	thread—->addDependence(threadA);
	thread—->addDependence(threadB);

	thread—->start();
	threadB->start();
	threadA->start();

	threadA->wait();
	threadB->wait();
	thread—->wait();
}

void Lesson_multithreading::run()
{
	LOG("Hardware concurrency: " << std::thread::hardware_concurrency());
	LOG("Main thread id: " << std::this_thread::get_id());

	mutexTest();
	threadDependenciesTest();
	conditionVaribaleTest();
	futureTest();

	//t3.detach();
}