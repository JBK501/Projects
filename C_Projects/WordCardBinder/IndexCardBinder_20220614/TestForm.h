#ifndef _TESTFORM_H
#define _TESTFORM_H

#include <Windows.h>

BOOL CALLBACK TestFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL TestForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL TestForm_OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL TestForm_OnWordClassEditKillFocused(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL TestForm_OnMeaningEditKillFocused(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL TestForm_OnGradeButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL TestForm_OnTimer(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL TestForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam);


#endif // !_TESTFORM_H
