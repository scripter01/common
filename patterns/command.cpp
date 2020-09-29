// command.cpp

/*
команда (command) - поведенческий тип паттерна
команда - это материлизаци€ вызова метода
клиент общаетс€ с исполнителем через команду, это как клиент в кафе делающий заказ
у официанта, где исполнитель повар
*/

class Command
{
public: 
	virtual ~Command() = default;
	virtual void execute() = 0;
};

class JumpCommand : public Command
{
public:
	virtual void execute()() { /* TODO */ };
};

class FireCommand : public Command
{
public:
	virtual void execute()() { /* TODO */ };
};

class InputHandler
{
public:
	void Update()
	{
		if (isPressedX())
			mButtonX->execute();
		else if (isPressedY())
			mButtonY->execute();
	}

protected::
	bool isPressedX() const { return false; }
	bool isPressedY() const { return false; }

private:
	Command* mButtonX;
	Command* mButtonY;
};

//////////////////////////////////////////////////////////////////////////

class MoveUnitCommand : public Command
{
public:
	MoveUnitCommand(Unit* unit, int x, int y) :
		mUnit(unit),
		mX(x),
		mY(y)
	{}

	virtual void execute()
	{
		mOldX = mUnit->getX();
		mOldY = mUnit->getY();
		mUnit->moveTo(mX, mY);
	}

	virtual void undo()
	{
		mUnit->moveTo(mOldX, mOldY);
	}

private:
	Unit* mUnit = nullptr;
	int mOldX, mOldY = 0;
	int mX, mY = 0;
};

/*
older [CMD][CMD][CMD][CMD][CMD][CMD][CMD][CMD] newer
                       |
              (undo)current(redo)

 огда пользователь выбирает "отмена", мы отмен€ем текущую команду и сдвигаем указатель на одну позицию назад.
 огда мы выполн€ем повтор, мы перемещаем указатель на позицию вперед и выполн€ем команду. 
 огда пользователь после отмены команды выполн€ем=т новую команду, все содержимое списка после текущей команды выбрасываетс€
*/