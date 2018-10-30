#include "stdafx.h"
#include "lesson_c11_a.h"

/****************************************************/
/*                   extern template                */
/****************************************************/

template<typename T>
ExternTemplatesTest<T>::ExternTemplatesTest(T data)
{
	LOG_TEST("extern template", data);
}

void externTemplatesTestInt(int number)
{
	ExternTemplatesTest<int> externTemplatesTest(number);
}