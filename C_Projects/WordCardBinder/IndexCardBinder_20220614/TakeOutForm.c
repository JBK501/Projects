#include "TakeOutForm.h"
#include "WordCardBinder.h"
#include "IndexCard.h"
#include "IndexCardBinder.h"
#include "resource.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <CommCtrl.h>

#pragma warning (disable : 4996)

BOOL CALLBACK TakeOutFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {

	BOOL ret;

	switch (message) {

	case WM_INITDIALOG:
		ret = TakeOutForm_OnInitDialog(hWnd, wParam, lParam);
		break;
	case WM_CLOSE:
		ret = TakeOutForm_OnClose(hWnd, wParam, lParam);
		break;
	default:
		ret = FALSE;
		break;
	}
	return ret;
}

//1. 윈도우가 생성될 때
BOOL TakeOutForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	HWND hWordCardBinder;
	WordCardBinder *wordCardBinder;
	WordCard wordCard;
	WordCard *current;
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

	//단어카드바인더 윈도우를 찾는다.
	hWordCardBinder = FindWindow("#32770", "단어카드바인더");

	wordCardBinder = (WordCardBinder*)GetWindowLongPtr(hWordCardBinder, GWLP_USERDATA);

	//색인철에서 꺼내기위한 단어카드링크저장
	current = wordCardBinder->current;

	//단어카드바인더 윈도우의 단어카드바인더에서 꺼낸다.
	wordCard = TakeOut(wordCardBinder, wordCardBinder->current);

	//단어카드의 시도횟수, 성공횟수를 저장한다.
	SetProp(hWnd, "PROP_TRYCOUNT", (HANDLE)wordCard.tryCount);
	SetProp(hWnd, "PROP_SUCCESSFUL", (HANDLE)wordCard.successfulCount);

	//색인철에서 꺼낸다.
	indexCardBinder = (IndexCardBinder*)GetProp(hWordCardBinder, "PROP_INDEXCARDBINDER");
	
	indexCardIndex = IndexCardBinder_TakeOut(indexCardBinder, current,wordCard.word.spelling[0]);

	//꺼낸 카드를 출력한다.
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITSPELLING), WM_SETTEXT,
		(WPARAM)0, (LPARAM)wordCard.word.spelling);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITMEANING), WM_SETTEXT,
		(WPARAM)0, (LPARAM)wordCard.word.meaning);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITWORDCLASS), WM_SETTEXT,
		(WPARAM)0, (LPARAM)wordCard.word.wordClass);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITEXAMPLESENTENCE), WM_SETTEXT,
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

	//단어카드바인더 윈도우의 트리뷰에서 찾은 품사를 지운다.
	SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_DELETEITEM,
		(WPARAM)0, (LPARAM)hWordClass);

	if (indexCardIndex != NULL) {	//색인카드가 있으면

		//색인카드에서 철자로 찾는다.
		index = IndexCard_FindBySpellings(indexCardIndex, wordCard.word.spelling);

		if (index == -1) {	//못 찾았으면

			//단어카드바인더 윈도우의 트리뷰에서 철자를 지운다.
			SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_DELETEITEM,
				(WPARAM)0, (LPARAM)hSpelling);
		}

	}
	else {	//색인카드가 없으면

		//단어카드바인더 윈도우의 트리뷰에서 철자를 지운다.
		SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_DELETEITEM,
			(WPARAM)0, (LPARAM)hSpelling);
		//단어카드바인더 윈도우의 트리뷰에서 알파벳을 지운다.
		SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_DELETEITEM,
			(WPARAM)0, (LPARAM)hAlphabat);
	}

	//단어카드바인더 윈도우의 단어카드바인더에서 카드가 있으면
	if (wordCardBinder->current != NULL) {

		//단어카드바인더 윈도우에 현재카드를 출력한다.
		SendMessage(GetDlgItem(hWordCardBinder, IDC_STATIC_EDITSPELLING), WM_SETTEXT,
			(WPARAM)0, (LPARAM)wordCardBinder->current->word.spelling);
		SendMessage(GetDlgItem(hWordCardBinder, IDC_STATIC_EDITMEANING), WM_SETTEXT,
			(WPARAM)0, (LPARAM)wordCardBinder->current->word.meaning);
		SendMessage(GetDlgItem(hWordCardBinder, IDC_STATIC_EDITWORDCLASS), WM_SETTEXT,
			(WPARAM)0, (LPARAM)wordCardBinder->current->word.wordClass);
		SendMessage(GetDlgItem(hWordCardBinder, IDC_STATIC_EDITEXAMPLESENTENCE), WM_SETTEXT,
			(WPARAM)0, (LPARAM)wordCardBinder->current->word.exampleSentence);

		

		//단어카드바인더 윈도우의 트리뷰에서 알파벳항목을 찾는다.
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

		//단어카드바인더 윈도우의 트리뷰에서 철자 항목을 찾는다.
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

		//단어카드바인더 윈도우의 트리뷰에서 품사 항목을 찾는다.
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
	}
	else{

		//없으면 빈칸을 출력한다.
		SendMessage(GetDlgItem(hWordCardBinder, IDC_STATIC_EDITSPELLING), WM_SETTEXT,
			(WPARAM)0, (LPARAM)"");
		SendMessage(GetDlgItem(hWordCardBinder, IDC_STATIC_EDITMEANING), WM_SETTEXT,
			(WPARAM)0, (LPARAM)"");
		SendMessage(GetDlgItem(hWordCardBinder, IDC_STATIC_EDITWORDCLASS), WM_SETTEXT,
			(WPARAM)0, (LPARAM)"");
		SendMessage(GetDlgItem(hWordCardBinder, IDC_STATIC_EDITEXAMPLESENTENCE), WM_SETTEXT,
			(WPARAM)0, (LPARAM)"");
	}
	return TRUE;
}

//2. 닫키 컨트롤을 클릭했을 때
BOOL TakeOutForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	int message;
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


	//2.1 메시지 박스를 출력한다.
	message = MessageBox(hWnd, "끼우시겠습니까?", "알림", MB_YESNOCANCEL);

	//2.2 예 버튼을 클릭했을 때
	if (message == IDYES) {

		//꺼낸 카드를 읽는다.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITSPELLING), WM_GETTEXT,
			(WPARAM)32, (LPARAM)wordCard.word.spelling);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITWORDCLASS), WM_GETTEXT,
			(WPARAM)16, (LPARAM)wordCard.word.wordClass);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITMEANING), WM_GETTEXT,
			(WPARAM)128, (LPARAM)wordCard.word.meaning);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITEXAMPLESENTENCE), WM_GETTEXT,
			(WPARAM)256, (LPARAM)wordCard.word.exampleSentence);

		//저장한 시행횟수, 성공횟수를 가져온다.
		wordCard.tryCount = (Long)GetProp(hWnd, "PROP_TRYCOUNT");
		wordCard.successfulCount = (Long)GetProp(hWnd, "PROP_SUCCESSFUL");
	

		//단어카드바인더 윈도우를 찾는다.
		hWordCardBinder = FindWindow("#32770", "단어카드바인더");

		wordCardBinder = (WordCardBinder*)GetWindowLongPtr(hWordCardBinder, GWLP_USERDATA);

		//단어카드바인더 윈도우의 단어카드바인더에서 끼운다.
		current = TakeIn(wordCardBinder, wordCard);

		//단어카드바인더 윈도우의 색인철에서 끼운다.
		indexCardBinder = (IndexCardBinder*)GetProp(hWordCardBinder, "PROP_INDEXCARDBINDER");

		indexCardIndex = IndexCardBinder_TakeIn(indexCardBinder, current);

#if 0
		//단어카드바인더 윈도우에 끼운 카드를 출력한다.
		SendMessage(GetDlgItem(hWordCardBinder, IDC_STATIC_EDITSPELLING), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->word.spelling);
		SendMessage(GetDlgItem(hWordCardBinder, IDC_STATIC_EDITMEANING), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->word.meaning);
		SendMessage(GetDlgItem(hWordCardBinder, IDC_STATIC_EDITWORDCLASS), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->word.wordClass);
		SendMessage(GetDlgItem(hWordCardBinder, IDC_STATIC_EDITEXAMPLESENTENCE), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->word.exampleSentence);
#endif
		//읽은 카드를 출력한다
		SendMessage(GetDlgItem(hWordCardBinder, IDC_STATIC_EDITSPELLING), WM_SETTEXT,
			(WPARAM)0, (LPARAM)wordCard.word.spelling);
		SendMessage(GetDlgItem(hWordCardBinder, IDC_STATIC_EDITWORDCLASS), WM_SETTEXT,
			(WPARAM)0, (LPARAM)wordCard.word.wordClass);
		SendMessage(GetDlgItem(hWordCardBinder, IDC_STATIC_EDITMEANING), WM_SETTEXT,
			(WPARAM)0, (LPARAM)wordCard.word.meaning);
		SendMessage(GetDlgItem(hWordCardBinder, IDC_STATIC_EDITEXAMPLESENTENCE), WM_SETTEXT,
			(WPARAM)0, (LPARAM)wordCard.word.exampleSentence);

		


		//단어카드바인더 윈도우의 색인철에서 정리한다.
		IndexCardBinder_Arrange(indexCardBinder);

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

		while (hAlphabat != NULL && current->word.spelling[0] != alphabat[0] + 32) {

			hAlphabat = (HTREEITEM)SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_GETNEXTITEM,
				(WPARAM)TVGN_NEXT, (LPARAM)hAlphabat);

			tvi.hItem = hAlphabat;
			SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_GETITEM,
				(WPARAM)0, (LPARAM)&tvi);
		}

		//못찾았으면
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

		//단어카드바인더 윈도우의 트리뷰에서 철자 항목을 찾는다.
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

		//못찾았으면
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

		//단어카드바인터 윈도우의 트리뷰에서 품사항목을 추가한다.

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

		//끼우기 윈도우를 없앤다.
		EndDialog(hWnd, 0);
	}
	else if (message == IDNO) {
		EndDialog(hWnd, 0);
	}

	RemoveProp(hWnd, "PROP_TRYCOUNT");
	RemoveProp(hWnd, "PROP_SUCCESSFUL");

	return TRUE;
}

