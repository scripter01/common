// flyweight.cpp

/*
приспособленец (flyweight, легковес, кеш) - структурный тип паттерна
приспособленец необходим когда требуетс€ максимально облегченный объект, обычно потому что нам требуетс€ таких очень много
шаблон раздел€ет данные объекта на два типа:
1) внутреннее состо€ние (intrinsic)
неуникальные дл€ каждого экземпл€ра объекта данные, которые можно иметь в одном экзепл€ре дл€ всех объектов
2) внешнее состо€ние (extrensic)
все что уникально дл€ каждого экземпл€ра
*/

// intrinsic
class TreeModel
{
	Mesh mMesh;
	Texture mBark;
};

// extrensic
class Tree
{
	TreeModel* mModel;
	Vector mPos;
	float mHeight;
};

//////////////////////////////////////////////////////////////////////////

class Terrain
{
public:
	Terrain(int moveCost, bool isWater) :
		mMoveCost(moveCost), mIsWater(isWater)
	{}
	int getMoveCost() const { return mMoveCost; }
	bool isWater() const { return mIsWater; }

private:
	int mMoveCost;
	bool mIsWater;
};

#define MAP_WIDTH 10
#define MAP_HEIGHT 10
#define GRASS_MOVE_COST 1
#define WATER_MOVE_COST 2

class World
{
public:
	World():
		mGrassTerrain(GRASS_MOVE_COST, false),
		mRiverTerrain(WATER_MOVE_COST, true)
	{}

	const Terrain& getTile(int x, int y) const
	{
		return *mTiles[x][y];
	}

	void init()
	{
		for (auto w = 0; w < MAP_WIDTH; w++)
		{
			for (auto h = 0; h < MAP_HEIGHT; h++)
			{
				const bool isRiver = rand() % 2 == 0;
				mTiles[x][y] = isRiver ? &mRiverTerrain : &mGrassTerrain;
			}
		}
	}

private:
	Terrain* mTiles[MAP_WIDTH][MAP_HEIGHT];
	Terrain mGrassTerrain;
	Terrain mRiverTerrain;
};

/*
–еализаци€:
1) разделить пол€ класса на две части: внутреннее и внешнее состо€ние
2) оставить пол€ внутреннего состо€ни€ в классе, но убедитьс€, что их значени€ не измен€емы
3) превратить пол€ внешнего состо€ни€ в параметры методов, где эти пол€ использовались.
   удалить эти пол€ из класса
4) создать фабрику, котора€ будет копировать и отдавать уже созданные объекты
   клиент запрашивает из фабрики легковесы
5) клиент должен хранить или вычисл€ть значени€ внешнего состо€ни€ и передавать его в методы объекты легковеса
*/