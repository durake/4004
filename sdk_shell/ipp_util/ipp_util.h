#ifndef _IPP_UTIL_H_
#define _IPP_UTIL_H_

#ifdef _WIN32
//#include <winsock2.h>
#include <windows.h> 
#include <stdio.h>
#include <string.h>
#include <inaddr.h>
void SetColor(int color);
void RestoreColor();
#define ipp_LogV(...) printf(__VA_ARGS__)
#define ipp_LogD(...) do{SetColor(FOREGROUND_BLUE);printf(__VA_ARGS__);RestoreColor();}while(0)
#define ipp_LogI(...) do{SetColor(FOREGROUND_RED | FOREGROUND_GREEN); printf(__VA_ARGS__);RestoreColor();}while(0)
#define ipp_LogE(...) do{SetColor(FOREGROUND_RED); printf(__VA_ARGS__);RestoreColor();}while(0)
#define ipp_LogW(...) do{SetColor(FOREGROUND_RED | FOREGROUND_GREEN); printf(__VA_ARGS__);RestoreColor();}while(0)

#define SLEEP(microSec) Sleep(microSec * 1000)
#define usleep(microSec) Sleep(microSec / 1000)
#define msleep(microSec) Sleep(microSec)

#define __func__ __FUNCTION__ 
#else
#include <stdio.h>
#define NONE "\033[m"
#define RED "\033[0;31m"
#define BLACK "\033[0;30m"
#define BLUE "\033[0;34m"
#define YELLOW "\033[1;33m"
#define ipp_LogV(...) printf(__VA_ARGS__)
#define ipp_LogD(...) do{printf(BLUE);printf(__VA_ARGS__);printf(NONE);}while(0)
#define ipp_LogI(...) do{printf(YELLOW);printf(__VA_ARGS__);printf(NONE);}while(0)
#define ipp_LogE(...) do{printf(RED);printf(__VA_ARGS__);printf(NONE);}while(0)
#define ipp_LogW(...) do{printf(YELLOW);printf(__VA_ARGS__);printf(NONE);}while(0)

#endif

#endif
