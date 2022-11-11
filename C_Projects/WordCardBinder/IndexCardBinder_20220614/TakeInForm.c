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


//1. �����찡 ������ ��
BOOL TakeInForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	//1.1 ǰ�� �޺��ڽ��� �׸��� �߰��Ѵ�.
	TCHAR wordClasses[][16] = { "���","����","����","�λ�",
		"�����","��ġ��","���ӻ�","��ź��" };
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
	

	//2. ö�ڿ� ��Ŀ���� ���� ��
	if (HIWORD(wParam) == EN_KILLFOCUS) {

		//2.1 ö�ڸ� �д´�.
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_SPELLING), WM_GETTEXT, 
			(WPARAM)32, (LPARAM)spelling);

		//2.2 �ܾ�ī����δ� �����츦 ã�´�.
		hWordCardBinder = FindWindow("#32770", "�ܾ�ī����δ�");

		//2.3 �ܾ�ī����δ� �������� ����ö���� ���ĺ����� ã�´�.
		
		indexCardBinder = (IndexCardBinder*)GetProp(hWordCardBinder, "PROP_INDEXCARDBINDER");

		indexCardIndex = IndexCardBinder_Find(indexCardBinder, spelling[0]);

		//2.4 ã������
		if (indexCardIndex != NULL) {

			//2.4.1 ã�� ����ī�忡�� ö���� ��ġ�� ã�´�.
			index = IndexCard_FindBySpellings(indexCardIndex, spelling);

			//2.4.2 ã������
			if (index >= 0) {

				current = IndexCard_GetAt(indexCardIndex, index);

				//2.4.2.1 ǰ��, �ǹ�, ������ ����Ѵ�.
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

	//3. ����� ��ư�� Ŭ������ ��
	if (HIWORD(wParam) == BN_CLICKED) {

		//3.1 ö��, �ǹ�, ǰ��, ������ �д´�.
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_SPELLING), WM_GETTEXT,
			(WPARAM)32, (LPARAM)wordCard.word.spelling);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_MEANING), WM_GETTEXT,
			(WPARAM)128, (LPARAM)wordCard.word.meaning);
		SendMessage(GetDlgItem(hWnd, IDC_COMBO_WORDCLASS), WM_GETTEXT,
			(WPARAM)16, (LPARAM)wordCard.word.wordClass);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_EXAMPLESENTENCE), WM_GETTEXT,
			(WPARAM)256, (LPARAM)wordCard.word.exampleSentence);

		//�ʵ��߰�
		wordCard.tryCount = 0;
		wordCard.successfulCount = 0;

		//3.2 �ܾ�ī����δ� �����츦 ã�´�.
		hWordCardBinder = FindWindow("#32770", "�ܾ�ī����δ�");

		wordCardBinder = (WordCardBinder*)GetWindowLongPtr(hWordCardBinder, GWLP_USERDATA);

		//3.3 �ܾ�ī����δ� �������� �ܾ�ī����δ����� �����.
		current = TakeIn(wordCardBinder, wordCard);

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

		//3.5 ����� �����츦 ���ش�.
		EndDialog(hWnd, 0);
	}
	return TRUE;
}

//4. �ݱ� ��Ʈ���� Ŭ������ ��
BOOL TakeInForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	//4.1 ����� �����츦 ���ش�.
	EndDialog(hWnd, 0);

	return TRUE;
}