#include "stdafx.h"
#include "lesson_stl.h"

/****************************************************/
/*                      sort                        */
/****************************************************/
void sortTest()
{
	struct Data
	{
		std::string name;
		int num;
	};

	struct DataSorter
	{
		bool operator()(const Data& a, const Data& b) const { return a.num < b.num; }
	};

	std::vector<Data> vec = { { "d", 4 }, { "c", 3 }, {"a", 1}, { "b", 2 }, };
	std::sort(vec.begin(), vec.end(), DataSorter());

	std::cout << "Test \"sort\": ";
	for (auto& data : vec) // [range-based for loop]
	{
		std::cout << data.num << ", " << data.name << "; ";
	}
	std::cout << "\n";
}

/****************************************************/
/*                     insert                       */
/****************************************************/
struct IntSorter
{
	bool operator()(int a, int b) const { return a < b; }
};

void insertInt(std::vector<int>& vec, const int i)
{
	auto it = std::lower_bound(vec.begin(), vec.end(), i, IntSorter());
	vec.insert(it, i);
}

void insertTest()
{
	std::vector<int> vec;

	insertInt(vec, 4);
	insertInt(vec, 1);
	insertInt(vec, 2);
	insertInt(vec, 3);

	std::cout << "Test \"insert\": ";
	for (auto& data : vec) // [range-based for loop]
	{
		std::cout << data << ", ";
	}
	std::cout << "\n";
}

void Lesson_stl::run()
{
	sortTest();
	insertTest();
}