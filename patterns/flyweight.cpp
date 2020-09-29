// flyweight.cpp

/*
�������������� (flyweight, ��������, ���) - ����������� ��� ��������
�������������� ��������� ����� ��������� ����������� ����������� ������, ������ ������ ��� ��� ��������� ����� ����� �����
������ ��������� ������ ������� �� ��� ����:
1) ���������� ��������� (intrinsic)
������������ ��� ������� ���������� ������� ������, ������� ����� ����� � ����� ��������� ��� ���� ��������
2) ������� ��������� (extrensic)
��� ��� ��������� ��� ������� ����������
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
����������:
1) ��������� ���� ������ �� ��� �����: ���������� � ������� ���������
2) �������� ���� ����������� ��������� � ������, �� ���������, ��� �� �������� �� ���������
3) ���������� ���� �������� ��������� � ��������� �������, ��� ��� ���� ��������������.
   ������� ��� ���� �� ������
4) ������� �������, ������� ����� ���������� � �������� ��� ��������� �������
   ������ ����������� �� ������� ���������
5) ������ ������ ������� ��� ��������� �������� �������� ��������� � ���������� ��� � ������ ������� ���������
*/