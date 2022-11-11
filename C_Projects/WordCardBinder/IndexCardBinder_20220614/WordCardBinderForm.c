#include "WordCardBinderForm.h"
#include "WordCardBinder.h"
#include "IndexCard.h"
#include "IndexCardBinder.h"
#include "resource.h"
#include "TakeInForm.h"
#include "FindingForm.h"
#include "TakeOutForm.h"
#include "TestForm.h"
#include "ResultForm.h"
#include <CommCtrl.h>
#include <stdio.h>
#include <stdlib.h>


#pragma warning (disable : 4996)

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine,
	int nCmdShow) {

	int response;
	response = DialogBox(hInstance, MAKEINTRESOURCE(IDD_WORDCARDBINDERFORM), NULL,
		WordCardBinderFormProc);
	return response;
}

BOOL CALLBACK WordCardBinderFormProc(HWND hWnd, UINT message,
	WPARAM wParam, LPARAM lParam) {

	BOOL ret;

	switch (message) {

	case WM_INITDIALOG:
		ret = WordCardBinderForm_OnInitDialog(hWnd, wParam, lParam);
		break;
	case WM_COMMAND:
		ret = WordCardBinderForm_OnCommand(hWnd, wParam, lParam);
		break;
	case WM_NOTIFY:
		ret = WordCardBinderForm_OnNotify(hWnd, wParam, lParam);
		break;
	case WM_CLOSE:
		ret = WordCardBinderForm_OnClose(hWnd, wParam, lParam);
		break;
	default:
		ret = FALSE;
		break;
	}
	return ret;
}


BOOL WordCardBinderForm_OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	BOOL ret;

	switch (LOWORD(wParam)){

	case IDC_BUTTON_FIRST:
		ret = WordCardBinderForm_OnFirstButtonClicked(hWnd, wParam, lParam);
		break;
	case IDC_BUTTON_PREVIOUS:
		ret = WordCardBinderForm_OnPreviousButtonClicked(hWnd, wParam, lParam);
		break;
	case IDC_BUTTON_NEXT:
		ret = WordCardBinderForm_OnNextButtonClicked(hWnd, wParam, lParam);
		break;
	case IDC_BUTTON_LAST:
		ret = WordCardBinderForm_OnLastButtonClicked(hWnd, wParam, lParam);
		break;
	case IDC_BUTTON_TAKEIN:
		ret = WordCardBinderForm_OnTakeInButtonClicked(hWnd, wParam, lParam);
		break;
	case IDC_BUTTON_FIND:
		ret = WordCardBinderForm_OnFindButtonClicked(hWnd, wParam, lParam);
		break;
	case IDC_BUTTON_TAKEOUT:
		ret = WordCardBinderForm_OnTakeOutButtonClicked(hWnd, wParam, lParam);
		break;
	case IDC_BUTTON_ARRANGE:
		ret = WordCardBinderForm_OnArrangeButtonClicked(hWnd, wParam, lParam);
		break;
	case IDC_BUTTON_TEST:
		ret = WordCardBinderForm_OnTestButtonClicked(hWnd, wParam, lParam);
		break;
	case IDC_BUTTON_RESULT:
		ret = WordCardBinderForm_OnResultButtonClicked(hWnd, wParam, lParam);
		break;
	default:
		ret = FALSE;
		break;
	}
	return ret;
}

BOOL WordCardBinderForm_OnNotify(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	BOOL ret;

	switch ((int)wParam) {
		
	case IDC_TREE_WORDS:
		ret = WordCardBinderForm_OnTreeViewItemDoubleClicked(hWnd, wParam, lParam);
		break;
	default:
		ret = FALSE;
		break;
	}
	return ret;
}



//1.윈도우가 생성될 때
BOOL WordCardBinderForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	WordCardBinder *wordCardBinder;
	Long count;
	WordCard *current;
	WordCard *previous;
	IndexCardBinder *indexCardBinder;
	IndexCard(*indexCards);
	Long i;
	Long j;
	TCHAR alphabat[2];
	TCHAR spelling[32];
	TCHAR wordClass[16];
	WordCard(*wordCards);
	Long learnCount;

	TVITEM tvi = { 0, };
	TVINSERTSTRUCT tvins = { 0, };
	HTREEITEM hRoot;
	HTREEITEM hAlphabat;
	HTREEITEM hSpelling;
	HTREEITEM hWordClass;
	HTREEITEM hPrevious;



	//1.1 단어카드 바인더를 만든다.
	wordCardBinder = (WordCardBinder*)malloc(sizeof(WordCardBinder));
	WordCardBinder_Create(wordCardBinder);

	SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG)wordCardBinder);

	//1.2 색인철을 만든다.
	indexCardBinder = (IndexCardBinder*)malloc(sizeof(IndexCardBinder));
	IndexCardBinder_Create(indexCardBinder);
	
	SetProp(hWnd, "PROP_INDEXCARDBINDER", (HANDLE)indexCardBinder);

	//1.3 단어카드 바인더에 적재한다.
	count = Load(wordCardBinder);

	//단어카드배열,외운개수를 저장한다.
	//wordCards = NULL;

	wordCards = (WordCard(*))calloc(100, sizeof(WordCard));
	learnCount = 0;

	SetProp(hWnd, "PROP_WORDCARDS", (HANDLE)wordCards);
	SetProp(hWnd, "PROP_LEARNCOUNT",(HANDLE)learnCount);
	

	//1.4 트리뷰에 루트항목을 추가한다.
	tvi.mask = TVIF_TEXT | TVIF_HANDLE;
	tvi.pszText = "단어들";
	tvins.item = tvi;
	tvins.hInsertAfter = TVI_ROOT;
	hRoot = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_INSERTITEM,
		(WPARAM)0, (LPARAM)&tvins);

	//1.5 단어카드가 적재되었으면
	if (count > 0) {

		//1.5.1 단어카드바인더에 있는 단어카드들을 색인철에 끼운다.
		previous = NULL;
		current = WordCardBinder_First(wordCardBinder);
		while (current != previous) {

			IndexCardBinder_TakeIn(indexCardBinder, current);
			previous = current;
			current = WordCardBinder_Next(wordCardBinder);
		}

		//1.5.2 색인철에서 정리한다.
		IndexCardBinder_Arrange(indexCardBinder);

		//1.5.3 색인카드 리스트를 만든다.
		IndexCardBinder_MakeList(indexCardBinder, &indexCards, &count);

		//1.5.4 색인카드 개수만큼 반복한다.
		i = 0;
		while (i < count) {

			//1.5.4.1 트리뷰에 알파벳을 추가한다.
			sprintf(alphabat, "%c\0", indexCards[i].alphabat - 32);
			tvi.pszText = alphabat;
			//tvi.pszText = &indexCards[i].alphabat;
			tvins.item = tvi;
			tvins.hParent = hRoot;
			tvins.hInsertAfter = TVI_LAST;
			tvins.hParent = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_INSERTITEM,
				(WPARAM)0, (LPARAM)&tvins);
			hAlphabat = tvins.hParent;

			//1.5.4.2 색인카드의 사용량만큼 반복한다.
			j = 0;
			while (j < indexCards[i].length) {

				current = IndexCard_GetAt(indexCards + i, j);
				
				//1.5.4.2.1 트리뷰의 알파벳의 하위항목에서 철자를 찾는다.
				hSpelling = (HTREEITEM) SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETNEXTITEM,
					(WPARAM)TVGN_CHILD, (LPARAM)hAlphabat);

				tvi.hItem = hSpelling;
				tvi.pszText = spelling;
				tvi.cchTextMax = 32;

				SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETITEM,
					(WPARAM)0, (LPARAM)&tvi);

				while (hSpelling != NULL && strcmp(current->word.spelling, spelling) != 0) {
					
					hSpelling = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETNEXTITEM,
						(WPARAM)TVGN_NEXT, (LPARAM)hSpelling);
					tvi.hItem = hSpelling;

					SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETITEM,
						(WPARAM)0, (LPARAM)&tvi);
				}

				//1.5.4.2.2 철자가 없다면
				if (hSpelling == NULL) {

					//1.5.4.2.2.1 트리뷰의 알파벳의 하위항목에 철자를 추가한다.
					tvi.pszText = current->word.spelling;
					tvins.item = tvi;
					tvins.hParent = hAlphabat;
					tvins.hInsertAfter = TVI_LAST;

					hSpelling = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_INSERTITEM,
						(WPARAM)0, (LPARAM)&tvins);

					tvins.hParent = hSpelling;
				}

				//1.5.4.2.3 철자의 하위항목에 품사를 추가한다.
				hWordClass = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETNEXTITEM,
					(WPARAM)TVGN_CHILD, (LPARAM)hSpelling);
				
				hPrevious = NULL;
				tvi.hItem = hWordClass;
				tvi.pszText = wordClass;
				tvi.cchTextMax = 16;

				SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETITEM, (WPARAM)0, (LPARAM)&tvi);

				while (hWordClass != NULL && strcmp(current->word.wordClass, wordClass) > 0) {

					hPrevious = hWordClass;
					hWordClass = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETNEXTITEM,
						(WPARAM)TVGN_NEXT, (LPARAM)hWordClass);

					tvi.hItem = hWordClass;
					SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETITEM, (WPARAM)0, (LPARAM)&tvi);
				}
				if (hPrevious == NULL) {
					tvins.hInsertAfter = TVI_FIRST;
				}
				else if (hWordClass == NULL) {
					tvins.hInsertAfter = TVI_LAST;
				}
				else if(hWordClass != NULL){
					tvins.hInsertAfter = hPrevious;
				}

				tvi.pszText = current->word.wordClass;
				tvins.item = tvi;
				SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_INSERTITEM,
					(WPARAM)0, (LPARAM)&tvins);

				j++;
			}
			i++;
		}
		if (indexCards != NULL) {
			free(indexCards);
		}

		//1.5.5 단어카드 바인더에서 첫 번째 카드로 이동한다.
		current = WordCardBinder_First(wordCardBinder);

		//1.5.6 현재카드를 출력한다.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITSPELLING), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->word.spelling);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITMEANING), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->word.meaning);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITWORDCLASS), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->word.wordClass);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITEXAMPLESENTENCE), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->word.exampleSentence);

		//1.5.7 트리뷰에서 알파벳 항목을 찾는다.
		hAlphabat = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETNEXTITEM,
			(WPARAM)TVGN_CHILD, (LPARAM)hRoot);

		tvi.hItem = hAlphabat;
		tvi.pszText = alphabat;
		tvi.cchTextMax = 2;
		SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETITEM,
			(WPARAM)0, (LPARAM)&tvi);

		while (hAlphabat != NULL && current->word.spelling[0] != alphabat[0] + 32) {
		
			hAlphabat = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETNEXTITEM,
				(WPARAM)TVGN_NEXT, (LPARAM)hAlphabat);
			tvi.hItem = hAlphabat;

			SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETITEM,
				(WPARAM)0, (LPARAM)&tvi);
		}
		
		//1.5.8 트리뷰에서 철자 항목을 찾는다.
		hSpelling = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETNEXTITEM,
			(WPARAM)TVGN_CHILD, (LPARAM)hAlphabat);

		tvi.hItem = hSpelling;
		tvi.pszText = spelling;
		tvi.cchTextMax = 32;
		SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETITEM,
			(WPARAM)0, (LPARAM)&tvi);

		while (hSpelling != NULL && strcmp(current->word.spelling, spelling) != 0) {

			hSpelling = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETNEXTITEM,
				(WPARAM)TVGN_NEXT, (LPARAM)hSpelling);
			tvi.hItem = hSpelling;

			SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETITEM,
				(WPARAM)0, (LPARAM)&tvi);
		}

		//1.5.9 트리뷰에서 품사 항목을 찾는다.
		hWordClass = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETNEXTITEM,
			(WPARAM)TVGN_CHILD, (LPARAM)hSpelling);

		tvi.hItem = hWordClass;
		tvi.pszText = wordClass;
		tvi.cchTextMax = 16;
		SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETITEM,
			(WPARAM)0, (LPARAM)&tvi);

		while (hWordClass != NULL && strcmp(current->word.wordClass, wordClass) != 0) {

			hWordClass = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETNEXTITEM,
				(WPARAM)TVGN_NEXT, (LPARAM)hWordClass);
			tvi.hItem = hWordClass;

			SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETITEM,
				(WPARAM)0, (LPARAM)&tvi);
		}

		//1.5.10 트리뷰에서 루트를 펼친다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_EXPAND,
			(WPARAM)TVE_EXPAND, (LPARAM)hRoot);

		//1.5.11 트리뷰에서 알파벳을 펼친다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_EXPAND,
			(WPARAM)TVE_EXPAND, (LPARAM)hAlphabat);

		//1.5.12 트리뷰에서 철자를 펼친다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_EXPAND,
			(WPARAM)TVE_EXPAND, (LPARAM)hSpelling);

		//1.5.13 트리뷰에서 해당 항목을 표시한다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), WM_SETFOCUS, (WPARAM)0, (LPARAM)0);

		SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_SELECTITEM,
			(WPARAM)TVGN_CARET, (LPARAM)hWordClass);
	}
	else{

		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITSPELLING), WM_SETTEXT,
			(WPARAM)0, (LPARAM)"");
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITMEANING), WM_SETTEXT,
			(WPARAM)0, (LPARAM)"");
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITWORDCLASS), WM_SETTEXT,
			(WPARAM)0, (LPARAM)"");
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITEXAMPLESENTENCE), WM_SETTEXT,
			(WPARAM)0, (LPARAM)"");
	}
	return TRUE;
}


BOOL WordCardBinderForm_OnFirstButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	WordCardBinder *wordCardBinder;
	WordCard *current;
	TCHAR alphabat[2];
	TCHAR spelling[32];
	TCHAR wordClass[16];
	
	TVITEM tvi = { 0, };
	HTREEITEM hRoot;
	HTREEITEM hAlphabat;
	HTREEITEM hSpelling;
	HTREEITEM hWordClass;


	//2.처음버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED) {

		wordCardBinder = (WordCardBinder*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
		//2.1 단어카드 바인더에서 첫 번째 카드로 이동한다.
		current = WordCardBinder_First(wordCardBinder);

		//2.2 현재 카드를 출력한다.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITSPELLING), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->word.spelling);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITMEANING), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->word.meaning);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITWORDCLASS), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->word.wordClass);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITEXAMPLESENTENCE), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->word.exampleSentence);

		

		//트리뷰에서 루트 항목을 찾는다.
		hRoot = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETNEXTITEM, (WPARAM)TVGN_ROOT,(LPARAM)0);
		
		//트리뷰의 루트항목의 하위항목에서 알파벳을 찾는다.
		hAlphabat = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETNEXTITEM, 
			(WPARAM)TVGN_CHILD, (LPARAM)hRoot);

		tvi.mask = TVIF_TEXT | TVIF_HANDLE;
		tvi.hItem = hAlphabat;
		tvi.pszText = alphabat;
		tvi.cchTextMax = 2;

		SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETITEM, (WPARAM)0, (LPARAM)&tvi);

		while (hAlphabat != NULL && current->word.spelling[0] != alphabat[0] + 32) {

			hAlphabat = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETNEXTITEM,
				(WPARAM)TVGN_NEXT, (LPARAM)hAlphabat);
			tvi.hItem = hAlphabat;

			SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETITEM,
				(WPARAM)0, (LPARAM)&tvi);
		}

		//트리뷰에서 철자 항목을 찾는다.
		hSpelling = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETNEXTITEM,
			(WPARAM)TVGN_CHILD, (LPARAM)hAlphabat);

		tvi.hItem = hSpelling;
		tvi.pszText = spelling;
		tvi.cchTextMax = 32;
		SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETITEM,
			(WPARAM)0, (LPARAM)&tvi);

		while (hSpelling != NULL && strcmp(current->word.spelling, spelling) != 0) {

			hSpelling = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETNEXTITEM,
				(WPARAM)TVGN_NEXT, (LPARAM)hSpelling);
			tvi.hItem = hSpelling;

			SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETITEM,
				(WPARAM)0, (LPARAM)&tvi);
		}

		//트리뷰에서 품사 항목을 찾는다.
		hWordClass = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETNEXTITEM,
			(WPARAM)TVGN_CHILD, (LPARAM)hSpelling);

		tvi.hItem = hWordClass;
		tvi.pszText = wordClass;
		tvi.cchTextMax = 16;
		SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETITEM,
			(WPARAM)0, (LPARAM)&tvi);

		while (hWordClass != NULL && strcmp(current->word.wordClass, wordClass) != 0) {

			hWordClass = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETNEXTITEM,
				(WPARAM)TVGN_NEXT, (LPARAM)hWordClass);
			tvi.hItem = hWordClass;

			SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETITEM,
				(WPARAM)0, (LPARAM)&tvi);
		}

		//트리뷰에서 루트를 펼친다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_EXPAND,
			(WPARAM)TVE_EXPAND, (LPARAM)hRoot);

		//트리뷰에서 알파벳을 펼친다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_EXPAND,
			(WPARAM)TVE_EXPAND, (LPARAM)hAlphabat);

		//트리뷰에서 철자를 펼친다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_EXPAND,
			(WPARAM)TVE_EXPAND, (LPARAM)hSpelling);

		//트리뷰에서 해당 항목을 표시한다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), WM_SETFOCUS, (WPARAM)0, (LPARAM)0);

		SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_SELECTITEM,
			(WPARAM)TVGN_CARET, (LPARAM)hWordClass);

	}
	return TRUE;
}

BOOL WordCardBinderForm_OnPreviousButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	WordCardBinder *wordCardBinder;
	WordCard *current;
	TCHAR alphabat[2];
	TCHAR spelling[32];
	TCHAR wordClass[16];

	TVITEM tvi = { 0, };
	HTREEITEM hRoot;
	HTREEITEM hAlphabat;
	HTREEITEM hSpelling;
	HTREEITEM hWordClass;

	//3. 이전버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED) {

		wordCardBinder = (WordCardBinder*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
		//3.1 단어카드 바인더에서 이전 카드로 이동한다.
		current = WordCardBinder_Previous(wordCardBinder);

		//3.2 현재 카드를 출력한다.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITSPELLING), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->word.spelling);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITMEANING), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->word.meaning);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITWORDCLASS), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->word.wordClass);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITEXAMPLESENTENCE), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->word.exampleSentence);

		

		//트리뷰에서 루트 항목을 찾는다.
		hRoot = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETNEXTITEM, (WPARAM)TVGN_ROOT, (LPARAM)0);

		//트리뷰의 루트항목의 하위항목에서 알파벳을 찾는다.
		hAlphabat = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETNEXTITEM,
			(WPARAM)TVGN_CHILD, (LPARAM)hRoot);

		tvi.mask = TVIF_TEXT | TVIF_HANDLE;
		tvi.hItem = hAlphabat;
		tvi.pszText = alphabat;
		tvi.cchTextMax = 2;

		SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETITEM, (WPARAM)0, (LPARAM)&tvi);

		while (hAlphabat != NULL && current->word.spelling[0] != alphabat[0] + 32) {

			hAlphabat = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETNEXTITEM,
				(WPARAM)TVGN_NEXT, (LPARAM)hAlphabat);
			tvi.hItem = hAlphabat;

			SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETITEM,
				(WPARAM)0, (LPARAM)&tvi);
		}

		//트리뷰에서 철자 항목을 찾는다.
		hSpelling = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETNEXTITEM,
			(WPARAM)TVGN_CHILD, (LPARAM)hAlphabat);

		tvi.hItem = hSpelling;
		tvi.pszText = spelling;
		tvi.cchTextMax = 32;
		SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETITEM,
			(WPARAM)0, (LPARAM)&tvi);

		while (hSpelling != NULL && strcmp(current->word.spelling, spelling) != 0) {

			hSpelling = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETNEXTITEM,
				(WPARAM)TVGN_NEXT, (LPARAM)hSpelling);
			tvi.hItem = hSpelling;

			SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETITEM,
				(WPARAM)0, (LPARAM)&tvi);
		}

		//트리뷰에서 품사 항목을 찾는다.
		hWordClass = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETNEXTITEM,
			(WPARAM)TVGN_CHILD, (LPARAM)hSpelling);

		tvi.hItem = hWordClass;
		tvi.pszText = wordClass;
		tvi.cchTextMax = 16;
		SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETITEM,
			(WPARAM)0, (LPARAM)&tvi);

		while (hWordClass != NULL && strcmp(current->word.wordClass, wordClass) != 0) {

			hWordClass = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETNEXTITEM,
				(WPARAM)TVGN_NEXT, (LPARAM)hWordClass);
			tvi.hItem = hWordClass;

			SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETITEM,
				(WPARAM)0, (LPARAM)&tvi);
		}

		//트리뷰에서 루트를 펼친다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_EXPAND,
			(WPARAM)TVE_EXPAND, (LPARAM)hRoot);

		//트리뷰에서 알파벳을 펼친다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_EXPAND,
			(WPARAM)TVE_EXPAND, (LPARAM)hAlphabat);

		//트리뷰에서 철자를 펼친다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_EXPAND,
			(WPARAM)TVE_EXPAND, (LPARAM)hSpelling);

		//트리뷰에서 해당 항목을 표시한다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), WM_SETFOCUS, (WPARAM)0, (LPARAM)0);

		SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_SELECTITEM,
			(WPARAM)TVGN_CARET, (LPARAM)hWordClass);
	}
	return TRUE;
}

BOOL WordCardBinderForm_OnNextButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	WordCardBinder *wordCardBinder;
	WordCard *current;
	TCHAR alphabat[2];
	TCHAR spelling[32];
	TCHAR wordClass[16];
	
	TVITEM tvi = { 0, };
	HTREEITEM hRoot;
	HTREEITEM hAlphabat;
	HTREEITEM hSpelling;
	HTREEITEM hWordClass;

	//4. 다음버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED) {

		wordCardBinder = (WordCardBinder*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
		//4.1 단어카드 바인더에서 다음 카드로 이동한다.
		current = WordCardBinder_Next(wordCardBinder);

		//4.2 현재 카드를 출력한다.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITSPELLING), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->word.spelling);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITMEANING), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->word.meaning);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITWORDCLASS), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->word.wordClass);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITEXAMPLESENTENCE), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->word.exampleSentence);

	

		//트리뷰에서 루트 항목을 찾는다.
		hRoot = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETNEXTITEM, 
			(WPARAM)TVGN_ROOT, (LPARAM)0);

		//트리뷰의 루트항목의 하위항목에서 알파벳을 찾는다.
		hAlphabat = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETNEXTITEM,
			(WPARAM)TVGN_CHILD, (LPARAM)hRoot);

		tvi.mask = TVIF_TEXT | TVIF_HANDLE;
		tvi.hItem = hAlphabat;
		tvi.pszText = alphabat;
		tvi.cchTextMax = 2;

		SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETITEM, (WPARAM)0, (LPARAM)&tvi);

		while (hAlphabat != NULL && current->word.spelling[0] != alphabat[0] + 32) {

			hAlphabat = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETNEXTITEM,
				(WPARAM)TVGN_NEXT, (LPARAM)hAlphabat);
			tvi.hItem = hAlphabat;

			SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETITEM,
				(WPARAM)0, (LPARAM)&tvi);
		}

		//트리뷰에서 철자 항목을 찾는다.
		hSpelling = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETNEXTITEM,
			(WPARAM)TVGN_CHILD, (LPARAM)hAlphabat);

		tvi.hItem = hSpelling;
		tvi.pszText = spelling;
		tvi.cchTextMax = 32;
		SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETITEM,
			(WPARAM)0, (LPARAM)&tvi);

		while (hSpelling != NULL && strcmp(current->word.spelling, spelling) != 0) {

			hSpelling = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETNEXTITEM,
				(WPARAM)TVGN_NEXT, (LPARAM)hSpelling);
			tvi.hItem = hSpelling;

			SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETITEM,
				(WPARAM)0, (LPARAM)&tvi);
		}

		//트리뷰에서 품사 항목을 찾는다.
		hWordClass = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETNEXTITEM,
			(WPARAM)TVGN_CHILD, (LPARAM)hSpelling);

		tvi.hItem = hWordClass;
		tvi.pszText = wordClass;
		tvi.cchTextMax = 16;
		SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETITEM,
			(WPARAM)0, (LPARAM)&tvi);

		while (hWordClass != NULL && strcmp(current->word.wordClass, wordClass) != 0) {

			hWordClass = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETNEXTITEM,
				(WPARAM)TVGN_NEXT, (LPARAM)hWordClass);
			tvi.hItem = hWordClass;

			SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETITEM,
				(WPARAM)0, (LPARAM)&tvi);
		}

		//트리뷰에서 루트를 펼친다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_EXPAND,
			(WPARAM)TVE_EXPAND, (LPARAM)hRoot);

		//트리뷰에서 알파벳을 펼친다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_EXPAND,
			(WPARAM)TVE_EXPAND, (LPARAM)hAlphabat);

		//트리뷰에서 철자를 펼친다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_EXPAND,
			(WPARAM)TVE_EXPAND, (LPARAM)hSpelling);

		//트리뷰에서 해당 항목을 표시한다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), WM_SETFOCUS, (WPARAM)0, (LPARAM)0);

		SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_SELECTITEM,
			(WPARAM)TVGN_CARET, (LPARAM)hWordClass);
	}
	return TRUE;
}

BOOL WordCardBinderForm_OnLastButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	WordCardBinder *wordCardBinder;
	WordCard *current;
	TCHAR alphabat[2];
	TCHAR spelling[32];
	TCHAR wordClass[16];

	TVITEM tvi = { 0, };
	HTREEITEM hRoot;
	HTREEITEM hAlphabat;
	HTREEITEM hSpelling;
	HTREEITEM hWordClass;


	//5.끝버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED) {

		wordCardBinder = (WordCardBinder*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
		//5.1 단어카드 바인더에서 마지막 카드로 이동한다.
		current = WordCardBinder_Last(wordCardBinder);

		//5.2 현재 카드를 출력한다.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITSPELLING), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->word.spelling);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITMEANING), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->word.meaning);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITWORDCLASS), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->word.wordClass);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITEXAMPLESENTENCE), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->word.exampleSentence);


		//트리뷰에서 루트 항목을 찾는다.
		hRoot = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETNEXTITEM, (WPARAM)TVGN_ROOT, (LPARAM)0);

		//트리뷰의 루트항목의 하위항목에서 알파벳을 찾는다.
		hAlphabat = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETNEXTITEM,
			(WPARAM)TVGN_CHILD, (LPARAM)hRoot);

		tvi.mask = TVIF_TEXT | TVIF_HANDLE;
		tvi.hItem = hAlphabat;
		tvi.pszText = alphabat;
		tvi.cchTextMax = 2;

		SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETITEM, (WPARAM)0, (LPARAM)&tvi);

		while (hAlphabat != NULL && current->word.spelling[0] != alphabat[0] + 32) {

			hAlphabat = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETNEXTITEM,
				(WPARAM)TVGN_NEXT, (LPARAM)hAlphabat);
			tvi.hItem = hAlphabat;

			SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETITEM,
				(WPARAM)0, (LPARAM)&tvi);
		}

		//트리뷰에서 철자 항목을 찾는다.
		hSpelling = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETNEXTITEM,
			(WPARAM)TVGN_CHILD, (LPARAM)hAlphabat);

		tvi.hItem = hSpelling;
		tvi.pszText = spelling;
		tvi.cchTextMax = 32;
		SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETITEM,
			(WPARAM)0, (LPARAM)&tvi);

		while (hSpelling != NULL && strcmp(current->word.spelling, spelling) != 0) {

			hSpelling = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETNEXTITEM,
				(WPARAM)TVGN_NEXT, (LPARAM)hSpelling);
			tvi.hItem = hSpelling;

			SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETITEM,
				(WPARAM)0, (LPARAM)&tvi);
		}

		//트리뷰에서 품사 항목을 찾는다.
		hWordClass = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETNEXTITEM,
			(WPARAM)TVGN_CHILD, (LPARAM)hSpelling);

		tvi.hItem = hWordClass;
		tvi.pszText = wordClass;
		tvi.cchTextMax = 16;
		SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETITEM,
			(WPARAM)0, (LPARAM)&tvi);

		while (hWordClass != NULL && strcmp(current->word.wordClass, wordClass) != 0) {

			hWordClass = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETNEXTITEM,
				(WPARAM)TVGN_NEXT, (LPARAM)hWordClass);
			tvi.hItem = hWordClass;

			SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETITEM,
				(WPARAM)0, (LPARAM)&tvi);
		}

		//트리뷰에서 루트를 펼친다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_EXPAND,
			(WPARAM)TVE_EXPAND, (LPARAM)hRoot);

		//트리뷰에서 알파벳을 펼친다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_EXPAND,
			(WPARAM)TVE_EXPAND, (LPARAM)hAlphabat);

		//트리뷰에서 철자를 펼친다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_EXPAND,
			(WPARAM)TVE_EXPAND, (LPARAM)hSpelling);

		//트리뷰에서 해당 항목을 표시한다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), WM_SETFOCUS, (WPARAM)0, (LPARAM)0);

		SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_SELECTITEM,
			(WPARAM)TVGN_CARET, (LPARAM)hWordClass);

	}
	return TRUE;
}


BOOL WordCardBinderForm_OnTakeInButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	// 6. 끼우기 버튼을 클릭했을 때
		if (HIWORD(wParam) == BN_CLICKED) {

			//6.1 끼우기 윈도우를 출력한다.
			DialogBox((HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
				MAKEINTRESOURCE(IDD_TAKEINFORM), NULL, TakeInFormProc);
		}
	return TRUE;
}



BOOL WordCardBinderForm_OnFindButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	//7. 찾기 버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED) {

		//7. 찾기 윈도우를 출력한다.
		DialogBox((HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
			MAKEINTRESOURCE(IDD_FINDINGFORM), NULL, FindingFormProc);
	}
	return TRUE;
}



BOOL WordCardBinderForm_OnTakeOutButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	//8. 꺼내기 버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED) {

		//8.1 꺼내기 윈도우를 출력한다.
		DialogBox((HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
			MAKEINTRESOURCE(IDD_TAKEOUTFORM), NULL, TakeOutFormProc);
	}
	return TRUE;
}


BOOL WordCardBinderForm_OnArrangeButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	WordCardBinder *wordCardBinder;
	WordCard *current;
	Long count;
	IndexCardBinder *indexCardBinder;
	IndexCard(*indexCards);
	Long i;
	Long j;
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
	

	//정리하기 버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED) {

		//색인철에서 정리한다.
		indexCardBinder = (IndexCardBinder*)GetProp(hWnd, "PROP_INDEXCARDBINDER");

		IndexCardBinder_Arrange(indexCardBinder);

		//트리뷰에서 모든 항목을 없앤다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_DELETEITEM, (WPARAM)0, (LPARAM)TVI_ROOT);

		//트리뷰에 루트항목을 추가한다.
		tvi.mask = TVIF_TEXT | TVIF_HANDLE;
		tvi.pszText = "단어들";
		tvins.item = tvi;
		tvins.hInsertAfter = TVI_ROOT;
		hRoot = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_INSERTITEM,
			(WPARAM)0, (LPARAM)&tvins);

		//색인카드 리스트를 만든다.
		IndexCardBinder_MakeList(indexCardBinder, &indexCards, &count);

		//색인카드 개수만큼 반복한다.
		i = 0;
		while (i < count) {

			//트리뷰에 알파벳을 추가한다.
			sprintf(alphabat, "%c\0", indexCards[i].alphabat - 32);
			tvi.pszText = alphabat;
			tvins.item = tvi;
			tvins.hParent = hRoot;
			tvins.hInsertAfter = TVI_LAST;
			tvins.hParent = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_INSERTITEM,
				(WPARAM)0, (LPARAM)&tvins);
			hAlphabat = tvins.hParent;

			//색인카드의 사용량만큼 반복한다.
			j = 0;
			while (j < indexCards[i].length) {

				current = IndexCard_GetAt(indexCards + i, j);

				//트리뷰의 알파벳의 하위항목에서 철자를 찾는다.
				hSpelling = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETNEXTITEM,
					(WPARAM)TVGN_CHILD, (LPARAM)hAlphabat);

				tvi.hItem = hSpelling;
				tvi.pszText = spelling;
				tvi.cchTextMax = 32;

				SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETITEM,
					(WPARAM)0, (LPARAM)&tvi);

				while (hSpelling != NULL && strcmp(current->word.spelling, spelling) != 0) {

					hSpelling = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETNEXTITEM,
						(WPARAM)TVGN_NEXT, (LPARAM)hSpelling);
					tvi.hItem = hSpelling;

					SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETITEM,
						(WPARAM)0, (LPARAM)&tvi);
				}

				//철자가 없다면
				if (hSpelling == NULL) {

					//트리뷰의 알파벳의 하위항목에 철자를 추가한다.
					tvi.pszText = current->word.spelling;
					tvins.item = tvi;
					tvins.hParent = hAlphabat;
					tvins.hInsertAfter = TVI_LAST;

					hSpelling = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_INSERTITEM,
						(WPARAM)0, (LPARAM)&tvins);

					tvins.hParent = hSpelling;
				}

				//철자의 하위항목에 품사를 추가한다.
				hWordClass = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETNEXTITEM,
					(WPARAM)TVGN_CHILD, (LPARAM)hSpelling);

				hPrevious = NULL;
				tvi.hItem = hWordClass;
				tvi.pszText = wordClass;
				tvi.cchTextMax = 16;

				SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETITEM, (WPARAM)0, (LPARAM)&tvi);

				while (hWordClass != NULL && strcmp(current->word.wordClass, wordClass) > 0) {

					hPrevious = hWordClass;
					hWordClass = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETNEXTITEM,
						(WPARAM)TVGN_NEXT, (LPARAM)hWordClass);

					tvi.hItem = hWordClass;
					SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETITEM, (WPARAM)0, (LPARAM)&tvi);
				}
				if (hPrevious == NULL) {
					tvins.hInsertAfter = TVI_FIRST;
				}
				else if (hWordClass == NULL) {
					tvins.hInsertAfter = TVI_LAST;
				}
				else if (hWordClass != NULL) {
					tvins.hInsertAfter = hPrevious;
				}

				tvi.pszText = current->word.wordClass;
				tvins.item = tvi;
				SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_INSERTITEM,
					(WPARAM)0, (LPARAM)&tvins);

				j++;
			}
			i++;
		}
		if (indexCards != NULL) {
			free(indexCards);
		}

		

		//단어카드 바인더에서 첫 번째 카드로 이동한다.
		wordCardBinder = (WordCardBinder*)GetWindowLongPtr(hWnd, GWLP_USERDATA);

		current = WordCardBinder_First(wordCardBinder);

		//현재카드를 출력한다.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITSPELLING), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->word.spelling);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITMEANING), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->word.meaning);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITWORDCLASS), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->word.wordClass);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITEXAMPLESENTENCE), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->word.exampleSentence);


		//트리뷰에서 알파벳 항목을 찾는다.
		hAlphabat = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETNEXTITEM,
			(WPARAM)TVGN_CHILD, (LPARAM)hRoot);

		tvi.hItem = hAlphabat;
		tvi.pszText = alphabat;
		tvi.cchTextMax = 2;
		SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETITEM,
			(WPARAM)0, (LPARAM)&tvi);

		while (hAlphabat != NULL && current->word.spelling[0] != alphabat[0] + 32) {

			hAlphabat = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETNEXTITEM,
				(WPARAM)TVGN_NEXT, (LPARAM)hAlphabat);
			tvi.hItem = hAlphabat;

			SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETITEM,
				(WPARAM)0, (LPARAM)&tvi);
		}

		//트리뷰에서 철자 항목을 찾는다.
		hSpelling = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETNEXTITEM,
			(WPARAM)TVGN_CHILD, (LPARAM)hAlphabat);

		tvi.hItem = hSpelling;
		tvi.pszText = spelling;
		tvi.cchTextMax = 32;
		SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETITEM,
			(WPARAM)0, (LPARAM)&tvi);

		while (hSpelling != NULL && strcmp(current->word.spelling, spelling) != 0) {

			hSpelling = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETNEXTITEM,
				(WPARAM)TVGN_NEXT, (LPARAM)hSpelling);
			tvi.hItem = hSpelling;

			SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETITEM,
				(WPARAM)0, (LPARAM)&tvi);
		}

		//트리뷰에서 품사 항목을 찾는다.
		hWordClass = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETNEXTITEM,
			(WPARAM)TVGN_CHILD, (LPARAM)hSpelling);

		tvi.hItem = hWordClass;
		tvi.pszText = wordClass;
		tvi.cchTextMax = 16;
		SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETITEM,
			(WPARAM)0, (LPARAM)&tvi);

		while (hWordClass != NULL && strcmp(current->word.wordClass, wordClass) != 0) {

			hWordClass = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETNEXTITEM,
				(WPARAM)TVGN_NEXT, (LPARAM)hWordClass);
			tvi.hItem = hWordClass;

			SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETITEM,
				(WPARAM)0, (LPARAM)&tvi);
		}

		//트리뷰에서 루트를 펼친다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_EXPAND,
			(WPARAM)TVE_EXPAND, (LPARAM)hRoot);

		//트리뷰에서 알파벳을 펼친다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_EXPAND,
			(WPARAM)TVE_EXPAND, (LPARAM)hAlphabat);

		//트리뷰에서 철자를 펼친다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_EXPAND,
			(WPARAM)TVE_EXPAND, (LPARAM)hSpelling);

		//트리뷰에서 해당 항목을 표시한다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), WM_SETFOCUS, (WPARAM)0, (LPARAM)0);

		SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_SELECTITEM,
			(WPARAM)TVGN_CARET, (LPARAM)hWordClass);
	}
	return TRUE;
}

BOOL WordCardBinderForm_OnTestButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	if (HIWORD(wParam) == BN_CLICKED) {	//시험보기 버튼을 클릭했을 때

		//시험보기 윈도우를 출력한다.
		DialogBox((HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
			MAKEINTRESOURCE(IDD_TESTFORM), NULL, TestFormProc);
	}
	return TRUE;
}

BOOL WordCardBinderForm_OnResultButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	if (HIWORD(wParam) == BN_CLICKED) {	//결과보기 버튼을 클릭했을 때

		//결과보기 윈도우를 출력한다.
		DialogBox((HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
			MAKEINTRESOURCE(IDD_RESULTFORM), NULL, ResultFormProc);
	}
	return TRUE;
}


BOOL WordCardBinderForm_OnTreeViewItemDoubleClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	WordCardBinder *wordCardBinder;
	WordCard *current;
	IndexCardBinder *indexCardBinder;
	IndexCard *indexCardIndex;
	TCHAR wordClass[16];
	TCHAR spelling[32];
	Long index;
	
	TVITEM tvi = { 0, };
	HTREEITEM hWordClass;
	HTREEITEM hSpelling;

	//트리뷰에서 품사 항목을 더블클릭 했을 때
	if (((LPNMHDR)lParam)->code == NM_DBLCLK) {	
	
		//트리뷰에서 해당 항목의 핸들을 읽는다.
		hWordClass = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETNEXTITEM,
			(WPARAM)TVGN_CARET, (LPARAM)0);

		//트리뷰에서 해당항목의 내용을 읽는다.
		tvi.mask = TVIF_TEXT | TVIF_HANDLE;
		
		tvi.hItem = hWordClass;
		tvi.pszText = wordClass;
		tvi.cchTextMax = 16;

		SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETITEM, (WPARAM)0, (LPARAM)&tvi);

		//트리뷰에서 부모항목의 핸들을 읽는다.
		hSpelling = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETNEXTITEM,
			(WPARAM)TVGN_PARENT, (LPARAM)hWordClass);

		//트리뷰에서 부모항목의 내용을 읽는다.
		tvi.hItem = hSpelling;
		tvi.pszText = spelling;
		tvi.cchTextMax = 32;

		SendMessage(GetDlgItem(hWnd, IDC_TREE_WORDS), TVM_GETITEM, (WPARAM)0, (LPARAM)&tvi);

		//색인철에서 알파벳으로 찾는다.
		indexCardBinder = (IndexCardBinder*)GetProp(hWnd, "PROP_INDEXCARDBINDER");

		indexCardIndex =  IndexCardBinder_Find(indexCardBinder, spelling[0]);

		//찾은 색인카드에서 단어카드의 위치를 찾는다.
		index = FindByWordCardMembers(indexCardIndex, spelling, wordClass);

		//찾은 색인카드에서 단어카드의 위치에 해당하는 단어카드를 가져온다.
		current = IndexCard_GetAt(indexCardIndex, index);

		//단어카드 바인더에서 이동한다.
		wordCardBinder = (WordCardBinder*)GetWindowLongPtr(hWnd, GWLP_USERDATA);

		current = WordCardBinder_Move(wordCardBinder, current);

		//해당카드를 출력한다.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITSPELLING), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->word.spelling);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITMEANING), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->word.meaning);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITWORDCLASS), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->word.wordClass);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITEXAMPLESENTENCE), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->word.exampleSentence);

	}
	return TRUE;
}


//10. 닫기 컨트롤을 클릭했을 때
BOOL WordCardBinderForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	WordCardBinder *wordCardBinder;
	IndexCardBinder *indexCardBinder;
	WordCard(*wordCards);

	//단어카드배열을 없앤다.
	wordCards = (WordCard(*))GetProp(hWnd, "PROP_WORDCARDS");
	if (wordCards != NULL) {
		
		free(wordCards);
		RemoveProp(hWnd, "PROP_WORDCARDS");
		
		RemoveProp(hWnd, "PROP_LEARNCOUNT");
	}

	wordCardBinder = (WordCardBinder*)GetWindowLongPtr(hWnd, GWLP_USERDATA);

	if (wordCardBinder != NULL) {

		//10.1 단어카드 바인더에서 저장한다.
		Save(wordCardBinder);

		//10.2 단어카드 바인더를 없앤다.
		WordCardBinder_Destroy(wordCardBinder);
		free(wordCardBinder);
	}

	indexCardBinder = (IndexCardBinder*)GetProp(hWnd, "PROP_INDEXCARDBINDER");

	if (indexCardBinder != NULL) {

		IndexCardBinder_Destroy(indexCardBinder);

		RemoveProp(hWnd, "PROP_INDEXCARDBINDER");

		free(indexCardBinder);
	}

	//10.3 윈도우를 없앤다.
	EndDialog(hWnd, 0);

	return TRUE;
}

