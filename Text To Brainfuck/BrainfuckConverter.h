#pragma once
class BrainfuckConverter
{
private:
	const char* chars;
	int size;
	char* result;
	int resultSize;
public:
	BrainfuckConverter(const char* chars, int size);
	~BrainfuckConverter();
	bool Convert();
	int GetResult(char* result);
};

