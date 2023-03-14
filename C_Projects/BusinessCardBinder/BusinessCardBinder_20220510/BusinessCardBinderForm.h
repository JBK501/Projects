#ifndef _BUSINESSCARDBINDERFORM_H
#define _BUSINESSCARDBINDERFORM_H

#include <Windows.h>

BOOL CALLBACK BusinessCardBinderFormProc(HWND hWnd, UINT message, 
	WPARAM wParam, LPARAM lParam);
BOOL BusinessCardBinderForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL BusinessCardBinderForm_OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL BusinessCardBinderForm_OnTakeInButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL BusinessCardBinderForm_OnFindButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL BusinessCardBinderForm_OnTakeOutButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL BusinessCardBinderForm_OnArrangeButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL BusinessCardBinderForm_OnFirstButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL BusinessCardBinderForm_OnPreviousButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL BusinessCardBinderForm_OnNextButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL BusinessCardBinderForm_OnLastButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL BusinessCardBinderForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam);

#endif // !_BUSINESSCARDBINDERFORM_H
