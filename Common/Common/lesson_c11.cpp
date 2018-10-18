#include "stdafx.h"
#include "lesson_c11.h"
#include "lesson_c11_a.h"

// ������� �������
extern template ExternTemplatesTest<int>;

// ���������� ����������� ��������� 
constexpr int getConstValue() { return 2; }

// ������ �������������
SimpleStruct getSimpleStructDefault() { return{ 1, 1.2f }; }

SequenceClass::SequenceClass(std::initializer_list<SimpleStruct> list)
{
	m_vec = list;
	print();
}

void SequenceClass::print()
{
	std::cout << "Test \"initializer list\": ";
	for (auto& data: m_vec) //  + for-���� �� ���������  + ����� �����
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
	/*                ������ �������������              */
	/****************************************************/
	SimpleStruct simpleStruct{ 1, 1.2f };
	simpleStruct = { 2, 2.4f };
	SequenceClass sequenceClass = { getSimpleStructDefault(), simpleStruct,{ 4, 4.8f } };

	/****************************************************/
	/*                   ����� �����                    */
	/****************************************************/
	auto testInt = 2;
	auto testFloat = 2.0f;
	decltype(testFloat) otherIntegerVariable = 5.0f;

	auto summInts = 0;
	std::vector<int> vecInts = { 1, 2, 3 };
	//for (std::vector<int>::const_iterator it = vecInts.cbegin(); it != vecInts.cend(); ++it)
	for (auto it = vecInts.cbegin(); it != vecInts.cend(); ++it)
	{
		summInts += *it;
	}
	std::cout << "Test \"auto in cycle\": " << summInts << "\n";

	/****************************************************/
	/*             For-���� �� ���������                */
	/****************************************************/
	auto summFloats = 0.0f;
	std::vector<float> vecFloats = { 0.1f, 0.2f, 0.3f };
	for (auto data: vecFloats)
	{
		summFloats += data;
	}
	std::cout << "Test \"foreach instruction\": " << summFloats << "\n";

	/****************************************************/
	/*      ���������� ����������� ���������            */
	/****************************************************/

	int some_value[getConstValue() + 2] = { 1, 2, 3, 4 }; // + ������� �������������
	constexpr double acceleration = 9.8;

	/****************************************************/
	/*                   ������� �������                */
	/****************************************************/
	externTemplatesTestInt(1);
	ExternTemplatesTest<int> externTemplatesTest(2);

	/****************************************************/
	/*              ������ - ������� � ������           */
	/****************************************************/
	// TODO

	/****************************************************/
	/*                  Rvalue Reference                */
	/****************************************************/
	// TODO
}