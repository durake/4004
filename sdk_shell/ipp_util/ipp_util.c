#ifdef _WIN32
#include <windows.h> 
#include <winnt.h> 
#include <stdio.h>

void SetColor(int color)
{
	HANDLE consolehwndD; 
	consolehwndD = GetStdHandle(STD_OUTPUT_HANDLE); 
	SetConsoleTextAttribute(consolehwndD,color); 
}

void RestoreColor()
{
	HANDLE consolehwndD; 
	consolehwndD = GetStdHandle(STD_OUTPUT_HANDLE); 
	SetConsoleTextAttribute(consolehwndD,FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); 
}

#endif
