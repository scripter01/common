#include "stdafx.h"
#include "lesson_c11.h"
#include "lesson_c11_a.h"

// Внешние шаблоны
extern template ExternTemplatesTest<int>;

// Обобщённые константные выражения 
constexpr int getConstValue() { return 5; }

// Списки инициализации
SequenceClass::SequenceClass(std::initializer_list<SimpleStruct> list)
{
	m_vec = list;
	print();
}

void SequenceClass::print()
{
	std::cout << "Test initializer list: ";
	for (auto& data: m_vec)
	{
		std::cout << data.i << ", " << data.f << "; ";
	}
	std::cout << "\n";
}

Lesson_c11::Lesson_c11():
	LessonBase("C++11")
{
}

void Lesson_c11::run()
{
	/****************************************************/
	/*      Обобщённые константные выражения            */
	/****************************************************/

	int some_value[getConstValue() + 7];
	constexpr double acceleration = 9.8;

	/****************************************************/
	/*                   Внешние шаблоны                */
	/****************************************************/
	externTemplatesTestInt(1);
	ExternTemplatesTest<int> externTemplatesTest(2);

	/****************************************************/
	/*                Списки инициализации              */
	/****************************************************/
	SimpleStruct simpleStruct = { 1, 1.2f};
	SequenceClass sequenceClass = { simpleStruct, {2, 2.4f} };

	/****************************************************/
	/*            Универсальная инициализация           */
	/****************************************************/

	/****************************************************/
	/*                  Rvalue Reference                */
	/****************************************************/
	// TODO
}