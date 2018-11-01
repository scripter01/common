#include "stdafx.h"
#include "utils.h"

int hexToInt(uint8_t* p)
{
	if (p[0] >= '0' && p[0] <= '9')
		return int(p[0] - '0');
	if (p[0] >= 'a' && p[0] <= 'f')
		return int(p[0] - 'a') + 10;
	if (p[0] >= 'A' && p[0] <= 'F')
		return int(p[0] - 'A') + 10;
	return 0;
}

vector4 strToVec4(const std::string& color)
{
	assert(color.length() >= 6 && color.length() <= 8);
	uint8_t* p = (uint8_t*)color.c_str();
	int r = hexToInt(p + 0) * 16 + hexToInt(p + 1);
	int g = hexToInt(p + 2) * 16 + hexToInt(p + 3);
	int b = hexToInt(p + 4) * 16 + hexToInt(p + 5);
	int a = 0;
	if (color.length() >= 8)
		a = hexToInt(p + 6) * 16 + hexToInt(p + 7);
	return vector4(float(r)/256.0f, float(g)/256.0f, float(b)/256.0f, float(a)/256.0f);
}
