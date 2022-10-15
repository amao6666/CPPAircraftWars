#include "Input.h"

Input::Input()
{
	hStdin = GetStdHandle(STD_INPUT_HANDLE);
}

void Input::GetInput(INPUT_RECORD* irInBuf, DWORD& cNumRead)
{
    using namespace std;

    DWORD NumInputs = 0;
    GetNumberOfConsoleInputEvents(hStdin, &NumInputs);
    if (NumInputs == 0) return; // 表示没有输入，可以不用阻塞等待
    ReadConsoleInput(hStdin, irInBuf, 128, &cNumRead); // 会阻塞进程，BIO
}
