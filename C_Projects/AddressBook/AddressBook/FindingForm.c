#include "FindingForm.h"
#include "AddressBook.h"
#include "resource.h"


#include <stdio.h>
#include <stdlib.h>
#include <commctrl.h>
#include <WinUser.h>
#pragma warning(disable:4996)

BOOL CALLBACK FindingFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {

	BOOL ret;

	switch (message){

	case WM_INITDIALOG:
		ret = FindingForm_OnInitDialog(hWnd, wParam, lParam);
		break;
	case WM_COMMAND:
		ret = FindingForm_OnCommand(hWnd, wParam, lParam);
		break;
	case WM_NOTIFY:
		ret = FindingForm_OnNotify(hWnd, wParam, lParam);
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

	switch ((int)wParam){

	case IDC_BUTTON_FIND:
		ret = FindingForm_OnFindButtonClicked(hWnd, wParam, lParam);
		break;
	default:
		ret = FALSE;
		break;
	}
	return ret;
}

BOOL FindingForm_OnNotify(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	BOOL ret;

	switch ((int)wParam){

	case IDC_LIST_PERSONALS:
		ret = FindingForm_OnListViewItemDoubleClicked(hWnd, wParam, lParam);
		break;
	default:
		ret = FALSE;
		break;
	}
	return ret;
}

BOOL FindingForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	//1. ã�������찡 ������ ��
	LVCOLUMN column = { 0, };

	//���� ����
	SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS),
		LVM_SETEXTENDEDLISTVIEWSTYLE,
		LVS_EX_FULLROWSELECT,
		LVS_EX_FULLROWSELECT);

	//1.1 ����Ʈ����Ʈ�� ����� �����.
	column.mask = LVCF_WIDTH | LVCF_TEXT;

	column.cx = 50;
	column.pszText = "��ȣ";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_INSERTCOLUMN,
		(WPARAM)0, (LPARAM)&column);

	column.cx = 100;
	column.pszText = "����";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_INSERTCOLUMN,
		(WPARAM)1, (LPARAM)&column);

	column.cx = 140;
	column.pszText = "�ּ�";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_INSERTCOLUMN,
		(WPARAM)2, (LPARAM)&column);

	column.cx = 120;
	column.pszText = "��ȭ��ȣ";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_INSERTCOLUMN,
		(WPARAM)3, (LPARAM)&column);

	column.cx = 170;
	column.pszText = "�̸����ּ�";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_INSERTCOLUMN,
		(WPARAM)4, (LPARAM)&column);

	return TRUE;
}

BOOL FindingForm_OnFindButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	AddressBook *addressBook;
	HWND hAddressBookForm;
	TCHAR name[11];
	Long(*indexes);
	Long count;
	Personal personal;
	LVITEM item = { 0, };
	TCHAR number[64];
	Long i = 0;

	if (HIWORD(wParam) == BN_CLICKED) {
		//2. ã���ư�� Ŭ������ ��

		//2.1 ������ �д´�.
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_NAME), WM_GETTEXT,
			(WPARAM)11, (LPARAM)name);

		//2.2 �ּҷ� �����츦 ã�´�.
		hAddressBookForm = FindWindow("#32770", "�ּҷ�");

		//2.3 �ּҷ� �������� �ּҷϿ��� ã�´�.
		addressBook = (AddressBook*)GetWindowLongPtr(hAddressBookForm, GWLP_USERDATA);

		//�ٽ� �˻��� �� ������ ���� ������ indexes �Ҵ�����
		indexes = (Long(*))GetWindowLongPtr(hWnd, GWLP_USERDATA);
		if (indexes != NULL) {
			free(indexes);
		}

		Find(addressBook, name, &indexes, &count);
		SetWindowLongPtr(hWnd, GWLP_USERDATA,(LONG_PTR)indexes);

		//2.4 ����Ʈ�� ��Ʈ���� �׸���� �����.
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_DELETEALLITEMS, (WPARAM)0, (LPARAM)0);

		//2.5 ã�� ���� ��ŭ ����Ʈ�� ��Ʈ�ѿ� �׸��� �߰��Ѵ�.
		item.mask = LVIF_TEXT;
		while (i < count) {

			item.iItem = i;

			item.iSubItem = 0;
			sprintf(number, "%d", i + 1);
			item.pszText = number;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_INSERTITEM, (WPARAM)0, (LPARAM)&item);

			personal = AddressBook_GetAt(addressBook, indexes[i]);

			item.iSubItem = 1;
			item.pszText = personal.name;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT, (WPARAM)i, (LPARAM)&item);

			item.iSubItem = 2;
			item.pszText = personal.address;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT, (WPARAM)i, (LPARAM)&item);

			item.iSubItem = 3;
			item.pszText = personal.telephoneNumber;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT, (WPARAM)i, (LPARAM)&item);

			item.iSubItem = 4;
			item.pszText = personal.eMailAddress;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT, (WPARAM)i, (LPARAM)&item);

			i++;
		}

	}
	return TRUE;
}

BOOL FindingForm_OnListViewItemDoubleClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	TCHAR name[11];
	TCHAR address[64];
	TCHAR telephoneNumber[12];
	TCHAR emailAddress[64];
	Long index; 
	HWND hAddressBookForm;
	LVITEM item = { 0, };
	Long(*indexes);

	if (((LPNMHDR)lParam)->code == NM_DBLCLK) {
		//3.����Ʈ�� ��Ʈ���� �׸��� ���� Ŭ������ ��

		//3.1 ����Ʈ�� ��Ʈ�� �ش� �׸��� ��ġ�� �д´�.
		index = SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_GETSELECTIONMARK, 
			(WPARAM)0, (LPARAM)0);

		//3.2 �ش� ��ġ�� ����, �ּ�, ��ȭ��ȣ, �̸����ּҸ� �д´�.
		item.mask = LVIF_TEXT|LVIF_STATE;
		
		item.iSubItem = 1;
		item.pszText = name;
		item.cchTextMax = 11;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_GETITEMTEXT, (WPARAM)index, (LPARAM)&item);

		item.iSubItem = 2;
		item.pszText = address;
		item.cchTextMax = 64;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_GETITEMTEXT, (WPARAM)index, (LPARAM)&item);

		item.iSubItem = 3;
		item.pszText = telephoneNumber;
		item.cchTextMax = 12;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_GETITEMTEXT, (WPARAM)index, (LPARAM)&item);


		item.iSubItem = 4;
		item.pszText = emailAddress;
		item.cchTextMax = 64;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_GETITEMTEXT, (WPARAM)index, (LPARAM)&item);

		//3.3 �ּҷ� �����츦 ã�´�.
		hAddressBookForm = FindWindow("#32770", "�ּҷ�");

		//3.4 �ּҷ� �������� ���ο� ����.
		SendMessage(GetDlgItem(hAddressBookForm, IDC_EDIT_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)name);
		SendMessage(GetDlgItem(hAddressBookForm, IDC_EDIT_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)address);
		SendMessage(GetDlgItem(hAddressBookForm, IDC_EDIT_TELEPHONENUMBER), WM_SETTEXT, 
			(WPARAM)0, (LPARAM)telephoneNumber);
		SendMessage(GetDlgItem(hAddressBookForm, IDC_EDIT_EMAILADDRESS), WM_SETTEXT, 
			(WPARAM)0, (LPARAM)emailAddress);

		//3.5 �ּҷ� ������ ����Ʈ�� ��Ʈ�ѿ��� �ش� �׸��� �����Ѵ�.
		indexes = (Long(*))GetWindowLongPtr(hWnd, GWLP_USERDATA);

		SendMessage(GetDlgItem(hAddressBookForm, IDC_LIST_PERSONALS), LVM_SETSELECTIONMARK,
			(WPARAM)0, (LPARAM)indexes[index]);

		item.state = LVIS_SELECTED | LVIS_FOCUSED;
		item.stateMask = LVIS_SELECTED | LVIS_FOCUSED;
		item.iItem = indexes[index];
		SendMessage(GetDlgItem(hAddressBookForm, IDC_LIST_PERSONALS), LVM_SETITEMSTATE,
			(WPARAM)indexes[index],
			(LPARAM)&item);

		SendMessage(GetDlgItem(hAddressBookForm, IDC_LIST_PERSONALS), WM_SETFOCUS,
			(WPARAM)0,
			(LPARAM)0);

#if 0
		ListView_SetItemState(GetDlgItem(hAddressBookForm, IDC_LIST_PERSONALS), indexes[index],
			LVNI_SELECTED | LVNI_FOCUSED, LVNI_SELECTED | LVNI_FOCUSED);
		SetFocus(GetDlgItem(hAddressBookForm, IDC_LIST_PERSONALS));
#endif

		//3.6 ã�� �����츦 ���ش�.
		if (indexes != NULL) {
			free(indexes);
		}
		EndDialog(hWnd, 0);
	}
	return TRUE;
}

BOOL FindingForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	//4. �ݱ���Ʈ���� Ŭ������ ��
	Long(*indexes);

	indexes = (Long(*))GetWindowLongPtr(hWnd, GWLP_USERDATA);

	if (indexes != NULL) {
		free(indexes);
	}
	//4.1 ã�������츦 ���ش�. 
	EndDialog(hWnd, 0);
	
	return TRUE;
}

