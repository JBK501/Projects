#include "TakeInForm.h"
#include "BusinessCardBinder.h"
#include "resource1.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma warning (disable : 4996)

BOOL CALLBACK TakeInFormProc(HWND hWnd, UINT message,
	WPARAM wParam, LPARAM lParam) {

	BOOL ret;

	switch (message){

	case WM_INITDIALOG:
		ret = TakeInForm_OnInitDialog(hWnd, wParam, lParam);
		break;
	case WM_COMMAND:
		ret = TakeInForm_OnCommand(hWnd, wParam, lParam);
		break;
	case WM_CLOSE:
		ret = TakeInForm_OnClose(hWnd, wParam, lParam);
		break;
	default:
		ret = FALSE;
		break;
	}
	return ret;
}

BOOL TakeInForm_OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	BOOL ret;

	switch (LOWORD(wParam)){

	case IDC_EDIT_COMPANYNAME:
		ret = TakeInForm_OnCompanyNameFocused(hWnd, wParam, lParam);
		break;
	case IDC_BUTTON_TAKEIN:
		ret = TakeInForm_OnTakeInButtonClicked(hWnd, wParam, lParam);
		break;
	default:
		ret = FALSE;
		break;
	}
	return ret;
}

BOOL TakeInForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	//1. �ֱ� �����찡 ������ ��
	TCHAR positions[][16] = { "����","���","�븮","����","����",
		"����","����","����" };
	TCHAR domains[][64] = { "naver.com","hanmail.net","gmail.com",
		"nate.com","yahoo.com" };
	Long i;

	//1.1 ���� �޺��ڽ��� �׸���� �߰��Ѵ�.
	for (i = 0; i < sizeof(positions) / sizeof(positions[0]); i++) {

		SendMessage(GetDlgItem(hWnd, IDC_COMBO_POSITION), CB_ADDSTRING, (WPARAM)0,
			(LPARAM)positions[i]);
	}

	//1.2 �����θ� �޺��ڽ��� �׸���� �߰��Ѵ�
	for (i = 0; i < sizeof(domains) / sizeof(domains[0]); i++) {

		SendMessage(GetDlgItem(hWnd, IDC_COMBO_DOMAIN), CB_ADDSTRING, (WPARAM)0,
			(LPARAM)domains[i]);
	}
	return TRUE;
}

BOOL TakeInForm_OnCompanyNameFocused(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	TCHAR companyName[32];
	HWND hBusinessCardBinder;
	BusinessCardBinder *businessCardBinder;
	BusinessCard *previous = NULL;
	BusinessCard *index;

	//2. ��ȣ�� ��Ŀ���� �� ��
	if (HIWORD(wParam) == EN_KILLFOCUS) {

		//2.1 ��ȣ�� �д´�.
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_COMPANYNAME), WM_GETTEXT,
			(WPARAM)32, (LPARAM)companyName);

		//2.2 ����ö �����츦 ã�´�.
		hBusinessCardBinder = FindWindow("#32770", "����ö");


		//2.3 ����ö �������� ����ö���� ��ȣ�� ã�´�.
		businessCardBinder =
			(BusinessCardBinder *)GetWindowLongPtr(hBusinessCardBinder, GWLP_USERDATA);

		index = FindByCompanyName(businessCardBinder, companyName);

		//2.3.1 ã������
		if (index!=NULL) {

			//2.3.1.1 �ּ�, ��ȭ��ȣ, �ѽ���ȣ, url�� ����Ѵ�.
			SendMessage(GetDlgItem(hWnd, IDC_EDIT_ADDRESS), WM_SETTEXT,
				(WPARAM)0, (LPARAM)index->company.address);
			SendMessage(GetDlgItem(hWnd, IDC_EDIT_TELEPHONENUMBER), WM_SETTEXT,
				(WPARAM)0, (LPARAM)index->company.telephoneNumber);
			SendMessage(GetDlgItem(hWnd, IDC_EDIT_PAXNUMBER), WM_SETTEXT,
				(WPARAM)0, (LPARAM)index->company.paxNumber);
			SendMessage(GetDlgItem(hWnd, IDC_EDIT_URL), WM_SETTEXT,
				(WPARAM)0, (LPARAM)index->company.url);
		}
	}
	return TRUE;
}


BOOL TakeInForm_OnTakeInButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	TCHAR name[16];
	TCHAR position[16];
	TCHAR cellphoneNumber[16];
	TCHAR id[64];
	TCHAR domain[32];
	TCHAR eMailAddress[128];
	TCHAR companyName[32];
	TCHAR address[64];
	TCHAR telephoneNumber[16];
	TCHAR paxNumber[16];
	TCHAR url[128];
	BusinessCard businessCard;
	HWND hBusinessCardBinder;
	BusinessCardBinder *businessCardBinder;
	BusinessCard *current;

	//3. �ֱ� ��ư�� Ŭ�� ���� ��
	if (HIWORD(wParam) == BN_CLICKED) {

		//3.1 ���ΰ� ȸ�� �����͸� �д´�.
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_NAME), WM_GETTEXT, 
			(WPARAM)16, (LPARAM)name);
		SendMessage(GetDlgItem(hWnd, IDC_COMBO_POSITION), WM_GETTEXT,
			(WPARAM)16, (LPARAM)position);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_CELLPHONENUMBER), WM_GETTEXT,
			(WPARAM)16, (LPARAM)cellphoneNumber);

		SendMessage(GetDlgItem(hWnd, IDC_EDIT_ID), WM_GETTEXT,
			(WPARAM)64, (LPARAM)id);
		SendMessage(GetDlgItem(hWnd, IDC_COMBO_DOMAIN), WM_GETTEXT,
			(WPARAM)32, (LPARAM)domain);
		sprintf(eMailAddress, "%s@%s", id, domain);

		SendMessage(GetDlgItem(hWnd, IDC_EDIT_COMPANYNAME), WM_GETTEXT,
			(WPARAM)32, (LPARAM)companyName);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_ADDRESS), WM_GETTEXT,
			(WPARAM)64, (LPARAM)address);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_TELEPHONENUMBER), WM_GETTEXT,
			(WPARAM)16, (LPARAM)telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_PAXNUMBER), WM_GETTEXT,
			(WPARAM)16, (LPARAM)paxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_URL), WM_GETTEXT,
			(WPARAM)128, (LPARAM)url);

		//3.2 ������ �����.
		strcpy(businessCard.personal.name, name);
		strcpy(businessCard.personal.position, position);
		strcpy(businessCard.personal.cellphoneNumber, cellphoneNumber);
		strcpy(businessCard.personal.eMailAddress, eMailAddress);
		strcpy(businessCard.company.name,companyName);
		strcpy(businessCard.company.address, address);
		strcpy(businessCard.company.telephoneNumber, telephoneNumber);
		strcpy(businessCard.company.paxNumber, paxNumber);
		strcpy(businessCard.company.url, url);
		

		//3.3 ����ö �����츦 ã�´�.
		hBusinessCardBinder = FindWindow("#32770", "����ö");

		//3.4 ����ö �������� ����ö���� �ִ´�.
		businessCardBinder = 
			(BusinessCardBinder*)GetWindowLongPtr(hBusinessCardBinder, GWLP_USERDATA);

		current = TakeIn(businessCardBinder, businessCard);

		//3.5 ����ö �����쿡�� ���Կ� ����Ѵ�.
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

		EndDialog(hWnd, 0);
	}
	return TRUE;
}


BOOL TakeInForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	//4.1 �ֱ� �����츦 ���ش�.
	EndDialog(hWnd, 0);

	return TRUE;
}