#include "WordCardBinder.h"
#include "IndexCard.h"
#include "IndexCardBinder.h"
#include "ResultForm.h"
#include "resource.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <CommCtrl.h>

#pragma warning (disable:4996)

BOOL CALLBACK ResultFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {

	BOOL ret;

	switch (message) {

	case WM_INITDIALOG:
		ret = ResultForm_OnInitDialog(hWnd, wParam, lParam);
		break;
	case WM_COMMAND:
		ret = ResultForm_OnCommand(hWnd, wParam, lParam);
		break;
	case WM_CLOSE:
		ret = ResultForm_OnClose(hWnd, wParam, lParam);
		break;
	default:
		ret = FALSE;
		break;
	}
	return ret;
}

BOOL ResultForm_OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	BOOL ret;

	switch (LOWORD(wParam)) {

		case IDC_BUTTON_FIRST:
			ret = ResultForm_OnFirstButtonClicked(hWnd, wParam, lParam);
			break;
		case IDC_BUTTON_PREVIOUS:
			ret = ResultForm_OnPreviousButtonClicked(hWnd, wParam, lParam);
			break;
		case IDC_BUTTON_NEXT:
			ret = ResultForm_OnNextButtonClicked(hWnd, wParam, lParam);
			break;
		case IDC_BUTTON_LAST:
			ret = ResultForm_OnLastButtonClicked(hWnd, wParam, lParam);
			break;
		case IDC_BUTTON_TAKEIN:
			ret = ResultForm_OnTakeInButtonClicked(hWnd, wParam, lParam);
			break;
		default:
			ret = FALSE;
			break;
	}
	return ret;
}


BOOL ResultForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	HWND hWordCardBinder;
	WordCard(*wordCards);
	Long learnCount;
	Long index;
	TCHAR strTryCount[8];
	TCHAR strSuccessfulCount[8];
	float correctRate;
	TCHAR strCorrectRate[8];

	//�ܾ�ī����δ� �����츦 ã�´�.
	hWordCardBinder = FindWindow("#32770", "�ܾ�ī����δ�");

	//�ܾ�ī�� �迭, �ܿ� ������ �����´�.
	wordCards = (WordCard(*))GetProp(hWordCardBinder, "PROP_WORDCARDS");
	learnCount = (Long)GetProp(hWordCardBinder, "PROP_LEARNCOUNT");

	//ù��° ī��� �̵��Ѵ�.
	index = 0;

	//������ġ�� �����Ѵ�.
	SetProp(hWnd, "PROP_INDEX", (HANDLE)index);

	//�ش�ī�带 ����Ѵ�.
	if (learnCount > 0) {

		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITSPELLING), WM_SETTEXT,
			(WPARAM)0, (LPARAM)wordCards[index].word.spelling);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITMEANING), WM_SETTEXT,
			(WPARAM)0, (LPARAM)wordCards[index].word.meaning);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITWORDCLASS), WM_SETTEXT,
			(WPARAM)0, (LPARAM)wordCards[index].word.wordClass);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITEXAMPLESENTENCE), WM_SETTEXT,
			(WPARAM)0, (LPARAM)wordCards[index].word.exampleSentence);

		sprintf(strTryCount, "%d��", wordCards[index].tryCount);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITTRYCOUNT), WM_SETTEXT,
			(WPARAM)0, (LPARAM)strTryCount);
		sprintf(strSuccessfulCount, "%d��", wordCards[index].successfulCount);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITSUCCESSFULCOUNT), WM_SETTEXT,
			(WPARAM)0, (LPARAM)strSuccessfulCount);

		if (wordCards[index].successfulCount == 0) {
			correctRate = 0;
		}
		else {
			correctRate = wordCards[index].successfulCount / (wordCards[index].tryCount*1.0F) * 100;
		}
		sprintf(strCorrectRate, "%.0f%%", correctRate);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITCORRECTRATE), WM_SETTEXT,
			(WPARAM)0, (LPARAM)strCorrectRate);
	}
	
	return TRUE;
}

BOOL ResultForm_OnFirstButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	HWND hWordCardBinder;
	WordCard(*wordCards);
	Long learnCount;
	Long index;
	TCHAR strTryCount[8];
	TCHAR strSuccessfulCount[8];
	float correctRate;
	TCHAR strCorrectRate[8];

	if (HIWORD(wParam) == BN_CLICKED) {

		//�ܾ�ī����δ� �����츦 ã�´�.
		hWordCardBinder = FindWindow("#32770", "�ܾ�ī����δ�");

		//�ܾ�ī�� �迭, �ܿ� ������ �����´�.
		wordCards = (WordCard(*))GetProp(hWordCardBinder, "PROP_WORDCARDS");
		learnCount = (Long)GetProp(hWordCardBinder, "PROP_LEARNCOUNT");

		//ù��° ī��� �̵��Ѵ�.
		index = (Long)GetProp(hWnd, "PROP_INDEX");
		index = 0;

		//������ġ�� �����Ѵ�.
		SetProp(hWnd, "PROP_INDEX", (HANDLE)index);

		//�ش�ī�带 ����Ѵ�.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITSPELLING), WM_SETTEXT,
				(WPARAM)0, (LPARAM)wordCards[index].word.spelling);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITMEANING), WM_SETTEXT,
				(WPARAM)0, (LPARAM)wordCards[index].word.meaning);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITWORDCLASS), WM_SETTEXT,
				(WPARAM)0, (LPARAM)wordCards[index].word.wordClass);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITEXAMPLESENTENCE), WM_SETTEXT,
				(WPARAM)0, (LPARAM)wordCards[index].word.exampleSentence);

		sprintf(strTryCount, "%d��", wordCards[index].tryCount);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITTRYCOUNT), WM_SETTEXT,
			(WPARAM)0, (LPARAM)strTryCount);
		sprintf(strSuccessfulCount, "%d��", wordCards[index].successfulCount);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITSUCCESSFULCOUNT), WM_SETTEXT,
			(WPARAM)0, (LPARAM)strSuccessfulCount);

		if (wordCards[index].successfulCount == 0) {
			correctRate = 0;
		}
		else {
			correctRate = wordCards[index].successfulCount / (wordCards[index].tryCount*1.0F) * 100;
		}
		sprintf(strCorrectRate, "%.0f%%", correctRate);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITCORRECTRATE), WM_SETTEXT,
			(WPARAM)0, (LPARAM)strCorrectRate);
		
	}

	return TRUE;
}

BOOL ResultForm_OnPreviousButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	HWND hWordCardBinder;
	WordCard(*wordCards);
	Long learnCount;
	Long index;
	TCHAR strTryCount[8];
	TCHAR strSuccessfulCount[8];
	float correctRate;
	TCHAR strCorrectRate[8];

	if (HIWORD(wParam) == BN_CLICKED) {

		//�ܾ�ī����δ� �����츦 ã�´�.
		hWordCardBinder = FindWindow("#32770", "�ܾ�ī����δ�");

		//�ܾ�ī�� �迭, �ܿ� ������ �����´�.
		wordCards = (WordCard(*))GetProp(hWordCardBinder, "PROP_WORDCARDS");
		learnCount = (Long)GetProp(hWordCardBinder, "PROP_LEARNCOUNT");

		//���� ī��� �̵��Ѵ�.
		index = (Long)GetProp(hWnd, "PROP_INDEX");
		index--;
		if (index < 0) {
			index = 0;
		}

		//������ġ�� �����Ѵ�.
		SetProp(hWnd, "PROP_INDEX", (HANDLE)index);

		//�ش�ī�带 ����Ѵ�.
		

			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITSPELLING), WM_SETTEXT,
				(WPARAM)0, (LPARAM)wordCards[index].word.spelling);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITMEANING), WM_SETTEXT,
				(WPARAM)0, (LPARAM)wordCards[index].word.meaning);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITWORDCLASS), WM_SETTEXT,
				(WPARAM)0, (LPARAM)wordCards[index].word.wordClass);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITEXAMPLESENTENCE), WM_SETTEXT,
				(WPARAM)0, (LPARAM)wordCards[index].word.exampleSentence);

			sprintf(strTryCount, "%d��", wordCards[index].tryCount);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITTRYCOUNT), WM_SETTEXT,
				(WPARAM)0, (LPARAM)strTryCount);
			sprintf(strSuccessfulCount, "%d��", wordCards[index].successfulCount);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITSUCCESSFULCOUNT), WM_SETTEXT,
				(WPARAM)0, (LPARAM)strSuccessfulCount);

			if (wordCards[index].successfulCount == 0) {
				correctRate = 0;
			}
			else {
				correctRate = wordCards[index].successfulCount / (wordCards[index].tryCount*1.0F) * 100;
			}
			sprintf(strCorrectRate, "%.0f%%", correctRate);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITCORRECTRATE), WM_SETTEXT,
				(WPARAM)0, (LPARAM)strCorrectRate);
		
	}
	return TRUE;
}


BOOL ResultForm_OnNextButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	HWND hWordCardBinder;
	WordCard(*wordCards);
	Long learnCount;
	Long index;
	TCHAR strTryCount[8];
	TCHAR strSuccessfulCount[8];
	float correctRate;
	TCHAR strCorrectRate[8];

	if (HIWORD(wParam) == BN_CLICKED) {

		//�ܾ�ī����δ� �����츦 ã�´�.
		hWordCardBinder = FindWindow("#32770", "�ܾ�ī����δ�");

		//�ܾ�ī�� �迭, �ܿ� ������ �����´�.
		wordCards = (WordCard(*))GetProp(hWordCardBinder, "PROP_WORDCARDS");
		learnCount = (Long)GetProp(hWordCardBinder, "PROP_LEARNCOUNT");

		//����ī��� �̵��Ѵ�.
		index = (Long)GetProp(hWnd, "PROP_INDEX");
		index++;
		if (index >= learnCount) {
			index = learnCount - 1;
		}

		//������ġ�� �����Ѵ�.
		SetProp(hWnd, "PROP_INDEX", (HANDLE)index);

		//�ش�ī�带 ����Ѵ�.
	

			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITSPELLING), WM_SETTEXT,
				(WPARAM)0, (LPARAM)wordCards[index].word.spelling);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITMEANING), WM_SETTEXT,
				(WPARAM)0, (LPARAM)wordCards[index].word.meaning);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITWORDCLASS), WM_SETTEXT,
				(WPARAM)0, (LPARAM)wordCards[index].word.wordClass);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITEXAMPLESENTENCE), WM_SETTEXT,
				(WPARAM)0, (LPARAM)wordCards[index].word.exampleSentence);

			sprintf(strTryCount, "%d��", wordCards[index].tryCount);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITTRYCOUNT), WM_SETTEXT,
				(WPARAM)0, (LPARAM)strTryCount);
			sprintf(strSuccessfulCount, "%d��", wordCards[index].successfulCount);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITSUCCESSFULCOUNT), WM_SETTEXT,
				(WPARAM)0, (LPARAM)strSuccessfulCount);

			if (wordCards[index].successfulCount == 0) {
				correctRate = 0;
			}
			else {
				correctRate = wordCards[index].successfulCount / (wordCards[index].tryCount*1.0F) * 100;
			}
			sprintf(strCorrectRate, "%.0f%%", correctRate);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITCORRECTRATE), WM_SETTEXT,
				(WPARAM)0, (LPARAM)strCorrectRate);
		
	}
	
	return TRUE;
}

BOOL ResultForm_OnLastButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	HWND hWordCardBinder;
	WordCard(*wordCards);
	Long learnCount;
	Long index;
	TCHAR strTryCount[8];
	TCHAR strSuccessfulCount[8];
	float correctRate;
	TCHAR strCorrectRate[8];

	if (HIWORD(wParam) == BN_CLICKED) {

		//�ܾ�ī����δ� �����츦 ã�´�.
		hWordCardBinder = FindWindow("#32770", "�ܾ�ī����δ�");

		//�ܾ�ī�� �迭, �ܿ� ������ �����´�.
		wordCards = (WordCard(*))GetProp(hWordCardBinder, "PROP_WORDCARDS");
		learnCount = (Long)GetProp(hWordCardBinder, "PROP_LEARNCOUNT");

		//������ī��� �̵��Ѵ�.
		index = (Long)GetProp(hWnd, "PROP_INDEX");
		index = learnCount - 1;

		//������ġ�� �����Ѵ�.
		SetProp(hWnd, "PROP_INDEX", (HANDLE)index);

		//�ش�ī�带 ����Ѵ�.
		

			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITSPELLING), WM_SETTEXT,
				(WPARAM)0, (LPARAM)wordCards[index].word.spelling);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITMEANING), WM_SETTEXT,
				(WPARAM)0, (LPARAM)wordCards[index].word.meaning);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITWORDCLASS), WM_SETTEXT,
				(WPARAM)0, (LPARAM)wordCards[index].word.wordClass);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITEXAMPLESENTENCE), WM_SETTEXT,
				(WPARAM)0, (LPARAM)wordCards[index].word.exampleSentence);

			sprintf(strTryCount, "%d��", wordCards[index].tryCount);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITTRYCOUNT), WM_SETTEXT,
				(WPARAM)0, (LPARAM)strTryCount);
			sprintf(strSuccessfulCount, "%d��", wordCards[index].successfulCount);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITSUCCESSFULCOUNT), WM_SETTEXT,
				(WPARAM)0, (LPARAM)strSuccessfulCount);

			if (wordCards[index].successfulCount == 0) {
				correctRate = 0;
			}
			else {
				correctRate = wordCards[index].successfulCount / (wordCards[index].tryCount*1.0F) * 100;
			}
			sprintf(strCorrectRate, "%.0f%%", correctRate);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITCORRECTRATE), WM_SETTEXT,
				(WPARAM)0, (LPARAM)strCorrectRate);
		
	}
	return TRUE;
}

BOOL ResultForm_OnTakeInButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	HWND hWordCardBinder;
	WordCard(*wordCards);
	WordCard(*afterWordCards) = NULL;
	Long learnCount;
	Long index;
	WordCardBinder *wordCardBinder;
	WordCard *current;
	IndexCardBinder *indexCardBinder;
	IndexCard *indexCardIndex;
	TCHAR alphabat[2];
	TCHAR spelling[32];
	TCHAR wordClass[16];

	TVITEM tvi = { 0, };
	TVINSERTSTRUCT tvins = { 0, };
	HTREEITEM hRoot;
	HTREEITEM hAlphabat;
	HTREEITEM hSpelling;
	HTREEITEM hWordClass;
	HTREEITEM hPrevious;
	Long i;
	Long j;

	if (HIWORD(wParam) == BN_CLICKED) {

		//�ܾ�ī����δ� �����츦 ã�´�.
		hWordCardBinder = FindWindow("#32770", "�ܾ�ī����δ�");

		//�ܾ�ī�� �迭, �ܿ� ����, ���� ��ġ�� �����´�.
		wordCards = (WordCard(*))GetProp(hWordCardBinder, "PROP_WORDCARDS");
		learnCount = (Long)GetProp(hWordCardBinder, "PROP_LEARNCOUNT");
		index = (Long)GetProp(hWnd, "PROP_INDEX");

		wordCardBinder = (WordCardBinder*)GetWindowLongPtr(hWordCardBinder, GWLP_USERDATA);

		//3.3 �ܾ�ī����δ� �������� �ܾ�ī����δ����� �����.
		current = TakeIn(wordCardBinder, wordCards[index]);

		//3.4 �ܾ�ī����δ� �������� ����ö���� �����.
		indexCardBinder = (IndexCardBinder*)GetProp(hWordCardBinder, "PROP_INDEXCARDBINDER");

		indexCardIndex = IndexCardBinder_TakeIn(indexCardBinder, current);

		//3.5 �ܾ�ī����δ� �����쿡 ���� ī�带 ����Ѵ�.
		SendMessage(GetDlgItem(hWordCardBinder, IDC_STATIC_EDITSPELLING), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->word.spelling);
		SendMessage(GetDlgItem(hWordCardBinder, IDC_STATIC_EDITMEANING), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->word.meaning);
		SendMessage(GetDlgItem(hWordCardBinder, IDC_STATIC_EDITWORDCLASS), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->word.wordClass);
		SendMessage(GetDlgItem(hWordCardBinder, IDC_STATIC_EDITEXAMPLESENTENCE), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->word.exampleSentence);


		//3.6 �ܾ�ī����δ� �������� ����ö���� �����Ѵ�.
		IndexCardBinder_Arrange(indexCardBinder);

		//3.7 �ܾ�ī����δ� �������� Ʈ���信�� ��Ʈ�׸��� ã�´�.
		hRoot = (HTREEITEM)SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_GETNEXTITEM,
			(WPARAM)TVGN_ROOT, (LPARAM)0);

		//3.8 �ܾ�ī����δ� �������� Ʈ���信�� ���ĺ��׸��� ã�´�.
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

		//3.9 ��ã������
		if (hAlphabat == NULL) {

			//���ĺ��� �߰��� ��ġ�� ���Ѵ�.
			hAlphabat = (HTREEITEM)SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_GETNEXTITEM,
				(WPARAM)TVGN_CHILD, (LPARAM)hRoot);

			hPrevious = NULL;
			tvi.hItem = hAlphabat;
			SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_GETITEM,
				(WPARAM)0, (LPARAM)&tvi);

			while (hAlphabat != NULL && current->word.spelling[0] > alphabat[0] + 32) {

				hPrevious = hAlphabat;

				hAlphabat = (HTREEITEM)SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_GETNEXTITEM,
					(WPARAM)TVGN_NEXT, (LPARAM)hAlphabat);
				tvi.hItem = hAlphabat;

				SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_GETITEM,
					(WPARAM)0, (LPARAM)&tvi);
			}

			if (hPrevious != NULL) {

				if (hAlphabat != NULL) {	//�߰��� ����
					tvins.hInsertAfter = hPrevious;
				}
				else {//�������� ����
					tvins.hInsertAfter = TVI_LAST;
				}
			}
			else {//ù��°�� ����
				tvins.hInsertAfter = TVI_FIRST;
			}

			sprintf(alphabat, "%c\0", current->word.spelling[0] - 32);
			tvi.pszText = alphabat;
			tvins.item = tvi;
			tvins.hParent = hRoot;

			//Ʈ���信�� �߰��Ѵ�.
			hAlphabat = (HTREEITEM)SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_INSERTITEM,
				(WPARAM)0, (LPARAM)&tvins);
		}

		//3.10 �ܾ�ī����δ� �������� Ʈ���信�� ö�� �׸��� ã�´�.
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

		//3.11 ��ã������
		if (hSpelling == NULL) {

			//ö�ڸ� �߰��� ��ġ�� ���Ѵ�.
			hSpelling = (HTREEITEM)SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_GETNEXTITEM,
				(WPARAM)TVGN_CHILD, (LPARAM)hAlphabat);

			hPrevious = NULL;
			tvi.hItem = hSpelling;
			SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_GETITEM,
				(WPARAM)0, (LPARAM)&tvi);

			while (hSpelling != NULL && strcmp(current->word.spelling, spelling) > 0) {

				hPrevious = hSpelling;

				hSpelling = (HTREEITEM)SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_GETNEXTITEM,
					(WPARAM)TVGN_NEXT, (LPARAM)hSpelling);
				tvi.hItem = hSpelling;

				SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_GETITEM,
					(WPARAM)0, (LPARAM)&tvi);
			}

			if (hPrevious != NULL) {

				if (hAlphabat != NULL) {	//�߰��� ����
					tvins.hInsertAfter = hPrevious;
				}
				else {//�������� ����
					tvins.hInsertAfter = TVI_LAST;
				}
			}
			else {//ù��°�� ����
				tvins.hInsertAfter = TVI_FIRST;
			}

			tvi.pszText = current->word.spelling;
			tvins.item = tvi;
			tvins.hParent = hAlphabat;

			//Ʈ���信�� �߰��Ѵ�.
			hSpelling = (HTREEITEM)SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_INSERTITEM,
				(WPARAM)0, (LPARAM)&tvins);
		}

		//3.12 �ܾ�ī������� �������� Ʈ���信�� ǰ���׸��� �߰��Ѵ�.

		//ǰ�縦 �߰��� ��ġ�� ���Ѵ�.
		hWordClass = (HTREEITEM)SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_GETNEXTITEM,
			(WPARAM)TVGN_CHILD, (LPARAM)hSpelling);

		hPrevious = NULL;
		tvi.hItem = hWordClass;
		tvi.pszText = wordClass;

		SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_GETITEM,
			(WPARAM)0, (LPARAM)&tvi);

		while (hWordClass != NULL && strcmp(current->word.wordClass, wordClass) > 0) {

			hPrevious = hWordClass;

			hWordClass = (HTREEITEM)SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_GETNEXTITEM,
				(WPARAM)TVGN_NEXT, (LPARAM)hWordClass);
			tvi.hItem = hWordClass;

			SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_GETITEM,
				(WPARAM)0, (LPARAM)&tvi);
		}

		if (hPrevious != NULL) {

			if (hAlphabat != NULL) {	//�߰��� ����
				tvins.hInsertAfter = hPrevious;
			}
			else {//�������� ����
				tvins.hInsertAfter = TVI_LAST;
			}
		}
		else {//ù��°�� ����
			tvins.hInsertAfter = TVI_FIRST;
		}

		tvi.pszText = current->word.wordClass;
		tvins.item = tvi;
		tvins.hParent = hSpelling;

		//Ʈ���信�� �߰��Ѵ�.
		hWordClass = (HTREEITEM)SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_INSERTITEM,
			(WPARAM)0, (LPARAM)&tvins);

		//Ʈ���信�� ��Ʈ�� ��ģ��.
		SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_EXPAND,
			(WPARAM)TVE_EXPAND, (LPARAM)hRoot);

		//Ʈ���信�� ���ĺ��� ��ģ��.
		SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_EXPAND,
			(WPARAM)TVE_EXPAND, (LPARAM)hAlphabat);

		//Ʈ���信�� ö�ڸ� ��ģ��.
		SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_EXPAND,
			(WPARAM)TVE_EXPAND, (LPARAM)hSpelling);

		//Ʈ���信�� �ش� �׸��� ǥ���Ѵ�.
		SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), WM_SETFOCUS, (WPARAM)0, (LPARAM)0);

		SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_SELECTITEM,
			(WPARAM)TVGN_CARET, (LPARAM)hWordClass);

		//�ܾ�ī�� �迭���� ���ش�.
		afterWordCards = (WordCard(*))calloc(100, sizeof(WordCard));

		i = 0;
		while (i < index) {

			afterWordCards[i] = wordCards[i];
			i++;
		}
		j = i;
		i++;
		while (i < learnCount) {

			afterWordCards[j] = wordCards[i];
			j++;
			i++;
		}
		learnCount--;

		//���ο� �ܾ�ī��迭�� �����Ѵ�.
		SetProp(hWordCardBinder, "PROP_LEARNCOUNT", (HANDLE)learnCount);
		SetProp(hWordCardBinder, "PROP_WORDCARDS",(HANDLE)afterWordCards);
		
		if (wordCards != NULL) {
			free(wordCards);
		}

		//3.5 ���躸�� �����츦 ���ش�.
		RemoveProp(hWnd, "PROP_INDEX");

		EndDialog(hWnd, 0);
	}
	return TRUE;
}


BOOL ResultForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	EndDialog(hWnd, 0);

	return TRUE;
}

