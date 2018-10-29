#include "stdafx.h"
#include "Lesson_smartPointers.h"

class ptrTestClass
{
public:
	ptrTestClass(const std::string& str): m_value(str){ std::cout << "create ptrTestClass: "<< m_value <<"\n"; }
	~ptrTestClass() { std::cout << "delete ptrTestClass: " << m_value << "\n"; }

	void doSomething() {}
	std::shared_ptr<ptrTestClass> m_otherPtr; //std::weak_ptr<ptrTestClass> m_otherPtr;

private:
	const std::string m_value;
};

/****************************************************/
/*                       auto_ptr                   */
/****************************************************/
void autoPtrTest()
{
	std::auto_ptr<ptrTestClass> ptrX(new ptrTestClass("auto1"));
	std::auto_ptr<ptrTestClass> ptrY;

	ptrY = ptrX;
	std::cout << "Test \"auto_ptr\": " << ptrX.get() << " " << ptrY.get() << "\n";
}

/****************************************************/
/*                     unique_ptr                   */
/****************************************************/
void uniquePtrTest()
{
	std::unique_ptr<ptrTestClass> ptrX(new ptrTestClass("unique1"));
	std::unique_ptr<ptrTestClass> ptrY;

	//ptrY = ptrX; // error, can't copy
	ptrY = std::move(ptrX);
	std::cout << "Test \"unique_ptr\": " << ptrX.get() << " " << ptrY.get() << "\n";
}

/****************************************************/
/*                     shared_ptr                   */
/****************************************************/
void sharedPtrTest()
{
	std::shared_ptr<ptrTestClass> ptrX(new ptrTestClass("shared1"));
	std::shared_ptr<ptrTestClass> ptrY(new ptrTestClass("shared2"));
	ptrY = ptrX;

	auto ptrZ = std::make_shared<ptrTestClass>("shared3");
	ptrTestClass* ptr = ptrZ.get();
	ptrZ.reset();

	std::cout << "Test \"unique_ptr\": " << ptrX.get() << " " << ptrY.get() << " " << ptrZ.get() << "\n";
}

/****************************************************/
/*                     weak_ptr                     */
/****************************************************/
void weakPtrTest()
{
	std::shared_ptr<ptrTestClass> ptrX(new ptrTestClass("test1"));
	std::shared_ptr<ptrTestClass> ptrY(new ptrTestClass("test2"));
	//bad: retain cycle
	ptrX->m_otherPtr = ptrY;
	ptrY->m_otherPtr = ptrX;

	std::shared_ptr<ptrTestClass> sharedPtr = std::make_shared<ptrTestClass>("shared4");
	std::weak_ptr<ptrTestClass> weakPtr(sharedPtr);
	if (std::shared_ptr<ptrTestClass> foo = weakPtr.lock())
		foo->doSomething();
}

void Lesson_smartPointers::run()
{
	autoPtrTest();
	uniquePtrTest();
	sharedPtrTest();
	weakPtrTest();
}