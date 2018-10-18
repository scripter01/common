#include "stdafx.h"
#include "lesson_c11.h"
#include "lesson_c11_a.h"

extern template ExternTemplatesTest<int>;
constexpr int getConstValue() { return 5; }

Lesson_c11::Lesson_c11():
	LessonBase("C++11")
{

}

void Lesson_c11::run()
{
	/****************************************************/
	/*      ���������� ����������� ���������            */
	/****************************************************/

	//constexpr 
	int some_value[getConstValue() + 7];
	constexpr double acceleration = 9.8;

	/****************************************************/
	/*                   ������� �������                */
	/****************************************************/
	externTemplatesTestInt(1);
	ExternTemplatesTest<int> externTemplatesTest(2);

	/****************************************************/
	/*                  Rvalue Reference                */
	/****************************************************/
	// TODO
}