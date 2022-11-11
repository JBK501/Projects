#include "FindingForm.h"
#include "WordBookForm.h"
#include "WordBook.h"
#include <afxcmn.h>

BEGIN_MESSAGE_MAP(FindingForm, CDialog)
	ON_BN_CLICKED(IDC_RADIO_SPELLING,OnSpellingRadioButtonClicked)
	ON_BN_CLICKED(IDC_RADIO_MEANING,OnMeaningRadioButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_FIND,OnFindButtonClicked)
	ON_NOTIFY(NM_DBLCLK,IDC_LIST_WORDS,OnListViewItemDoubleClicked)
	ON_WM_CLOSE()
END_MESSAGE_MAP()



FindingForm::FindingForm(CWnd *parent)
	:CDialog(FindingForm::IDD, parent) {

	this->indexes = NULL;
	Long count = 0;
}

// 찾기 윈도우가 생성될 때
BOOL FindingForm::OnInitDialog() {

	CDialog::OnInitDialog();

	// 철자 라디오 버튼을 선택한다.
	((CButton*)GetDlgItem(IDC_RADIO_SPELLING))->SetCheck(TRUE);

	// 리스트뷰 컨트롤 헤더를 만든다.
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->InsertColumn(0, "번호", LVCFMT_LEFT, 50);
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->InsertColumn(1, "철자", LVCFMT_LEFT, 110);
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->InsertColumn(2, "의미", LVCFMT_LEFT, 110);
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->InsertColumn(3, "품사", LVCFMT_LEFT, 70);
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->InsertColumn(4, "예문", LVCFMT_LEFT, 200);

	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->SetExtendedStyle(LVS_EX_FULLROWSELECT);

	return FALSE;
}

// 철자 라디오 버튼을 선택했을 때
void FindingForm::OnSpellingRadioButtonClicked() {

	// 의미 라디오 버튼을 선택 해제한다.
	((CButton*)GetDlgItem(IDC_RADIO_MEANING))->SetCheck(FALSE);
	
	// 의미를 지운다.
	GetDlgItem(IDC_EDIT_MEANING)->SetWindowText("");
}

// 의미 라디오 버튼을 선택했을 때
void FindingForm::OnMeaningRadioButtonClicked() {

	// 철자 라디오 버튼을 선택 해제한다.
	((CButton*)GetDlgItem(IDC_RADIO_SPELLING))->SetCheck(FALSE);

	// 철자를 지운다.
	GetDlgItem(IDC_EDIT_SPELLING)->SetWindowText("");
}

// 찾기 버튼을 클릭했을 때
void FindingForm::OnFindButtonClicked() {

	Long i;
	
	// 철자 라디오버튼, 철자, 의미 라디오버튼, 의미를 읽는다.
	int spellingRadioButton = ((CButton*)GetDlgItem(IDC_RADIO_SPELLING))->GetCheck();
	
	CString spelling;
	GetDlgItem(IDC_EDIT_SPELLING)->GetWindowText(spelling);

	int meaningRadioButton = ((CButton*)GetDlgItem(IDC_RADIO_MEANING))->GetCheck();

	CString meaning;
	GetDlgItem(IDC_EDIT_MEANING)->GetWindowText(meaning);

	// 단어장 윈도우를 찾는다.
	WordBookForm *wordBookForm = (WordBookForm*)FindWindow("#32770", "단어장");

	// 이전에 찾았던 단어위치들 삭제
	if (this->indexes != NULL) {
		delete[] this->indexes;
	}

	// 선택된 버튼에 따라서 단어장에서 찾는다.
	if (spellingRadioButton == BST_CHECKED) {
		wordBookForm->wordBook->FindBySpelling((LPCTSTR)spelling, &(this->indexes), &(this->count));
	}
	else if (meaningRadioButton == BST_CHECKED) {
		wordBookForm->wordBook->FindByMeaning((LPCTSTR)meaning, &(this->indexes), &(this->count));
	}

	// 리스트뷰 컨트롤의 모든 항목들을 지운다.
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->DeleteAllItems();

	// 찾은 개수 만큼 리스트뷰 컨트롤에 항목을 추가한다.
	Word word;
	CString wordClass;
	CString exampleSentence;
	CString number;

	i = 0;
	while (i < this->count) {

		word = wordBookForm->wordBook->GetAt(this->indexes[i]);
		
		spelling = CString(word.GetSpelling().c_str());
		meaning = CString(word.GetMeaning().c_str());
		wordClass = CString(word.GetWordClass().c_str());
		exampleSentence = CString(word.GetExampleSentence().c_str());

		CString number;
		number.Format("%d",i + 1);

		((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->InsertItem(i, number);
		((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->SetItemText(i, 1, spelling);
		((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->SetItemText(i, 2, meaning);
		((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->SetItemText(i, 3, wordClass);
		((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->SetItemText(i, 4, exampleSentence);
		
		i++;
	}
}

void FindingForm::OnListViewItemDoubleClicked(NMHDR *pNotifyStruct, LRESULT *result) {

	// 해당 항목의 위치를 읽는다.
	Long index = ((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->GetSelectionMark();

	// 해당 위치의 철자,의미,품사,예문을 읽는다.
	CString spelling = ((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->GetItemText(index, 1);
	CString meaning = ((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->GetItemText(index, 2);
	CString wordClass = ((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->GetItemText(index, 3);
	CString exampleSentence = ((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->GetItemText(index, 4);

	// 단어장 윈도우를 찾는다.
	WordBookForm *wordBookForm = (WordBookForm*)CWnd::FindWindow("#32770", "단어장");

	// 단어장 윈도우의 단어에 쓴다.
	wordBookForm->GetDlgItem(IDC_EDIT_SPELLING)->SetWindowText(spelling);
	wordBookForm->GetDlgItem(IDC_EDIT_MEANING)->SetWindowText(meaning);
	wordBookForm->GetDlgItem(IDC_COMBO_WORDCLASS)->SetWindowText(wordClass);
	wordBookForm->GetDlgItem(IDC_EDIT_EXAMPLESENTENCE)->SetWindowText(exampleSentence);

	// 단어장 윈도우의 리스트뷰 컨트롤에서 표시된 항목을 해제한다.
	((CListCtrl*)wordBookForm->GetDlgItem(IDC_LIST_WORDS))->SetItemState(-1, 0, LVIS_SELECTED);

	// 단어장 윈도우의 리스트뷰 컨트롤에서 해당하는 항목을 선택한다.
	((CListCtrl*)wordBookForm->GetDlgItem(IDC_LIST_WORDS))->SetSelectionMark(this->indexes[index]);

	// 단어장 윈도우의 리스트뷰 컨트롤에서 해당하는 항목을 표시한다.
	((CListCtrl*)wordBookForm->GetDlgItem(IDC_LIST_WORDS))->SetItemState(this->indexes[index],
		LVIS_FOCUSED | LVIS_SELECTED,
		LVIS_FOCUSED | LVIS_SELECTED);
	
	// 찾기 윈도우를 없앤다.

	if (this->indexes != NULL) {
		delete[] this->indexes;
	}

	EndDialog(0);
	
	((CListCtrl*)wordBookForm->GetDlgItem(IDC_LIST_WORDS))->SetFocus();
}

//닫기 컨트롤을 클릭했을 때
void FindingForm::OnClose() {

	//찾은 단어위치들 제거
	if (this->indexes != NULL) {
		delete[] this->indexes;
	}
	// 찾기 윈도우를 없앤다.
	EndDialog(0);
}