#include "FindingForm.h"
#include "AddressBookForm.h"
#include "AddressBook.h"
#include <afxcmn.h>

BEGIN_MESSAGE_MAP(FindingForm, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_FIND, OnFindButtonClicked)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_PERSONALS, OnListViewItemDoubleClicked)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

FindingForm::FindingForm(CWnd *parent) :CDialog(FindingForm::IDD,parent) {

	this->indexes = NULL;
	this->count = 0;
}

BOOL FindingForm::OnInitDialog() {

	CDialog::OnInitDialog(); //오버라이딩

	//리스트뷰 컨트롤 헤더를 만든다.
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->InsertColumn(0, "번호", LVCFMT_LEFT, 50);
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->InsertColumn(1, "성명", LVCFMT_LEFT, 100);
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->InsertColumn(2, "주소", LVCFMT_LEFT, 140);
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->InsertColumn(3, "전화번호", LVCFMT_LEFT, 120);
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->InsertColumn(4, "이메일주소", LVCFMT_LEFT, 170);

	//리스트뷰 컨트롤 항목을 표시한다.
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->SetExtendedStyle(LVS_EX_FULLROWSELECT);

	return FALSE;
}

void FindingForm::OnFindButtonClicked() {

	AddressBookForm *addressBookForm;
	CString name;
	CString address;
	CString telephoneNumber;
	CString eMailAddress;
	CString number;
	Personal personal;
	Long i = 0;

	//성명을 읽는다.
	GetDlgItem(IDC_EDIT_NAME)->GetWindowText(name);

	//주소록 윈도우를 찾는다.
	addressBookForm = (AddressBookForm*)CWnd::FindWindow("#32770", "주소록");

	//이전에 찾은 위치를 없앤다.
	if (this->indexes != NULL) {
		delete[] this->indexes;
	}

	//주소록 윈도우의 주소록에서 찾는다.
	addressBookForm->addressBook->Find((LPCTSTR)name, &(this->indexes), &(this->count));

	//리스트뷰 컨트롤의 모든 항목을 지운다.
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->DeleteAllItems();

	//찾은 개수만큼 리스트뷰 컨트롤에 항목을 추가한다.
	while (i < count) {

		personal = addressBookForm->addressBook->GetAt(this->indexes[i]);

		name = CString(personal.GetName().c_str());
		address = CString(personal.GetAddress().c_str());
		telephoneNumber = CString(personal.GetTelephoneNumber().c_str());
		eMailAddress = CString(personal.GetEMailAddress().c_str());

		number.Format("%d", i + 1);

		((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->InsertItem(i, number);
		((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(i, 1, name);
		((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(i, 2, address);
		((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(i, 3, telephoneNumber);
		((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(i, 4, eMailAddress);

		i++;
	}
}

void FindingForm::OnListViewItemDoubleClicked(NMHDR *pNotifyStruct, LRESULT *result) {

	Long index;
	CString name;
	CString address;
	CString telephoneNumber;
	CString eMailAddress;
	AddressBookForm *addressBookForm;
	//LVITEM item{ 0, };

	//해당 항목의 위치를 읽는다.
	index = ((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->GetSelectionMark();

	//해당 위치의 개인을 읽는다.
	name = ((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->GetItemText(index, 1);
	address = ((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->GetItemText(index, 2);
	telephoneNumber = ((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->GetItemText(index, 3);
	eMailAddress = ((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->GetItemText(index, 4);

	//주소록 윈도우를 찾는다.
	addressBookForm = (AddressBookForm*)CWnd::FindWindowA("#32770", "주소록");

	//주소록 윈도우의 개인에 쓴다.
	addressBookForm->GetDlgItem(IDC_EDIT_NAME)->SetWindowText(name);
	addressBookForm->GetDlgItem(IDC_EDIT_ADDRESS)->SetWindowText(address);
	addressBookForm->GetDlgItem(IDC_EDIT_TELEPHONENUMBER)->SetWindowText(telephoneNumber);
	addressBookForm->GetDlgItem(IDC_EDIT_EMAILADDRESS)->SetWindowText(eMailAddress);

	//주소록 윈도우의 리스트뷰 컨트롤에서 표시된 항목을 해제한다.
	((CListCtrl*)(addressBookForm->GetDlgItem(IDC_LIST_PERSONALS)))->SetItemState(-1, 0, LVIS_SELECTED);

	//주소록 윈도우의 리스트뷰 컨트롤에서 해당 항목을 선택한다.
	((CListCtrl*)(addressBookForm->GetDlgItem(IDC_LIST_PERSONALS)))->SetSelectionMark(this->indexes[index]);

	//주소록 윈도우의 리스트뷰 컨트롤에서 해당 항목을 표시한다.
	((CListCtrl*)(addressBookForm->GetDlgItem(IDC_LIST_PERSONALS)))->SetItemState(this->indexes[index],
		LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
	
	//((CListCtrl*)(addressBookForm->GetDlgItem(IDC_LIST_PERSONALS)))->ModifyStyle(0, LVS_SHOWSELALWAYS);
	
#if 0 
	//API방식
	item.mask = LVIF_STATE;
	item.state = LVIS_SELECTED | LVIS_FOCUSED;
	item.stateMask = LVIS_SELECTED | LVIS_FOCUSED;
	item.iItem = indexes[index];
	::SendMessage(addressBookForm->GetDlgItem(IDC_LIST_PERSONALS)->m_hWnd, LVM_SETITEMSTATE,
		(WPARAM)indexes[index],
		(LPARAM)&item);

	::SendMessage(addressBookForm->GetDlgItem(IDC_LIST_PERSONALS)->m_hWnd,WM_SETFOCUS,
		(WPARAM)0,
		(LPARAM)0);
#endif

	//찾기 윈도우를 없앤다.
	if (this->indexes != NULL) {
		delete[] this->indexes;
	}

	EndDialog(0);

	addressBookForm->GetDlgItem(IDC_LIST_PERSONALS)->SetFocus(); 
	//mfc같은 경우 포커스가 FindingFrom에 집중되어 있어서 addressBookForm에 focus를 지정할 수 없다.
	//따라서 mfc에서는 EndDialog로 FindingForm이 종료된 후에야 focus를 지정할 수 있다.
}

void FindingForm::OnClose() {

	if (this->indexes != NULL) {
		delete[] this->indexes;
	}

	EndDialog(0);
}