// command.cpp

/*
команда (command) - поведенческий тип паттерна
команда - это материлизация вызова метода
клиент общается с исполнителем через команду, это как клиент в кафе делающий заказ
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

private:
	bool isPressedX() const { return false; }
	bool isPressedY() const { return false; }

private:
	Command* mButtonX;
	Command* mButtonY;
};