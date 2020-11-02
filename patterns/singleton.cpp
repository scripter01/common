// singleton.cpp

/*
�������� (singleton, ��������) - ����������� ��� ��������
�������� - ��� ����������� ������ ��������������, ������� �����������, ��� � ������ ���� ������ ���� ���������, � 
������������� � ���� ���������� ����� �������
*/

class FileSystem
{
public:
	static FileSystem& instance()
	{
		static FileSystem* instance = new FileSystem();
		return *instance;
	}

private:
	FileSystem() = default;
};

/*
C++11 �����������, ��� ������������� ��������� ����������� ���������� ���������� ������ ���� ���, ���� � ������ 
������������� �������.
����� ���� �������� ��������:
������ FileSystem � ������������ ���������, ����������� � ������, ��� ���������� � instance
*/