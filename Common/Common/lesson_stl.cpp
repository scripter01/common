#include "stdafx.h"
#include "lesson_stl.h"

/****************************************************/
/*                       sort                       */
/****************************************************/
void sortTest()
{
	struct Data
	{
		std::string name;
		int num;
	};

	struct WorkerSorter
	{
		bool operator()(const Data& a, const Data& b) const { return a.num < b.num; }
	};

	std::vector<Data> vec = { { "d", 4 }, { "c", 3 }, {"a", 1}, { "b", 2 }, };
	std::sort(vec.begin(), vec.end(), WorkerSorter());

	std::cout << "Test \"sort\": ";
	for (auto& data : vec) // [range-based for loop]
	{
		std::cout << data.num << ", " << data.name << "; ";
	}
	std::cout << "\n";
}

void Lesson_stl::run()
{
	sortTest();
}