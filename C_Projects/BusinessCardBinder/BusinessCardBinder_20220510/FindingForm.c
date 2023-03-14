#include "FindingForm.h"
#include "BusinessCardBinder.h"
#include "resource1.h"
#include <stdio.h>
#include <stdlib.h>

#pragma warning (disable : 4996)

BOOL CALLBACK FindingFormProc(HWND hWnd, UINT message,
	WPARAM wParam, LPARAM lParam) {

	BOOL ret;

	switch (message){

	case WM_COMMAND:
		ret = FindingForm_OnCommand(hWnd, wParam, lParam);
		break;
	case WM_CLOSE:
		ret = FindingForm_OnClose(hWnd, wParam, lParam);
		break;
	default:
		ret = FALSE;
		break;
	}
	return ret;
}

BOOL FindingForm_OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	BOOL ret;

	switch (LOWORD(wParam)){

	case IDC_BUTTON_FIND:
		ret = FindingForm_OnFindButtonClicked(hWnd, wParam, lParam);
		break;
	case IDC_BUTTON_SELECT:
		ret = FindingForm_OnSelectButtonClicked(hWnd, wParam, lParam);
		break;
	case IDC_BUTTON_FIRST:
		ret = FindingForm_OnFirstButtonClicked(hWnd, wParam, lParam);
		break;
	case IDC_BUTTON_PREVIOUS:
		ret = FindingForm_OnPreviousButtonClicked(hWnd, wParam, lParam);
		break;
	case IDC_BUTTON_NEXT:
		ret = FindingForm_OnNextButtonClicked(hWnd, wParam, lParam);
		break;
	case IDC_BUTTON_LAST:
		ret = FindingForm_OnLastButtonClicked(hWnd, wParam, lParam);
		break;
	default:
		ret = FALSE;
		break;
	}
	return ret;
}

BOOL FindingForm_OnFindButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	TCHAR name[16];
	HWND hBusinessCardBinder;
	BusinessCardBinder *businessCardBinder;
	BusinessCard *(*indexes);
	Long count;
	Long current = -1;

	//1. 찾기버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED) {

		//1.1 성명을 읽는다.
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_FINDNAME), WM_GETTEXT, 
			(WPARAM)16, (LPARAM)name);

		//1.2 명함철 윈도우를 찾는다.
		hBusinessCardBinder = FindWindow("#32770", "명함철");

		//1.3 명함철 윈도우의 명함철에서 찾는다.
		businessCardBinder = 
			(BusinessCardBinder*)GetWindowLongPtr(hBusinessCardBinder, GWLP_USERDATA);

		//+ 인덱스 없애기
		indexes = (BusinessCard*(*))GetWindowLongPtr(hWnd, GWLP_USERDATA);
		if (indexes != NULL) {
			free(indexes);
		}

		Find(businessCardBinder, name, &indexes, &count);

		//+ 찾기 윈도우에 저장한다.
		SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG)indexes);
		SetProp(hWnd, "PROP_CURRENT", (HANDLE)current);
		SetProp(hWnd, "PROP_COUNT", (HANDLE)count);

		//1.4 찾았으면
		if (count > 0) {
			
			//1.4.1 첫 번째 위치로 이동한다.
			current = 0;
			SetProp(hWnd, "PROP_CURRENT", (HANDLE)current);

			//1.4.2 현재명함을 출력한다
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITNAME), WM_SETTEXT,
				(WPARAM)0, (LPARAM)indexes[current]->personal.name);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITPOSITION), WM_SETTEXT,
				(WPARAM)0, (LPARAM)indexes[current]->personal.position);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITCELLPHONENUMBER), WM_SETTEXT,
				(WPARAM)0, (LPARAM)indexes[current]->personal.cellphoneNumber);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITEMAILADDRESS), WM_SETTEXT,
				(WPARAM)0, (LPARAM)indexes[current]->personal.eMailAddress);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITCOMPANYNAME), WM_SETTEXT,
				(WPARAM)0, (LPARAM)indexes[current]->company.name);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITADDRESS), WM_SETTEXT,
				(WPARAM)0, (LPARAM)indexes[current]->company.address);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITTELEPHONENUMBER), WM_SETTEXT,
				(WPARAM)0, (LPARAM)indexes[current]->company.telephoneNumber);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITPAXNUMBER), WM_SETTEXT,
				(WPARAM)0, (LPARAM)indexes[current]->company.paxNumber);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITURL), WM_SETTEXT,
				(WPARAM)0, (LPARAM)indexes[current]->company.url);
		}
		else {

			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITNAME), WM_SETTEXT,
				(WPARAM)0, (LPARAM)"");
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITPOSITION), WM_SETTEXT,
				(WPARAM)0, (LPARAM)"");
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITCELLPHONENUMBER), WM_SETTEXT,
				(WPARAM)0, (LPARAM)"");
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITEMAILADDRESS), WM_SETTEXT,
				(WPARAM)0, (LPARAM)"");
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITCOMPANYNAME), WM_SETTEXT,
				(WPARAM)0, (LPARAM)"");
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITADDRESS), WM_SETTEXT,
				(WPARAM)0, (LPARAM)"");
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITTELEPHONENUMBER), WM_SETTEXT,
				(WPARAM)0, (LPARAM)"");
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITPAXNUMBER), WM_SETTEXT,
				(WPARAM)0, (LPARAM)"");
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITURL), WM_SETTEXT,
				(WPARAM)0, (LPARAM)"");
		}
	}
	return TRUE;
}

BOOL FindingForm_OnSelectButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	HWND hBusinessCardBinder;
	BusinessCardBinder *businessCardBinder;
	BusinessCard *(*indexes);
	Long current;
	BusinessCard *index;
	TCHAR name[16];
	TCHAR position[16];
	TCHAR cellphoneNumber[16];
	TCHAR eMailAddress[128];
	TCHAR companyName[32];
	TCHAR address[64];
	TCHAR telephoneNumber[16];
	TCHAR paxNumber[16];
	TCHAR url[128];

	//2. 선택 버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED) {

		//+ 찾기 윈도우에 저장한 위치값 가져오기
		indexes = (BusinessCard*(*))GetWindowLongPtr(hWnd, GWLP_USERDATA);
		current = (Long)GetProp(hWnd, "PROP_CURRENT");

		//2.1 명함철 윈도우를 찾는다.
		hBusinessCardBinder = FindWindow("#32770", "명함철");

		//2.2 명함철 윈도우의 명함철에서 이동한다.
		businessCardBinder = (BusinessCardBinder*)GetWindowLongPtr(hBusinessCardBinder, GWLP_USERDATA);

		index = BusinessCardBinder_Move(businessCardBinder, indexes[current]);

		//2.3 명함철 윈도우의 명함에 출력한다.

		//2.3.1 찾기 윈도우의 명함을 가져온다.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITNAME), WM_GETTEXT,
			(WPARAM)16, (LPARAM)name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITPOSITION), WM_GETTEXT,
			(WPARAM)16, (LPARAM)position);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITCELLPHONENUMBER), WM_GETTEXT,
			(WPARAM)16, (LPARAM)cellphoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITEMAILADDRESS), WM_GETTEXT,
			(WPARAM)128, (LPARAM)eMailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITCOMPANYNAME), WM_GETTEXT,
			(WPARAM)32, (LPARAM)companyName);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITADDRESS), WM_GETTEXT,
			(WPARAM)64, (LPARAM)address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITTELEPHONENUMBER), WM_GETTEXT,
			(WPARAM)16, (LPARAM)telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITPAXNUMBER), WM_GETTEXT,
			(WPARAM)16, (LPARAM)paxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITURL), WM_GETTEXT,
			(WPARAM)128, (LPARAM)url);

		//2.3.2 명함철 윈도우의 명함에 출력한다.
		SendMessage(GetDlgItem(hBusinessCardBinder, IDC_STATIC_EDITNAME), WM_SETTEXT,
			(WPARAM)0, (LPARAM)name);
		SendMessage(GetDlgItem(hBusinessCardBinder, IDC_STATIC_EDITPOSITION), WM_SETTEXT,
			(WPARAM)0, (LPARAM)position);
		SendMessage(GetDlgItem(hBusinessCardBinder, IDC_STATIC_EDITCELLPHONENUMBER), WM_SETTEXT,
			(WPARAM)0, (LPARAM)cellphoneNumber);
		SendMessage(GetDlgItem(hBusinessCardBinder, IDC_STATIC_EDITEMAILADDRESS), WM_SETTEXT,
			(WPARAM)0, (LPARAM)eMailAddress);
		SendMessage(GetDlgItem(hBusinessCardBinder, IDC_STATIC_EDITCOMPANYNAME), WM_SETTEXT,
			(WPARAM)0, (LPARAM)companyName);
		SendMessage(GetDlgItem(hBusinessCardBinder, IDC_STATIC_EDITADDRESS), WM_SETTEXT,
			(WPARAM)0, (LPARAM)address);
		SendMessage(GetDlgItem(hBusinessCardBinder, IDC_STATIC_EDITTELEPHONENUMBER), WM_SETTEXT,
			(WPARAM)0, (LPARAM)telephoneNumber);
		SendMessage(GetDlgItem(hBusinessCardBinder, IDC_STATIC_EDITPAXNUMBER), WM_SETTEXT,
			(WPARAM)0, (LPARAM)paxNumber);
		SendMessage(GetDlgItem(hBusinessCardBinder, IDC_STATIC_EDITURL), WM_SETTEXT,
			(WPARAM)0, (LPARAM)url);

		//2.4 찾기 윈도우를 없앤다.
		if (indexes != NULL) {
			free(indexes);
		}
		RemoveProp(hWnd, "PROP_CURRENT");
		RemoveProp(hWnd, "PROP_COUNT");

		EndDialog(hWnd, 0);
	}
	return TRUE;
}

BOOL FindingForm_OnFirstButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	BusinessCard *(*indexes);
	Long current;

	//3. 처음 버튼을 클릭 했을 때
	if (HIWORD(wParam) == BN_CLICKED) {

		indexes = (BusinessCard*(*))GetWindowLongPtr(hWnd, GWLP_USERDATA);
		current = (Long)GetProp(hWnd, "PROP_CURRENT");
		
		//3.1 첫 번째 명함으로 이동한다.
		current = 0;

		SetProp(hWnd, "PROP_CURRENT", (HANDLE)current);

		//3.2 현재 명함을 출력한다.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITNAME), WM_SETTEXT,
			(WPARAM)0, (LPARAM)indexes[current]->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITPOSITION), WM_SETTEXT,
			(WPARAM)0, (LPARAM)indexes[current]->personal.position);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITCELLPHONENUMBER), WM_SETTEXT,
			(WPARAM)0, (LPARAM)indexes[current]->personal.cellphoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITEMAILADDRESS), WM_SETTEXT,
			(WPARAM)0, (LPARAM)indexes[current]->personal.eMailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITCOMPANYNAME), WM_SETTEXT,
			(WPARAM)0, (LPARAM)indexes[current]->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITADDRESS), WM_SETTEXT,
			(WPARAM)0, (LPARAM)indexes[current]->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITTELEPHONENUMBER), WM_SETTEXT,
			(WPARAM)0, (LPARAM)indexes[current]->company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITPAXNUMBER), WM_SETTEXT,
			(WPARAM)0, (LPARAM)indexes[current]->company.paxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITURL), WM_SETTEXT,
			(WPARAM)0, (LPARAM)indexes[current]->company.url);
	}
	return TRUE;
}

BOOL FindingForm_OnPreviousButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	BusinessCard *(*indexes);
	Long current;

	//4. 이전 버튼을 클릭 했을 때
	if (HIWORD(wParam) == BN_CLICKED) {

		indexes = (BusinessCard*(*))GetWindowLongPtr(hWnd, GWLP_USERDATA);
		current = (Long)GetProp(hWnd, "PROP_CURRENT");

		//4.1 이전 명함으로 이동한다.
		current--;
		if (current < 0) {

			current = 0;
		}

		SetProp(hWnd, "PROP_CURRENT", (HANDLE)current);

		//4.2 현재 명함을 출력한다.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITNAME), WM_SETTEXT,
			(WPARAM)0, (LPARAM)indexes[current]->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITPOSITION), WM_SETTEXT,
			(WPARAM)0, (LPARAM)indexes[current]->personal.position);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITCELLPHONENUMBER), WM_SETTEXT,
			(WPARAM)0, (LPARAM)indexes[current]->personal.cellphoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITEMAILADDRESS), WM_SETTEXT,
			(WPARAM)0, (LPARAM)indexes[current]->personal.eMailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITCOMPANYNAME), WM_SETTEXT,
			(WPARAM)0, (LPARAM)indexes[current]->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITADDRESS), WM_SETTEXT,
			(WPARAM)0, (LPARAM)indexes[current]->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITTELEPHONENUMBER), WM_SETTEXT,
			(WPARAM)0, (LPARAM)indexes[current]->company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITPAXNUMBER), WM_SETTEXT,
			(WPARAM)0, (LPARAM)indexes[current]->company.paxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITURL), WM_SETTEXT,
			(WPARAM)0, (LPARAM)indexes[current]->company.url);
	}
	return TRUE;
}

BOOL FindingForm_OnNextButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	BusinessCard *(*indexes);
	Long current;
	Long count;

	//5. 다음 버튼을 클릭 했을 때
	if (HIWORD(wParam) == BN_CLICKED) {

		indexes = (BusinessCard*(*))GetWindowLongPtr(hWnd, GWLP_USERDATA);
		current = (Long)GetProp(hWnd, "PROP_CURRENT");
		count = (Long)GetProp(hWnd, "PROP_COUNT");

		//5.1 다음 명함으로 이동한다.
		current++;
		if (current >= count) {

			current = count - 1;
		}

		SetProp(hWnd, "PROP_CURRENT", (HANDLE)current);

		//5.2 현재 명함을 출력한다.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITNAME), WM_SETTEXT,
			(WPARAM)0, (LPARAM)indexes[current]->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITPOSITION), WM_SETTEXT,
			(WPARAM)0, (LPARAM)indexes[current]->personal.position);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITCELLPHONENUMBER), WM_SETTEXT,
			(WPARAM)0, (LPARAM)indexes[current]->personal.cellphoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITEMAILADDRESS), WM_SETTEXT,
			(WPARAM)0, (LPARAM)indexes[current]->personal.eMailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITCOMPANYNAME), WM_SETTEXT,
			(WPARAM)0, (LPARAM)indexes[current]->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITADDRESS), WM_SETTEXT,
			(WPARAM)0, (LPARAM)indexes[current]->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITTELEPHONENUMBER), WM_SETTEXT,
			(WPARAM)0, (LPARAM)indexes[current]->company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITPAXNUMBER), WM_SETTEXT,
			(WPARAM)0, (LPARAM)indexes[current]->company.paxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITURL), WM_SETTEXT,
			(WPARAM)0, (LPARAM)indexes[current]->company.url);
	}
	return TRUE;
}

BOOL FindingForm_OnLastButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	BusinessCard *(*indexes);
	Long current;
	Long count;

	//6. 끝 버튼을 클릭 했을 때
	if (HIWORD(wParam) == BN_CLICKED) {

		indexes = (BusinessCard*(*))GetWindowLongPtr(hWnd, GWLP_USERDATA);
		current = (Long)GetProp(hWnd, "PROP_CURRENT");
		count = (Long)GetProp(hWnd, "PROP_COUNT");

		//6.1 마지막 명함으로 이동한다.
		current = count - 1;

		SetProp(hWnd, "PROP_CURRENT", (HANDLE)current);

		//6.2 현재 명함을 출력한다.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITNAME), WM_SETTEXT,
			(WPARAM)0, (LPARAM)indexes[current]->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITPOSITION), WM_SETTEXT,
			(WPARAM)0, (LPARAM)indexes[current]->personal.position);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITCELLPHONENUMBER), WM_SETTEXT,
			(WPARAM)0, (LPARAM)indexes[current]->personal.cellphoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITEMAILADDRESS), WM_SETTEXT,
			(WPARAM)0, (LPARAM)indexes[current]->personal.eMailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITCOMPANYNAME), WM_SETTEXT,
			(WPARAM)0, (LPARAM)indexes[current]->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITADDRESS), WM_SETTEXT,
			(WPARAM)0, (LPARAM)indexes[current]->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITTELEPHONENUMBER), WM_SETTEXT,
			(WPARAM)0, (LPARAM)indexes[current]->company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITPAXNUMBER), WM_SETTEXT,
			(WPARAM)0, (LPARAM)indexes[current]->company.paxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITURL), WM_SETTEXT,
			(WPARAM)0, (LPARAM)indexes[current]->company.url);
	}
	return TRUE;
}


BOOL FindingForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	BusinessCard*(*indexes);
	
	indexes = (BusinessCard*(*))GetWindowLongPtr(hWnd, GWLP_USERDATA);
	
	if (indexes != NULL) {
		free(indexes);
	}
	RemoveProp(hWnd, "PROP_CURRENT");
	RemoveProp(hWnd, "PROP_COUNT");

	EndDialog(hWnd, 0);

	return TRUE;
}
