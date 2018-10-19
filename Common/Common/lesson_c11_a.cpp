#include "stdafx.h"
#include "lesson_c11_a.h"

/****************************************************/
/*                   extern template                */
/****************************************************/

template<typename T>
ExternTemplatesTest<T>::ExternTemplatesTest(T data)
{
	std::cout << "Test \"extern template\": " << data << "\n";
}

void externTemplatesTestInt(int number)
{
	ExternTemplatesTest<int> externTemplatesTest(number);
}