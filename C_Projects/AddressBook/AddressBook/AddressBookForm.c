#include "AddressBookForm.h"
#include "AddressBook.h"
#include "resource.h"
#include "FindingForm.h"
#include <stdio.h>
#include <stdlib.h>
#include <Commctrl.h>
#include <WinUser.h>


#pragma warning (disable:4996)

int WINAPI WinMain(HINSTANCE hInstance,	HINSTANCE hPrevInstance, LPSTR lpCmdLine,
	int nCmdShow) {

	int response;
	response = DialogBox(hInstance, MAKEINTRESOURCE(IDD_ADDRESSBOOKFORM), NULL,
		AddressBookFormProc);
	return response;
}

BOOL CALLBACK AddressBookFormProc(HWND hWnd, UINT message, WPARAM wParam,
	LPARAM lParam) {

	BOOL ret;
	switch (message){

	case WM_INITDIALOG:
		ret = AddressBookForm_OnInitDialog(hWnd, wParam, lParam);
		break;
	case WM_COMMAND:
		ret = AddressBookForm_OnCommand(hWnd, wParam, lParam);
		break;
	case WM_NOTIFY:
		ret = AddressBookForm_OnNotify(hWnd, wParam, lParam);
		break;
	case WM_CLOSE:
		ret = AddressBookForm_OnClose(hWnd, wParam, lParam);
		break;
	default:
		ret = FALSE;
		break;
	}
	return ret;
}

BOOL AddressBookForm_OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	BOOL ret;

	switch (LOWORD(wParam)){

	case IDC_BUTTON_RECORD:
		ret = AddressBookForm_OnRecordButtonClicked(hWnd, wParam, lParam);
		break;
	case IDC_BUTTON_FIND:
		ret = AddressBookForm_OnFindButtonClicked(hWnd, wParam, lParam);
		break;
	case IDC_BUTTON_CORRECT:
		ret = AddressBookForm_OnCorrectButtonClicked(hWnd, wParam, lParam);
		break;
	case IDC_BUTTON_ERASE:
		ret = AddressBookForm_OnEraseButtonClicked(hWnd, wParam, lParam);
		break;
	case IDC_BUTTON_ARRANGE:
		ret = AddressBookForm_OnArrangeButtonClicked(hWnd, wParam, lParam);
		break;
	default:
		ret = FALSE;
		break;
	}
	return ret;
}

BOOL AddressBookForm_OnNotify(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	BOOL ret;
	switch ((int)wParam){

	case IDC_LIST_PERSONALS:
		ret = AddressBookForm_OnListViewItemDoubleClicked(hWnd, wParam, lParam);
		break;
	default:
		ret = FALSE;
		break;
	}
	return ret;
}

BOOL AddressBookForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	
	//1.�����찡 ������ ��
	AddressBook *addressBook;
	Personal personal;
	Long count;
	LVCOLUMN column = { 0, };
	LVITEM item = { 0, };
	TCHAR number[64];
	Long i = 0;
	
	//1.1 �ּҷ��� �����.
	addressBook = (AddressBook*)malloc(sizeof(AddressBook));
	AddressBook_Create(addressBook,10000);

	//OnInitDialog�� ������ �ּҷ� ���
	SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)addressBook);
	
	//1.2 �ּҷϿ��� �����ϴ�.
	count = Load(addressBook);

	//���� ����
	SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS),
		LVM_SETEXTENDEDLISTVIEWSTYLE,
		LVS_EX_FULLROWSELECT,
		LVS_EX_FULLROWSELECT);

	//1.3 ����Ʈ����Ʈ���� ����� �����.
	column.mask = LVCF_WIDTH | LVCF_TEXT; //����� �� ����
	column.cx = 50;
	column.pszText = "��ȣ";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_INSERTCOLUMN, (WPARAM)0,
		(LPARAM)&column);

	column.cx = 100;
	column.pszText = "����";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_INSERTCOLUMN, (WPARAM)1,
		(LPARAM)&column);

	column.cx = 140;
	column.pszText = "�ּ�";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_INSERTCOLUMN, (WPARAM)2,
		(LPARAM)&column);

	column.cx = 120;
	column.pszText = "��ȭ��ȣ";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_INSERTCOLUMN, (WPARAM)3,
		(LPARAM)&column);

	column.cx = 170;
	column.pszText = "�̸����ּ�";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_INSERTCOLUMN, (WPARAM)4,
		(LPARAM)&column);

	//1.4 ������ ������ŭ ����Ʈ�� ��Ʈ�ѿ� �׸��� �߰��Ѵ�.
	item.mask = LVIF_TEXT;
	while (i < count) {
		item.iItem = i;
		item.iSubItem = 0;
		sprintf(number, "%d", i + 1);
		item.pszText = number;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_INSERTITEM, (WPARAM)0,
			(LPARAM)&item);

		personal = AddressBook_GetAt(addressBook, i);

		item.iSubItem = 1;
		item.pszText = personal.name;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT, (WPARAM)i,
			(LPARAM)&item);

		item.iSubItem = 2;
		item.pszText = personal.address;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT, (WPARAM)i,
			(LPARAM)&item);

		item.iSubItem = 3;
		item.pszText = personal.telephoneNumber;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT, (WPARAM)i,
			(LPARAM)&item);

		item.iSubItem = 4;
		item.pszText = personal.eMailAddress;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT, (WPARAM)i,
			(LPARAM)&item);

		i++;
	}
	return TRUE;
}

BOOL AddressBookForm_OnListViewItemDoubleClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	
	TCHAR name[11];
	TCHAR address[64];
	TCHAR telephoneNumber[12];
	TCHAR eMailAddress[64];
	Long index;
	LVITEM item = { 0, };

	if (((LPNMHDR)lParam)->code == NM_DBLCLK) {	

		//4. ����Ʈ�� ��Ʈ���� �׸��� ���� Ŭ�� ���� ��
		
		//4.1 ����Ʈ�� ��Ʈ�� �ش� �׸��� ��ġ�� �д´�.
		index = SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_GETSELECTIONMARK, (WPARAM)0, (LPARAM)0);

		//4.2 ����Ʈ�� ��Ʈ�� �ش� ��ġ�� ����, �ּ�, ��ȭ��ȣ, �̸��� �ּҸ� �д´�.
		item.mask = LVIF_TEXT;
		item.iItem = index;

		item.iSubItem = 1;
		item.pszText = name;
		item.cchTextMax = 11;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_GETITEMTEXT, 
			(WPARAM)index, (LPARAM)&item);

		item.iSubItem = 2;
		item.pszText = address;
		item.cchTextMax = 64;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_GETITEMTEXT,
			(WPARAM)index, (LPARAM)&item);

		item.iSubItem = 3;
		item.pszText = telephoneNumber;
		item.cchTextMax = 12;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_GETITEMTEXT,
			(WPARAM)index, (LPARAM)&item);

		item.iSubItem = 4;
		item.pszText = eMailAddress;
		item.cchTextMax = 64;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_GETITEMTEXT,
			(WPARAM)index, (LPARAM)&item);

		//4.3 ���ο� ����.
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_NAME), WM_SETTEXT, 
			(WPARAM)0, (LPARAM)name);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_ADDRESS), WM_SETTEXT, 
			(WPARAM)0, (LPARAM)address);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_TELEPHONENUMBER), WM_SETTEXT, 
			(WPARAM)0, (LPARAM)telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_EMAILADDRESS), WM_SETTEXT, 
			(WPARAM)0, (LPARAM)eMailAddress);
	}
	return TRUE;
}

BOOL AddressBookForm_OnRecordButtonClicked(HWND hWnd, WPARAM wParam, 
	LPARAM lParam) {

	AddressBook *addressBook;
	TCHAR name[11];
	TCHAR address[64];
	TCHAR telephoneNumber[12];
	TCHAR eMailAddress[64];
	Long index;
	Personal personal;
	LVITEM item = { 0, };
	TCHAR number[64];

	if (HIWORD(wParam) == BN_CLICKED) {//2. �����ϱ� ��ư�� Ŭ������ ��

		//2.1 ����, �ּ�, ��ȭ��ȣ, �̸��� �ּҸ� �д´�.
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_NAME), WM_GETTEXT, (WPARAM)11, (LPARAM)name);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_ADDRESS), WM_GETTEXT, (WPARAM)64, (LPARAM)address);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_TELEPHONENUMBER), WM_GETTEXT, (WPARAM)12, (LPARAM)telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_EMAILADDRESS), WM_GETTEXT, (WPARAM)64, (LPARAM)eMailAddress);

		//2.2 �ּҷϿ��� �����Ѵ�.
		addressBook = (AddressBook*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
		index = Record(addressBook, name, address, telephoneNumber, eMailAddress);

		//2.3 ����Ʈ�� ��Ʈ�ѿ� �׸��� �߰��Ѵ�.
		item.mask = LVIF_TEXT;
		item.iItem = index;

		item.iSubItem = 0;
		sprintf(number, "%d", index + 1);
		item.pszText = number;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_INSERTITEM, (WPARAM)0, (LPARAM)&item);

		personal = AddressBook_GetAt(addressBook, index);

		item.iSubItem = 1;
		item.pszText = personal.name;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);

		item.iSubItem = 2;
		item.pszText = personal.address;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);

		item.iSubItem = 3;
		item.pszText = personal.telephoneNumber;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);

		item.iSubItem = 4;
		item.pszText = personal.eMailAddress;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
	}
	return TRUE;
}

BOOL AddressBookForm_OnFindButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	if (HIWORD(wParam) == BN_CLICKED) {

		DialogBox((HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
			MAKEINTRESOURCE(IDD_FINDINGFORM), NULL, FindingFormProc);
	}
	return TRUE;
}

BOOL AddressBookForm_OnCorrectButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	AddressBook *addressBook;
	TCHAR address[64];
	TCHAR telephoneNumber[12];
	TCHAR eMailAddress[64];
	Long index;
	Personal personal;
	LVITEM item = { 0, };

	if (HIWORD(wParam) == BN_CLICKED) {	//5. ��ġ�� ��ư�� Ŭ������ ��

		//5.1 ����Ʈ�� ��Ʈ�ѿ��� ��ġ�� �д´�.
		index = SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_GETSELECTIONMARK,
			(WPARAM)0, (LPARAM)0);

		//5.2 �ּ�, ��ȭ��ȣ, �̸��� �ּҸ� �д´�.
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_ADDRESS), WM_GETTEXT, (WPARAM)64, (LPARAM)address);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_TELEPHONENUMBER), WM_GETTEXT, (WPARAM)12, (LPARAM)telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_EMAILADDRESS), WM_GETTEXT, (WPARAM)64, (LPARAM)eMailAddress);

		//5.3 �ּҷϿ��� ��ģ��.
		addressBook = (AddressBook*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
		
		index = Correct(addressBook, index, address, telephoneNumber, eMailAddress);

		//5.4 ����Ʈ�� ��Ʈ���� �ش� �׸��� ��ģ��.
		item.mask = LVIF_TEXT;
		item.iItem = index;

		personal = AddressBook_GetAt(addressBook, index);
		item.iSubItem = 2;
		item.pszText = personal.address;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);

		item.iSubItem = 3;
		item.pszText = personal.telephoneNumber;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);

		item.iSubItem = 4;
		item.pszText = personal.eMailAddress;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
	}
	return TRUE;
}

BOOL AddressBookForm_OnEraseButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	AddressBook *addressBook;
	Long index;
	LVITEM item = { 0, };
	TCHAR number[64];
	Long i;

	if (HIWORD(wParam) == BN_CLICKED) {	//6. ����� ��ư�� Ŭ������ ��

		//6.1 ����Ʈ�� ��Ʈ�ѿ��� ��ġ�� �д´�.
		index = SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_GETSELECTIONMARK, 
			(WPARAM)0, (LPARAM)0);
		
		//6.2 �ּҷϿ��� �����.
		addressBook = (AddressBook*)GetWindowLongPtr(hWnd, GWLP_USERDATA);

		Erase(addressBook, index);

		//6.3 ����Ʈ�� ��Ʈ���� �ش� �׸��� �����.
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_DELETEITEM, (WPARAM)index, (LPARAM)0);

		//6.4 ���� �׸� ������ ��ȣ���� �����Ѵ�.
		item.mask = LVIF_TEXT;
		item.iSubItem = 0;
		i = index;
		while (i < addressBook->length) {

			item.iItem = i;
			sprintf(number, "%d", i + 1);
			item.pszText = number;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT, (WPARAM)i, (LPARAM)&item);
			
			i++;
		}
	}
	return TRUE;
}

BOOL AddressBookForm_OnArrangeButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	AddressBook *addressBook;
	Personal personal;
	LVITEM item = { 0, };
	TCHAR number[64];
	Long i = 0;

	if (HIWORD(wParam) == BN_CLICKED) {	//7. �����ϱ� ��ư�� Ŭ������ ��

		//7.1 �ּҷϿ��� �����Ѵ�.
		addressBook = (AddressBook*)GetWindowLongPtr(hWnd, GWLP_USERDATA);

		Arrange(addressBook);

		//7.2 ����Ʈ�� ��Ʈ���� ��� �׸���� �����.
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_DELETEALLITEMS,
			(WPARAM)0, (LPARAM)0);

		//7.3 �ּҷ��� ���� �� ��ŭ ����Ʈ�� ��Ʈ�ѿ� �׸��� �߰��Ѵ�.
		item.mask = LVIF_TEXT;
		while (i < addressBook->length) {

			item.iItem = i;

			item.iSubItem = 0;
			sprintf(number, "%d",i + 1);
			item.pszText = number;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_INSERTITEM, 
				(WPARAM)0,(LPARAM)&item);

			personal = AddressBook_GetAt(addressBook, i);

			item.iSubItem = 1;
			item.pszText = personal.name;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT,
				(WPARAM)i, (LPARAM)&item);

			item.iSubItem = 2;
			item.pszText = personal.address;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT,
				(WPARAM)i, (LPARAM)&item);

			item.iSubItem = 3;
			item.pszText = personal.telephoneNumber;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT,
				(WPARAM)i, (LPARAM)&item);

			item.iSubItem = 4;
			item.pszText = personal.eMailAddress;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT,
				(WPARAM)i, (LPARAM)&item);

			i++;
		}
	}
	return TRUE;
}

BOOL AddressBookForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	//8. �ݱ� ��Ʈ���� Ŭ������ ��
	AddressBook *addressBook;

	addressBook = (AddressBook*)GetWindowLongPtr(hWnd, GWLP_USERDATA);

	if (addressBook != NULL) {

		//8.1 �ּҷϿ��� ��ũ ���Ͽ� �����Ѵ�.
		Save(addressBook);

		//8.2 �ּҷ��� ���ش�.
		AddressBook_Destroy(addressBook);
		free(addressBook);
	}
	//8.3 �����츦 ���ش�.
	EndDialog(hWnd, 0);

	return TRUE;
}