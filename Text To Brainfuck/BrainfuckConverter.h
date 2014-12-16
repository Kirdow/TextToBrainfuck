#pragma once
class BrainfuckConverter
{
private:
	const char* chars;
	int size;
	char* result;
	int resultSize;
	void Add(char* chars, int size);
	void GetNearestMult(int diff, int* ra, int* rb);
public:
	BrainfuckConverter(const char* chars, int size);
	~BrainfuckConverter();
	bool Convert();
	int GetResult(char** result);
};

