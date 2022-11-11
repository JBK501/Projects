#include "AddressBookForm.h"
#include "FindingForm.h"
#include "AddressBook.h"
#include <afxcmn.h>
#include <afxdb.h>


BEGIN_MESSAGE_MAP(AddressBookForm, CDialog)

	ON_BN_CLICKED(IDC_BUTTON_RECORD, OnRecordButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_FIND, OnFindButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_CORRECT, OnCorrectButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_ERASE, OnEraseButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_ARRANGE, OnArrangeButtonClicked)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_PERSONALS, OnListViewItemDoubleClicked)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


AddressBookForm::AddressBookForm(CWnd *parent) :CDialog(AddressBookForm::IDD, parent) {
	this->addressBook = NULL;
}


CString AddressBookForm::GetCode() {

	CDatabase db;
	CRecordset rs(&db);
	CString sql = "SELECT Personal.code FROM Personal ORDER BY code DESC;";

	db.OpenEx("DSN=AddressBook;UID=root;PWD=0000");
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);

	CString previous = "P0000";
	if (!rs.IsEOF()) {
		rs.GetFieldValue((short)0, previous);
	}

	CString current;
	CString numbers;

	numbers = previous.Right(4);

	int last = atoi((LPCTSTR)numbers);
	last++;

	current.Format("P%04d", last);

	rs.Close();
	db.Close();

	return current;
}


void AddressBookForm::Load() {

	CDatabase db;
	CRecordset rs(&db);
	CString sql = "SELECT Personal.name,Personal.address,Personal.telephoneNumber,Personal.eMailAddress "
		"FROM Personal;";

	db.OpenEx("DSN=AddressBook;UID=root;PWD=0000");
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);

	CString name;
	CString address;
	CString telephoneNumber;
	CString eMailAddress;


	while (!rs.IsEOF()) {

		rs.GetFieldValue((short)0, name);
		rs.GetFieldValue((short)1, address);
		rs.GetFieldValue((short)2, telephoneNumber);
		rs.GetFieldValue((short)3, eMailAddress);

		this->addressBook->Record((LPCTSTR)name, (LPCTSTR)address, (LPCTSTR)telephoneNumber, (LPCTSTR)eMailAddress);

		rs.MoveNext();
	}
	rs.Close();
	db.Close();
}

void AddressBookForm::Insert(Long index) {

	CDatabase db;
	Personal personal = this->addressBook->GetAt(index);
	
	CString sql;
	sql.Format("INSERT INTO Personal(code,name,address,telephoneNumber,eMailAddress) "
		"VALUES('%s','%s','%s','%s','%s');", (LPCTSTR)(this->GetCode()), personal.GetName().c_str(),
		personal.GetAddress().c_str(), personal.GetTelephoneNumber().c_str(),
		personal.GetEMailAddress().c_str());

	db.OpenEx("DSN=AddressBook;UID=root;PWD=0000");
	db.ExecuteSQL(sql);

	db.Close();
}

void AddressBookForm::Modify(Long index) {

	CDatabase db;
	CRecordset rs(&db);

	Personal personal = this->addressBook->GetAt(index);

	CString sql = "SELECT Personal.code FROM Personal;";

	db.OpenEx("DSN=AddressBook;UID=root;PWD=0000");
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);

	CString code;

	Long i = 0;
	while (!rs.IsEOF() && i <= index) {

		rs.GetFieldValue((short)0, code);

		rs.MoveNext();
		i++;
	}

	sql.Format("UPDATE Personal SET address='%s',telephoneNumber='%s',eMailAddress='%s' "
		"WHERE Personal.code='%s';", personal.GetAddress().c_str(), personal.GetTelephoneNumber().c_str(),
		personal.GetEMailAddress().c_str(), (LPCTSTR)code);

	db.ExecuteSQL(sql);
	
	rs.Close();
	db.Close();
}

void AddressBookForm::Delete(Long index) {

	CDatabase db;
	CRecordset rs(&db);

	CString sql = "SELECT Personal.code FROM Personal;";

	db.OpenEx("DSN=AddressBook;UID=root;PWD=0000");
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);

	CString code;

	Long i = 0;
	while (!rs.IsEOF() && i <= index) {

		rs.GetFieldValue((short)0, code);

		rs.MoveNext();
		i++;
	}

	sql.Format("DELETE FROM Personal WHERE Personal.code='%s';", (LPCTSTR)code);

	db.ExecuteSQL(sql);

	rs.Close();
	db.Close();
}

void AddressBookForm::Save() {

	CDatabase db;
	CRecordset rs(&db);
	CString sql = "SELECT Personal.code FROM Personal;";

	db.OpenEx("DSN=AddressBook;UID=root;PWD=0000");
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);

	sql = CString("DELETE FROM Personal;");
	db.ExecuteSQL(sql);

	CString code;
	Personal personal;
	Long i = 0;

	while (i < this->addressBook->GetLength()) {

		personal = this->addressBook->GetAt(i);
		rs.GetFieldValue((short)0, code);

		sql.Format("INSERT INTO Personal(code,name,address,telephoneNumber,eMailAddress) "
			"VALUES('%s','%s','%s','%s','%s');", (LPCTSTR)code, personal.GetName().c_str(),
			personal.GetAddress().c_str(), personal.GetTelephoneNumber().c_str(),
			personal.GetEMailAddress().c_str());

		db.ExecuteSQL(sql);

		rs.MoveNext();

		i++;
	}
	rs.Close();
	db.Close();
}


BOOL AddressBookForm::OnInitDialog() {

	CDialog::OnInitDialog();	//�������̵�

	//�ּҷ��� �����.
	this->addressBook = new AddressBook;

	//�ּҷϿ��� �����Ѵ�.
	this->Load();

	//����Ʈ�� ��Ʈ�� ����� �����.
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->InsertColumn(0, "��ȣ", LVCFMT_LEFT, 50);
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->InsertColumn(1, "����", LVCFMT_LEFT, 100);
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->InsertColumn(2, "�ּ�", LVCFMT_LEFT, 140);
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->InsertColumn(3, "��ȭ��ȣ", LVCFMT_LEFT, 120);
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->InsertColumn(4, "�̸����ּ�", LVCFMT_LEFT, 170);

	Personal personal;
	CString name;
	CString address;
	CString telephoneNumber;
	CString eMailAddress;
	CString number;

	Long i = 0;
	while (i < this->addressBook->GetLength()) {

		personal = this->addressBook->GetAt(i);

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

	//����Ʈ�� �׸��� ǥ���Ѵ�.
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->SetExtendedStyle(LVS_EX_FULLROWSELECT);

	return FALSE;
}

void AddressBookForm::OnRecordButtonClicked() {

	CString name;
	CString address;
	CString telephoneNumber;
	CString eMailAddress;
	Long index;

	//����, �ּ�, ��ȭ��ȣ, �̸��� �ּҸ� �д´�.
	GetDlgItem(IDC_EDIT_NAME)->GetWindowText(name);
	GetDlgItem(IDC_EDIT_ADDRESS)->GetWindowText(address);
	GetDlgItem(IDC_EDIT_TELEPHONENUMBER)->GetWindowText(telephoneNumber);
	GetDlgItem(IDC_EDIT_EMAILADDRESS)->GetWindowText(eMailAddress);

	//�ּҷϿ��� �����Ѵ�.
	index = this->addressBook->Record((LPCTSTR)name, (LPCTSTR)address,
		(LPCTSTR)telephoneNumber, (LPCTSTR)eMailAddress);
	this->Insert(index);

	//����Ʈ�� ��Ʈ�ѿ� �׸��� �߰��Ѵ�.
	Personal personal = this->addressBook->GetAt(index);

	name = CString(personal.GetName().c_str());
	address = CString(personal.GetAddress().c_str());
	telephoneNumber = CString(personal.GetTelephoneNumber().c_str());
	eMailAddress = CString(personal.GetEMailAddress().c_str());

	CString number;
	number.Format("%d", index + 1);

	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->InsertItem(index, number);
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(index, 1, name);
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(index, 2, address);
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(index, 3, telephoneNumber);
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(index, 4, eMailAddress);
}


void AddressBookForm::OnFindButtonClicked() {

	FindingForm findingForm;
	
	findingForm.DoModal();
}


void AddressBookForm::OnCorrectButtonClicked() {

	Long index;
	CString address;
	CString telephoneNumber;
	CString eMailAddress;

	//����Ʈ�� ��Ʈ�ѿ��� �ش� �׸��� ��ġ�� �д´�.
	index = ((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->GetSelectionMark();

	//������ ��Ʈ���� �ּ�, ��ȭ��ȣ, �̸��� �ּҸ� �д´�.
	GetDlgItem(IDC_EDIT_ADDRESS)->GetWindowText(address);
	GetDlgItem(IDC_EDIT_TELEPHONENUMBER)->GetWindowText(telephoneNumber);
	GetDlgItem(IDC_EDIT_EMAILADDRESS)->GetWindowText(eMailAddress);

	//�ּҷϿ��� ��ģ��.
	index = this->addressBook->Correct(index, (LPCTSTR)address, (LPCTSTR)telephoneNumber, (LPCTSTR)eMailAddress);
	this->Modify(index);

	//����Ʈ�� ��Ʈ�ѿ��� �ش� �׸��� �����Ѵ�.
	Personal personal = this->addressBook->GetAt(index);

	address = CString(personal.GetAddress().c_str());
	telephoneNumber = CString(personal.GetTelephoneNumber().c_str());
	eMailAddress = CString(personal.GetEMailAddress().c_str());

	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(index, 2, address);
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(index, 3, telephoneNumber);
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(index, 4, eMailAddress);
}

void AddressBookForm::OnEraseButtonClicked() {

	Long index; 
	Long i;
	CString number;

	//����Ʈ�� ��Ʈ�ѿ��� �ش� �׸��� ��ġ�� �д´�.
	index = ((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->GetSelectionMark();

	//�ּҷϿ��� �����.
	this->addressBook->Erase(index);
	this->Delete(index);
	
	//����Ʈ�� ��Ʈ�ѿ��� �����.
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->DeleteItem(index);

	//���� ������ �׸� ��ȣ�� �����Ѵ�.
	i = index;
	while (i < this->addressBook->GetLength()) {

		number.Format("%d", i + 1);
		((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(i, 0, number);

		i++;
	}
}

void AddressBookForm::OnArrangeButtonClicked() {

	Long i = 0;
	Personal personal;
	CString name;
	CString address;
	CString telephoneNumber;
	CString eMailAddress;
	CString number;

	//�ּҷϿ��� �����Ѵ�.
	this->addressBook->Arrange();

	//����Ʈ�� ��Ʈ���� ��� �׸���� ���ش�.
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->DeleteAllItems();

	//��뷮 ��ŭ ����Ʈ�� ��Ʈ�ѿ� �׸���� �߰��Ѵ�.
	while (i < this->addressBook->GetLength()) {

		personal = this->addressBook->GetAt(i);

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

void AddressBookForm::OnListViewItemDoubleClicked(NMHDR *pNotifyStruct, LRESULT *result) {

	Long index;
	CString name;
	CString address;
	CString telephoneNumber;
	CString eMailAddress;

	//����Ʈ�� ��Ʈ�ѿ��� �ش� �׸��� ��ġ�� �д´�.
	index = ((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->GetSelectionMark();

	//�ش� ��ġ�� ������ �д´�.
	name = ((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->GetItemText(index, 1);
	address = ((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->GetItemText(index, 2);
	telephoneNumber = ((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->GetItemText(index, 3);
	eMailAddress = ((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->GetItemText(index, 4);

	//������ ��Ʈ���� ���ο� ����.
	GetDlgItem(IDC_EDIT_NAME)->SetWindowText(name);
	GetDlgItem(IDC_EDIT_ADDRESS)->SetWindowText(address);
	GetDlgItem(IDC_EDIT_TELEPHONENUMBER)->SetWindowText(telephoneNumber);
	GetDlgItem(IDC_EDIT_EMAILADDRESS)->SetWindowText(eMailAddress);
}

void AddressBookForm::OnClose() {

	if (this->addressBook != NULL) {

		this->Save();
		delete this->addressBook;
	}
	EndDialog(0);
}