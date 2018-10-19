#ifndef LESSON_C11_A_H
#define LESSON_C11_A_H

/****************************************************/
/*                   extern template                */
/****************************************************/

template<typename T>
class ExternTemplatesTest
{
public:
	ExternTemplatesTest(T data);
};

void externTemplatesTestInt(int number);

#endif //LESSON_BASE_H