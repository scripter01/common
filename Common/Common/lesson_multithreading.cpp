#include "stdafx.h"
#include "lesson_multithreading.h"

#include "cvmarkersobj.h"
Concurrency::diagnostic::marker_series g_series;

#define C_SPAN(name) Concurrency::diagnostic::span c_span(g_series, _T(name));
#define C_FLAG(name) g_series.write_flag(_T(name));
#define C_MSG(name) g_series.write_message(_T(name));

void threadFoo(int& num, std::mutex* mtx)
{
	C_SPAN("threadFoo");
	for (int i = 0; i < 10; i++)
	{
		if (mtx)
			mtx->lock();
		std::cout << num << " ";
		num++;
		if (mtx)
			mtx->unlock();
	}
}

void Lesson_multithreading::run()
{
	LOG("Hardware concurrency: " << std::thread::hardware_concurrency());
	LOG("Main thread id: " << std::this_thread::get_id());

	C_FLAG("start threading");

	std::mutex mtx;
	static int num = 0;

	C_MSG("t1 and t2");
	std::thread t1(threadFoo, std::ref(num), &mtx);
	std::thread t2(threadFoo, std::ref(num), &mtx);
	if (t1.joinable())
		t1.join();
	if (t2.joinable())
		t2.join();

	C_MSG("t3");
	std::thread t3(threadFoo, std::ref(num), nullptr);
	t3.detach();
}