#include "TakeOutForm.h"
#include "BusinessCardBinder.h"
#include "resource1.h"

#pragma warning (disable : 4996)

BOOL CALLBACK TakeOutFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {

	BOOL ret;
	
	switch (message){

	case WM_INITDIALOG:
		ret = TakeOutForm_OnInitDialog(hWnd, wParam, lParam);
		break;
	case WM_CLOSE:
		ret = TakeOutForm_OnClose(hWnd, wParam, lParam);
		break;
	default:
		ret = FALSE;
		break;
	}
	return ret;
}
	
BOOL TakeOutForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam) {	

	//1.꺼내기 윈도우가 생성될 때
	HWND hBusinessCardBinder;
	BusinessCardBinder *businessCardBinder;
	BusinessCard businessCard;

	//1.1 명함철 윈도우를 찾는다.
	hBusinessCardBinder = FindWindow("#32770", "명함철");

	//1.2 명함철 윈도우의 명함철에서 꺼낸다.
	businessCardBinder = 
		(BusinessCardBinder*)GetWindowLongPtr(hBusinessCardBinder, GWLP_USERDATA);

	businessCard = TakeOut(businessCardBinder, businessCardBinder->current);

	//1.3 꺼낸 명함을 출력한다.
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITNAME), WM_SETTEXT,
		(WPARAM)0, (LPARAM)businessCard.personal.name);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITPOSITION), WM_SETTEXT,
		(WPARAM)0, (LPARAM)businessCard.personal.position);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITCELLPHONENUMBER), WM_SETTEXT,
		(WPARAM)0, (LPARAM)businessCard.personal.cellphoneNumber);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITEMAILADDRESS), WM_SETTEXT,
		(WPARAM)0, (LPARAM)businessCard.personal.eMailAddress);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITCOMPANYNAME), WM_SETTEXT,
		(WPARAM)0, (LPARAM)businessCard.company.name);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITADDRESS), WM_SETTEXT,
		(WPARAM)0, (LPARAM)businessCard.company.address);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITTELEPHONENUMBER), WM_SETTEXT,
		(WPARAM)0, (LPARAM)businessCard.company.telephoneNumber);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITPAXNUMBER), WM_SETTEXT,
		(WPARAM)0, (LPARAM)businessCard.company.paxNumber);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITURL), WM_SETTEXT,
		(WPARAM)0, (LPARAM)businessCard.company.url);

	//1.4 명함철 윈도우의 명함철에 명함이 있으면
	if (businessCardBinder->current != NULL) {

		//1.4.1 명함철 윈도우에서 현재 명함을 출력한다.
		SendMessage(GetDlgItem(hBusinessCardBinder, IDC_STATIC_EDITNAME), WM_SETTEXT,
			(WPARAM)0, (LPARAM)businessCardBinder->current->personal.name);
		SendMessage(GetDlgItem(hBusinessCardBinder, IDC_STATIC_EDITPOSITION), WM_SETTEXT,
			(WPARAM)0, (LPARAM)businessCardBinder->current->personal.position);
		SendMessage(GetDlgItem(hBusinessCardBinder, IDC_STATIC_EDITCELLPHONENUMBER), WM_SETTEXT,
			(WPARAM)0, (LPARAM)businessCardBinder->current->personal.cellphoneNumber);
		SendMessage(GetDlgItem(hBusinessCardBinder, IDC_STATIC_EDITEMAILADDRESS), WM_SETTEXT,
			(WPARAM)0, (LPARAM)businessCardBinder->current->personal.eMailAddress);
		SendMessage(GetDlgItem(hBusinessCardBinder, IDC_STATIC_EDITCOMPANYNAME), WM_SETTEXT,
			(WPARAM)0, (LPARAM)businessCardBinder->current->company.name);
		SendMessage(GetDlgItem(hBusinessCardBinder, IDC_STATIC_EDITADDRESS), WM_SETTEXT,
			(WPARAM)0, (LPARAM)businessCardBinder->current->company.address);
		SendMessage(GetDlgItem(hBusinessCardBinder, IDC_STATIC_EDITTELEPHONENUMBER), WM_SETTEXT,
			(WPARAM)0, (LPARAM)businessCardBinder->current->company.telephoneNumber);
		SendMessage(GetDlgItem(hBusinessCardBinder, IDC_STATIC_EDITPAXNUMBER), WM_SETTEXT,
			(WPARAM)0, (LPARAM)businessCardBinder->current->company.paxNumber);
		SendMessage(GetDlgItem(hBusinessCardBinder, IDC_STATIC_EDITURL), WM_SETTEXT,
			(WPARAM)0, (LPARAM)businessCardBinder->current->company.url);
	}
	else {

		SendMessage(GetDlgItem(hBusinessCardBinder, IDC_STATIC_EDITNAME), WM_SETTEXT,
			(WPARAM)0, (LPARAM)"");
		SendMessage(GetDlgItem(hBusinessCardBinder, IDC_STATIC_EDITPOSITION), WM_SETTEXT,
			(WPARAM)0, (LPARAM)"");
		SendMessage(GetDlgItem(hBusinessCardBinder, IDC_STATIC_EDITCELLPHONENUMBER), WM_SETTEXT,
			(WPARAM)0, (LPARAM)"");
		SendMessage(GetDlgItem(hBusinessCardBinder, IDC_STATIC_EDITEMAILADDRESS), WM_SETTEXT,
			(WPARAM)0, (LPARAM)"");
		SendMessage(GetDlgItem(hBusinessCardBinder, IDC_STATIC_EDITCOMPANYNAME), WM_SETTEXT,
			(WPARAM)0, (LPARAM)"");
		SendMessage(GetDlgItem(hBusinessCardBinder, IDC_STATIC_EDITADDRESS), WM_SETTEXT,
			(WPARAM)0, (LPARAM)"");
		SendMessage(GetDlgItem(hBusinessCardBinder, IDC_STATIC_EDITTELEPHONENUMBER), WM_SETTEXT,
			(WPARAM)0, (LPARAM)"");
		SendMessage(GetDlgItem(hBusinessCardBinder, IDC_STATIC_EDITPAXNUMBER), WM_SETTEXT,
			(WPARAM)0, (LPARAM)"");
		SendMessage(GetDlgItem(hBusinessCardBinder, IDC_STATIC_EDITURL), WM_SETTEXT,
			(WPARAM)0, (LPARAM)"");
	}
	return TRUE;
}

BOOL TakeOutForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	//2. 닫기 컨트롤을 클릭했을 때
	int message;
	BusinessCard businessCard;
	HWND hBusinessCardBinder;
	BusinessCardBinder *businessCardBinder;
	BusinessCard *current;

	//2.1 메시지 박스를 출력한다.
	message = MessageBox(hWnd, "넣으시겠습니까?", "알림", MB_YESNOCANCEL);

	//2.2 예 버튼을 클릭했을 때
	if (message == IDYES) {	

		//2.2.1 명함을 읽는다.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITNAME), WM_GETTEXT,
			(WPARAM)16, (LPARAM)businessCard.personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITPOSITION), WM_GETTEXT,
			(WPARAM)16, (LPARAM)businessCard.personal.position);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITCELLPHONENUMBER), WM_GETTEXT,
			(WPARAM)16, (LPARAM)businessCard.personal.cellphoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITEMAILADDRESS), WM_GETTEXT,
			(WPARAM)128, (LPARAM)businessCard.personal.eMailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITCOMPANYNAME), WM_GETTEXT,
			(WPARAM)32, (LPARAM)businessCard.company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITADDRESS), WM_GETTEXT,
			(WPARAM)64, (LPARAM)businessCard.company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITTELEPHONENUMBER), WM_GETTEXT,
			(WPARAM)16, (LPARAM)businessCard.company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITPAXNUMBER), WM_GETTEXT,
			(WPARAM)16, (LPARAM)businessCard.company.paxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITURL), WM_GETTEXT,
			(WPARAM)128, (LPARAM)businessCard.company.url);
		businessCard.next = NULL;

		//2.2.2 명함철 윈도우를 찾는다.
		hBusinessCardBinder = FindWindow("#32770", "명함철");
		
		//2.2.3 명함철 윈도우의 명함철에 넣는다.
		businessCardBinder = 
			(BusinessCardBinder*)GetWindowLongPtr(hBusinessCardBinder, GWLP_USERDATA);

		current = TakeIn(businessCardBinder, businessCard);

		//2.2.4 명함철 윈도우에서 현재 명함을 출력한다.
		SendMessage(GetDlgItem(hBusinessCardBinder, IDC_STATIC_EDITNAME), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->personal.name);
		SendMessage(GetDlgItem(hBusinessCardBinder, IDC_STATIC_EDITPOSITION), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->personal.position);
		SendMessage(GetDlgItem(hBusinessCardBinder, IDC_STATIC_EDITCELLPHONENUMBER), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->personal.cellphoneNumber);
		SendMessage(GetDlgItem(hBusinessCardBinder, IDC_STATIC_EDITEMAILADDRESS), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->personal.eMailAddress);
		SendMessage(GetDlgItem(hBusinessCardBinder, IDC_STATIC_EDITCOMPANYNAME), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->company.name);
		SendMessage(GetDlgItem(hBusinessCardBinder, IDC_STATIC_EDITADDRESS), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->company.address);
		SendMessage(GetDlgItem(hBusinessCardBinder, IDC_STATIC_EDITTELEPHONENUMBER), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->company.telephoneNumber);
		SendMessage(GetDlgItem(hBusinessCardBinder, IDC_STATIC_EDITPAXNUMBER), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->company.paxNumber);
		SendMessage(GetDlgItem(hBusinessCardBinder, IDC_STATIC_EDITURL), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->company.url);

		//2.2.5 닫기 윈도우를 없앤다.
		EndDialog(hWnd, 0);
	}
	else if (message == IDNO) {
		EndDialog(hWnd, 0);
	}
	return TRUE;
}

