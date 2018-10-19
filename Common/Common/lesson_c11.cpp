#include "stdafx.h"
#include "lesson_c11.h"
#include "lesson_c11_a.h"

/****************************************************/
/*                initializer list                  */
/****************************************************/
struct SimpleStruct
{
	int i;
	float f;
};

SimpleStruct getSimpleStructDefault() { return{ 1, 1.2f }; }

class SequenceClass
{
public:
	SequenceClass(std::initializer_list<SimpleStruct> list);

private:
	void print();

private:
	std::vector<SimpleStruct> m_vec;
};

SequenceClass::SequenceClass(std::initializer_list<SimpleStruct> list)
{
	m_vec = list;
	print();
}

void SequenceClass::print()
{
	std::cout << "Test \"initializer list\": ";
	for (auto& data : m_vec) //  + for-цикл по коллекции  + вывод типов
	{
		std::cout << data.i << ", " << data.f << "; ";
	}
	std::cout << "\n";
}

void initializerListTest()
{
	SimpleStruct simpleStruct{ 1, 1.2f };
	simpleStruct = { 2, 2.4f };
	SequenceClass sequenceClass = { getSimpleStructDefault(), simpleStruct,{ 4, 4.8f } };
}

/****************************************************/
/*                  type inference                  */
/****************************************************/
void typeInferenceTest()
{
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
}

/****************************************************/
/*                range-based for loop              */
/****************************************************/
void rangeBasedLoopTest()
{
	auto summFloats = 0.0f;
	std::vector<float> vecFloats = { 0.1f, 0.2f, 0.3f };
	for (auto data : vecFloats)
	{
		summFloats += data;
	}
	std::cout << "Test \"foreach instruction\": " << summFloats << "\n";
}

/****************************************************/
/*        generalized constant expressions          */
/****************************************************/
constexpr int getConstValue() { return 2; }

void generalizedConstantExpressionsTest()
{
	int some_value[getConstValue() + 2] = { 1, 2, 3, 4 }; // + спискок инициализации
	constexpr double acceleration = 9.8;
}

/****************************************************/
/*                   extern template                */
/****************************************************/
extern template ExternTemplatesTest<int>;

void externTemplateTest()
{
	externTemplatesTestInt(1);
	ExternTemplatesTest<int> externTemplatesTest(2);
}

/****************************************************/
/*           lambda functions and expressions       */
/****************************************************/
struct IntComparer
{
	bool operator()(const int x, const int y) const
	{
		return x < y;
	};
};

class SortedIntVector
{
public:
	SortedIntVector() : m_valueMax(0) {}
	SortedIntVector& insert(int number);
	void print() const;

private:
	std::vector<int> m_vec;
	int m_valueMax;
};

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

void lambdaFunctionsAndExpressionsTest()
{
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
}

/****************************************************/
/*         object construction improvement          */
/****************************************************/
// Улучшение конструкторов объектов
class ImproveConstructionClass
{
public:
	ImproveConstructionClass(int _intValue) : intValue(_intValue) {}
	ImproveConstructionClass() : ImproveConstructionClass(42) {}
	void print() const { std::cout << "Test \"improve construction class\": " << intValue << " " << floatValue << "\n"; }

private:
	int intValue;
	float floatValue = 10.5f;
};

void objectConstructionImprovementTest()
{
	ImproveConstructionClass improveConstructionClass;
	improveConstructionClass.print();
}

/****************************************************/
/*  defaulted and deleted special member functions  */
/****************************************************/
class SpecifierTestClass
{
public:
	SpecifierTestClass() = default;
	SpecifierTestClass(int x) { m_value = x; }
	SpecifierTestClass(float x) = delete;
	void print() const { std::cout << "Test \"specifiers\": " << m_value << "\n"; }

private:
	int m_value = 5; // + улучшение конструкторов объектов
};

void defaultedAndDeletedTest()
{
	//SpecifierTestClass specifierTestClass(10.5f); //error
	SpecifierTestClass specifierTestClass;
	specifierTestClass.print();
}

/****************************************************/
/*           explicit overrides and final           */
/****************************************************/
struct InheritanceA
{
	virtual void insert(int number) {}
	virtual void print() const {}
};

struct InheritanceB : public InheritanceA
{
	//virtual void insort(int number) override {} // error
	virtual void print() const final {}
};

struct InheritanceC final : InheritanceB
{
	//virtual void print() const final {}; // error: final in base class
};

/* error: C is final class
struct InheritanceD : public InheritanceC
{};
*/

void overridesAndFinalTest()
{
	InheritanceC inheritanceTest;
}

/****************************************************/
/*              null pointer constant               */
/****************************************************/
void foo(char*) { std::cout << "Test \"nullptr\": " << 1 << "\n"; }
void foo(int) { std::cout << "Test \"nullptr\": " << 2 << "\n"; }

void nullPointerConstantTest()
{
	foo(NULL); // call foo(int);
	foo(nullptr); // call foo(char *)
}

/****************************************************/
/*             strongly typed enumerations          */
/****************************************************/
enum class UintEnum : unsigned int
{
	ONE,
	TWO
};

void stronglyTypedEnumerationsTest()
{
	std::cout << "Test \"enum\": " << static_cast<unsigned int>(UintEnum::ONE) << " " << static_cast<unsigned int>(UintEnum::TWO) << "\n";
}

/****************************************************/
/*                  rvalue Reference                */
/****************************************************/
void rValueReferenceTest()
{
	// TODO
}

void Lesson_c11::run()
{
	initializerListTest();
	typeInferenceTest();
	rangeBasedLoopTest();
	generalizedConstantExpressionsTest();
	externTemplateTest();
	lambdaFunctionsAndExpressionsTest();
	objectConstructionImprovementTest();
	defaultedAndDeletedTest();
	overridesAndFinalTest();
	nullPointerConstantTest();
	stronglyTypedEnumerationsTest();
	rValueReferenceTest();
}