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
	for (auto& data : m_vec) // [range-based for loop]
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
	for (auto it = vecInts.cbegin(); it != vecInts.cend(); ++it) // std::vector<int>::const_iterator it
	{
		summInts += *it;
	}
	LOG_TEST("type inference", summInts);
}

/****************************************************/
/*                range-based for loop              */
/****************************************************/
void rangeBasedLoopTest()
{
	auto summFloats = 0.0f; // [type inference]
	std::vector<float> vecFloats = { 0.1f, 0.2f, 0.3f }; // [initializer list]
	for (auto data : vecFloats) // [type inference]
	{
		summFloats += data;
	}
	LOG_TEST("range-based for loop", summFloats);
}

/****************************************************/
/*        generalized constant expressions          */
/****************************************************/
constexpr int getConstValue() { return 2; }

void generalizedConstantExpressionsTest()
{
	int some_value[getConstValue() + 2] = { 1, 2, 3, 4 }; // [initializer list]
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
/*         object construction improvement          */
/****************************************************/
class ImproveConstructionClass
{
public:
	ImproveConstructionClass() : ImproveConstructionClass(42) {}

private:
	ImproveConstructionClass(int _intValue) : intValue(_intValue) { print(); }
	void print() const { LOG_TEST("object construction improvement", intValue << " " << floatValue); }

private:
	int intValue;
	float floatValue = 10.5f;
};

void objectConstructionImprovementTest()
{
	ImproveConstructionClass improveConstructionClass;
}

/****************************************************/
/*           lambda functions and expressions       */
/****************************************************/
//#define USE_PREDICATE 1

#ifdef USE_PREDICATE
struct IntComparer
{
	bool operator()(const int x, const int y) const
	{
		return x < y;
	};
};
#endif

class SortedIntVector
{
public:
	SortedIntVector& insert(int number);
	void print() const;

private:
	std::vector<int> m_vec;
	int m_valueMax = 0; // [object construction improvement]
};

SortedIntVector& SortedIntVector::insert(int number)
{
#ifdef USE_PREDICATE
	auto it = std::lower_bound(m_vec.begin(), m_vec.end(), number, IntComparer());
	// TODO FIND MAX VALUE
#else
	// auto it = std::lower_bound(m_vec.begin(), m_vec.end(), number, [&](const int x, const int y) { m_valueMax = std::max(x,y); return x < y; });

	// int valueMax = 0;
	// auto it = std::lower_bound(m_vec.begin(), m_vec.end(), number, [&valueMax](const int x, const int y) { valueMax = std::max(x,y); return x < y; });
	// m_valueMax = valueMax;

	auto it = std::lower_bound(m_vec.begin(), m_vec.end(), number, [this](const int x, const int y) { this->m_valueMax = std::max(x, y); return x < y; });
#endif

	m_vec.insert(it, number);
	return *this;
}

void SortedIntVector::print() const
{
	std::cout << "Test \"lambda functions and expression\": ";
	for (auto& data : m_vec) // [range-based for loop][type inference]
	{
		std::cout << data << ", ";
	}
	std::cout << "max value: " << m_valueMax << "\n";
}

void lambdaFunctionsAndExpressionsTest()
{
	// [captures](arg1, arg2) -> result_type { /* code */ }
	// [](int x, int y) { return x + y; }
	// [this]() { this->foo(); }
	// [](int x, int y) -> int { int z = x + y; return z; }

	SortedIntVector sortedVec;
	sortedVec.insert(1).insert(0).insert(100).insert(99);
	sortedVec.print();

	int total = 0;
	int value = 5;
	[&, value](int x) { total += (x * value); } (1); 
	LOG_TEST("lambda functions and expression", total);

	auto myLambdaFunc = [] { LOG("lambda functions and expression"); }; // [type inference]
	myLambdaFunc();
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
	void print() const { LOG_TEST("defaulted and deleted special member functions", m_value); }

private:
	int m_value = 5; // [object construction improvement]
};

void defaultedAndDeletedTest()
{
	// SpecifierTestClass specifierTestClass(10.5f); // error
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
	//virtual void insort(int number) override {} // error: name insort
	virtual void print() const final {}
};

struct InheritanceC final : InheritanceB
{
	//virtual void print() const final {}; // error: final in base class
};

/* 
struct InheritanceD : public InheritanceC // error: C is final class
{};
*/

void overridesAndFinalTest()
{
	InheritanceC inheritanceTest;
}

/****************************************************/
/*              null pointer constant               */
/****************************************************/
void foo(char*) { LOG_TEST("null pointer constant", "foo(char*)"); }
void foo(int) { LOG_TEST("null pointer constant", "foo(int)"); }

void nullPointerConstantTest()
{
	foo(NULL); // call foo(int);
	foo(nullptr); // call foo(char*)
}

/****************************************************/
/*             strongly typed enumerations          */
/****************************************************/
enum class UintEnum : unsigned int
{
	ONE = 2,
	TWO
};

void stronglyTypedEnumerationsTest()
{
	LOG_TEST("strongly typed enumerations", static_cast<unsigned int>(UintEnum::ONE) << " " << static_cast<unsigned int>(UintEnum::TWO));
}

/****************************************************/
/*                  rvalue reference                */
/****************************************************/
class RvalueReferenceClass
{
public:
	RvalueReferenceClass(int* pValue)
	{ 
		m_pValue = pValue;
		LOG("RvalueReferenceClass call constructor");
	};
	~RvalueReferenceClass()
	{
		if (m_pValue)
		{
			LOG("RvalueReferenceClass delete data");
			delete m_pValue;
			m_pValue = nullptr;
		}
	};
	RvalueReferenceClass(RvalueReferenceClass& obj)
	{
		m_pValue = obj.getPtr();
		LOG("RvalueReferenceClass call copy constructor");
	};
	RvalueReferenceClass(RvalueReferenceClass&& obj): m_pValue(obj.getPtr())
	{
		obj.m_pValue = 0;
		LOG("RvalueReferenceClass call move constructor");
	}
	RvalueReferenceClass& operator=(RvalueReferenceClass&& obj)
	{
		std::swap(m_pValue, obj.m_pValue);
		LOG("RvalueReferenceClass swap");
		return *this;
	}
	int getValue() const { return *m_pValue; }
	int* getPtr() const { return m_pValue; }

private:
	int* m_pValue = NULL;
};

template <typename T>
void print(T&& x)
{
	LOG_TEST("rvalue reference", ++x);
}

void rvalueReferenceTest()
{
	RvalueReferenceClass a(new int(10));
	RvalueReferenceClass b(new int(100));

	print(a.getValue());
	print(2);

	auto tmp = std::move(a);
	a = std::move(b);
	b = std::move(tmp);

	int tet = 5;
}


/****************************************************/
/*           Alternative function syntax            */
/****************************************************/

template <typename T, typename E>
auto addition(T a, E b) -> decltype(a + b) 
{
	return a + b;
}

void alternativeFunctionSyntaxTest()
{
	const auto data = addition(2, 3.14f); // c - float
	LOG_TEST("alternative function syntax", typeid(data).name());
}

/****************************************************/
/*                  Regular expressions             */
/****************************************************/
void regularExpressionsTest()
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
	objectConstructionImprovementTest();
	lambdaFunctionsAndExpressionsTest();
	defaultedAndDeletedTest();
	overridesAndFinalTest();
	nullPointerConstantTest();
	stronglyTypedEnumerationsTest();
	rvalueReferenceTest();
	alternativeFunctionSyntaxTest();
	regularExpressionsTest();
}