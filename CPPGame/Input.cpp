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
    if (NumInputs == 0) return; // ��ʾû�����룬���Բ��������ȴ�
    ReadConsoleInput(hStdin, irInBuf, 128, &cNumRead); // ���������̣�BIO
}
