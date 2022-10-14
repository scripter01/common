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
	LOG_TEST("bit field", sizeof(bitField1));

	struct bitField2
	{
		char a : 3;
		char b : 3;
		char c : 3;
	};
	LOG_TEST("bit field", sizeof(bitField2));

	struct bitField3
	{
		int a : 3;
		char b : 3;
		char c : 3;
	};
	LOG_TEST("bit field", sizeof(bitField3)); // 8 byte, multiple of max type size
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
	LOG_TEST("int to hex", logCeil(16, pow(2, 32)));
	//64bit int -> Septenary (7)
	//log(7)(2^64)=23
	LOG_TEST("int to hex", logCeil(7, pow(2, 64)));

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
	LOG_TEST("int to hex", convertingStream.str());
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
	LOG_TEST("bitwise operations", data << " " << dataTest);

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

	LOG_TEST("bitwise operations", flags << " " << (flags & TEST_FLAG_ERROR) << " " << (flags & TEST_FLAG_WARNING));
}

/****************************************************/
/*                       endian                     */
/****************************************************/
void endianTest()
{
	const uint8_t a = 1;
	const uint8_t b = 1;
	const uint8_t c = 1;
	const uint8_t d = 1;
	const uint32_t littleEndian = a | (b << 8) | (c << 16) | (d << 24);
	const uint32_t bigEndian = d | (c << 8) | (b << 16) | (a << 24);
}

/****************************************************/
/*                         ?                        */
/****************************************************/
void sashaTest()
{
	/*
	2 ^ 1 = 1   0000   0   0
	2 ^ 2 = 1   0001   1   1
	2 ^ 3 = 1   0010   2   2
	2 ^ 4 = 1   0011   3   3
	2 ^ 5 = 1   0100   4   4
	2 ^ 6 = 1   0101   5   5
	2 ^ 7 = 1   0110   6   6
	2 ^ 8 = 1   0111   7   7
	2 ^ 9 = 1   1000   8   8
	2 ^ 10 = 1  1001   9   9
	2 ^ 11 = 1  1010   A   10
	2 ^ 12 = 1  1011   B   11
	2 ^ 13 = 1  1100   C   12
	2 ^ 14 = 1  1101   D   13
	2 ^ 15 = 1  1110   E   14
	2 ^ 16 = 1  1111   F   15
	*/

	uint16_t params = 0;
	/*
	bits 0..7   = A(8)
	bits 8..13  = A(6)
	bits 14     = A(1)
	bits 15     = A(1)
	*/

	uint8_t A = params & 0xFF;         // 1111 1111 (F -> 1111) FF
	uint8_t B = (params >> 8) & 0x3F;  // 0011 1111 (0011 -> 3, F -> 1111) 3F
	uint8_t C = (params >> 14) & 0x01;
	uint8_t D = (params >> 15) & 0x01;

	uint16_t params2 = (A & 0xFF) | ((B & 0x3F) << 8) | ((C & 0x01) << 14) | ((D & 0x01) << 15);

	//////////////////////////////////////////////////////////////////////////

	auto checkBit = [](uint32_t value, uint8_t bitIndex)
	{
		return ((value > bitIndex) & 0x01) != 0;
	};
	uint32_t flags = 0x84210000;
	checkBit(flags, 0);
}

void Lesson_bits::run()
{
	bitFieldTest();
	intToHexTest();
	bitwiseOperationsTest();
	endianTest();
}