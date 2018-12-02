#ifndef ABSTRACT_FACTORY_H
#define ABSTRACT_FACTORY_H

class SoldierAnt
{
public:
	virtual void info() = 0;
	virtual ~SoldierAnt() {}
};

class WorkerAnt
{
public:
	virtual void info() = 0;
	virtual ~WorkerAnt() {}
};

class AntsFactory
{
public:
	virtual SoldierAnt* createSoldierAnt() = 0;
	virtual WorkerAnt* createWorkerAnt() = 0;
	virtual ~AntsFactory() {}
};

class RedSoldierAnt: public SoldierAnt
{
public:
	void info() { printf("Red Soldier Ant"); }
};

class RedWorkerAnt: public WorkerAnt
{
public:
	void info() { printf("Red Worker Ant"); }
};

class RedAntsFactory : public AntsFactory
{
public:
	SoldierAnt* createSoldierAnt() { return new RedSoldierAnt; }
	WorkerAnt* createWorkerAnt() { return new RedWorkerAnt; }
};

class AbstractFactoryTest
{
public:
	void createAnts(AntsFactory& factory) 
	{
		// use factory
	}
};


#endif //ABSTRACT_FACTORY_H