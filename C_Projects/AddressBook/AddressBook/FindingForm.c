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

	//1. 찾기윈도우가 생성될 때
	LVCOLUMN column = { 0, };

	//한줄 선택
	SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS),
		LVM_SETEXTENDEDLISTVIEWSTYLE,
		LVS_EX_FULLROWSELECT,
		LVS_EX_FULLROWSELECT);

	//1.1 리스트뷰컨트롤 헤더를 만든다.
	column.mask = LVCF_WIDTH | LVCF_TEXT;

	column.cx = 50;
	column.pszText = "번호";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_INSERTCOLUMN,
		(WPARAM)0, (LPARAM)&column);

	column.cx = 100;
	column.pszText = "성명";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_INSERTCOLUMN,
		(WPARAM)1, (LPARAM)&column);

	column.cx = 140;
	column.pszText = "주소";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_INSERTCOLUMN,
		(WPARAM)2, (LPARAM)&column);

	column.cx = 120;
	column.pszText = "전화번호";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_INSERTCOLUMN,
		(WPARAM)3, (LPARAM)&column);

	column.cx = 170;
	column.pszText = "이메일주소";
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
		//2. 찾기버튼을 클릭했을 때

		//2.1 성명을 읽는다.
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_NAME), WM_GETTEXT,
			(WPARAM)11, (LPARAM)name);

		//2.2 주소록 윈도우를 찾는다.
		hAddressBookForm = FindWindow("#32770", "주소록");

		//2.3 주소록 윈도우의 주소록에서 찾는다.
		addressBook = (AddressBook*)GetWindowLongPtr(hAddressBookForm, GWLP_USERDATA);

		//다시 검색할 때 이전에 힙에 저장한 indexes 할당해제
		indexes = (Long(*))GetWindowLongPtr(hWnd, GWLP_USERDATA);
		if (indexes != NULL) {
			free(indexes);
		}

		Find(addressBook, name, &indexes, &count);
		SetWindowLongPtr(hWnd, GWLP_USERDATA,(LONG_PTR)indexes);

		//2.4 리스트뷰 컨트롤의 항목들을 지운다.
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_DELETEALLITEMS, (WPARAM)0, (LPARAM)0);

		//2.5 찾은 개수 만큼 리스트뷰 컨트롤에 항목을 추가한다.
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
		//3.리스트뷰 컨트롤의 항목을 더블 클릭했을 때

		//3.1 리스트뷰 컨트롤 해당 항목의 위치를 읽는다.
		index = SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_GETSELECTIONMARK, 
			(WPARAM)0, (LPARAM)0);

		//3.2 해당 위치의 성명, 주소, 전화번호, 이메일주소를 읽는다.
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

		//3.3 주소록 윈도우를 찾는다.
		hAddressBookForm = FindWindow("#32770", "주소록");

		//3.4 주소록 윈도우의 개인에 쓴다.
		SendMessage(GetDlgItem(hAddressBookForm, IDC_EDIT_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)name);
		SendMessage(GetDlgItem(hAddressBookForm, IDC_EDIT_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)address);
		SendMessage(GetDlgItem(hAddressBookForm, IDC_EDIT_TELEPHONENUMBER), WM_SETTEXT, 
			(WPARAM)0, (LPARAM)telephoneNumber);
		SendMessage(GetDlgItem(hAddressBookForm, IDC_EDIT_EMAILADDRESS), WM_SETTEXT, 
			(WPARAM)0, (LPARAM)emailAddress);

		//3.5 주소록 윈도우 리스트뷰 컨트롤에서 해당 항목을 선택한다.
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

		//3.6 찾기 윈도우를 없앤다.
		if (indexes != NULL) {
			free(indexes);
		}
		EndDialog(hWnd, 0);
	}
	return TRUE;
}

BOOL FindingForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	//4. 닫기컨트롤을 클릭했을 때
	Long(*indexes);

	indexes = (Long(*))GetWindowLongPtr(hWnd, GWLP_USERDATA);

	if (indexes != NULL) {
		free(indexes);
	}
	//4.1 찾기윈도우를 없앤다. 
	EndDialog(hWnd, 0);
	
	return TRUE;
}

