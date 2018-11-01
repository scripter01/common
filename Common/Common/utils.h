#ifndef LESSON_UTILS_H
#define LESSON_UTILS_H

#define LOG(a) { std::cout << a << std::endl; }
#define LOG_TEST(name, a) LOG("Test \""<< name << "\": " << a)

struct vector4
{
	vector4(float _r, float _g, float _b, float _a): r(_r), g(_g), b(_b), a(_a)
	{}
	vector4() : vector4(0.0f,0.0f,0.0f,0.0f)
	{}

	float r;
	float g;
	float b;
	float a;
};

vector4 strToVec4(const std::string& color);
int hexToInt(uint8_t* p);

#endif //LESSON_UTILS_H
