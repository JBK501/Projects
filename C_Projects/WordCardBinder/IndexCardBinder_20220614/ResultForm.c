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

	//단어카드바인더 윈도우를 찾는다.
	hWordCardBinder = FindWindow("#32770", "단어카드바인더");

	//단어카드 배열, 외운 개수를 가져온다.
	wordCards = (WordCard(*))GetProp(hWordCardBinder, "PROP_WORDCARDS");
	learnCount = (Long)GetProp(hWordCardBinder, "PROP_LEARNCOUNT");

	//첫번째 카드로 이동한다.
	index = 0;

	//현재위치를 저장한다.
	SetProp(hWnd, "PROP_INDEX", (HANDLE)index);

	//해당카드를 출력한다.
	if (learnCount > 0) {

		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITSPELLING), WM_SETTEXT,
			(WPARAM)0, (LPARAM)wordCards[index].word.spelling);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITMEANING), WM_SETTEXT,
			(WPARAM)0, (LPARAM)wordCards[index].word.meaning);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITWORDCLASS), WM_SETTEXT,
			(WPARAM)0, (LPARAM)wordCards[index].word.wordClass);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITEXAMPLESENTENCE), WM_SETTEXT,
			(WPARAM)0, (LPARAM)wordCards[index].word.exampleSentence);

		sprintf(strTryCount, "%d번", wordCards[index].tryCount);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITTRYCOUNT), WM_SETTEXT,
			(WPARAM)0, (LPARAM)strTryCount);
		sprintf(strSuccessfulCount, "%d번", wordCards[index].successfulCount);
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

		//단어카드바인더 윈도우를 찾는다.
		hWordCardBinder = FindWindow("#32770", "단어카드바인더");

		//단어카드 배열, 외운 개수를 가져온다.
		wordCards = (WordCard(*))GetProp(hWordCardBinder, "PROP_WORDCARDS");
		learnCount = (Long)GetProp(hWordCardBinder, "PROP_LEARNCOUNT");

		//첫번째 카드로 이동한다.
		index = (Long)GetProp(hWnd, "PROP_INDEX");
		index = 0;

		//현재위치를 저장한다.
		SetProp(hWnd, "PROP_INDEX", (HANDLE)index);

		//해당카드를 출력한다.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITSPELLING), WM_SETTEXT,
				(WPARAM)0, (LPARAM)wordCards[index].word.spelling);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITMEANING), WM_SETTEXT,
				(WPARAM)0, (LPARAM)wordCards[index].word.meaning);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITWORDCLASS), WM_SETTEXT,
				(WPARAM)0, (LPARAM)wordCards[index].word.wordClass);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITEXAMPLESENTENCE), WM_SETTEXT,
				(WPARAM)0, (LPARAM)wordCards[index].word.exampleSentence);

		sprintf(strTryCount, "%d번", wordCards[index].tryCount);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITTRYCOUNT), WM_SETTEXT,
			(WPARAM)0, (LPARAM)strTryCount);
		sprintf(strSuccessfulCount, "%d번", wordCards[index].successfulCount);
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

		//단어카드바인더 윈도우를 찾는다.
		hWordCardBinder = FindWindow("#32770", "단어카드바인더");

		//단어카드 배열, 외운 개수를 가져온다.
		wordCards = (WordCard(*))GetProp(hWordCardBinder, "PROP_WORDCARDS");
		learnCount = (Long)GetProp(hWordCardBinder, "PROP_LEARNCOUNT");

		//이전 카드로 이동한다.
		index = (Long)GetProp(hWnd, "PROP_INDEX");
		index--;
		if (index < 0) {
			index = 0;
		}

		//현재위치를 저장한다.
		SetProp(hWnd, "PROP_INDEX", (HANDLE)index);

		//해당카드를 출력한다.
		

			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITSPELLING), WM_SETTEXT,
				(WPARAM)0, (LPARAM)wordCards[index].word.spelling);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITMEANING), WM_SETTEXT,
				(WPARAM)0, (LPARAM)wordCards[index].word.meaning);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITWORDCLASS), WM_SETTEXT,
				(WPARAM)0, (LPARAM)wordCards[index].word.wordClass);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITEXAMPLESENTENCE), WM_SETTEXT,
				(WPARAM)0, (LPARAM)wordCards[index].word.exampleSentence);

			sprintf(strTryCount, "%d번", wordCards[index].tryCount);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITTRYCOUNT), WM_SETTEXT,
				(WPARAM)0, (LPARAM)strTryCount);
			sprintf(strSuccessfulCount, "%d번", wordCards[index].successfulCount);
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

		//단어카드바인더 윈도우를 찾는다.
		hWordCardBinder = FindWindow("#32770", "단어카드바인더");

		//단어카드 배열, 외운 개수를 가져온다.
		wordCards = (WordCard(*))GetProp(hWordCardBinder, "PROP_WORDCARDS");
		learnCount = (Long)GetProp(hWordCardBinder, "PROP_LEARNCOUNT");

		//다음카드로 이동한다.
		index = (Long)GetProp(hWnd, "PROP_INDEX");
		index++;
		if (index >= learnCount) {
			index = learnCount - 1;
		}

		//현재위치를 저장한다.
		SetProp(hWnd, "PROP_INDEX", (HANDLE)index);

		//해당카드를 출력한다.
	

			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITSPELLING), WM_SETTEXT,
				(WPARAM)0, (LPARAM)wordCards[index].word.spelling);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITMEANING), WM_SETTEXT,
				(WPARAM)0, (LPARAM)wordCards[index].word.meaning);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITWORDCLASS), WM_SETTEXT,
				(WPARAM)0, (LPARAM)wordCards[index].word.wordClass);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITEXAMPLESENTENCE), WM_SETTEXT,
				(WPARAM)0, (LPARAM)wordCards[index].word.exampleSentence);

			sprintf(strTryCount, "%d번", wordCards[index].tryCount);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITTRYCOUNT), WM_SETTEXT,
				(WPARAM)0, (LPARAM)strTryCount);
			sprintf(strSuccessfulCount, "%d번", wordCards[index].successfulCount);
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

		//단어카드바인더 윈도우를 찾는다.
		hWordCardBinder = FindWindow("#32770", "단어카드바인더");

		//단어카드 배열, 외운 개수를 가져온다.
		wordCards = (WordCard(*))GetProp(hWordCardBinder, "PROP_WORDCARDS");
		learnCount = (Long)GetProp(hWordCardBinder, "PROP_LEARNCOUNT");

		//마지막카드로 이동한다.
		index = (Long)GetProp(hWnd, "PROP_INDEX");
		index = learnCount - 1;

		//현재위치를 저장한다.
		SetProp(hWnd, "PROP_INDEX", (HANDLE)index);

		//해당카드를 출력한다.
		

			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITSPELLING), WM_SETTEXT,
				(WPARAM)0, (LPARAM)wordCards[index].word.spelling);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITMEANING), WM_SETTEXT,
				(WPARAM)0, (LPARAM)wordCards[index].word.meaning);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITWORDCLASS), WM_SETTEXT,
				(WPARAM)0, (LPARAM)wordCards[index].word.wordClass);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITEXAMPLESENTENCE), WM_SETTEXT,
				(WPARAM)0, (LPARAM)wordCards[index].word.exampleSentence);

			sprintf(strTryCount, "%d번", wordCards[index].tryCount);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITTRYCOUNT), WM_SETTEXT,
				(WPARAM)0, (LPARAM)strTryCount);
			sprintf(strSuccessfulCount, "%d번", wordCards[index].successfulCount);
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

		//단어카드바인더 윈도우를 찾는다.
		hWordCardBinder = FindWindow("#32770", "단어카드바인더");

		//단어카드 배열, 외운 개수, 현재 위치를 가져온다.
		wordCards = (WordCard(*))GetProp(hWordCardBinder, "PROP_WORDCARDS");
		learnCount = (Long)GetProp(hWordCardBinder, "PROP_LEARNCOUNT");
		index = (Long)GetProp(hWnd, "PROP_INDEX");

		wordCardBinder = (WordCardBinder*)GetWindowLongPtr(hWordCardBinder, GWLP_USERDATA);

		//3.3 단어카드바인더 윈도우의 단어카드바인더에서 끼운다.
		current = TakeIn(wordCardBinder, wordCards[index]);

		//3.4 단어카드바인더 윈도우의 색인철에서 끼운다.
		indexCardBinder = (IndexCardBinder*)GetProp(hWordCardBinder, "PROP_INDEXCARDBINDER");

		indexCardIndex = IndexCardBinder_TakeIn(indexCardBinder, current);

		//3.5 단어카드바인더 윈도우에 끼운 카드를 출력한다.
		SendMessage(GetDlgItem(hWordCardBinder, IDC_STATIC_EDITSPELLING), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->word.spelling);
		SendMessage(GetDlgItem(hWordCardBinder, IDC_STATIC_EDITMEANING), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->word.meaning);
		SendMessage(GetDlgItem(hWordCardBinder, IDC_STATIC_EDITWORDCLASS), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->word.wordClass);
		SendMessage(GetDlgItem(hWordCardBinder, IDC_STATIC_EDITEXAMPLESENTENCE), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->word.exampleSentence);


		//3.6 단어카드바인더 윈도우의 색인철에서 정리한다.
		IndexCardBinder_Arrange(indexCardBinder);

		//3.7 단어카드바인더 윈도우의 트리뷰에서 루트항목을 찾는다.
		hRoot = (HTREEITEM)SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_GETNEXTITEM,
			(WPARAM)TVGN_ROOT, (LPARAM)0);

		//3.8 단어카드바인더 윈도우의 트리뷰에서 알파벳항목을 찾는다.
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

		//3.9 못찾았으면
		if (hAlphabat == NULL) {

			//알파벳을 추가할 위치를 구한다.
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

				if (hAlphabat != NULL) {	//중간에 삽입
					tvins.hInsertAfter = hPrevious;
				}
				else {//마지막에 삽입
					tvins.hInsertAfter = TVI_LAST;
				}
			}
			else {//첫번째에 삽입
				tvins.hInsertAfter = TVI_FIRST;
			}

			sprintf(alphabat, "%c\0", current->word.spelling[0] - 32);
			tvi.pszText = alphabat;
			tvins.item = tvi;
			tvins.hParent = hRoot;

			//트리뷰에서 추가한다.
			hAlphabat = (HTREEITEM)SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_INSERTITEM,
				(WPARAM)0, (LPARAM)&tvins);
		}

		//3.10 단어카드바인더 윈도우의 트리뷰에서 철자 항목을 찾는다.
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

		//3.11 못찾았으면
		if (hSpelling == NULL) {

			//철자를 추가할 위치를 구한다.
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

				if (hAlphabat != NULL) {	//중간에 삽입
					tvins.hInsertAfter = hPrevious;
				}
				else {//마지막에 삽입
					tvins.hInsertAfter = TVI_LAST;
				}
			}
			else {//첫번째에 삽입
				tvins.hInsertAfter = TVI_FIRST;
			}

			tvi.pszText = current->word.spelling;
			tvins.item = tvi;
			tvins.hParent = hAlphabat;

			//트리뷰에서 추가한다.
			hSpelling = (HTREEITEM)SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_INSERTITEM,
				(WPARAM)0, (LPARAM)&tvins);
		}

		//3.12 단어카드바인터 윈도우의 트리뷰에서 품사항목을 추가한다.

		//품사를 추가할 위치를 구한다.
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

			if (hAlphabat != NULL) {	//중간에 삽입
				tvins.hInsertAfter = hPrevious;
			}
			else {//마지막에 삽입
				tvins.hInsertAfter = TVI_LAST;
			}
		}
		else {//첫번째에 삽입
			tvins.hInsertAfter = TVI_FIRST;
		}

		tvi.pszText = current->word.wordClass;
		tvins.item = tvi;
		tvins.hParent = hSpelling;

		//트리뷰에서 추가한다.
		hWordClass = (HTREEITEM)SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_INSERTITEM,
			(WPARAM)0, (LPARAM)&tvins);

		//트리뷰에서 루트를 펼친다.
		SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_EXPAND,
			(WPARAM)TVE_EXPAND, (LPARAM)hRoot);

		//트리뷰에서 알파벳을 펼친다.
		SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_EXPAND,
			(WPARAM)TVE_EXPAND, (LPARAM)hAlphabat);

		//트리뷰에서 철자를 펼친다.
		SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_EXPAND,
			(WPARAM)TVE_EXPAND, (LPARAM)hSpelling);

		//트리뷰에서 해당 항목을 표시한다.
		SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), WM_SETFOCUS, (WPARAM)0, (LPARAM)0);

		SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_SELECTITEM,
			(WPARAM)TVGN_CARET, (LPARAM)hWordClass);

		//단어카드 배열에서 없앤다.
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

		//새로운 단어카드배열을 저장한다.
		SetProp(hWordCardBinder, "PROP_LEARNCOUNT", (HANDLE)learnCount);
		SetProp(hWordCardBinder, "PROP_WORDCARDS",(HANDLE)afterWordCards);
		
		if (wordCards != NULL) {
			free(wordCards);
		}

		//3.5 시험보기 윈도우를 없앤다.
		RemoveProp(hWnd, "PROP_INDEX");

		EndDialog(hWnd, 0);
	}
	return TRUE;
}


BOOL ResultForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	EndDialog(hWnd, 0);

	return TRUE;
}

