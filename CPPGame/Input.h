#pragma once
#include <windows.h>

class Input
{
	HANDLE hStdin;
public:
	Input();
	void GetInput(INPUT_RECORD* irInBuf, DWORD& cNumRead);
};

