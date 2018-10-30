#include "stdafx.h"
#include "Lesson_smartPointers.h"

class ptrTestClass
{
public:
	ptrTestClass(const std::string& str): m_value(str){ std::cout << "create ptrTestClass: "<< m_value <<"\n"; }
	~ptrTestClass() { std::cout << "delete ptrTestClass: " << m_value << "\n"; }

	void doSomething() {}
	const std::string& getValue() const { return m_value; }
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

/****************************************************/
/*                     deleter ptr                  */
/****************************************************/
struct deleterPtr
{
	void operator()(ptrTestClass* ptr) const
	{
		std::cout << "special delete ptrTestClass: " << ptr->getValue() << "\n";
		if (ptr->m_otherPtr)
			ptr->m_otherPtr.reset();
	}
};

void deleterPtrTest()
{
	std::shared_ptr<ptrTestClass> ptrX(new ptrTestClass("test3"), deleterPtr());
}

/****************************************************/
/*                  enable from this                */
/****************************************************/
struct sharedFromThisClassTest: public ptrTestClass, public std::enable_shared_from_this<sharedFromThisClassTest>
{
	sharedFromThisClassTest(const std::string& str) : ptrTestClass(str) {}
	std::shared_ptr<sharedFromThisClassTest> getptr() { return shared_from_this(); }
};

void sharedFromThisTest()
{
	std::shared_ptr<sharedFromThisClassTest> ptrX(new sharedFromThisClassTest("sharedfromthis"));
	std::shared_ptr<sharedFromThisClassTest> ptrY = ptrX->getptr();
	std::shared_ptr<sharedFromThisClassTest> ptrZ = ptrX->shared_from_this();
}

void Lesson_smartPointers::run()
{
	autoPtrTest();
	uniquePtrTest();
	sharedPtrTest();
	weakPtrTest();
	deleterPtrTest();
	sharedFromThisTest();
}