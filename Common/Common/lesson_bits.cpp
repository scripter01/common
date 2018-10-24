#include "stdafx.h"
#include "lesson_bits.h"

// [][][][][][][][] 8 bit = 1 byte

/****************************************************/
/*                     bit field                    */
/****************************************************/
void bitFieldTest()
{
	struct bitField1
	{
		char a : 3;
		char b : 3;
		char c : 2;
	};
	std::cout << "Test \"bit field\": " << sizeof(bitField1) << "\n"; // 1 byte

	struct bitField2
	{
		char a : 3;
		char b : 3;
		char c : 3;
	};
	std::cout << "Test \"bit field\": " << sizeof(bitField2) << "\n"; // 2 byte

	struct bitField3
	{
		int a : 3;
		char b : 3;
		char c : 3;
	};
	std::cout << "Test \"bit field\": " << sizeof(bitField3) << "\n"; // 8 byte, multiple of max type size
}

int logCeil(double base, double x)
{ 
	return int(ceil(log(x) / log(base)));
}

/****************************************************/
/*                     int to hex                   */
/****************************************************/
void intToHexTest()
{
	//32bit int -> hex (16)
	//log(16)(2^32)=23
	std::cout << "Test \"intToHexStringTest\": "  << logCeil(16, pow(2, 32)) << "\n";
	//64bit int -> Septenary (7)
	//log(7)(2^64)=23
	std::cout << "Test \"intToHexStringTest\": " << logCeil(7, pow(2, 64)) << "\n";

	//2^8=256 per byte
	//16^2=256 = 2 symbols per byte
	const auto symbolPerByte = 2;
	const auto symbolCount = sizeof(int)*symbolPerByte;
	const auto bufferSize = symbolCount + 1; // +1 for '\0'

	std::string data = "";
	data.reserve(bufferSize);
	_itoa_s(4294967295, &data[0], bufferSize, 16);

	std::stringstream convertingStream;
	convertingStream << "0x" << std::setfill('0') << std::setw(symbolCount) << data.c_str() << std::endl;
	std::cout << "Test \"int to hex\": " << convertingStream.str();
}

/****************************************************/
/*                 bitwise operations               */
/****************************************************/
void bitwiseOperationsTest()
{
	const uint32_t data = 5; // [0..31]
	// high 8 bits data [24..31]
	const uint8_t highData8 = data >> 24;
	// low 8 bits data [0..7]
	const uint8_t lowData8 = data & 0x000000FF;
	uint32_t dataTest = (uint32_t(highData8) << 24) | lowData8;
	std::cout << "Test \"bitwise operations\": " << data << " " << dataTest << "\n";

	// low 10 bits data [0..9]
	// 0011 1111 1111 = 3 F F
	const uint8_t lowData10 = data & 0x000003FF;

	enum TestFlags
	{
		TEST_FLAG_NONE = 0,
		TEST_FLAG_WARNING = 1,
		TEST_FLAG_ERROR = 2
	};

	uint32_t flags = TEST_FLAG_NONE;
	flags |= TEST_FLAG_ERROR;
	flags |= TEST_FLAG_WARNING;
	flags ^= TEST_FLAG_WARNING;

	std::cout << "Test \"bitwise operations\": " << flags  << " " << (flags & TEST_FLAG_ERROR) << " " << (flags & TEST_FLAG_WARNING) << "\n";
}

void Lesson_bits::run()
{
	bitFieldTest();
	intToHexTest();
	bitwiseOperationsTest();
}