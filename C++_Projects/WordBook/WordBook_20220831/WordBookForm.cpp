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

// 적재하다.
void WordBookForm::Load() {

	// 데이터 베이스에서 단어들을 가져온다.
	CDatabase db;
	CRecordset rs(&db);
	CString sql = "SELECT Word.spelling,Word.meaning,Word.wordClass,Word.exampleSentence FROM Word;";

	db.OpenEx("DSN=WordBook;UID=root;PWD=0000");
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);

	// 가져온 개수만큼 단어장에 기재한다.
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

// 기본키를 구하다.
CString WordBookForm::GetGode() {

	// 오늘 날짜를 구한다.
	Date today_ = Date::Today();

	CString today;
	today.Format("%04d%02d%02d", today_.GetYear(), today_.GetMonth(), today_.GetDay());

	CDatabase db;
	CRecordset rs(&db);
	CString sql = "SELECT Word.code FROM Word ORDER BY code DESC;";

	db.OpenEx("DSN=WordBook;UID=root;PWD=0000");	// Connection
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);	// Request & Response

	CString code;
	code.Format("%s000", (LPCTSTR)today);	// 코드 초기화

	// db에 데이터가 있으면
	if (!rs.IsEOF()) {

		// 이전 코드를 구한다.
		CString previousCode;
		rs.GetFieldValue((short)0, previousCode);

		// 이전 코드의 날짜를 구한다.
		CString previousDate = previousCode.Left(8);

		// 오늘날짜와 같다면
		if (today.Compare(previousDate) == 0) {
			code = CString(previousCode);	// 이전코드를 사용한다.
		}
	}

	// 번호를 구한다.
	CString numbers = code.Right(3);
	
	Long number = atoi((LPCTSTR)numbers);

	// 번호를 더한다.
	number++;

	// 새로운 코드를 구한다.
	CString newCode;
	newCode.Format("%s%03d", (LPCTSTR)today, number);

	rs.Close();
	db.Close();	//DisConnection

	return newCode;
}

void WordBookForm::Insert(Long index) {

	Word word = this->wordBook->GetAt(index);	// 기재한 단어를 가져온다.
	CString code = this->GetGode();	// 기본키를 구한다.

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

// 데이터베이스에서 수정하다.
void WordBookForm::Modify(Long index) {

	Word word = this->wordBook->GetAt(index);	// 수정한 단어를 가져온다.

	CDatabase db;
	CRecordset rs(&db);
	CString sql = "SELECT Word.code FROM Word;";	// 기본키들을 가져온다.

	db.OpenEx("DSN=WordBook;UID=root;PWD=0000");	// Connection
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);	// Request & Response

	// 데이터베이스에서 수정한 위치에 해당하는 기본키를 찾는다.
	CString code;
	
	Long i = 0;
	while (!rs.IsEOF() && i <= index) {

		rs.GetFieldValue((short)0, code);

		rs.MoveNext();
		i++;
	}

	// 데이터베이스에서 수정한다.
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
	CString sql = "SELECT Word.code FROM Word;";	// 기본키들을 가져온다.

	db.OpenEx("DSN=WordBook;UID=root;PWD=0000");	// Connection
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);	// Request & Response

	// 데이터베이스에서 수정한 위치에 해당하는 기본키를 찾는다.
	CString code;

	Long i = 0;
	while (!rs.IsEOF() && i <= index) {

		rs.GetFieldValue((short)0, code);

		rs.MoveNext();
		i++;
	}

	// 데이터베이스에서 삭제한다.
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

	// 단어장 데이터베이스의 모든 단어들을 삭제한다.
	sql = CString("DELETE FROM Word;");
	db.ExecuteSQL(sql);

	// 단어장의 사용량 만큼 데이터베이스에 단어들을 추가한다.
	Word word;
	CString code;
	Long i = 0;

	while (i < this->wordBook->GetLength()) {

		word = this->wordBook->GetAt(i);	// 단어를 가져온다.
		rs.GetFieldValue((short)0, code);	// 가져온 코드를 읽는다.

		// 단어장 데이터베이스의 단어 테이블에 추가한다.
		sql.Format("INSERT INTO Word(code,spelling,meaning,wordClass,exampleSentence) "
			"VALUES('%s','%s','%s','%s','%s');", (LPCTSTR)code, word.GetSpelling().c_str(),
			word.GetMeaning().c_str(), word.GetWordClass().c_str(),
			word.GetExampleSentence().c_str());

		db.ExecuteSQL(sql);

		rs.MoveNext();	// 다음 키로 이동한다.
		i++;
	}

	rs.Close();
	db.Close();
}

// 윈도우가 생성될 때
BOOL WordBookForm::OnInitDialog() {

	CDialog::OnInitDialog();

	Long i = 0;

	// 단어장을 만든다.
	this->wordBook = new WordBook;

	// 단어장에 적재한다.
	this->Load();

	// 콤보박스에 목록을 추가한다.
	TCHAR wordClasses[][16] = { "명사","대명사","동사","형용사","부사","전치사","접속사","감탄사" };

	i = 0;
	for (i = 0; i < sizeof(wordClasses) / sizeof(wordClasses[i]); i++) {
		((CComboBox*)GetDlgItem(IDC_COMBO_WORDCLASS))->AddString(wordClasses[i]);
	}

	// 리스트뷰 컨트롤 헤더를 만든다.
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->InsertColumn(0, "번호", LVCFMT_LEFT, 50);
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->InsertColumn(1, "철자", LVCFMT_LEFT, 110);
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->InsertColumn(2, "의미", LVCFMT_LEFT, 110);
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->InsertColumn(3, "품사", LVCFMT_LEFT, 70);
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->InsertColumn(4, "예문", LVCFMT_LEFT, 200);

	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->SetExtendedStyle(LVS_EX_FULLROWSELECT);

	// 적재한 개수만큼 리스트뷰 컨트롤에 항목을 추가한다.
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

// 기재하기 버튼을 클릭했을 때
void WordBookForm::OnRecordButtonClicked() {

	// 철자,의미,품사,예문을 읽는다.
	CString spelling;
	GetDlgItem(IDC_EDIT_SPELLING)->GetWindowText(spelling);

	CString meaning;
	GetDlgItem(IDC_EDIT_MEANING)->GetWindowText(meaning);

	CString wordClass;
	GetDlgItem(IDC_COMBO_WORDCLASS)->GetWindowText(wordClass);

	CString exampleSentence;
	GetDlgItem(IDC_EDIT_EXAMPLESENTENCE)->GetWindowText(exampleSentence);

	// 단어장에서 기재한다.
	Long index = this->wordBook->Record((LPCTSTR)spelling, (LPCTSTR)meaning,
		(LPCTSTR)wordClass, (LPCTSTR)exampleSentence);

	// 데이터베이스에 저장한다.
	this->Insert(index);

	//리스트뷰 컨트롤에 항목을 추가한다.
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

//고치기 버튼을 클릭했을 때
void WordBookForm::OnCorrectButtonClicked() {

	//리스트뷰 컨트롤에서 해당 항목의 위치를 읽는다.
	Long index = ((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->GetSelectionMark();

	//의미,품사,예문을 읽는다.
	CString meaning;
	GetDlgItem(IDC_EDIT_MEANING)->GetWindowText(meaning);

	CString wordClass;
	GetDlgItem(IDC_COMBO_WORDCLASS)->GetWindowText(wordClass);

	CString exampleSentence;
	GetDlgItem(IDC_EDIT_EXAMPLESENTENCE)->GetWindowText(exampleSentence);

	//단어장에서 고친다.
	index = this->wordBook->Correct(index, (LPCTSTR)meaning, 
		(LPCTSTR)wordClass, (LPCTSTR)exampleSentence);

	// 데이터베이스에서 고친다
	this->Modify(index);

	//리스트뷰 컨트롤에서 해당 항목을 고친다.
	Word word = this->wordBook->GetAt(index);
	
	meaning = CString(word.GetMeaning().c_str());
	wordClass = CString(word.GetWordClass().c_str());
	exampleSentence = CString(word.GetExampleSentence().c_str());

	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->SetItemText(index, 2, meaning);
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->SetItemText(index, 3, wordClass);
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->SetItemText(index, 4, exampleSentence);
}

// 지우기 버튼을 클릭했을 때
void WordBookForm::OnEraseButtonClicked() {

	Long i;

	// 지울 항목의 위치를 읽는다.
	Long index = ((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->GetSelectionMark();

	// 단어장에서 지운다.
	this->wordBook->Erase(index);
	this->Delete(index);
	
	// 리스트뷰 컨트롤에서 지운다.
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->DeleteItem(index);

	// 리스트뷰 컨트롤에서 지운 항목 이후의 번호들을 수정한다.
	CString number;

	i = index;
	while (i < this->wordBook->GetLength()) {

		number.Format("%d", i + 1);
		((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->SetItemText(i, 0, number);

		i++;
	}
}

// 정리하기 버튼을 클릭했을 때
void WordBookForm::OnArrangeButtonClicked() {

	Long i;
	
	// 단어장에서 정리한다.
	this->wordBook->Arrange();

	// 리스트뷰 컨트롤의 모든 항목들을 지운다.
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->DeleteAllItems();

	// 단어장의 사용량 만큼 리스트뷰 컨트롤에 항목들을 추가한다.
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


// 리스트뷰 항목을 더블클릭 했을 때
void WordBookForm::OnListViewItemDoubleClicked(NMHDR *pNotifyStruct, LRESULT *result) {

	// 해당 항목의 위치를 읽는다.
	Long index = ((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->GetSelectionMark();

	// 해당 위치의 철자,의미,품사,예문을 읽는다.
	CString spelling = ((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->GetItemText(index, 1);
	CString meaning = ((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->GetItemText(index, 2);
	CString wordClass = ((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->GetItemText(index, 3);
	CString exampleSentence = ((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->GetItemText(index, 4);
	
	// 단어에 쓴다.
	GetDlgItem(IDC_EDIT_SPELLING)->SetWindowText(spelling);
	GetDlgItem(IDC_EDIT_MEANING)->SetWindowText(meaning);
	GetDlgItem(IDC_COMBO_WORDCLASS)->SetWindowText(wordClass);
	GetDlgItem(IDC_EDIT_EXAMPLESENTENCE)->SetWindowText(exampleSentence);
}

// 닫기 컨트롤을 클릭했을 때
void WordBookForm::OnClose() {

	if (this->wordBook != NULL) {
		// 단어장에서 저장한다.
		this->Save();

		//단어장을 없앤다.
		delete this->wordBook;
	}
	//윈도우를 없앤다.
	this->EndDialog(0);
}