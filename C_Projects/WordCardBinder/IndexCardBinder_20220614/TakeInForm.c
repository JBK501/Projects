#include "TakeInForm.h"
#include "WordCardBinder.h"
#include "resource.h"
#include "IndexCard.h"
#include "IndexCardBinder.h"
#include <CommCtrl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma warning(disable : 4996)

BOOL CALLBACK TakeInFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {

	BOOL ret;

	switch (message) {

	case WM_INITDIALOG:
		ret = TakeInForm_OnInitDialog(hWnd, wParam, lParam);
		break;
	case WM_COMMAND:
		ret = TakeInForm_OnCommand(hWnd, wParam, lParam);
		break;
	case WM_CLOSE:
		ret = TakeInForm_OnClose(hWnd, wParam, lParam);
		break;
	default:
		ret = FALSE;
		break;
	}
	return ret;
}

BOOL TakeInForm_OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	BOOL ret;

	switch(LOWORD(wParam)) {

		case IDC_EDIT_SPELLING:
			ret = TakeInForm_OnSpellingEditKillFocus(hWnd, wParam, lParam);
			break;
		case IDC_BUTTON_TAKEIN:
			ret = TakeInForm_OnTakeInButtonClicked(hWnd, wParam, lParam);
			break;
		default:
			ret = FALSE;
			break;
	}
	return ret;
}


//1. 윈도우가 생성될 때
BOOL TakeInForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	//1.1 품사 콤보박스에 항목을 추가한다.
	TCHAR wordClasses[][16] = { "명사","대명사","동사","부사",
		"형용사","전치사","접속사","감탄사" };
	Long i;

	for (i = 0; i < sizeof(wordClasses) / sizeof(wordClasses[0]); i++) {
		SendMessage(GetDlgItem(hWnd, IDC_COMBO_WORDCLASS), CB_ADDSTRING,
			(WPARAM)0, (LPARAM)wordClasses[i]);
	}
	return TRUE;
}

BOOL TakeInForm_OnSpellingEditKillFocus(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	TCHAR spelling[32];
	HWND hWordCardBinder;
	WordCard *current;
	IndexCardBinder *indexCardBinder;
	IndexCard *indexCardIndex;
	Long index;
	

	//2. 철자에 포커스를 잃을 때
	if (HIWORD(wParam) == EN_KILLFOCUS) {

		//2.1 철자를 읽는다.
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_SPELLING), WM_GETTEXT, 
			(WPARAM)32, (LPARAM)spelling);

		//2.2 단어카드바인더 윈도우를 찾는다.
		hWordCardBinder = FindWindow("#32770", "단어카드바인더");

		//2.3 단어카드바인더 윈도우의 색인철에서 알파벳으로 찾는다.
		
		indexCardBinder = (IndexCardBinder*)GetProp(hWordCardBinder, "PROP_INDEXCARDBINDER");

		indexCardIndex = IndexCardBinder_Find(indexCardBinder, spelling[0]);

		//2.4 찾았으면
		if (indexCardIndex != NULL) {

			//2.4.1 찾은 색인카드에서 철자의 위치를 찾는다.
			index = IndexCard_FindBySpellings(indexCardIndex, spelling);

			//2.4.2 찾았으면
			if (index >= 0) {

				current = IndexCard_GetAt(indexCardIndex, index);

				//2.4.2.1 품사, 의미, 예문을 출력한다.
				SendMessage(GetDlgItem(hWnd, IDC_COMBO_WORDCLASS), WM_SETTEXT,
					(WPARAM)0, (LPARAM)current->word.wordClass);
				SendMessage(GetDlgItem(hWnd, IDC_EDIT_MEANING), WM_SETTEXT,
					(WPARAM)0, (LPARAM)current->word.meaning);
				SendMessage(GetDlgItem(hWnd, IDC_EDIT_EXAMPLESENTENCE), WM_SETTEXT,
					(WPARAM)0, (LPARAM)current->word.exampleSentence);
			}
		}
	}
	return TRUE;
}

BOOL TakeInForm_OnTakeInButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	WordCard wordCard;
	HWND hWordCardBinder;
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

	//3. 끼우기 버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED) {

		//3.1 철자, 의미, 품사, 예문을 읽는다.
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_SPELLING), WM_GETTEXT,
			(WPARAM)32, (LPARAM)wordCard.word.spelling);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_MEANING), WM_GETTEXT,
			(WPARAM)128, (LPARAM)wordCard.word.meaning);
		SendMessage(GetDlgItem(hWnd, IDC_COMBO_WORDCLASS), WM_GETTEXT,
			(WPARAM)16, (LPARAM)wordCard.word.wordClass);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_EXAMPLESENTENCE), WM_GETTEXT,
			(WPARAM)256, (LPARAM)wordCard.word.exampleSentence);

		//필드추가
		wordCard.tryCount = 0;
		wordCard.successfulCount = 0;

		//3.2 단어카드바인더 윈도우를 찾는다.
		hWordCardBinder = FindWindow("#32770", "단어카드바인더");

		wordCardBinder = (WordCardBinder*)GetWindowLongPtr(hWordCardBinder, GWLP_USERDATA);

		//3.3 단어카드바인더 윈도우의 단어카드바인더에서 끼운다.
		current = TakeIn(wordCardBinder, wordCard);

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

		//3.5 끼우기 윈도우를 없앤다.
		EndDialog(hWnd, 0);
	}
	return TRUE;
}

//4. 닫기 컨트롤을 클릭했을 때
BOOL TakeInForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	//4.1 끼우기 윈도우를 없앤다.
	EndDialog(hWnd, 0);

	return TRUE;
}