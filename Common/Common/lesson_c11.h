#ifndef LESSON_C11_H
#define LESSON_C11_H

#include "lessonBase.h"

// ������ �������������
struct SimpleStruct
{
	int i;
	float f;
};

class SequenceClass
{
public:
	SequenceClass(std::initializer_list<SimpleStruct> list);
	
private:
	void print();

private:
	std::vector<SimpleStruct> m_vec;
};

// ������ - ������� � ���������
class SortedIntVector
{
public:
	SortedIntVector();
	SortedIntVector& insert(int number);
	void print() const;

private:
	std::vector<int> m_vec;
	int m_valueMax;
};

// ��������� ������������� ��������
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

// ������������� default � delete
class SpecifierTestClass
{
public:
	SpecifierTestClass() = default;
	SpecifierTestClass(int x) { m_value = x; }
	SpecifierTestClass(float x) = delete;
	void print() const { std::cout << "Test \"specifiers\": " << m_value << "\n"; }

private:
	int m_value = 5; // + ��������� ������������� ��������
};

class Lesson_c11: public LessonBase
{
public:
	Lesson_c11();

	void run();
};

#endif //LESSON_C11