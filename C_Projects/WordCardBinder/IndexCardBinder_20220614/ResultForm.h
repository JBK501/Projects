#ifndef _RESULTFORM_H
#define _RESULTFORM_H

#include <Windows.h>

BOOL CALLBACK ResultFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL ResultForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL ResultForm_OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL ResultForm_OnFirstButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL ResultForm_OnPreviousButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL ResultForm_OnNextButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL ResultForm_OnLastButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL ResultForm_OnTakeInButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL ResultForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam);

#endif // !RESULTFORM_H
