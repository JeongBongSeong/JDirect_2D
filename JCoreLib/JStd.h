#pragma once
#define _WINSOCKAPI_
#include<winsock2.h>
#include<windows.h>
#include<d3d11.h>
#include<iostream>
#include<atlconv.h>	//A2W W2A
#include<vector>
#include<list>
#include<map>
#include<tchar.h>
#include<string>
#include<functional>
#include<d3dcompiler.h>
#include"JCollision.h"

#pragma comment (lib,"d3d11.lib")
#pragma comment (lib,"D3DCompiler.lib")
#pragma comment (lib,"DirectXTK.lib")
using namespace std;

extern RECT g_rtClient;
extern HWND g_hWnd;

extern float	g_fSecPerFrame;
extern float	g_fGameTimer;
extern POINT	g_ptMouse;

static std::wstring to_mw(const std::string& _src)
{
	USES_CONVERSION;
	return std::wstring(A2W(_src.c_str()));
}
static std::string to_wm(const std::wstring& _src)
{
	USES_CONVERSION;
	return std::string(W2A(_src.c_str()));
}

template<class T>
class JSingleton
{
public:
	static T& Get()
	{
		static T theSingle;
		return theSingle;
	}
};

static void DisplayText(const char* fmt, ...)
{
	va_list arg;
	va_start(arg, fmt);
	char buf[1024 + 256] = { 0, };
	vsprintf_s(buf, fmt, arg);
	OutputDebugStringA((char*)buf);
	va_end(arg);
}


#define GAME_START int WINAPI wWinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance, LPWSTR    lpCmdLine, int       nCmdShow){   Sample core;   
#define GAME_WIN(s,x,y) if (core.MyRegisterClass(hInstance) == FALSE) return 1;   if (core.SetWindow(L#s, x, y) == FALSE) return 1;   core.GameRun();    return 1;}
#define SIMPLE_WIN() if (core.MyRegisterClass(hInstance) == FALSE) return 1;   if (core.SetWindow() == FALSE) return 1;   core.GameRun();    return 1;}
#define GAME_RUN(s,x,y) GAME_START; GAME_WIN(s,x,y);
#define RUN() GAME_START; SIMPLE_WIN();

#define BEGIN_START(S) friend class JSingleton<S>