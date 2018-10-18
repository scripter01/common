#include "stdafx.h"
#include "lesson_c11.h"
#include "lesson_c11_a.h"

// ������� �������
extern template ExternTemplatesTest<int>;

// ���������� ����������� ��������� 
constexpr int getConstValue() { return 5; }

// ������ �������������
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
	/*      ���������� ����������� ���������            */
	/****************************************************/

	int some_value[getConstValue() + 7];
	constexpr double acceleration = 9.8;

	/****************************************************/
	/*                   ������� �������                */
	/****************************************************/
	externTemplatesTestInt(1);
	ExternTemplatesTest<int> externTemplatesTest(2);

	/****************************************************/
	/*                ������ �������������              */
	/****************************************************/
	SimpleStruct simpleStruct = { 1, 1.2f};
	SequenceClass sequenceClass = { simpleStruct, {2, 2.4f} };

	/****************************************************/
	/*            ������������� �������������           */
	/****************************************************/

	/****************************************************/
	/*                  Rvalue Reference                */
	/****************************************************/
	// TODO
}