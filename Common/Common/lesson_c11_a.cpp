#include "stdafx.h"
#include "lesson_c11_a.h"

template<typename T>
ExternTemplatesTest<T>::ExternTemplatesTest(T data)
{
	std::cout << "Test extern templates " << data << "\n";
}

void externTemplatesTestInt(int number)
{
	ExternTemplatesTest<int> externTemplatesTest(number);
}