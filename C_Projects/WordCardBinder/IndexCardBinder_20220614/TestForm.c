#include "WordCardBinder.h"
#include "IndexCard.h"
#include "IndexCardBinder.h"
#include "TestForm.h"
#include "resource.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <CommCtrl.h>

#define IDT_TIMER 1


#pragma warning (disable : 4996)

BOOL CALLBACK TestFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {

	BOOL ret;
	

	switch (message) {

	case WM_INITDIALOG:
		ret = TestForm_OnInitDialog(hWnd, wParam, lParam);
		break;
	case WM_TIMER:
		ret = TestForm_OnTimer(hWnd, wParam, lParam);
		break;
	case WM_COMMAND:
		ret = TestForm_OnCommand(hWnd, wParam, lParam);
		break;
	case WM_CLOSE:
		ret = TestForm_OnClose(hWnd, wParam, lParam);
		break;
	default:
		ret = FALSE;
		break;
	}
	return ret;
}

BOOL TestForm_OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	BOOL ret;

	switch (LOWORD(wParam)){

	case IDC_EDIT_WORDCLASS:
		ret = TestForm_OnWordClassEditKillFocused(hWnd, wParam, lParam);
		break;
	case IDC_EDIT_MEANING:
		ret = TestForm_OnMeaningEditKillFocused(hWnd, wParam, lParam);
		break;
	case IDC_BUTTON_GRADE:
		ret = TestForm_OnGradeButtonClicked(hWnd, wParam, lParam);
		break;
	default:
		ret = FALSE;
		break;
	}
	return ret;
}



BOOL TestForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam) {	//�����찡 ������ ��

	HWND hWordCardBinder;
	WordCardBinder *wordCardBinder;
	WordCard *current;
	Long questionNumber = 1;
	Long correctCount = 0;
	char pQuestionNumber[8];
	char pQuestionCount[8];
	char pCorrectCount[8];
	HTREEITEM hRoot;
	int currentTime;
	int currentMinutes;
	int currentSeconds;
	char strCuttentTime[16];
	//WordCard(*wordCards);
	//Long learnCount = 0;

	SetProp(hWnd, "PROP_QUESTIONNUMBER", (HANDLE)questionNumber);
	SetProp(hWnd, "PROP_CORRECTCOUNT", (HANDLE)correctCount);
	
	
	//�ܾ�ī����δ� �����츦 ã�´�.
	hWordCardBinder = FindWindow("#32770", "�ܾ�ī����δ�");

	//�ܾ�ī����δ� �������� Ʈ���信�� ��Ʈ�׸��� ã�´�.
	hRoot = (HTREEITEM)SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_GETNEXTITEM,
		(WPARAM)TVGN_ROOT, (LPARAM)0);

	//�ܾ�ī����δ� �������� Ʈ���並 ���´�.
	SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_EXPAND, 
		(WPARAM)TVE_COLLAPSE, (LPARAM)hRoot);

	//�ܾ�ī����δ� �������� Ʈ���並 ��Ȱ��ȭ �Ѵ�.
	SendMessage(GetDlgItem(hWordCardBinder,IDC_TREE_WORDS), WM_ENABLE, (WPARAM)FALSE, (LPARAM)0);
	
	//�ܾ�ī����δ� �������� �ܾ �����.
	SendMessage(GetDlgItem(hWordCardBinder, IDC_STATIC_EDITSPELLING), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
	SendMessage(GetDlgItem(hWordCardBinder, IDC_STATIC_EDITMEANING), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
	SendMessage(GetDlgItem(hWordCardBinder, IDC_STATIC_EDITWORDCLASS), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
	SendMessage(GetDlgItem(hWordCardBinder, IDC_STATIC_EDITEXAMPLESENTENCE), WM_SETTEXT, (WPARAM)0, (LPARAM)"");

	//�ܾ�ī����δ� �������� �ܾ�ī����δ����� ù��° ī��� �̵��Ѵ�.
	wordCardBinder = (WordCardBinder*)GetWindowLongPtr(hWordCardBinder, GWLP_USERDATA);

	current = WordCardBinder_First(wordCardBinder);

	//�ܾ�ī���� �õ�Ƚ���� �ø���.
	current->tryCount++;

#if 0
	//���� �������� ������ ��(���� �������� ������)
	//�ܾ�ī�� �迭�� �ܿ���� �ʱ�ȭ �Ѵ�.
	wordCards = (WordCard(*))GetProp(hWordCardBinder, "PROP_WORDCARDS");

	if (wordCards != NULL) {
		free(wordCards);
	}
	wordCards = (WordCard(*))calloc(wordCardBinder->length, sizeof(WordCard));

	SetProp(hWordCardBinder, "PROP_WORDCARDS", (HANDLE)wordCards);
	SetProp(hWordCardBinder, "PROP_LEARNCOUNT", (HANDLE)learnCount);
#endif

	//���躸�� �����쿡 �ش�ī���� ö�ڸ� ����Ѵ�..
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITSPELLING2), WM_SETTEXT, (WPARAM)0, (LPARAM)current->word.spelling);

	//���躸�� �����쿡 ���� ��ȣ�� ����Ѵ�.
	sprintf(pQuestionNumber, "%d\0", questionNumber);

	SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITQUESTIONNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)pQuestionNumber);

	//���躸�� �����쿡 ���� ������ ����Ѵ�.
	sprintf(pQuestionCount, "%d\0", wordCardBinder->length);

	SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITQUESTIONCOUNT), WM_SETTEXT, (WPARAM)0, (LPARAM)pQuestionCount);

	SetProp(hWnd, "PROP_QUESTIONCOUNT", (HANDLE)wordCardBinder->length);

	//���躸�� �����쿡 ���� ������ ����Ѵ�.
	sprintf(pCorrectCount, "%d\0", correctCount);

	SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITCORRECTCOUNT), WM_SETTEXT, (WPARAM)0, (LPARAM)pCorrectCount);

	//���躸�� �������� �ǹ̸� ��Ȱ��ȭ �Ѵ�.
	SendMessage(GetDlgItem(hWnd, IDC_EDIT_MEANING), WM_ENABLE, (WPARAM)FALSE, (LPARAM)0);

	//���躸�� �������� ������ ��Ȱ��ȭ �Ѵ�.
	SendMessage(GetDlgItem(hWnd, IDC_EDIT_EXAMPLESENTENCE), WM_ENABLE, (WPARAM)FALSE, (LPARAM)0);

	//���躸�� �������� ä���ϱ� ��ư�� ��Ȱ��ȭ �Ѵ�.
	SendMessage(GetDlgItem(hWnd, IDC_EDIT_EXAMPLESENTENCE), WM_ENABLE, (WPARAM)FALSE, (LPARAM)0);

	//Ÿ�̸Ӹ� �����Ѵ�.
	SetTimer(hWnd,             // handle to main window 
		IDT_TIMER,            // timer identifier 
		1000,                 // 10-second interval 
		(TIMERPROC)NULL);     // no timer callback 
	SendMessage(hWnd, WM_TIMER, 1, 0);

	currentTime = wordCardBinder->length * 20;	//������ 20��
	SetProp(hWnd, "PROP_CURRENTTIME", (HANDLE)currentTime);

	currentMinutes = currentTime / 60;
	currentSeconds = currentTime % 60;
	sprintf(strCuttentTime, "%d�� %d��", currentMinutes,currentSeconds);

	SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITTIMER), WM_SETTEXT, (WPARAM)0, (LPARAM)strCuttentTime);

	return TRUE;
}

BOOL TestForm_OnWordClassEditKillFocused(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	HWND hWordCardBinder;
	WordCardBinder *wordCardBinder;
	TCHAR wordClass[16];

	if (HIWORD(wParam) == EN_KILLFOCUS) {

		//���躸�� �������� ǰ�縦 �д´�.
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_WORDCLASS), WM_GETTEXT, (WPARAM)16, (LPARAM)wordClass);

		//�ܾ�ī����δ� �����츦 ã�´�.
		hWordCardBinder = FindWindow("#32770", "�ܾ�ī����δ�");

		//ǰ�縦 ���Ѵ�.
		wordCardBinder = (WordCardBinder*)GetWindowLongPtr(hWordCardBinder, GWLP_USERDATA);

		if (strcmp(wordCardBinder->current->word.wordClass, wordClass) == 0) {	//������

			//���躸�� �������� �ǹ̸� Ȱ��ȭ�Ѵ�.
			SendMessage(GetDlgItem(hWnd, IDC_EDIT_MEANING),WM_ENABLE, (WPARAM)TRUE, (LPARAM)0);
		}
		else {
			SendMessage(GetDlgItem(hWnd, IDC_EDIT_WORDCLASS), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
		}
	}
	return TRUE;
}

BOOL TestForm_OnMeaningEditKillFocused(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	HWND hWordCardBinder;
	WordCardBinder *wordCardBinder;
	TCHAR meaning[128];

	if (HIWORD(wParam) == EN_KILLFOCUS) {

		//���躸�� �������� �ǹ̸� �д´�.
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_MEANING), WM_GETTEXT, (WPARAM)128, (LPARAM)meaning);

		//�ܾ�ī����δ� �����츦 ã�´�.
		hWordCardBinder = FindWindow("#32770", "�ܾ�ī����δ�");

		//�ǹ̸� ���Ѵ�.
		wordCardBinder = (WordCardBinder*)GetWindowLongPtr(hWordCardBinder, GWLP_USERDATA);

		if (strcmp(wordCardBinder->current->word.meaning, meaning) == 0) {	//������

			//���躸�� �������� ������ Ȱ��ȭ�Ѵ�.
			SendMessage(GetDlgItem(hWnd, IDC_EDIT_EXAMPLESENTENCE), WM_ENABLE, (WPARAM)TRUE, (LPARAM)0);
		}
		else {
			SendMessage(GetDlgItem(hWnd, IDC_EDIT_MEANING), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
		}
	}
	return TRUE;
}


BOOL TestForm_OnGradeButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	HWND hWordCardBinder;
	WordCardBinder *wordCardBinder;
	WordCard *current;
	TCHAR exampleSentence[256];
	Long questionNumber;
	Long correctCount;
	TCHAR pQuestionNumber[8];
	TCHAR pCorrectCount[8];
	WordCard(*wordCards);
	Long learnCount;
	Long questionCount;

	WordCard wordCard;
	IndexCardBinder *indexCardBinder;
	IndexCard *indexCardIndex;
	Long index;
	TCHAR alphabat[2];
	TCHAR spelling[32];
	TCHAR wordClass[16];
	TVITEM tvi = { 0, };
	HTREEITEM hRoot;
	HTREEITEM hAlphabat;
	HTREEITEM hSpelling;
	HTREEITEM hWordClass;


	if (HIWORD(wParam) == BN_CLICKED) {

		//���躸�� �������� ������ �д´�.
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_EXAMPLESENTENCE), WM_GETTEXT, (WPARAM)256, (LPARAM)exampleSentence);

		//�ܾ�ī����δ� �����츦 ã�´�.
		hWordCardBinder = FindWindow("#32770", "�ܾ�ī����δ�");

		wordCardBinder = (WordCardBinder*)GetWindowLongPtr(hWordCardBinder, GWLP_USERDATA);

		//������ ���Ѵ�.
		if (strcmp(wordCardBinder->current->word.exampleSentence, exampleSentence) == 0) {

			//������
			//�ܾ�ī���� ����Ƚ���� �ø���.
			wordCardBinder->current->successfulCount++;

			//���躸�� �����쿡 ���� ������ �ø���..
			correctCount = (Long)GetProp(hWnd, "PROP_CORRECTCOUNT");
			correctCount++;
			SetProp(hWnd, "PROP_CORRECTCOUNT", (HANDLE)correctCount);
			
			sprintf(pCorrectCount, "%d\0", correctCount);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITCORRECTCOUNT), WM_SETTEXT, (WPARAM)0, (LPARAM)pCorrectCount);

			//�ܾ�ī�� ���δ� �����쿡�� ������.

			//����ö���� ���������� �ܾ�ī�帵ũ����
			current = wordCardBinder->current;

			//�ܾ�ī����δ� �������� �ܾ�ī����δ����� ������.
			wordCard = TakeOut(wordCardBinder, wordCardBinder->current);

			//���� ī�带 �����Ѵ�.
			wordCards = (WordCard(*))GetProp(hWordCardBinder, "PROP_WORDCARDS");

			learnCount = (Long)GetProp(hWordCardBinder, "PROP_LEARNCOUNT");

			wordCards[learnCount] = wordCard;

			//�ϱ��� ������ �ø���.
			learnCount++;
			SetProp(hWordCardBinder, "PROP_LEARNCOUNT", (HANDLE)learnCount);

			//����ö���� ������.
			indexCardBinder = (IndexCardBinder*)GetProp(hWordCardBinder, "PROP_INDEXCARDBINDER");

			indexCardIndex = IndexCardBinder_TakeOut(indexCardBinder, current, wordCard.word.spelling[0]);

			//�ܾ�ī����δ� �������� Ʈ���信�� ��Ʈ�׸��� ã�´�.
			hRoot = (HTREEITEM)SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_GETNEXTITEM,
				(WPARAM)TVGN_ROOT, (LPARAM)0);

			//�ܾ�ī����δ� �������� Ʈ���信�� ���ĺ��׸��� ã�´�.
			hAlphabat = (HTREEITEM)SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_GETNEXTITEM,
				(WPARAM)TVGN_CHILD, (LPARAM)hRoot);

			tvi.mask = TVIF_TEXT | TVIF_HANDLE;
			tvi.hItem = hAlphabat;
			tvi.pszText = alphabat;
			tvi.cchTextMax = 2;

			SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_GETITEM,
				(WPARAM)0, (LPARAM)&tvi);

			while (hAlphabat != NULL && wordCard.word.spelling[0] != alphabat[0] + 32) {

				hAlphabat = (HTREEITEM)SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_GETNEXTITEM,
					(WPARAM)TVGN_NEXT, (LPARAM)hAlphabat);

				tvi.hItem = hAlphabat;
				SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_GETITEM,
					(WPARAM)0, (LPARAM)&tvi);
			}

			//�ܾ�ī����δ� �������� Ʈ���信�� ö�� �׸��� ã�´�.
			hSpelling = (HTREEITEM)SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_GETNEXTITEM,
				(WPARAM)TVGN_CHILD, (LPARAM)hAlphabat);

			tvi.hItem = hSpelling;
			tvi.pszText = spelling;
			tvi.cchTextMax = 32;

			SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_GETITEM,
				(WPARAM)0, (LPARAM)&tvi);

			while (hSpelling != NULL && strcmp(wordCard.word.spelling, spelling) != 0) {

				hSpelling = (HTREEITEM)SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_GETNEXTITEM,
					(WPARAM)TVGN_NEXT, (LPARAM)hSpelling);

				tvi.hItem = hSpelling;
				SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_GETITEM,
					(WPARAM)0, (LPARAM)&tvi);
			}

			//�ܾ�ī����δ� �������� Ʈ���信�� ǰ�� �׸��� ã�´�.
			hWordClass = (HTREEITEM)SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_GETNEXTITEM,
				(WPARAM)TVGN_CHILD, (LPARAM)hSpelling);

			tvi.hItem = hWordClass;
			tvi.pszText = wordClass;
			tvi.cchTextMax = 16;

			SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_GETITEM,
				(WPARAM)0, (LPARAM)&tvi);

			while (hWordClass != NULL && strcmp(wordCard.word.wordClass, wordClass) != 0) {

				hWordClass = (HTREEITEM)SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_GETNEXTITEM,
					(WPARAM)TVGN_NEXT, (LPARAM)hWordClass);

				tvi.hItem = hWordClass;
				SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_GETITEM,
					(WPARAM)0, (LPARAM)&tvi);
			}

			//�ܾ�ī����δ� �������� Ʈ���信�� ã�� ǰ�縦 �����.
			SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_DELETEITEM,
				(WPARAM)0, (LPARAM)hWordClass);

			if (indexCardIndex != NULL) {	//����ī�尡 ������

				//����ī�忡�� ö�ڷ� ã�´�.
				index = IndexCard_FindBySpellings(indexCardIndex, wordCard.word.spelling);

				if (index == -1) {	//�� ã������

					//�ܾ�ī����δ� �������� Ʈ���信�� ö�ڸ� �����.
					SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_DELETEITEM,
						(WPARAM)0, (LPARAM)hSpelling);
				}

			}
			else {	//����ī�尡 ������

				//�ܾ�ī����δ� �������� Ʈ���信�� ö�ڸ� �����.
				SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_DELETEITEM,
					(WPARAM)0, (LPARAM)hSpelling);
				//�ܾ�ī����δ� �������� Ʈ���信�� ���ĺ��� �����.
				SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_DELETEITEM,
					(WPARAM)0, (LPARAM)hAlphabat);
			}
#if 0
			//�ܾ�ī����δ� �������� �ܾ�ī����δ����� ī�尡 ������
			if (wordCardBinder->current != NULL) {

				//�ܾ�ī����δ� �����쿡 ����ī�带 ����Ѵ�.
				SendMessage(GetDlgItem(hWordCardBinder, IDC_STATIC_EDITSPELLING), WM_SETTEXT,
					(WPARAM)0, (LPARAM)wordCardBinder->current->word.spelling);
				SendMessage(GetDlgItem(hWordCardBinder, IDC_STATIC_EDITMEANING), WM_SETTEXT,
					(WPARAM)0, (LPARAM)wordCardBinder->current->word.meaning);
				SendMessage(GetDlgItem(hWordCardBinder, IDC_STATIC_EDITWORDCLASS), WM_SETTEXT,
					(WPARAM)0, (LPARAM)wordCardBinder->current->word.wordClass);
				SendMessage(GetDlgItem(hWordCardBinder, IDC_STATIC_EDITEXAMPLESENTENCE), WM_SETTEXT,
					(WPARAM)0, (LPARAM)wordCardBinder->current->word.exampleSentence);

				//�ܾ�ī����δ� �������� Ʈ���信�� ���ĺ��׸��� ã�´�.
				hAlphabat = (HTREEITEM)SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_GETNEXTITEM,
					(WPARAM)TVGN_CHILD, (LPARAM)hRoot);

				tvi.hItem = hAlphabat;
				tvi.pszText = alphabat;
				tvi.cchTextMax = 2;

				SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_GETITEM,
					(WPARAM)0, (LPARAM)&tvi);

				while (hAlphabat != NULL && wordCardBinder->current->word.spelling[0] != alphabat[0] + 32) {

					hAlphabat = (HTREEITEM)SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_GETNEXTITEM,
						(WPARAM)TVGN_NEXT, (LPARAM)hAlphabat);

					tvi.hItem = hAlphabat;
					SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_GETITEM,
						(WPARAM)0, (LPARAM)&tvi);
				}

				//�ܾ�ī����δ� �������� Ʈ���信�� ö�� �׸��� ã�´�.
				hSpelling = (HTREEITEM)SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_GETNEXTITEM,
					(WPARAM)TVGN_CHILD, (LPARAM)hAlphabat);

				tvi.hItem = hSpelling;
				tvi.pszText = spelling;
				tvi.cchTextMax = 32;

				SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_GETITEM,
					(WPARAM)0, (LPARAM)&tvi);

				while (hSpelling != NULL && strcmp(wordCardBinder->current->word.spelling, spelling) != 0) {

					hSpelling = (HTREEITEM)SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_GETNEXTITEM,
						(WPARAM)TVGN_NEXT, (LPARAM)hSpelling);

					tvi.hItem = hSpelling;
					SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_GETITEM,
						(WPARAM)0, (LPARAM)&tvi);
				}

				//�ܾ�ī����δ� �������� Ʈ���信�� ǰ�� �׸��� ã�´�.
				hWordClass = (HTREEITEM)SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_GETNEXTITEM,
					(WPARAM)TVGN_CHILD, (LPARAM)hSpelling);

				tvi.hItem = hWordClass;
				tvi.pszText = wordClass;
				tvi.cchTextMax = 16;

				SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_GETITEM,
					(WPARAM)0, (LPARAM)&tvi);

				while (hWordClass != NULL && strcmp(wordCardBinder->current->word.wordClass, wordClass) != 0) {

					hWordClass = (HTREEITEM)SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_GETNEXTITEM,
						(WPARAM)TVGN_NEXT, (LPARAM)hWordClass);

					tvi.hItem = hWordClass;
					SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_GETITEM,
						(WPARAM)0, (LPARAM)&tvi);
				}

				//�ܾ�ī����δ� �������� Ʈ���信�� ��Ʈ�� ��ģ��.
				SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_EXPAND,
					(WPARAM)TVE_EXPAND, (LPARAM)hRoot);

				//�ܾ�ī����δ� �������� Ʈ���信�� ���ĺ��� ��ģ��.
				SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_EXPAND,
					(WPARAM)TVE_EXPAND, (LPARAM)hAlphabat);

				//�ܾ�ī����δ� �������� Ʈ���信�� ö�ڸ� ��ģ��.
				SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_EXPAND,
					(WPARAM)TVE_EXPAND, (LPARAM)hSpelling);

				//�ܾ�ī����δ� �������� Ʈ���信�� �ش� �׸��� ǥ���Ѵ�.
				SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), WM_SETFOCUS, (WPARAM)0, (LPARAM)0);

				SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_SELECTITEM,
					(WPARAM)TVGN_CARET, (LPARAM)hWordClass);
			}
			else {

				//������ ��ĭ�� ����Ѵ�.
				SendMessage(GetDlgItem(hWordCardBinder, IDC_STATIC_EDITSPELLING), WM_SETTEXT,
					(WPARAM)0, (LPARAM)"");
				SendMessage(GetDlgItem(hWordCardBinder, IDC_STATIC_EDITMEANING), WM_SETTEXT,
					(WPARAM)0, (LPARAM)"");
				SendMessage(GetDlgItem(hWordCardBinder, IDC_STATIC_EDITWORDCLASS), WM_SETTEXT,
					(WPARAM)0, (LPARAM)"");
				SendMessage(GetDlgItem(hWordCardBinder, IDC_STATIC_EDITEXAMPLESENTENCE), WM_SETTEXT,
					(WPARAM)0, (LPARAM)"");
			}
#endif

			questionCount = (Long)GetProp(hWnd, "PROP_QUESTIONCOUNT");
			//���� ��ȣ�� ��ü ���� ���� ���� ���� ��
			questionNumber = (Long)GetProp(hWnd, "PROP_QUESTIONNUMBER");
			if (questionNumber < questionCount) {

				//�ܾ�ī����δ����� ����ī��� �̵��Ѵ�.
				//current = WordCardBinder_Next(wordCardBinder);
				current = wordCardBinder->current;

				//�ܾ�ī���� �õ�Ƚ���� �ø���.
				current->tryCount++;

				//���躸�� �����쿡 �ش�ī���� ö�ڸ� ����Ѵ�..
				SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITSPELLING2), WM_SETTEXT,
					(WPARAM)0, (LPARAM)current->word.spelling);

				//���躸�� �����쿡 ���� ��ȣ�� ����Ѵ�.
				questionNumber++;
				SetProp(hWnd, "PROP_QUESTIONNUMBER", (HANDLE)questionNumber);

				sprintf(pQuestionNumber, "%d\0", questionNumber);
				SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITQUESTIONNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)pQuestionNumber);

				//���躸�� �������� ǰ�縦 �����.
				SendMessage(GetDlgItem(hWnd, IDC_EDIT_WORDCLASS), WM_SETTEXT, (WPARAM)0, (LPARAM)"");

				//���躸�� �������� �ǹ̸� ��Ȱ��ȭ �Ѵ�.
				SendMessage(GetDlgItem(hWnd, IDC_EDIT_MEANING), WM_ENABLE, (WPARAM)FALSE, (LPARAM)0);
				SendMessage(GetDlgItem(hWnd, IDC_EDIT_MEANING), WM_SETTEXT, (WPARAM)0, (LPARAM)"");

				//���躸�� �������� ������ ��Ȱ��ȭ �Ѵ�.
				SendMessage(GetDlgItem(hWnd, IDC_EDIT_EXAMPLESENTENCE), WM_ENABLE, (WPARAM)FALSE, (LPARAM)0);
				SendMessage(GetDlgItem(hWnd, IDC_EDIT_EXAMPLESENTENCE), WM_SETTEXT, (WPARAM)0, (LPARAM)"");


				//���躸�� �������� ä���ϱ� ��ư�� ��Ȱ��ȭ �Ѵ�.
				SendMessage(GetDlgItem(hWnd, IDC_EDIT_EXAMPLESENTENCE), WM_ENABLE, (WPARAM)FALSE, (LPARAM)0);
			}
			else {
				//���� ��ȣ�� ��ü ���� ������ ���� ��
				TestForm_OnClose(hWnd, wParam, lParam);
			}
		}
		else {
			//�ٸ���
			//������ �����.
			SendMessage(GetDlgItem(hWnd, IDC_EDIT_EXAMPLESENTENCE), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
		}
	}
	return TRUE;
}

BOOL TestForm_OnTimer(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	int currentTime;
	int currentMinutes;
	int currentSeconds;
	char strCurrentTime[16];

	//SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITTIMER), WM_GETTEXT, (WPARAM)8, (LPARAM)strCurrentTime);

	currentTime = (int)GetProp(hWnd, "PROP_CURRENTTIME");
	currentTime--;
	SetProp(hWnd, "PROP_CURRENTTIME", (HANDLE)currentTime);

	currentMinutes = currentTime / 60;
	currentSeconds = currentTime % 60;

	sprintf(strCurrentTime, "%d�� %d��", currentMinutes, currentSeconds);

	//sprintf(strCurrentTime, "%d��", currentTime);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITTIMER), WM_SETTEXT, (WPARAM)0, (LPARAM)strCurrentTime);
	if (currentTime == 0) {
		TestForm_OnClose(hWnd, wParam, lParam);
	}

	return TRUE;
}


BOOL TestForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam) {	//�ݱ� ��Ʈ���� Ŭ������ ��

	HWND hWordCardBinder;
	WordCardBinder *wordCardBinder;
	WordCard *current;
	Long correctCount;
	float score;
	TCHAR pScore[8];
	TCHAR alphabat[2];
	TCHAR spelling[32];
	TCHAR wordClass[16];
	int message;
	TVITEM tvi = { 0, };
	HTREEITEM hRoot;
	HTREEITEM hAlphabat;
	HTREEITEM hSpelling;
	HTREEITEM hWordClass;


	//�ܾ�ī����δ� �����츦 ã�´�.
	hWordCardBinder = FindWindow("#32770", "�ܾ�ī����δ�");

	//�ܾ�ī����δ� �������� Ʈ���並 Ȱ��ȭ �Ѵ�.
	SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), WM_ENABLE, (WPARAM)TRUE, (LPARAM)0);

	wordCardBinder = (WordCardBinder*)GetWindowLongPtr(hWordCardBinder, GWLP_USERDATA);

	//�޽��� �ڽ��� ����Ѵ�.
	correctCount = (Long)GetProp(hWnd,"PROP_CORRECTCOUNT");

	score = correctCount / ((wordCardBinder->length + correctCount) * 1.0F) * 100;
	sprintf(pScore, "%.0f��", score);

	message = MessageBox(hWnd, (LPCSTR)pScore, (LPCSTR)"������",MB_OK);

	if (message = IDOK) {

		
		if (wordCardBinder->length > 0) {

			//�ܾ�ī����δ� �������� �ܾ�ī����δ����� ù��° ī��� �̵��Ѵ�.
			current = WordCardBinder_First(wordCardBinder);

			//�ش�ī�带 ����Ѵ�.
			SendMessage(GetDlgItem(hWordCardBinder, IDC_STATIC_EDITSPELLING), WM_SETTEXT,
				(WPARAM)0, (LPARAM)current->word.spelling);
			SendMessage(GetDlgItem(hWordCardBinder, IDC_STATIC_EDITMEANING), WM_SETTEXT,
				(WPARAM)0, (LPARAM)current->word.meaning);
			SendMessage(GetDlgItem(hWordCardBinder, IDC_STATIC_EDITWORDCLASS), WM_SETTEXT,
				(WPARAM)0, (LPARAM)current->word.wordClass);
			SendMessage(GetDlgItem(hWordCardBinder, IDC_STATIC_EDITEXAMPLESENTENCE), WM_SETTEXT,
				(WPARAM)0, (LPARAM)current->word.exampleSentence);


			

			//�ܾ�ī����δ� �������� Ʈ���信�� ��Ʈ�׸��� ã�´�.
			hRoot = (HTREEITEM)SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_GETNEXTITEM,
				(WPARAM)TVGN_ROOT, (LPARAM)0);

			//�ܾ�ī����δ� �������� Ʈ���信�� ���ĺ��׸��� ã�´�.
			hAlphabat = (HTREEITEM)SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_GETNEXTITEM,
				(WPARAM)TVGN_CHILD, (LPARAM)hRoot);

			tvi.mask = TVIF_TEXT | TVIF_HANDLE;
			tvi.hItem = hAlphabat;
			tvi.pszText = alphabat;
			tvi.cchTextMax = 2;

			SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_GETITEM,
				(WPARAM)0, (LPARAM)&tvi);

			while (hAlphabat != NULL && current->word.spelling[0] != alphabat[0] + 32) {

				hAlphabat = (HTREEITEM)SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_GETNEXTITEM,
					(WPARAM)TVGN_NEXT, (LPARAM)hAlphabat);

				tvi.hItem = hAlphabat;
				SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_GETITEM,
					(WPARAM)0, (LPARAM)&tvi);
			}

			//�ܾ�ī����δ� �������� Ʈ���信�� ö�� �׸��� ã�´�.
			hSpelling = (HTREEITEM)SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_GETNEXTITEM,
				(WPARAM)TVGN_CHILD, (LPARAM)hAlphabat);

			tvi.hItem = hSpelling;
			tvi.pszText = spelling;
			tvi.cchTextMax = 32;

			SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_GETITEM,
				(WPARAM)0, (LPARAM)&tvi);

			while (hSpelling != NULL && strcmp(current->word.spelling, spelling) != 0) {

				hSpelling = (HTREEITEM)SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_GETNEXTITEM,
					(WPARAM)TVGN_NEXT, (LPARAM)hSpelling);

				tvi.hItem = hSpelling;
				SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_GETITEM,
					(WPARAM)0, (LPARAM)&tvi);
			}

			//�ܾ�ī����δ� �������� Ʈ���信�� ǰ�� �׸��� ã�´�.
			hWordClass = (HTREEITEM)SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_GETNEXTITEM,
				(WPARAM)TVGN_CHILD, (LPARAM)hSpelling);

			tvi.hItem = hWordClass;
			tvi.pszText = wordClass;
			tvi.cchTextMax = 16;

			SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_GETITEM,
				(WPARAM)0, (LPARAM)&tvi);

			while (hWordClass != NULL && strcmp(current->word.wordClass, wordClass) != 0) {

				hWordClass = (HTREEITEM)SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_GETNEXTITEM,
					(WPARAM)TVGN_NEXT, (LPARAM)hWordClass);

				tvi.hItem = hWordClass;
				SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_GETITEM,
					(WPARAM)0, (LPARAM)&tvi);
			}

			//�ܾ�ī����δ� �������� Ʈ���信�� ��Ʈ�� ��ģ��.
			SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_EXPAND,
				(WPARAM)TVE_EXPAND, (LPARAM)hRoot);

			//�ܾ�ī����δ� �������� Ʈ���信�� ���ĺ��� ��ģ��.
			SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_EXPAND,
				(WPARAM)TVE_EXPAND, (LPARAM)hAlphabat);

			//�ܾ�ī����δ� �������� Ʈ���信�� ö�ڸ� ��ģ��.
			SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_EXPAND,
				(WPARAM)TVE_EXPAND, (LPARAM)hSpelling);

			//�ܾ�ī����δ� �������� Ʈ���信�� �ش� �׸��� ǥ���Ѵ�.
			SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), WM_SETFOCUS, (WPARAM)0, (LPARAM)0);

			SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_SELECTITEM,
				(WPARAM)TVGN_CARET, (LPARAM)hWordClass);
		}
		else {
			
		//������ ��ĭ�� ����Ѵ�.
		SendMessage(GetDlgItem(hWordCardBinder, IDC_STATIC_EDITSPELLING), WM_SETTEXT,
			(WPARAM)0, (LPARAM)"");
		SendMessage(GetDlgItem(hWordCardBinder, IDC_STATIC_EDITMEANING), WM_SETTEXT,
			(WPARAM)0, (LPARAM)"");
		SendMessage(GetDlgItem(hWordCardBinder, IDC_STATIC_EDITWORDCLASS), WM_SETTEXT,
			(WPARAM)0, (LPARAM)"");
		SendMessage(GetDlgItem(hWordCardBinder, IDC_STATIC_EDITEXAMPLESENTENCE), WM_SETTEXT,
			(WPARAM)0, (LPARAM)"");
		}
		
		RemoveProp(hWnd, "PROP_CORRECTCOUNT");
		RemoveProp(hWnd, "PROP_QUESTIONNUMBER");
		RemoveProp(hWnd, "PROP_QUESTIONCOUNT");
		RemoveProp(hWnd, "PROP_CURRENTTIME");

		KillTimer(hWnd, IDT_TIMER);

		EndDialog(hWnd, 0);
	}
	return TRUE;
}
