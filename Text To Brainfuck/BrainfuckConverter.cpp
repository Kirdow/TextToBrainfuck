#include "BrainfuckConverter.h"


BrainfuckConverter::BrainfuckConverter(const char* chars, int size)
{
	this->chars = chars;
	this->size = size;
	this->result = new char[size];
	this->resultSize = size;
}


BrainfuckConverter::~BrainfuckConverter()
{
}

bool BrainfuckConverter::Convert()
{
	return true;
}

int BrainfuckConverter::GetResult(char* result)
{
	result = this->result;
	return resultSize;
}