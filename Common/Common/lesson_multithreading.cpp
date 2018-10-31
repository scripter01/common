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

std::mutex g_mtxFlag;
bool flag = false;

#define CYCLE_COUNT 50

void threadLog(int& num)
{
	C_SPAN("threadLog");
	std::unique_lock<std::mutex> ulock(g_mtx);
	g_cv.wait(ulock, [] {return flag == true; });
	for (int i = 0; i < CYCLE_COUNT; i++)
	{
		g_mtxFlag.lock();
		num++;
		g_mtxFlag.unlock();
		Sleep(100);
	}
}

void threadSignal()
{
	C_SPAN("threadSignal");
	Sleep(1000);
	g_mtxFlag.lock();
	flag = true;
	LOG("SIGNAL");
	g_mtxFlag.unlock();
	g_cv.notify_all();
}

void threadStatus(int& a, int& b)
{
	C_SPAN("threadStatus");
	while (true)
	{
		g_mtxFlag.lock();
		LOG("a: " << a << ", b: "<< b);
		if (a == CYCLE_COUNT && b == CYCLE_COUNT)
			break;
		g_mtxFlag.unlock();
		Sleep(300);
	}
}

void conditionVaribaleTest()
{
	C_FLAG("condition variable test");

	C_MSG("t1 and t2");
	int a = 0;
	std::thread t1(threadLog, std::ref(a));
	int b = 0;
	std::thread t2(threadLog, std::ref(b));
	std::thread tSignal(threadSignal);
	std::thread tStatus(threadStatus, std::ref(a), std::ref(b));

	t1.join();
	t2.join();
	tSignal.join();
	tStatus.join();
}

void Lesson_multithreading::run()
{
	LOG("Hardware concurrency: " << std::thread::hardware_concurrency());
	LOG("Main thread id: " << std::this_thread::get_id());

	mutexTest();
	conditionVaribaleTest();

	//t3.detach();
}