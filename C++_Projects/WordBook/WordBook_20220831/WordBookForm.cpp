#include "WordBookForm.h"
#include "WordBook.h"
#include "FindingForm.h"
#include "Date.h"
#include <afxcmn.h>
#include <afxdb.h>

BEGIN_MESSAGE_MAP(WordBookForm, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_RECORD, OnRecordButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_FIND, OnFindButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_CORRECT, OnCorrectButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_ERASE, OnEraseButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_ARRANGE, OnArrangeButtonClicked)
	ON_NOTIFY(NM_DBLCLK,IDC_LIST_WORDS,OnListViewItemDoubleClicked)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

WordBookForm::WordBookForm(CWnd *parent)
	:CDialog(WordBookForm::IDD, parent) {
	this->wordBook = NULL;
}

// �����ϴ�.
void WordBookForm::Load() {

	// ������ ���̽����� �ܾ���� �����´�.
	CDatabase db;
	CRecordset rs(&db);
	CString sql = "SELECT Word.spelling,Word.meaning,Word.wordClass,Word.exampleSentence FROM Word;";

	db.OpenEx("DSN=WordBook;UID=root;PWD=0000");
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);

	// ������ ������ŭ �ܾ��忡 �����Ѵ�.
	CString spelling;
	CString meaning;
	CString wordClass;
	CString exampleSentence;

	while (!rs.IsEOF()) {

		rs.GetFieldValue((short)0, spelling);
		rs.GetFieldValue((short)1, meaning);
		rs.GetFieldValue((short)2, wordClass);
		rs.GetFieldValue((short)3, exampleSentence);

		this->wordBook->Record((LPCTSTR)spelling, (LPCTSTR)meaning,
			(LPCTSTR)wordClass, (LPCTSTR)exampleSentence);

		rs.MoveNext();
	}
	rs.Close();
	db.Close();	//DisConnection
}

// �⺻Ű�� ���ϴ�.
CString WordBookForm::GetGode() {

	// ���� ��¥�� ���Ѵ�.
	Date today_ = Date::Today();

	CString today;
	today.Format("%04d%02d%02d", today_.GetYear(), today_.GetMonth(), today_.GetDay());

	CDatabase db;
	CRecordset rs(&db);
	CString sql = "SELECT Word.code FROM Word ORDER BY code DESC;";

	db.OpenEx("DSN=WordBook;UID=root;PWD=0000");	// Connection
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);	// Request & Response

	CString code;
	code.Format("%s000", (LPCTSTR)today);	// �ڵ� �ʱ�ȭ

	// db�� �����Ͱ� ������
	if (!rs.IsEOF()) {

		// ���� �ڵ带 ���Ѵ�.
		CString previousCode;
		rs.GetFieldValue((short)0, previousCode);

		// ���� �ڵ��� ��¥�� ���Ѵ�.
		CString previousDate = previousCode.Left(8);

		// ���ó�¥�� ���ٸ�
		if (today.Compare(previousDate) == 0) {
			code = CString(previousCode);	// �����ڵ带 ����Ѵ�.
		}
	}

	// ��ȣ�� ���Ѵ�.
	CString numbers = code.Right(3);
	
	Long number = atoi((LPCTSTR)numbers);

	// ��ȣ�� ���Ѵ�.
	number++;

	// ���ο� �ڵ带 ���Ѵ�.
	CString newCode;
	newCode.Format("%s%03d", (LPCTSTR)today, number);

	rs.Close();
	db.Close();	//DisConnection

	return newCode;
}

void WordBookForm::Insert(Long index) {

	Word word = this->wordBook->GetAt(index);	// ������ �ܾ �����´�.
	CString code = this->GetGode();	// �⺻Ű�� ���Ѵ�.

	CDatabase db;
	CString sql;
	sql.Format("INSERT INTO Word(code,spelling,meaning,wordClass,exampleSentence) "
		"VALUES('%s','%s','%s','%s','%s');", (LPCTSTR)code, word.GetSpelling().c_str(),
		word.GetMeaning().c_str(), word.GetWordClass().c_str(),
		word.GetExampleSentence().c_str());

	db.OpenEx("DSN=WordBook;UID=root;PWD=0000");	// Connection
	db.ExecuteSQL(sql); // Request

	db.Close(); //Disconnection
}

// �����ͺ��̽����� �����ϴ�.
void WordBookForm::Modify(Long index) {

	Word word = this->wordBook->GetAt(index);	// ������ �ܾ �����´�.

	CDatabase db;
	CRecordset rs(&db);
	CString sql = "SELECT Word.code FROM Word;";	// �⺻Ű���� �����´�.

	db.OpenEx("DSN=WordBook;UID=root;PWD=0000");	// Connection
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);	// Request & Response

	// �����ͺ��̽����� ������ ��ġ�� �ش��ϴ� �⺻Ű�� ã�´�.
	CString code;
	
	Long i = 0;
	while (!rs.IsEOF() && i <= index) {

		rs.GetFieldValue((short)0, code);

		rs.MoveNext();
		i++;
	}

	// �����ͺ��̽����� �����Ѵ�.
	sql.Format("UPDATE Word SET meaning='%s',wordClass='%s',exampleSentence='%s' "
		"WHERE Word.code='%s';", word.GetMeaning().c_str(),
		word.GetWordClass().c_str(), word.GetExampleSentence().c_str(),code);

	db.ExecuteSQL(sql); // Request

	rs.Close();
	db.Close(); // Disconnection
}

void WordBookForm::Delete(Long index) {

	CDatabase db;
	CRecordset rs(&db);
	CString sql = "SELECT Word.code FROM Word;";	// �⺻Ű���� �����´�.

	db.OpenEx("DSN=WordBook;UID=root;PWD=0000");	// Connection
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);	// Request & Response

	// �����ͺ��̽����� ������ ��ġ�� �ش��ϴ� �⺻Ű�� ã�´�.
	CString code;

	Long i = 0;
	while (!rs.IsEOF() && i <= index) {

		rs.GetFieldValue((short)0, code);

		rs.MoveNext();
		i++;
	}

	// �����ͺ��̽����� �����Ѵ�.
	sql.Format("DELETE FROM Word WHERE Word.code='%s';", (LPCTSTR)code);
	db.ExecuteSQL(sql);

	rs.Close();
	db.Close(); // Disconnection
}

void WordBookForm::Save() {

	CDatabase db;
	CRecordset rs(&db);
	CString sql = "SELECT Word.code FROM Word;";

	db.OpenEx("DSN=WordBook;UID=root;PWD=0000");	// Connection
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);	// Request & Response

	// �ܾ��� �����ͺ��̽��� ��� �ܾ���� �����Ѵ�.
	sql = CString("DELETE FROM Word;");
	db.ExecuteSQL(sql);

	// �ܾ����� ��뷮 ��ŭ �����ͺ��̽��� �ܾ���� �߰��Ѵ�.
	Word word;
	CString code;
	Long i = 0;

	while (i < this->wordBook->GetLength()) {

		word = this->wordBook->GetAt(i);	// �ܾ �����´�.
		rs.GetFieldValue((short)0, code);	// ������ �ڵ带 �д´�.

		// �ܾ��� �����ͺ��̽��� �ܾ� ���̺� �߰��Ѵ�.
		sql.Format("INSERT INTO Word(code,spelling,meaning,wordClass,exampleSentence) "
			"VALUES('%s','%s','%s','%s','%s');", (LPCTSTR)code, word.GetSpelling().c_str(),
			word.GetMeaning().c_str(), word.GetWordClass().c_str(),
			word.GetExampleSentence().c_str());

		db.ExecuteSQL(sql);

		rs.MoveNext();	// ���� Ű�� �̵��Ѵ�.
		i++;
	}

	rs.Close();
	db.Close();
}

// �����찡 ������ ��
BOOL WordBookForm::OnInitDialog() {

	CDialog::OnInitDialog();

	Long i = 0;

	// �ܾ����� �����.
	this->wordBook = new WordBook;

	// �ܾ��忡 �����Ѵ�.
	this->Load();

	// �޺��ڽ��� ����� �߰��Ѵ�.
	TCHAR wordClasses[][16] = { "���","����","����","�����","�λ�","��ġ��","���ӻ�","��ź��" };

	i = 0;
	for (i = 0; i < sizeof(wordClasses) / sizeof(wordClasses[i]); i++) {
		((CComboBox*)GetDlgItem(IDC_COMBO_WORDCLASS))->AddString(wordClasses[i]);
	}

	// ����Ʈ�� ��Ʈ�� ����� �����.
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->InsertColumn(0, "��ȣ", LVCFMT_LEFT, 50);
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->InsertColumn(1, "ö��", LVCFMT_LEFT, 110);
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->InsertColumn(2, "�ǹ�", LVCFMT_LEFT, 110);
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->InsertColumn(3, "ǰ��", LVCFMT_LEFT, 70);
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->InsertColumn(4, "����", LVCFMT_LEFT, 200);

	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->SetExtendedStyle(LVS_EX_FULLROWSELECT);

	// ������ ������ŭ ����Ʈ�� ��Ʈ�ѿ� �׸��� �߰��Ѵ�.
	Word word;
	CString spelling;
	CString meaning;
	CString wordClass;
	CString exampleSentence;
	CString number;

	i = 0;
	while (i < this->wordBook->GetLength()) {

		word = this->wordBook->GetAt(i);

		spelling = CString(word.GetSpelling().c_str());
		meaning = CString(word.GetMeaning().c_str());
		wordClass = CString(word.GetWordClass().c_str());
		exampleSentence = CString(word.GetExampleSentence().c_str());

		number.Format("%d", i + 1);

		((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->InsertItem(i, number);
		((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->SetItemText(i, 1, spelling);
		((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->SetItemText(i, 2, meaning);
		((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->SetItemText(i, 3, wordClass);
		((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->SetItemText(i, 4, exampleSentence);

		i++;
	}

	return FALSE;
}

// �����ϱ� ��ư�� Ŭ������ ��
void WordBookForm::OnRecordButtonClicked() {

	// ö��,�ǹ�,ǰ��,������ �д´�.
	CString spelling;
	GetDlgItem(IDC_EDIT_SPELLING)->GetWindowText(spelling);

	CString meaning;
	GetDlgItem(IDC_EDIT_MEANING)->GetWindowText(meaning);

	CString wordClass;
	GetDlgItem(IDC_COMBO_WORDCLASS)->GetWindowText(wordClass);

	CString exampleSentence;
	GetDlgItem(IDC_EDIT_EXAMPLESENTENCE)->GetWindowText(exampleSentence);

	// �ܾ��忡�� �����Ѵ�.
	Long index = this->wordBook->Record((LPCTSTR)spelling, (LPCTSTR)meaning,
		(LPCTSTR)wordClass, (LPCTSTR)exampleSentence);

	// �����ͺ��̽��� �����Ѵ�.
	this->Insert(index);

	//����Ʈ�� ��Ʈ�ѿ� �׸��� �߰��Ѵ�.
	Word word = this->wordBook->GetAt(index);

	spelling = CString(word.GetSpelling().c_str());
	meaning = CString(word.GetMeaning().c_str());
	wordClass = CString(word.GetWordClass().c_str());
	exampleSentence = CString(word.GetExampleSentence().c_str());

	CString number;
	number.Format("%d", index + 1);

	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->InsertItem(index, number);
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->SetItemText(index, 1, spelling);
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->SetItemText(index, 2, meaning);
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->SetItemText(index, 3, wordClass);
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->SetItemText(index, 4, exampleSentence);
}

void WordBookForm::OnFindButtonClicked() {

	FindingForm findingForm;
	findingForm.DoModal();
}

//��ġ�� ��ư�� Ŭ������ ��
void WordBookForm::OnCorrectButtonClicked() {

	//����Ʈ�� ��Ʈ�ѿ��� �ش� �׸��� ��ġ�� �д´�.
	Long index = ((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->GetSelectionMark();

	//�ǹ�,ǰ��,������ �д´�.
	CString meaning;
	GetDlgItem(IDC_EDIT_MEANING)->GetWindowText(meaning);

	CString wordClass;
	GetDlgItem(IDC_COMBO_WORDCLASS)->GetWindowText(wordClass);

	CString exampleSentence;
	GetDlgItem(IDC_EDIT_EXAMPLESENTENCE)->GetWindowText(exampleSentence);

	//�ܾ��忡�� ��ģ��.
	index = this->wordBook->Correct(index, (LPCTSTR)meaning, 
		(LPCTSTR)wordClass, (LPCTSTR)exampleSentence);

	// �����ͺ��̽����� ��ģ��
	this->Modify(index);

	//����Ʈ�� ��Ʈ�ѿ��� �ش� �׸��� ��ģ��.
	Word word = this->wordBook->GetAt(index);
	
	meaning = CString(word.GetMeaning().c_str());
	wordClass = CString(word.GetWordClass().c_str());
	exampleSentence = CString(word.GetExampleSentence().c_str());

	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->SetItemText(index, 2, meaning);
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->SetItemText(index, 3, wordClass);
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->SetItemText(index, 4, exampleSentence);
}

// ����� ��ư�� Ŭ������ ��
void WordBookForm::OnEraseButtonClicked() {

	Long i;

	// ���� �׸��� ��ġ�� �д´�.
	Long index = ((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->GetSelectionMark();

	// �ܾ��忡�� �����.
	this->wordBook->Erase(index);
	this->Delete(index);
	
	// ����Ʈ�� ��Ʈ�ѿ��� �����.
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->DeleteItem(index);

	// ����Ʈ�� ��Ʈ�ѿ��� ���� �׸� ������ ��ȣ���� �����Ѵ�.
	CString number;

	i = index;
	while (i < this->wordBook->GetLength()) {

		number.Format("%d", i + 1);
		((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->SetItemText(i, 0, number);

		i++;
	}
}

// �����ϱ� ��ư�� Ŭ������ ��
void WordBookForm::OnArrangeButtonClicked() {

	Long i;
	
	// �ܾ��忡�� �����Ѵ�.
	this->wordBook->Arrange();

	// ����Ʈ�� ��Ʈ���� ��� �׸���� �����.
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->DeleteAllItems();

	// �ܾ����� ��뷮 ��ŭ ����Ʈ�� ��Ʈ�ѿ� �׸���� �߰��Ѵ�.
	Word word;
	CString spelling;
	CString meaning;
	CString wordClass;
	CString exampleSentence;
	CString number;

	i = 0;
	while (i < this->wordBook->GetLength()) {

		word = this->wordBook->GetAt(i);
		
		spelling = CString(word.GetSpelling().c_str());
		meaning = CString(word.GetMeaning().c_str());
		wordClass = CString(word.GetWordClass().c_str());
		exampleSentence = CString(word.GetExampleSentence().c_str());
		
		number.Format("%d", i + 1);

		((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->InsertItem(i, number);
		((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->SetItemText(i, 1, spelling);
		((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->SetItemText(i, 2, meaning);
		((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->SetItemText(i, 3, wordClass);
		((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->SetItemText(i, 4, exampleSentence);

		i++;
	}
}


// ����Ʈ�� �׸��� ����Ŭ�� ���� ��
void WordBookForm::OnListViewItemDoubleClicked(NMHDR *pNotifyStruct, LRESULT *result) {

	// �ش� �׸��� ��ġ�� �д´�.
	Long index = ((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->GetSelectionMark();

	// �ش� ��ġ�� ö��,�ǹ�,ǰ��,������ �д´�.
	CString spelling = ((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->GetItemText(index, 1);
	CString meaning = ((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->GetItemText(index, 2);
	CString wordClass = ((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->GetItemText(index, 3);
	CString exampleSentence = ((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->GetItemText(index, 4);
	
	// �ܾ ����.
	GetDlgItem(IDC_EDIT_SPELLING)->SetWindowText(spelling);
	GetDlgItem(IDC_EDIT_MEANING)->SetWindowText(meaning);
	GetDlgItem(IDC_COMBO_WORDCLASS)->SetWindowText(wordClass);
	GetDlgItem(IDC_EDIT_EXAMPLESENTENCE)->SetWindowText(exampleSentence);
}

// �ݱ� ��Ʈ���� Ŭ������ ��
void WordBookForm::OnClose() {

	if (this->wordBook != NULL) {
		// �ܾ��忡�� �����Ѵ�.
		this->Save();

		//�ܾ����� ���ش�.
		delete this->wordBook;
	}
	//�����츦 ���ش�.
	this->EndDialog(0);
}