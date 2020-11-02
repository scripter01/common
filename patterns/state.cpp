// state.cpp

/*
��������� (state) - ������������� ��� ��������
��������� - ��� ������������� ������ ��������������, ������� ��������� �������� ������ ��������� � �����������
�� ������ ���������.
������� ��������� ���������� ������������� � ������ �� ��������� ������ ��������� (����� ������, �������� �������).
�������� ���� ������� � ���, ��� ��������� ����� ���������� � ����� �� ���������� ���������, ������� ��� �����
������� ���� �����.

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

// ������ ����������
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

// ���������� �� �������
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
������ ������������ ��������� ��� ������������ ������� (concurrent state machines) ��� ������, ����� ������������
���������� ����� ����� �������� ������.
������������� ������ ��������� ��� ������������� ������� ���������� �� ������������. ����� ������������� �������
��������� �� ������ ������������� ������� ������� ���� ����������� ���.
������� � ���������� ������� (pushdown automato) ��� ����� � ��� ������ �������� ������������� ��������� �� 
��������� �������� ����. ����������� ��� ��������:
- ��������� (push) ����� ��������� � ����
- ������� (pop) ������� ��������� �� �����
*/
