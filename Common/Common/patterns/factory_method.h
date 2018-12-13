#ifndef FACTORY_METHOD_H
#define FACTORY_METHOD_H

#include <iostream> 
#include <vector> 

enum ANT_TYPE { ANT_WORKER = 0, ANT_SOLDIER };

class Ant
{
public:
	virtual void info() = 0;
	virtual ~Ant() {}
	static Ant* createAnt(ANT_TYPE type);
};

class WorkerAnt : public Ant
{
public:
	void info() { std::cout << "Worker Ant" << "\n"; }
};

class SoldierAnt : public Ant
{
public:
	void info() { std::cout << "Soldier Ant" << "\n"; }
};

Ant* Ant::createAnt(ANT_TYPE type)
{
	Ant* ant = nullptr;
	switch (type)
	{
	case ANT_WORKER:
		ant = new WorkerAnt();
		break;
	case ANT_SOLDIER:
		ant = new SoldierAnt();
		break;
	}
	return ant;
};

int factoryMethodTest()
{
	std::vector<Ant*> ants;
	ants.push_back(Ant::createAnt(ANT_WORKER));
	ants.push_back(Ant::createAnt(ANT_SOLDIER));

	for (int i = 0; i<ants.size(); i++)
		ants[i]->info();

	// TODO delete
	return 0;
}


#endif //FACTORY_METHOD_H