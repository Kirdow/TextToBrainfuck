
#include <iostream>
#include <conio.h>

#include <fstream>
#include "BrainfuckConverter.h"

int main(int argc, char** argv)
{
	if (argc > 1)
	{
		char* filePath = argv[1];

		int len = strlen(filePath);
//		std::cout << &filePath[len - 4];
		bool __fExists = true;
		const char* testTxt = ".txt";
		for (int i = len - 4; i < len; i++)
		{
			if (filePath[i] != testTxt[i - len + 4]) __fExists = false;
		}
		if (__fExists)
		{
			bool exists = false;
			std::ifstream _f(filePath);
			if (_f.good())
			{
				exists = true;
			}
			_f.close();
			if (exists)
			{
				std::ifstream f(filePath);
				int size = -1;
				while (f)
				{
					char* ch = new char[1];
					f.read(ch, 1);
					size++;
				}
				f.close();
				f.open(filePath);
				char* textChars = new char[size+1];
				textChars[size] = '\0';
				f.read(textChars, size);
				f.close();
				BrainfuckConverter conv(textChars, size);
				conv.Convert();
				char* result = nullptr;
				int resultSize = conv.GetResult(&result);
				
				std::cout << "Enter name of output file (Must be in the same directory as the input file): ";
				char* _input = new char[1024];
				std::cin >> _input;
				int _inLen = strlen(_input);

				int dirSlash = 0;
				for (dirSlash = len - 1; filePath[dirSlash] != '/' && filePath[dirSlash] != '\\' && dirSlash >= 0; dirSlash--){	}
				if (dirSlash > -1)
				{
					char* outFileName = new char[dirSlash + _inLen + 2];
					outFileName[dirSlash + _inLen + 1] = '\0';
					for (int i = 0; i < dirSlash + 1; i++)
					{
						outFileName[i] = filePath[i];
					}
					for (int i = 0; i < _inLen; i++)
					{
						outFileName[i + dirSlash + 1] = _input[i];
					}
					std::ofstream ofs(outFileName);
					ofs.write("Brainfuck Code: \r\n", 18);
					ofs.write(result, resultSize);
					ofs.close();
//					std::cout << outFileName << std::endl;
					while (!_kbhit())
					{
					}
					return 0;
				}
				
			}
			else
			{
				std::cout << "File does not exist" << std::endl;
				std::cout << "Press any key to exit...";
				while (!_kbhit())
				{
				}
				return 0;
			}
//			FILE* file = fopen
		}
		else
		{
			std::cout << "File must be a .txt file" << std::endl;
			std::cout << "Press any key to exit...";
			while (!_kbhit())
			{
			}
			return 0;
		}
	}
}