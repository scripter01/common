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

class ThreadsController
{
public:
	ThreadsController() : m_working(false) {}
	bool canWorking() { return m_working; }
	void setWorkState(bool state)
	{
		std::unique_lock<std::mutex> lck(m_mtx);
		std::cout << "state " << state << std::endl;
		m_working = state; 
		if (m_working)
			m_cv.notify_all();
	}
	void threadWait(std::unique_lock<std::mutex>& ulock) 
	{ 
		m_cv.wait(ulock, std::bind(&ThreadsController::canWorking, this));
	}
	std::mutex& getMutex() { return m_mtx; }
private:
	bool m_working;
	std::condition_variable m_cv;
	std::mutex m_mtx;
};

ThreadsController g_threadsController;

void threadLog()
{
	C_SPAN("threadLog");
	while (true)
	{
		std::unique_lock<std::mutex> ulock(g_threadsController.getMutex());
		g_threadsController.threadWait(ulock);
		std::cout << "thread " << std::this_thread::get_id() <<" is working" << std::endl;
		Sleep(2000);
	}
}

void threadInput()
{
	C_SPAN("threadInput");
	while (true)
	{
		char inputData;
		std::cin >> inputData;
		std::cout << "\n";
		switch (inputData)
		{
		case 'y':
			g_threadsController.setWorkState(true);
			break;
		case 'n':
			g_threadsController.setWorkState(false);
			break;
		default:
			return;
			break;
		}
	}
}

void conditionVaribaleTest()
{
	C_FLAG("condition variable test");

	C_MSG("t1 and t2");
	std::thread t1(threadLog);
	std::thread t2(threadLog);
	std::thread t3(threadInput);

	std::cout << "thread " << t1.get_id() << " is ready" << std::endl;
	std::cout << "thread " << t2.get_id() << " is ready" << std::endl;
	std::cout << "Input (y/n/...):" << std::endl;

	if (t1.joinable())
		t1.join();
	if (t2.joinable())
		t2.join();
	if (t3.joinable())
		t3.join();
}

void Lesson_multithreading::run()
{
	LOG("Hardware concurrency: " << std::thread::hardware_concurrency());
	LOG("Main thread id: " << std::this_thread::get_id());

	mutexTest();
	conditionVaribaleTest();

	//t3.detach();
}