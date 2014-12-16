#include "BrainfuckConverter.h"
#include <math.h>

BrainfuckConverter::BrainfuckConverter(const char* chars, int size)
{
	this->chars = chars;
	this->size = size;
	this->result = new char[1];
	this->result[0] = '\0';
	this->resultSize = size;
}


BrainfuckConverter::~BrainfuckConverter()
{
}

//Converts this->chars (Text) into this->result (Brainfuck Code)
bool BrainfuckConverter::Convert()
{
	//The current position in this->chars
	int position = 0;
	//The values that is changing in the brainfuck "RAM", the real verion has 30k, I only use 100 in this one.
	char* values = new char[100];
	int vPos = 0;
	Add(">", 1);
	char* baseValAdd = new char[82];
	//Initializes index 1 through 9, and gives them a value interval of 25 starting at 25.
	for (int i = 1; i < 10; i++)
	{
		values[i] = 25 * i;
	}
	//The Final Brainfuck code for the previous part
	Add(">+++++[<+++++>-]<[>+>++>+++>++++>+++++>++++++>+++++++>++++++++>++++++++<<<<<<<<<-]", 82);
	
	//Loops through all the this->chars letters and makes the brainfuck code for them.
	while (position < size)
	{
		int nChars = 0;
		int pChars = 0;
		char* chars = new char[1024];
		char c = this->chars[position];
		int bDiff = 256;
		int bDiffOriginal = -1;
		int bDiffPos = -1;
		//Checks for which of the indexes 1 - 9 that is the best to use.
		for (int i = 1; i < 10; i++)
		{
			int diff = values[i] - c;
			if (diff < 0) diff = -diff;
			if (diff < bDiff)
			{
				bDiffOriginal = values[i] - c;
				bDiff = diff;
				bDiffPos = i;
			}
		}
		//If last check succeeds this code handles the brainfuck generating.
		if (bDiffPos > 0)
		{
			int a = 0;
			int b = 0;
			//Gets the best pair to multiply to get to the destination
			GetNearestMult(bDiff, &a, &b);
			//Checks if a or b is = 0, if so, skips the loop
			int val = a * b;
			char* tChars = nullptr;
			if (val > 0)
			{
				tChars = new char[a];
				//Sets the first multiplication 'a' at index 0
				for (int i = 0; i < a; i++)
				{
					tChars[i] = '+';
				}
				//Adds those chars to the final code
				Add(tChars, a);
				tChars = new char[b + bDiffPos * 2 + 3];
				//Adds the loop start, the characters to get to the correct index and the charecters to get back
				tChars[0] = '[';
				for (int i = 0; i < bDiffPos; i++)
				{
					tChars[i + 1] = '>';
					tChars[1 + bDiffPos + b + i] = '<';
				}
				//Adds the values at the correct index
				for (int i = 0; i < b; i++)
				{
					tChars[1 + bDiffPos + i] = bDiffOriginal < 0 ? '-' : '+';
				}
				//Adds the ending of the loop
				tChars[b + bDiffPos * 2 + 1] = '-';
				tChars[b + bDiffPos * 2 + 2] = ']';
				//Adds the loop to the final code
				Add(tChars, b + bDiffPos * 2 + 3);
			}
			int nDiff = bDiffOriginal + (bDiff < 0 ? -val : val);
			tChars = new char[nDiff < 0 ? -nDiff : nDiff];
			int pDiff = nDiff < 0 ? -nDiff : nDiff;
			for (int i = 0; i < pDiff; i++)
			{
				tChars[i] = nDiff < 0 ? '-' : '+';
			}
			Add(tChars, nDiff);
			Add(".", 1);

		}
		position++;
	}
	return true;
}

int BrainfuckConverter::GetResult(char** result)
{
	*result = this->result;
	return resultSize;
}

void BrainfuckConverter::Add(char* chars, int size)
{
	char* nResult = new char[resultSize + size + 1];
	for (int i = 0; i < resultSize; i++)
	{
		nResult[i] = result[i];
	}
	for (int i = resultSize; i < resultSize + size; i++)
	{
		nResult[i] = chars[i-resultSize];
	}
	nResult[resultSize + size] = '\0';
	this->result = nResult;
	this->resultSize += size;
}

void BrainfuckConverter::GetNearestMult(int diff, int* ra, int* rb)
{
	int mid = diff / 2;
	int a = 0;
	int b = diff;
	int _a = a;
	int _b = b;
	int bDiff = diff;
	for (a = 0; a <= mid; a++)
	{
		int _diff = diff - a*b;
		if (_diff < 0) _diff = -_diff;
		if (_diff < bDiff)
		{
			_a = a;
			_b = b;
			bDiff = _diff;
		}
		b--;
	}
	*ra = _a;
	*rb = _b;
}