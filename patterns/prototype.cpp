// prototype.cpp

/*
прототип (prototype, клон) - порождающий тип паттерна
прототип - это порождающий паттер проектирования, который позволяет копировать объекты,
не вдаваясь в подробности их реализации. паттерн поручает создание копий самим копируемым объектам.
*/

class Monster
{
public:
	virtual ~Monster() = default;
	virtual Monster* clone() = 0;
};

class Ghost : public Monster
{
public:
	Ghost(int health, int speed):
		mHealth(health), mSpeed(speed)
	{}

	virtual Monster* clone() override
	{
		return new Ghost(mHealth, mSpeed);
	}

private:
	int mHealth = 0;
	int mSpeed = 0;
};

class Spawner
{
public:
	Spawner(Monster* prototype) :
		mPrototype(prototype)
	{}

	Monster* spawn()
	{
		return mPrototype? mPrototype->clone(): nullptr;
	}

private:
	Monster* mPrototype = nullptr;
};