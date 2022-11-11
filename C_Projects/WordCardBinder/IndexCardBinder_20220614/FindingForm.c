#include "FindingForm.h"
#include "WordCardBinder.h"
#include "IndexCard.h"
#include "IndexCardBinder.h"
#include "resource.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <CommCtrl.h>

#pragma warning(disable : 4996)


BOOL CALLBACK FindingFormProc(HWND hWnd, UINT message,
	WPARAM wParam, LPARAM lParam) {

	BOOL ret;

	switch (message) {

	case WM_INITDIALOG:
		ret = FindingForm_OnInitDialog(hWnd, wParam, lParam);
		break;
	case WM_COMMAND:
		ret = FindingForm_OnCommand(hWnd, wParam, lParam);
		break;
	case WM_CLOSE:
		ret = FindingForm_OnClose(hWnd, wParam, lParam);
		break;
	default:
		ret = FALSE;
		break;
	}
	return ret;
}

BOOL FindingForm_OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	BOOL ret;

	switch (LOWORD(wParam)) {

	case IDC_RADIO_SPELLING:
		ret = FindingForm_OnSpellingRadioButtonClicked(hWnd, wParam, lParam);
		break;
	case IDC_RADIO_MEANING:
		ret = FindingForm_OnMeaningRadioButtonClicked(hWnd, wParam, lParam);
		break;
	case IDC_BUTTON_FIND:
		ret = FindingForm_OnFindButtonClicked(hWnd, wParam, lParam);
		break;
	case IDC_BUTTON_FIRST:
		ret = FindingForm_OnFirstButtonClicked(hWnd, wParam, lParam);
		break;
	case IDC_BUTTON_PREVIOUS:
		ret = FindingForm_OnPreviousButtonClicked(hWnd, wParam, lParam);
		break;
	case IDC_BUTTON_NEXT:
		ret = FindingForm_OnNextButtonClicked(hWnd, wParam, lParam);
		break;
	case IDC_BUTTON_LAST:
		ret = FindingForm_OnLastButtonClicked(hWnd, wParam, lParam);
		break;
	case IDC_BUTTON_SELECT:
		ret = FindingForm_OnSelectButtonClicked(hWnd, wParam, lParam);
		break;
	default:
		ret = FALSE;
		break;
	}
	return ret;
}


//1. 윈도우가 생성될 때
BOOL FindingForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	//1.1 철자 라디오버튼을 선택한다.
	SendMessage(GetDlgItem(hWnd, IDC_RADIO_SPELLING), BM_SETCHECK,
		(WPARAM)BST_CHECKED, (LPARAM)0);

	return TRUE;
}

BOOL FindingForm_OnSpellingRadioButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	//2. 철자 라디오버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED) {

		//2.1 의미 라디오버튼을 선택해제한다.
		SendMessage(GetDlgItem(hWnd, IDC_RADIO_MEANING), BM_SETCHECK,
			(WPARAM)BST_UNCHECKED, (LPARAM)0);

		//2.2 의미를 없앤다.
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_MEANING), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
	}
	return TRUE;
}

BOOL FindingForm_OnMeaningRadioButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	//3. 의미 라디오버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED) {

		//3.1 철자 라디오버튼을 선택해제한다.
		SendMessage(GetDlgItem(hWnd, IDC_RADIO_SPELLING), BM_SETCHECK,
			(WPARAM)BST_UNCHECKED, (LPARAM)0);

		//3.2 철자를 없앤다.
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_SPELLING), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
	}
	return TRUE;
}

BOOL FindingForm_OnFindButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	int spellingRadioButton;
	TCHAR spelling[32];
	int meaningRadioButton;
	TCHAR meaning[32];
	HWND hWordCardBinder;
	WordCardBinder *wordCardBinder;
	WordCard*(*indexes);
	Long count;
	Long current = -1;

	
	//4. 찾기 버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED) {

		//4.1 철자 라디오버튼, 철자, 의미 라디오버튼, 의미를 읽는다.
		spellingRadioButton = SendMessage(GetDlgItem(hWnd, IDC_RADIO_SPELLING),
			BM_GETSTATE, (WPARAM)0, (LPARAM)0);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_SPELLING), WM_GETTEXT,
			(WPARAM)32, (LPARAM)spelling);
		meaningRadioButton = SendMessage(GetDlgItem(hWnd, IDC_RADIO_MEANING),
			BM_GETSTATE, (WPARAM)0, (LPARAM)0);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_MEANING), WM_GETTEXT,
			(WPARAM)32, (LPARAM)meaning);

		//4.2 단어카드바인더 윈도우를 찾는다.
		hWordCardBinder = FindWindow("#32770", "단어카드바인더");
		
		wordCardBinder = (WordCardBinder*)GetWindowLongPtr(hWordCardBinder, GWLP_USERDATA);

		//기존에 찾은 내용 제거
		indexes = (WordCard*(*))GetWindowLongPtr(hWnd, GWLP_USERDATA);
		if (indexes != NULL) {
			free(indexes);
		}

		//4.3 철자 라디오버튼이 선택됐을 때
		if (spellingRadioButton == BST_CHECKED) {
			
			//4.3.1 단어카드바인더에서 철자로 찾는다.
			FindBySpelling(wordCardBinder, spelling, &indexes, &count);
		}
		//4.4 의미 라디오버튼이 선택됐을 때
		if (meaningRadioButton == BST_CHECKED) {

			//4.4.1 단어카드바인더에서 의미로 찾는다.
			FindByMeaning(wordCardBinder, meaning, &indexes, &count);
		}
		SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG)indexes);
		SetProp(hWnd, "PROP_CURRENT", (HANDLE)current);
		SetProp(hWnd, "PROP_COUNT", (HANDLE)count);

		//4.5 찾았으면
		if (count > 0) {
			
			//4.5.1 첫 번째 위치로 이동한다.
			current = 0;
			SetProp(hWnd, "PROP_CURRENT", (HANDLE)current);

			//4.5.2 현재 카드를 출력한다.
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITSPELLING), WM_SETTEXT,
				(WPARAM)0, (LPARAM)indexes[current]->word.spelling);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITMEANING), WM_SETTEXT,
				(WPARAM)0, (LPARAM)indexes[current]->word.meaning);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITWORDCLASS), WM_SETTEXT,
				(WPARAM)0, (LPARAM)indexes[current]->word.wordClass);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITEXAMPLESENTENCE), WM_SETTEXT,
				(WPARAM)0, (LPARAM)indexes[current]->word.exampleSentence);
		}
		else {

			//못 찾았으면 빈칸출력
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITSPELLING), WM_SETTEXT,
				(WPARAM)0, (LPARAM)"");
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITMEANING), WM_SETTEXT,
				(WPARAM)0, (LPARAM)"");
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITWORDCLASS), WM_SETTEXT,
				(WPARAM)0, (LPARAM)"");
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITEXAMPLESENTENCE), WM_SETTEXT,
				(WPARAM)0, (LPARAM)"");
		}
	}
	return TRUE;
}


BOOL FindingForm_OnFirstButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	WordCard*(*indexes);
	Long current;

	//5. 처음버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED) {

		//5.1 첫 번째 위치로 이동한다.
		indexes = (WordCard*(*))GetWindowLongPtr(hWnd, GWLP_USERDATA);
		current = (Long)GetProp(hWnd, "PROP_CURRENT");

		current = 0;
		SetProp(hWnd, "PROP_CURRENT", (HANDLE)current);

		//5.2 현재 카드를 출력한다.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITSPELLING), WM_SETTEXT,
			(WPARAM)0, (LPARAM)indexes[current]->word.spelling);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITMEANING), WM_SETTEXT,
			(WPARAM)0, (LPARAM)indexes[current]->word.meaning);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITWORDCLASS), WM_SETTEXT,
			(WPARAM)0, (LPARAM)indexes[current]->word.wordClass);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITEXAMPLESENTENCE), WM_SETTEXT,
			(WPARAM)0, (LPARAM)indexes[current]->word.exampleSentence);
	}
	return TRUE;
}

BOOL FindingForm_OnPreviousButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	WordCard*(*indexes);
	Long current;

	//6. 이전버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED) {

		//6.1 이전 위치로 이동한다.
		indexes = (WordCard*(*))GetWindowLongPtr(hWnd, GWLP_USERDATA);
		current = (Long)GetProp(hWnd, "PROP_CURRENT");

		current--;
		if (current < 0) {
			current = 0;
		}
		SetProp(hWnd, "PROP_CURRENT", (HANDLE)current);

		//6.2 현재 카드를 출력한다.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITSPELLING), WM_SETTEXT,
			(WPARAM)0, (LPARAM)indexes[current]->word.spelling);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITMEANING), WM_SETTEXT,
			(WPARAM)0, (LPARAM)indexes[current]->word.meaning);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITWORDCLASS), WM_SETTEXT,
			(WPARAM)0, (LPARAM)indexes[current]->word.wordClass);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITEXAMPLESENTENCE), WM_SETTEXT,
			(WPARAM)0, (LPARAM)indexes[current]->word.exampleSentence);
	}
	return TRUE;
}

BOOL FindingForm_OnNextButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	WordCard*(*indexes);
	Long current;
	Long count;

	//7. 다음버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED) {

		//7.1 다음 위치로 이동한다.
		indexes = (WordCard*(*))GetWindowLongPtr(hWnd, GWLP_USERDATA);
		current = (Long)GetProp(hWnd, "PROP_CURRENT");
		count = (Long)GetProp(hWnd, "PROP_COUNT");

		current++;
		if (current>=count) {
			current = count-1;
		}
		SetProp(hWnd, "PROP_CURRENT", (HANDLE)current);

		//7.2 현재 카드를 출력한다.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITSPELLING), WM_SETTEXT,
			(WPARAM)0, (LPARAM)indexes[current]->word.spelling);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITMEANING), WM_SETTEXT,
			(WPARAM)0, (LPARAM)indexes[current]->word.meaning);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITWORDCLASS), WM_SETTEXT,
			(WPARAM)0, (LPARAM)indexes[current]->word.wordClass);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITEXAMPLESENTENCE), WM_SETTEXT,
			(WPARAM)0, (LPARAM)indexes[current]->word.exampleSentence);
	}
	return TRUE;
}

BOOL FindingForm_OnLastButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	WordCard*(*indexes);
	Long current;
	Long count;

	//8. 끝버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED) {

		//8.1 마지막 위치로 이동한다.
		indexes = (WordCard*(*))GetWindowLongPtr(hWnd, GWLP_USERDATA);
		count = (Long)GetProp(hWnd, "PROP_COUNT");
		
		current = count - 1;
		SetProp(hWnd, "PROP_CURRENT", (HANDLE)current);

		//8.2 현재 카드를 출력한다.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITSPELLING), WM_SETTEXT,
			(WPARAM)0, (LPARAM)indexes[current]->word.spelling);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITMEANING), WM_SETTEXT,
			(WPARAM)0, (LPARAM)indexes[current]->word.meaning);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITWORDCLASS), WM_SETTEXT,
			(WPARAM)0, (LPARAM)indexes[current]->word.wordClass);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITEXAMPLESENTENCE), WM_SETTEXT,
			(WPARAM)0, (LPARAM)indexes[current]->word.exampleSentence);
	}
	return TRUE;
}

BOOL FindingForm_OnSelectButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	HWND hWordCardBinder;
	WordCardBinder *wordCardBinder;
	WordCard*(*indexes);
	Long current;
	WordCard wordCard;
	TCHAR alphabat[2];
	TCHAR spelling[32];
	TCHAR wordClass[16];

	TVITEM tvi = { 0, };
	HTREEITEM hRoot;
	HTREEITEM hAlphabat;
	HTREEITEM hSpelling;
	HTREEITEM hWordClass;

	//9. 선택버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED) {

		//9.1 단어카드바인더 윈도우를 찾는다.
		hWordCardBinder = FindWindow("#32770", "단어카드바인더");
		
		wordCardBinder = (WordCardBinder*)GetWindowLongPtr(hWordCardBinder, GWLP_USERDATA);

		//9.2 단어카드바인더 윈도우의 단어카드바인더에서 이동한다.
		indexes = (WordCard*(*))GetWindowLongPtr(hWnd, GWLP_USERDATA);
		current = (Long)GetProp(hWnd, "PROP_CURRENT");

		WordCardBinder_Move(wordCardBinder, indexes[current]);

		//9.3 단어카드바인더 윈도우에 찾은카드를 출력한다.

		//9.3.1 찾은 카드를 읽는다
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITSPELLING), WM_GETTEXT,
			(WPARAM)32, (LPARAM)wordCard.word.spelling);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITWORDCLASS), WM_GETTEXT,
			(WPARAM)16, (LPARAM)wordCard.word.wordClass);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITMEANING), WM_GETTEXT,
			(WPARAM)128, (LPARAM)wordCard.word.meaning);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITEXAMPLESENTENCE), WM_GETTEXT,
			(WPARAM)256, (LPARAM)wordCard.word.exampleSentence);

		//9.3.2 읽은 카드를 출력한다
		SendMessage(GetDlgItem(hWordCardBinder, IDC_STATIC_EDITSPELLING), WM_SETTEXT,
			(WPARAM)0, (LPARAM)wordCard.word.spelling);
		SendMessage(GetDlgItem(hWordCardBinder, IDC_STATIC_EDITWORDCLASS), WM_SETTEXT,
			(WPARAM)0, (LPARAM)wordCard.word.wordClass);
		SendMessage(GetDlgItem(hWordCardBinder, IDC_STATIC_EDITMEANING), WM_SETTEXT,
			(WPARAM)0, (LPARAM)wordCard.word.meaning);
		SendMessage(GetDlgItem(hWordCardBinder, IDC_STATIC_EDITEXAMPLESENTENCE), WM_SETTEXT,
			(WPARAM)0, (LPARAM)wordCard.word.exampleSentence);


		//단어카드바인더 윈도우의 트리뷰에서 루트항목을 찾는다.
		hRoot = (HTREEITEM)SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_GETNEXTITEM,
			(WPARAM)TVGN_ROOT, (LPARAM)0);

		//단어카드바인더 윈도우의 트리뷰에서 알파벳항목을 찾는다.
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

		//단어카드바인더 윈도우의 트리뷰에서 철자 항목을 찾는다.
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

		//단어카드바인더 윈도우의 트리뷰에서 품사 항목을 찾는다.
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

		//단어카드바인더 윈도우의 트리뷰에서 루트를 펼친다.
		SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_EXPAND,
			(WPARAM)TVE_EXPAND, (LPARAM)hRoot);

		//단어카드바인더 윈도우의 트리뷰에서 알파벳을 펼친다.
		SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_EXPAND,
			(WPARAM)TVE_EXPAND, (LPARAM)hAlphabat);

		//단어카드바인더 윈도우의 트리뷰에서 철자를 펼친다.
		SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_EXPAND,
			(WPARAM)TVE_EXPAND, (LPARAM)hSpelling);

		//단어카드바인더 윈도우의 트리뷰에서 해당 항목을 표시한다.
		SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), WM_SETFOCUS, (WPARAM)0, (LPARAM)0);

		SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_SELECTITEM,
			(WPARAM)TVGN_CARET, (LPARAM)hWordClass);


		//9.4 찾기 윈도우를 없앤다.
		if (indexes != NULL) {
			free(indexes);
		}
		RemoveProp(hWnd, "PROP_CURRENT");
		RemoveProp(hWnd, "PROP_COUNT");

		EndDialog(hWnd, 0);
	}
	return TRUE;
}


//10. 닫기컨트롤을 클릭했을 때
BOOL FindingForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	WordCard*(*indexes);
	
	//10.1 찾기윈도우를 없앤다.
	indexes = (WordCard*(*))GetWindowLongPtr(hWnd, GWLP_USERDATA);
	if (indexes != NULL) {
		free(indexes);
	}
	RemoveProp(hWnd, "PROP_CURRENT");
	RemoveProp(hWnd, "PROP_COUNT");

	EndDialog(hWnd, 0);

	return 0;
}



