#include "stdafx.h"
#include "lesson_bits.h"

// [][][][][][][][] 8 bit = 1 byte

void bitFieldTest()
{
	struct bitField1
	{
		char a : 3;
		char b : 3;
		char c : 2;
	};
	std::cout << "Test \"bitField\": " << sizeof(bitField1) << "\n"; // 1 byte

	struct bitField2
	{
		char a : 3;
		char b : 3;
		char c : 3;
	};
	std::cout << "Test \"bitField\": " << sizeof(bitField2) << "\n"; // 2 byte

	struct bitField3
	{
		int a : 3;
		char b : 3;
		char c : 3;
	};
	std::cout << "Test \"bitField\": " << sizeof(bitField3) << "\n"; // 8 byte, multiple of max type size
}

float logCeil(double base, double x)
{ 
	return int(ceil(log(x) / log(base)));
}

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
	std::cout << "Test \"intToHexTest\": " << convertingStream.str();
}

void Lesson_bits::run()
{
	bitFieldTest();
	intToHexTest();
}