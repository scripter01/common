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
std::atomic<bool> flag = false;

#define THREAD_MAX_VALUE 999999

void threadInc(std::atomic<int>& num)
{
	C_SPAN("threadLog");
	while (true)
	{
		std::unique_lock<std::mutex> ulock(g_mtx);

		//g_cv.wait(ulock, []() {return flag == true; });
		while (g_cv.wait_for(ulock, std::chrono::milliseconds(300), []() {return flag == true;} ) == false)
			std::cout << "thread " << std::this_thread::get_id() << " wait" << std::endl;

		num++;
		if (num >= THREAD_MAX_VALUE)
			break;
	}
}

void threadSignal()
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
	std::atomic<int> a = 0;
	std::atomic<int> b = 0;
	std::thread t1(threadInc, std::ref(a));
	std::thread t2(threadInc, std::ref(b));
	std::thread tStatus(threadStatus, std::ref(a), std::ref(b));
	std::thread tSignal(threadSignal);

	t1.join();
	t2.join();
	tStatus.join();
	tSignal.join();
}

void Lesson_multithreading::run()
{
	LOG("Hardware concurrency: " << std::thread::hardware_concurrency());
	LOG("Main thread id: " << std::this_thread::get_id());

	mutexTest();
	conditionVaribaleTest();

	//t3.detach();
}