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

// ã�� �����찡 ������ ��
BOOL FindingForm::OnInitDialog() {

	CDialog::OnInitDialog();

	// ö�� ���� ��ư�� �����Ѵ�.
	((CButton*)GetDlgItem(IDC_RADIO_SPELLING))->SetCheck(TRUE);

	// ����Ʈ�� ��Ʈ�� ����� �����.
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->InsertColumn(0, "��ȣ", LVCFMT_LEFT, 50);
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->InsertColumn(1, "ö��", LVCFMT_LEFT, 110);
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->InsertColumn(2, "�ǹ�", LVCFMT_LEFT, 110);
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->InsertColumn(3, "ǰ��", LVCFMT_LEFT, 70);
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->InsertColumn(4, "����", LVCFMT_LEFT, 200);

	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->SetExtendedStyle(LVS_EX_FULLROWSELECT);

	return FALSE;
}

// ö�� ���� ��ư�� �������� ��
void FindingForm::OnSpellingRadioButtonClicked() {

	// �ǹ� ���� ��ư�� ���� �����Ѵ�.
	((CButton*)GetDlgItem(IDC_RADIO_MEANING))->SetCheck(FALSE);
	
	// �ǹ̸� �����.
	GetDlgItem(IDC_EDIT_MEANING)->SetWindowText("");
}

// �ǹ� ���� ��ư�� �������� ��
void FindingForm::OnMeaningRadioButtonClicked() {

	// ö�� ���� ��ư�� ���� �����Ѵ�.
	((CButton*)GetDlgItem(IDC_RADIO_SPELLING))->SetCheck(FALSE);

	// ö�ڸ� �����.
	GetDlgItem(IDC_EDIT_SPELLING)->SetWindowText("");
}

// ã�� ��ư�� Ŭ������ ��
void FindingForm::OnFindButtonClicked() {

	Long i;
	
	// ö�� ������ư, ö��, �ǹ� ������ư, �ǹ̸� �д´�.
	int spellingRadioButton = ((CButton*)GetDlgItem(IDC_RADIO_SPELLING))->GetCheck();
	
	CString spelling;
	GetDlgItem(IDC_EDIT_SPELLING)->GetWindowText(spelling);

	int meaningRadioButton = ((CButton*)GetDlgItem(IDC_RADIO_MEANING))->GetCheck();

	CString meaning;
	GetDlgItem(IDC_EDIT_MEANING)->GetWindowText(meaning);

	// �ܾ��� �����츦 ã�´�.
	WordBookForm *wordBookForm = (WordBookForm*)FindWindow("#32770", "�ܾ���");

	// ������ ã�Ҵ� �ܾ���ġ�� ����
	if (this->indexes != NULL) {
		delete[] this->indexes;
	}

	// ���õ� ��ư�� ���� �ܾ��忡�� ã�´�.
	if (spellingRadioButton == BST_CHECKED) {
		wordBookForm->wordBook->FindBySpelling((LPCTSTR)spelling, &(this->indexes), &(this->count));
	}
	else if (meaningRadioButton == BST_CHECKED) {
		wordBookForm->wordBook->FindByMeaning((LPCTSTR)meaning, &(this->indexes), &(this->count));
	}

	// ����Ʈ�� ��Ʈ���� ��� �׸���� �����.
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->DeleteAllItems();

	// ã�� ���� ��ŭ ����Ʈ�� ��Ʈ�ѿ� �׸��� �߰��Ѵ�.
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

	// �ش� �׸��� ��ġ�� �д´�.
	Long index = ((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->GetSelectionMark();

	// �ش� ��ġ�� ö��,�ǹ�,ǰ��,������ �д´�.
	CString spelling = ((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->GetItemText(index, 1);
	CString meaning = ((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->GetItemText(index, 2);
	CString wordClass = ((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->GetItemText(index, 3);
	CString exampleSentence = ((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->GetItemText(index, 4);

	// �ܾ��� �����츦 ã�´�.
	WordBookForm *wordBookForm = (WordBookForm*)CWnd::FindWindow("#32770", "�ܾ���");

	// �ܾ��� �������� �ܾ ����.
	wordBookForm->GetDlgItem(IDC_EDIT_SPELLING)->SetWindowText(spelling);
	wordBookForm->GetDlgItem(IDC_EDIT_MEANING)->SetWindowText(meaning);
	wordBookForm->GetDlgItem(IDC_COMBO_WORDCLASS)->SetWindowText(wordClass);
	wordBookForm->GetDlgItem(IDC_EDIT_EXAMPLESENTENCE)->SetWindowText(exampleSentence);

	// �ܾ��� �������� ����Ʈ�� ��Ʈ�ѿ��� ǥ�õ� �׸��� �����Ѵ�.
	((CListCtrl*)wordBookForm->GetDlgItem(IDC_LIST_WORDS))->SetItemState(-1, 0, LVIS_SELECTED);

	// �ܾ��� �������� ����Ʈ�� ��Ʈ�ѿ��� �ش��ϴ� �׸��� �����Ѵ�.
	((CListCtrl*)wordBookForm->GetDlgItem(IDC_LIST_WORDS))->SetSelectionMark(this->indexes[index]);

	// �ܾ��� �������� ����Ʈ�� ��Ʈ�ѿ��� �ش��ϴ� �׸��� ǥ���Ѵ�.
	((CListCtrl*)wordBookForm->GetDlgItem(IDC_LIST_WORDS))->SetItemState(this->indexes[index],
		LVIS_FOCUSED | LVIS_SELECTED,
		LVIS_FOCUSED | LVIS_SELECTED);
	
	// ã�� �����츦 ���ش�.

	if (this->indexes != NULL) {
		delete[] this->indexes;
	}

	EndDialog(0);
	
	((CListCtrl*)wordBookForm->GetDlgItem(IDC_LIST_WORDS))->SetFocus();
}

//�ݱ� ��Ʈ���� Ŭ������ ��
void FindingForm::OnClose() {

	//ã�� �ܾ���ġ�� ����
	if (this->indexes != NULL) {
		delete[] this->indexes;
	}
	// ã�� �����츦 ���ش�.
	EndDialog(0);
}