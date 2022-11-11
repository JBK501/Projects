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

	//1.������ �����찡 ������ ��
	HWND hBusinessCardBinder;
	BusinessCardBinder *businessCardBinder;
	BusinessCard businessCard;

	//1.1 ����ö �����츦 ã�´�.
	hBusinessCardBinder = FindWindow("#32770", "����ö");

	//1.2 ����ö �������� ����ö���� ������.
	businessCardBinder = 
		(BusinessCardBinder*)GetWindowLongPtr(hBusinessCardBinder, GWLP_USERDATA);

	businessCard = TakeOut(businessCardBinder, businessCardBinder->current);

	//1.3 ���� ������ ����Ѵ�.
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

	//1.4 ����ö �������� ����ö�� ������ ������
	if (businessCardBinder->current != NULL) {

		//1.4.1 ����ö �����쿡�� ���� ������ ����Ѵ�.
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

	//2. �ݱ� ��Ʈ���� Ŭ������ ��
	int message;
	BusinessCard businessCard;
	HWND hBusinessCardBinder;
	BusinessCardBinder *businessCardBinder;
	BusinessCard *current;

	//2.1 �޽��� �ڽ��� ����Ѵ�.
	message = MessageBox(hWnd, "�����ðڽ��ϱ�?", "�˸�", MB_YESNOCANCEL);

	//2.2 �� ��ư�� Ŭ������ ��
	if (message == IDYES) {	

		//2.2.1 ������ �д´�.
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

		//2.2.2 ����ö �����츦 ã�´�.
		hBusinessCardBinder = FindWindow("#32770", "����ö");
		
		//2.2.3 ����ö �������� ����ö�� �ִ´�.
		businessCardBinder = 
			(BusinessCardBinder*)GetWindowLongPtr(hBusinessCardBinder, GWLP_USERDATA);

		current = TakeIn(businessCardBinder, businessCard);

		//2.2.4 ����ö �����쿡�� ���� ������ ����Ѵ�.
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

		//2.2.5 �ݱ� �����츦 ���ش�.
		EndDialog(hWnd, 0);
	}
	else if (message == IDNO) {
		EndDialog(hWnd, 0);
	}
	return TRUE;
}

