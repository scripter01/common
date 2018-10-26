#include "stdafx.h"
#include "test.h"

struct IReceiver
{
	virtual void Receive(const char* data, unsigned int size) = 0;
};

struct ICallback
{
	virtual void BinaryPacket(const char* data, unsigned int size) = 0;
	virtual void TextPacket(const char* data, unsigned int size) = 0;
};

struct MyIReceiver : public IReceiver
{
	MyIReceiver(ICallback* callback) : m_callback(callback)
	{}

	void Receive(const char* data, unsigned int size) override
	{

	}

private:
	ICallback* m_callback;
};

void Test::run()
{
	
}