#include "BusinessCardBinderForm.h"
#include "BusinessCardBinder.h"
#include "resource1.h"
#include "TakeInForm.h"
#include "FindingForm.h"
#include "TakeOutForm.h"
#include <stdio.h>
#include <stdlib.h>


#pragma warning (disable : 4996)

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine,
	int nCmdShow) {

	int response;
	response = DialogBox(hInstance, MAKEINTRESOURCE(IDD_BUSINESSCARDBINDERFORM), NULL,
		BusinessCardBinderFormProc);
	return response;
}

BOOL CALLBACK BusinessCardBinderFormProc(HWND hWnd, UINT message, 
	WPARAM wParam, LPARAM lParam) {

	BOOL ret;
	
	switch (message) {

	case WM_INITDIALOG:
		ret = BusinessCardBinderForm_OnInitDialog(hWnd, wParam, lParam);
		break;
	case WM_COMMAND:
		ret = BusinessCardBinderForm_OnCommand(hWnd, wParam, lParam);
		break;
	case WM_CLOSE:
		ret = BusinessCardBinderForm_OnClose(hWnd, wParam, lParam);
		break;
	default:
		ret = FALSE;
		break;
	}

	return ret;
}

BOOL BusinessCardBinderForm_OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	BOOL ret;
	switch (LOWORD(wParam)){

	case IDC_BUTTON_TAKEIN:
		ret = BusinessCardBinderForm_OnTakeInButtonClicked(hWnd,wParam,lParam);
		break;
	case IDC_BUTTON_FIND:
		ret = BusinessCardBinderForm_OnFindButtonClicked(hWnd, wParam, lParam);
		break;
	case IDC_BUTTON_TAKEOUT:
		ret = BusinessCardBinderForm_OnTakeOutButtonClicked(hWnd, wParam, lParam);
		break;
#if 0
	case IDC_BUTTON_ARRANGE:
		ret = BusinessCardBinderForm_OnArrangeButtonClicked(hWnd, wParam, lParam);
		break;
#endif
	case IDC_BUTTON_FIRST:
		ret = BusinessCardBinderForm_OnFirstButtonClicked(hWnd, wParam, lParam);
		break;
	case IDC_BUTTON_PREVIOUS:
		ret = BusinessCardBinderForm_OnPreviousButtonClicked(hWnd, wParam, lParam);
		break;
	case IDC_BUTTON_NEXT:
		ret = BusinessCardBinderForm_OnNextButtonClicked(hWnd, wParam, lParam);
		break;
	case IDC_BUTTON_LAST:
		ret = BusinessCardBinderForm_OnLastButtonClicked(hWnd, wParam, lParam);
		break;
	default:
		ret = FALSE;
		break;
	}
	return ret;
}

BOOL BusinessCardBinderForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	
	//1.윈도우가 생성될 때
	BusinessCardBinder *businessCardBinder;
	BusinessCard *current;
	Long count;

	//1.1 명함철을 만든다.
	businessCardBinder = (BusinessCardBinder*)malloc(sizeof(BusinessCardBinder));
	BusinessCardBinder_Create(businessCardBinder);

	SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG)businessCardBinder);

	//1.2 명함철에서 적재한다.
	count = Load(businessCardBinder);

	if (count > 0) {

		//1.3 명함철에서 첫 번째 명함으로 이동한다.
		current = BusinessCardBinder_First(businessCardBinder);

		//1.4 현재 명함을 출력한다.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITNAME), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITPOSITION), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->personal.position);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITCELLPHONENUMBER), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->personal.cellphoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITEMAILADDRESS), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->personal.eMailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITCOMPANYNAME), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITADDRESS), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITTELEPHONENUMBER), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITPAXNUMBER), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->company.paxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITURL), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->company.url);
	}
	return TRUE;
}

BOOL BusinessCardBinderForm_OnFirstButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	
	BusinessCardBinder *businessCardBinder;
	BusinessCard *current;

	if (HIWORD(wParam) == BN_CLICKED) {	//2. 처음버튼을 클릭했을 때

		businessCardBinder = (BusinessCardBinder*)GetWindowLongPtr(hWnd, GWLP_USERDATA);

		//2.1 명함철에서 첫 번째 명함으로 이동한다.
		current = BusinessCardBinder_First(businessCardBinder);

		//2.2 현재 명함을 출력한다.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITNAME), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITPOSITION), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->personal.position);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITCELLPHONENUMBER), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->personal.cellphoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITEMAILADDRESS), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->personal.eMailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITCOMPANYNAME), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITADDRESS), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITTELEPHONENUMBER), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITPAXNUMBER), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->company.paxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITURL), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->company.url);
	}
	return TRUE;
}

BOOL BusinessCardBinderForm_OnPreviousButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	BusinessCardBinder *businessCardBinder;
	BusinessCard *current;

	if (HIWORD(wParam) == BN_CLICKED) {	//3. 이전버튼을 클릭했을 때

		businessCardBinder = (BusinessCardBinder*)GetWindowLongPtr(hWnd, GWLP_USERDATA);

		//3.1 명함철에서 이전 명함으로 이동한다.
		current = BusinessCardBinder_Previous(businessCardBinder);

		//3.2 이전 명함을 출력한다.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITNAME), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITPOSITION), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->personal.position);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITCELLPHONENUMBER), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->personal.cellphoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITEMAILADDRESS), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->personal.eMailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITCOMPANYNAME), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITADDRESS), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITTELEPHONENUMBER), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITPAXNUMBER), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->company.paxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITURL), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->company.url);
	}
	return TRUE;
}

BOOL BusinessCardBinderForm_OnNextButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	BusinessCardBinder *businessCardBinder;
	BusinessCard *current;

	if (HIWORD(wParam) == BN_CLICKED) {	//4. 다음버튼을 클릭했을 때

		businessCardBinder = (BusinessCardBinder*)GetWindowLongPtr(hWnd, GWLP_USERDATA);

		//4.1 명함철에서 다음 명함으로 이동한다.
		current = BusinessCardBinder_Next(businessCardBinder);

		//4.2 다음 명함을 출력한다.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITNAME), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITPOSITION), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->personal.position);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITCELLPHONENUMBER), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->personal.cellphoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITEMAILADDRESS), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->personal.eMailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITCOMPANYNAME), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITADDRESS), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITTELEPHONENUMBER), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITPAXNUMBER), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->company.paxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITURL), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->company.url);
	}
	return TRUE;
}

BOOL BusinessCardBinderForm_OnLastButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	BusinessCardBinder *businessCardBinder;
	BusinessCard *current;

	if (HIWORD(wParam) == BN_CLICKED) {	//5. 끝버튼을 클릭했을 때

		businessCardBinder = (BusinessCardBinder*)GetWindowLongPtr(hWnd, GWLP_USERDATA);

		//5.1 명함철에서 마지막 명함으로 이동한다.
		current = BusinessCardBinder_Last(businessCardBinder);

		//5.2 마지막 명함을 출력한다.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITNAME), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITPOSITION), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->personal.position);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITCELLPHONENUMBER), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->personal.cellphoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITEMAILADDRESS), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->personal.eMailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITCOMPANYNAME), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITADDRESS), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITTELEPHONENUMBER), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITPAXNUMBER), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->company.paxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITURL), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->company.url);
	}
	return TRUE;
}


BOOL BusinessCardBinderForm_OnTakeInButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	//6. 넣기 버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED) {

		//6.1 넣기 윈도우를 출력한다.
		DialogBox((HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
			MAKEINTRESOURCE(IDD_TAKEINFORM), NULL, TakeInFormProc);
	}
	return TRUE;
}



BOOL BusinessCardBinderForm_OnFindButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	//7. 찾기 버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED) {

		//7. 찾기 윈도우를 출력한다.
		DialogBox((HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
			MAKEINTRESOURCE(IDD_FINDINGFORM), NULL, FindingFormProc);
	}
	return TRUE;
}



BOOL BusinessCardBinderForm_OnTakeOutButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	//8. 꺼내기 버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED) {

		//8.1 꺼내기 윈도우를 출력한다.
		DialogBox((HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
			MAKEINTRESOURCE(IDD_TAKEOUTFORM), NULL, TakeOutFormProc);
	}
	return TRUE;
}

#if 0
BOOL BusinessCardBinderForm_OnArrangeButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	BusinessCardBinder *businessCardBinder;
	BusinessCard *current;

	if (HIWORD(wParam) == BN_CLICKED) {	//9. 정리하기버튼을 클릭했을 때

		businessCardBinder = (BusinessCardBinder*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
		
		//9.1 명함철에서 정리한다.
		Arrange(businessCardBinder);

		//9.2 명함철에서 첫 번째 명함으로 이동한다.
		current = BusinessCardBinder_First(businessCardBinder);

		//9.3 현재 명함을 출력한다.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITNAME), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITPOSITION), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->personal.position);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITCELLPHONENUMBER), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->personal.cellphoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITEMAILADDRESS), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->personal.eMailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITCOMPANYNAME), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITADDRESS), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITTELEPHONENUMBER), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITPAXNUMBER), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->company.paxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITURL), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->company.url);
	}
	return TRUE;
}
#endif

BOOL BusinessCardBinderForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	//10. 닫기 컨트롤을 클릭했을 때
	BusinessCardBinder *businessCardBinder;
	
	businessCardBinder = (BusinessCardBinder*)GetWindowLongPtr(hWnd, GWLP_USERDATA);

	if (businessCardBinder != NULL) {

		//10.1 명함철에서 저장한다.
		Save(businessCardBinder);

		//10.2 명함철을 없앤다.
		BusinessCardBinder_Destroy(businessCardBinder);

		free(businessCardBinder);
	}
	//10.3 윈도우를 없앤다.
	EndDialog(hWnd, 0);

	return TRUE;
}