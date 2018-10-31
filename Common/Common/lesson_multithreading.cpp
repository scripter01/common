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

void Lesson_multithreading::run()
{
	LOG("Hardware concurrency: " << std::thread::hardware_concurrency());
	LOG("Main thread id: " << std::this_thread::get_id());

	C_FLAG("start threading");

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

	//t3.detach();
}