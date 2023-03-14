#ifndef _TAKEOUTFORM_H
#define _TAKEOUTFORM_H

#include <windows.h>

BOOL CALLBACK TakeOutFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL TakeOutForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL TakeOutForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam);

#endif // !_TAKEOUTFORM_H
