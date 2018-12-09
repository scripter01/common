#ifndef BUILDER_H
#define BUILDER_H

#include <iostream> 
#include <vector>

class SoldierAnt
{
public:
	virtual void info() { std::cout << "Soldier Ant" << std::endl; }
	virtual ~SoldierAnt() {}
};

class WorkerAnt
{
public:
	virtual void info() { std::cout << "Worker Ant" << std::endl; }
	virtual ~WorkerAnt() {}
};

class Ants
{
public:
	void info() 
	{
		for (auto i = 0; i<m_soldiers.size(); ++i)
			m_soldiers[i].info();
		for (auto i = 0; i<m_workers.size(); ++i)
			m_workers[i].info();
	}

	std::vector<SoldierAnt> m_soldiers;
	std::vector<WorkerAnt> m_workers;
};

class AntsBuilder
{
protected:
	Ants* m_ants;

public:
	AntsBuilder():
		m_ants(0) 
	{}
	virtual ~AntsBuilder() {}
	virtual void buildWorkers() {}
	virtual void buildSoldiers() {}
	virtual Ants* getAnts() { return m_ants; }
};

class RedAntsBuilder : public AntsBuilder
{
public:
	void createArmy() { m_ants = new Ants; }
	void buildSoldiers() { m_ants->m_soldiers.push_back(SoldierAnt()); }
};


class BlackAntsBuilder : public AntsBuilder
{
public:
	void createArmy() { m_ants = new Ants; }
	void buildWorkers() { m_ants->m_workers.push_back(WorkerAnt()); }
	void buildSoldiers() { m_ants->m_soldiers.push_back(SoldierAnt()); }
};

class Director
{
public:
	Ants* createAnts(AntsBuilder& builder)
	{
		builder.buildWorkers();
		builder.buildSoldiers();
		return(builder.getAnts());
	}
};

int builderTest()
{
	Director dir;
	RedAntsBuilder redBuilder;
	BlackAntsBuilder blackBuilder;

	Ants* redAnts = dir.createAnts(redBuilder);
	Ants* blackAnts = dir.createAnts(blackBuilder);
	std::cout << "Red ants:" << std::endl;
	redAnts->info();
	std::cout << "Black ants:" << std::endl;
	blackAnts->info();
	// use builders

	return 0;
}

#endif //BUILDER_H