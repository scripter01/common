// observer.cpp

/*
����������� (observer, ��������-���������, ���������) - ������������� ��� ��������
����������� - ��� ������������� ������ ��������������, ������� ������ �������� ��������, ����������
����� �������� ������� � ����������� �� �������, ������������ � ������ ��������

! ���������� ����������� � ��������� �������
*/

class Observer
{
public:
	virtual ~Observer() = default;
	virtual void onNotify(const Event event) = 0;
};

class Achievements : public Observer
{
public:
	virtual void onNotify(const Event event)
	{
		switch (event)
		{
			// ...
		default:
			break;
		}
	}
};

class Subject
{
public:
	virtual ~Subject() = default;
	void addObserver(Observer* observer)
	{
		mObservers.insert(observer);
	}

	void removeObserver(Observer* observer)
	{
		mObservers.erase(observer);
	}

protected:
	void notify(const Event event)
	{
		for (auto observer : mObservers)
			observer->onNotify(event);
	}

private:
	std::set<Observer*> mObservers;
};

/*
�������� ����������� �� Sunject � �������� notify(), � ��� ���������� ���������
*/