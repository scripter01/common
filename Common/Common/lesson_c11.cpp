#include "stdafx.h"
#include "lesson_c11.h"
#include "lesson_c11_a.h"

// Внешние шаблоны
extern template ExternTemplatesTest<int>;

// Обобщённые константные выражения 
constexpr int getConstValue() { return 2; }

// Списки инициализации
SimpleStruct getSimpleStructDefault() { return{ 1, 1.2f }; }

SequenceClass::SequenceClass(std::initializer_list<SimpleStruct> list)
{
	m_vec = list;
	print();
}

void SequenceClass::print()
{
	std::cout << "Test \"initializer list\": ";
	for (auto& data: m_vec) //  + for-цикл по коллекции  + вывод типов
	{
		std::cout << data.i << ", " << data.f << "; ";
	}
	std::cout << "\n";
}

// Лямбда - функции и выражения
struct IntComparer
{
	bool operator()(const int x, const int y) const
	{
		return x < y;
	};
};

SortedIntVector::SortedIntVector():
	m_valueMax(0)
{

}

SortedIntVector& SortedIntVector::insert(int number)
{
	//auto it = std::lower_bound(m_vec.begin(), m_vec.end(), number, IntComparer());
	//auto it = std::lower_bound(m_vec.begin(), m_vec.end(), number, [&](const int x, const int y) { m_valueMax = std::max(x,y); return x < y; });
	//int valueMax = 0;
	//auto it = std::lower_bound(m_vec.begin(), m_vec.end(), number, [&valueMax](const int x, const int y) { valueMax = std::max(x,y); return x < y; });
	auto it = std::lower_bound(m_vec.begin(), m_vec.end(), number, [this](const int x, const int y) { this->m_valueMax = std::max(x, y); return x < y; });
	m_vec.insert(it, number);
	return *this;
}

void SortedIntVector::print() const
{
	std::cout << "Test \"lambda function\": ";
	for (auto& data : m_vec) //  + for-цикл по коллекции  + вывод типов
	{
		std::cout << data << ", ";
	}
	std::cout << "max value: " << m_valueMax << "\n";
}

// Константа нулевого указателя
void foo(char*) { std::cout << "Test \"nullptr\": " << 1 << "\n"; }
void foo(int) { std::cout << "Test \"nullptr\": " <<  2 << "\n"; }

Lesson_c11::Lesson_c11():
	LessonBase("C++11")
{
}

void Lesson_c11::run()
{
	/****************************************************/
	/*                initializer list                  */
	/****************************************************/
	SimpleStruct simpleStruct{ 1, 1.2f };
	simpleStruct = { 2, 2.4f };
	SequenceClass sequenceClass = { getSimpleStructDefault(), simpleStruct,{ 4, 4.8f } };

	/****************************************************/
	/*                  type inference                  */
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
	/*                range-based for loop              */
	/****************************************************/
	auto summFloats = 0.0f;
	std::vector<float> vecFloats = { 0.1f, 0.2f, 0.3f };
	for (auto data: vecFloats)
	{
		summFloats += data;
	}
	std::cout << "Test \"foreach instruction\": " << summFloats << "\n";

	/****************************************************/
	/*          geralized constant expressions          */
	/****************************************************/

	int some_value[getConstValue() + 2] = { 1, 2, 3, 4 }; // + спискок инициализации
	constexpr double acceleration = 9.8;

	/****************************************************/
	/*                   extern template                */
	/****************************************************/
	externTemplatesTestInt(1);
	ExternTemplatesTest<int> externTemplatesTest(2);

	/****************************************************/
	/*           lambda functions and expressions       */
	/****************************************************/
	// [](int x, int y) { return x + y; }
	// [this]() { this->foo(); }
	// [](int x, int y) -> int { int z = x + y; return z; }

	SortedIntVector sortedVec;
	sortedVec.insert(1).insert(0).insert(100).insert(99);
	sortedVec.print();

	int total = 0;
	int value = 5;
	[&, value](int x) { total += (x * value); } (1); //(1) вызов лямбда-функции с передачей значения 1
	std::cout << "Test \"lambda function\": " << total << "\n";
	auto myLambdaFunc = [] { std::cout << "Test \"lambda function\"\n"; };
	myLambdaFunc();

	/****************************************************/
	/*         object construction improvement          */
	/****************************************************/
	ImproveConstructionClass improveConstructionClass;
	improveConstructionClass.print();

	/****************************************************/
	/*  defaulted and deleted special member functions  */
	/****************************************************/
	//SpecifierTestClass specifierTestClass(10.5f); //error
	SpecifierTestClass specifierTestClass;
	specifierTestClass.print();

	/****************************************************/
	/*           explicit overrides and final           */
	/****************************************************/
	InheritanceC inheritanceTest;

	/****************************************************/
	/*              null pointer constant               */
	/****************************************************/
	foo(NULL); // call foo(int);
	foo(nullptr); // call foo(char *)

	/****************************************************/
	/*             strongly typed enumerations          */
	/****************************************************/
	std::cout << "Test \"enum\": " << static_cast<unsigned int>(UintEnum::ONE) << " " << static_cast<unsigned int>(UintEnum::TWO) << "\n";
	
	/****************************************************/
	/*                  Rvalue Reference                */
	/****************************************************/
	// TODO
}