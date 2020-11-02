// state.cpp

/*
состояние (state) - поведенческий тип паттерна
состояние - это поведенческий паттер проектирования, который позволяет объектам менять поведение в зависимости
от своего состояния.
Паттерн состояние невозможно рассматривать в отрыве от концепции машины состояний (стейт машина, конечный автомат).
Основная идея которой в том, что программа может находиться в одном из нескольких состояний, которые все время
сменяют друг друга.

A --> B --> C
^     |     ^
|     v     |
D --> E --> F

*/

enum State
{
	STATE_STANDING = 0,
	STATE_JUMPING,
	STATE_DIVING
};

// плохая реализация
void Player::handleInput(Input input)
{
	switch (mState)
	{
	case STATE_STANDING:
	{
		if (input == PRESS_B)
		{
			mState = STATE_JUMPING;
			mVelocityY = JUMP_VELOCITY;
			setGraphics(IMAGE_JUMP);
		}
	}
	break;

	case STATE_JUMPING:
	{
		if (input == PRESS_DOWN)
		{
			mState = STATE_DIVING;
			SetGraphics(IMAGE_DIVE);
		}
	}
	break;
	}
}

// реализация на стейтах
class PlayerState
{
public:
	virtual ~PlayerState() = default;
	virtual void handleInput(Player& player, INPUT input) {};
	virtual void update(Player& player) {};
	virtual void enter(Player& player) {};
};

class Player
{
public:
	void handleInput(Input input)
	{
		if (mState)
			mState->handleInput(*this, input)
	}

	void update()
	{
		if (mState)
			mState->update(*this);
	}

	void changeState(PlayerState* state)
	{
		if (mState)
			delete mState;
		mState = state;
		if (mState)
			mState->enter(*this);
	}

private:
	PlayerState* mState = nullptr;
};

/*
машина конкурентных состояний или конкурентный автомат (concurrent state machines) это машина, когда одновременно
существует более одной конечной машины.
иерархическая машина состояний или иерархический автомат базируется на наследовании. можно отнаследовать похожие
состояния от одного родительского классаи вынести туда дублирующий код.
автомат с магазинной памятью (pushdown automato) это когда у нас вместо хранения единственного указателя на 
состояние хранится стек. добавляется две операции:
- поместить (push) новое состояние в стек
- извлечь (pop) верхнее состояние из стека
*/
