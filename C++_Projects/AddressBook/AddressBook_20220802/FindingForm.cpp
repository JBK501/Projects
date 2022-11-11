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

	CDialog::OnInitDialog(); //�������̵�

	//����Ʈ�� ��Ʈ�� ����� �����.
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->InsertColumn(0, "��ȣ", LVCFMT_LEFT, 50);
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->InsertColumn(1, "����", LVCFMT_LEFT, 100);
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->InsertColumn(2, "�ּ�", LVCFMT_LEFT, 140);
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->InsertColumn(3, "��ȭ��ȣ", LVCFMT_LEFT, 120);
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->InsertColumn(4, "�̸����ּ�", LVCFMT_LEFT, 170);

	//����Ʈ�� ��Ʈ�� �׸��� ǥ���Ѵ�.
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

	//������ �д´�.
	GetDlgItem(IDC_EDIT_NAME)->GetWindowText(name);

	//�ּҷ� �����츦 ã�´�.
	addressBookForm = (AddressBookForm*)CWnd::FindWindow("#32770", "�ּҷ�");

	//������ ã�� ��ġ�� ���ش�.
	if (this->indexes != NULL) {
		delete[] this->indexes;
	}

	//�ּҷ� �������� �ּҷϿ��� ã�´�.
	addressBookForm->addressBook->Find((LPCTSTR)name, &(this->indexes), &(this->count));

	//����Ʈ�� ��Ʈ���� ��� �׸��� �����.
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->DeleteAllItems();

	//ã�� ������ŭ ����Ʈ�� ��Ʈ�ѿ� �׸��� �߰��Ѵ�.
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

	//�ش� �׸��� ��ġ�� �д´�.
	index = ((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->GetSelectionMark();

	//�ش� ��ġ�� ������ �д´�.
	name = ((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->GetItemText(index, 1);
	address = ((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->GetItemText(index, 2);
	telephoneNumber = ((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->GetItemText(index, 3);
	eMailAddress = ((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->GetItemText(index, 4);

	//�ּҷ� �����츦 ã�´�.
	addressBookForm = (AddressBookForm*)CWnd::FindWindowA("#32770", "�ּҷ�");

	//�ּҷ� �������� ���ο� ����.
	addressBookForm->GetDlgItem(IDC_EDIT_NAME)->SetWindowText(name);
	addressBookForm->GetDlgItem(IDC_EDIT_ADDRESS)->SetWindowText(address);
	addressBookForm->GetDlgItem(IDC_EDIT_TELEPHONENUMBER)->SetWindowText(telephoneNumber);
	addressBookForm->GetDlgItem(IDC_EDIT_EMAILADDRESS)->SetWindowText(eMailAddress);

	//�ּҷ� �������� ����Ʈ�� ��Ʈ�ѿ��� ǥ�õ� �׸��� �����Ѵ�.
	((CListCtrl*)(addressBookForm->GetDlgItem(IDC_LIST_PERSONALS)))->SetItemState(-1, 0, LVIS_SELECTED);

	//�ּҷ� �������� ����Ʈ�� ��Ʈ�ѿ��� �ش� �׸��� �����Ѵ�.
	((CListCtrl*)(addressBookForm->GetDlgItem(IDC_LIST_PERSONALS)))->SetSelectionMark(this->indexes[index]);

	//�ּҷ� �������� ����Ʈ�� ��Ʈ�ѿ��� �ش� �׸��� ǥ���Ѵ�.
	((CListCtrl*)(addressBookForm->GetDlgItem(IDC_LIST_PERSONALS)))->SetItemState(this->indexes[index],
		LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
	
	//((CListCtrl*)(addressBookForm->GetDlgItem(IDC_LIST_PERSONALS)))->ModifyStyle(0, LVS_SHOWSELALWAYS);
	
#if 0 
	//API���
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

	//ã�� �����츦 ���ش�.
	if (this->indexes != NULL) {
		delete[] this->indexes;
	}

	EndDialog(0);

	addressBookForm->GetDlgItem(IDC_LIST_PERSONALS)->SetFocus(); 
	//mfc���� ��� ��Ŀ���� FindingFrom�� ���ߵǾ� �־ addressBookForm�� focus�� ������ �� ����.
	//���� mfc������ EndDialog�� FindingForm�� ����� �Ŀ��� focus�� ������ �� �ִ�.
}

void FindingForm::OnClose() {

	if (this->indexes != NULL) {
		delete[] this->indexes;
	}

	EndDialog(0);
}