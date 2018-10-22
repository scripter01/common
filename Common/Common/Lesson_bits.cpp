#include "stdafx.h"
#include "lesson_bits.h"

void bitFieldTest()
{
	struct bitField1
	{
		char a : 3;
		char b : 3;
		char c : 2;
	};
	std::cout << "Test \"bitField\": " << sizeof(bitField1) << "\n"; // 1 bite

	struct bitField2
	{
		char a : 3;
		char b : 3;
		char c : 3;
	};
	std::cout << "Test \"bitField\": " << sizeof(bitField2) << "\n"; // 2 bite

	struct bitField3
	{
		int a : 3;
		char b : 3;
		char c : 3;
	};
	std::cout << "Test \"bitField\": " << sizeof(bitField3) << "\n"; // 8 bite, multiple of max type size
}

void Lesson_bits::run()
{
	bitFieldTest();
}