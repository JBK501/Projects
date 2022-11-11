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


//1. �����찡 ������ ��
BOOL FindingForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	//1.1 ö�� ������ư�� �����Ѵ�.
	SendMessage(GetDlgItem(hWnd, IDC_RADIO_SPELLING), BM_SETCHECK,
		(WPARAM)BST_CHECKED, (LPARAM)0);

	return TRUE;
}

BOOL FindingForm_OnSpellingRadioButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	//2. ö�� ������ư�� Ŭ������ ��
	if (HIWORD(wParam) == BN_CLICKED) {

		//2.1 �ǹ� ������ư�� ���������Ѵ�.
		SendMessage(GetDlgItem(hWnd, IDC_RADIO_MEANING), BM_SETCHECK,
			(WPARAM)BST_UNCHECKED, (LPARAM)0);

		//2.2 �ǹ̸� ���ش�.
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_MEANING), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
	}
	return TRUE;
}

BOOL FindingForm_OnMeaningRadioButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	//3. �ǹ� ������ư�� Ŭ������ ��
	if (HIWORD(wParam) == BN_CLICKED) {

		//3.1 ö�� ������ư�� ���������Ѵ�.
		SendMessage(GetDlgItem(hWnd, IDC_RADIO_SPELLING), BM_SETCHECK,
			(WPARAM)BST_UNCHECKED, (LPARAM)0);

		//3.2 ö�ڸ� ���ش�.
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

	
	//4. ã�� ��ư�� Ŭ������ ��
	if (HIWORD(wParam) == BN_CLICKED) {

		//4.1 ö�� ������ư, ö��, �ǹ� ������ư, �ǹ̸� �д´�.
		spellingRadioButton = SendMessage(GetDlgItem(hWnd, IDC_RADIO_SPELLING),
			BM_GETSTATE, (WPARAM)0, (LPARAM)0);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_SPELLING), WM_GETTEXT,
			(WPARAM)32, (LPARAM)spelling);
		meaningRadioButton = SendMessage(GetDlgItem(hWnd, IDC_RADIO_MEANING),
			BM_GETSTATE, (WPARAM)0, (LPARAM)0);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_MEANING), WM_GETTEXT,
			(WPARAM)32, (LPARAM)meaning);

		//4.2 �ܾ�ī����δ� �����츦 ã�´�.
		hWordCardBinder = FindWindow("#32770", "�ܾ�ī����δ�");
		
		wordCardBinder = (WordCardBinder*)GetWindowLongPtr(hWordCardBinder, GWLP_USERDATA);

		//������ ã�� ���� ����
		indexes = (WordCard*(*))GetWindowLongPtr(hWnd, GWLP_USERDATA);
		if (indexes != NULL) {
			free(indexes);
		}

		//4.3 ö�� ������ư�� ���õ��� ��
		if (spellingRadioButton == BST_CHECKED) {
			
			//4.3.1 �ܾ�ī����δ����� ö�ڷ� ã�´�.
			FindBySpelling(wordCardBinder, spelling, &indexes, &count);
		}
		//4.4 �ǹ� ������ư�� ���õ��� ��
		if (meaningRadioButton == BST_CHECKED) {

			//4.4.1 �ܾ�ī����δ����� �ǹ̷� ã�´�.
			FindByMeaning(wordCardBinder, meaning, &indexes, &count);
		}
		SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG)indexes);
		SetProp(hWnd, "PROP_CURRENT", (HANDLE)current);
		SetProp(hWnd, "PROP_COUNT", (HANDLE)count);

		//4.5 ã������
		if (count > 0) {
			
			//4.5.1 ù ��° ��ġ�� �̵��Ѵ�.
			current = 0;
			SetProp(hWnd, "PROP_CURRENT", (HANDLE)current);

			//4.5.2 ���� ī�带 ����Ѵ�.
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

			//�� ã������ ��ĭ���
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

	//5. ó����ư�� Ŭ������ ��
	if (HIWORD(wParam) == BN_CLICKED) {

		//5.1 ù ��° ��ġ�� �̵��Ѵ�.
		indexes = (WordCard*(*))GetWindowLongPtr(hWnd, GWLP_USERDATA);
		current = (Long)GetProp(hWnd, "PROP_CURRENT");

		current = 0;
		SetProp(hWnd, "PROP_CURRENT", (HANDLE)current);

		//5.2 ���� ī�带 ����Ѵ�.
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

	//6. ������ư�� Ŭ������ ��
	if (HIWORD(wParam) == BN_CLICKED) {

		//6.1 ���� ��ġ�� �̵��Ѵ�.
		indexes = (WordCard*(*))GetWindowLongPtr(hWnd, GWLP_USERDATA);
		current = (Long)GetProp(hWnd, "PROP_CURRENT");

		current--;
		if (current < 0) {
			current = 0;
		}
		SetProp(hWnd, "PROP_CURRENT", (HANDLE)current);

		//6.2 ���� ī�带 ����Ѵ�.
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

	//7. ������ư�� Ŭ������ ��
	if (HIWORD(wParam) == BN_CLICKED) {

		//7.1 ���� ��ġ�� �̵��Ѵ�.
		indexes = (WordCard*(*))GetWindowLongPtr(hWnd, GWLP_USERDATA);
		current = (Long)GetProp(hWnd, "PROP_CURRENT");
		count = (Long)GetProp(hWnd, "PROP_COUNT");

		current++;
		if (current>=count) {
			current = count-1;
		}
		SetProp(hWnd, "PROP_CURRENT", (HANDLE)current);

		//7.2 ���� ī�带 ����Ѵ�.
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

	//8. ����ư�� Ŭ������ ��
	if (HIWORD(wParam) == BN_CLICKED) {

		//8.1 ������ ��ġ�� �̵��Ѵ�.
		indexes = (WordCard*(*))GetWindowLongPtr(hWnd, GWLP_USERDATA);
		count = (Long)GetProp(hWnd, "PROP_COUNT");
		
		current = count - 1;
		SetProp(hWnd, "PROP_CURRENT", (HANDLE)current);

		//8.2 ���� ī�带 ����Ѵ�.
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

	//9. ���ù�ư�� Ŭ������ ��
	if (HIWORD(wParam) == BN_CLICKED) {

		//9.1 �ܾ�ī����δ� �����츦 ã�´�.
		hWordCardBinder = FindWindow("#32770", "�ܾ�ī����δ�");
		
		wordCardBinder = (WordCardBinder*)GetWindowLongPtr(hWordCardBinder, GWLP_USERDATA);

		//9.2 �ܾ�ī����δ� �������� �ܾ�ī����δ����� �̵��Ѵ�.
		indexes = (WordCard*(*))GetWindowLongPtr(hWnd, GWLP_USERDATA);
		current = (Long)GetProp(hWnd, "PROP_CURRENT");

		WordCardBinder_Move(wordCardBinder, indexes[current]);

		//9.3 �ܾ�ī����δ� �����쿡 ã��ī�带 ����Ѵ�.

		//9.3.1 ã�� ī�带 �д´�
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITSPELLING), WM_GETTEXT,
			(WPARAM)32, (LPARAM)wordCard.word.spelling);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITWORDCLASS), WM_GETTEXT,
			(WPARAM)16, (LPARAM)wordCard.word.wordClass);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITMEANING), WM_GETTEXT,
			(WPARAM)128, (LPARAM)wordCard.word.meaning);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITEXAMPLESENTENCE), WM_GETTEXT,
			(WPARAM)256, (LPARAM)wordCard.word.exampleSentence);

		//9.3.2 ���� ī�带 ����Ѵ�
		SendMessage(GetDlgItem(hWordCardBinder, IDC_STATIC_EDITSPELLING), WM_SETTEXT,
			(WPARAM)0, (LPARAM)wordCard.word.spelling);
		SendMessage(GetDlgItem(hWordCardBinder, IDC_STATIC_EDITWORDCLASS), WM_SETTEXT,
			(WPARAM)0, (LPARAM)wordCard.word.wordClass);
		SendMessage(GetDlgItem(hWordCardBinder, IDC_STATIC_EDITMEANING), WM_SETTEXT,
			(WPARAM)0, (LPARAM)wordCard.word.meaning);
		SendMessage(GetDlgItem(hWordCardBinder, IDC_STATIC_EDITEXAMPLESENTENCE), WM_SETTEXT,
			(WPARAM)0, (LPARAM)wordCard.word.exampleSentence);


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


		//9.4 ã�� �����츦 ���ش�.
		if (indexes != NULL) {
			free(indexes);
		}
		RemoveProp(hWnd, "PROP_CURRENT");
		RemoveProp(hWnd, "PROP_COUNT");

		EndDialog(hWnd, 0);
	}
	return TRUE;
}


//10. �ݱ���Ʈ���� Ŭ������ ��
BOOL FindingForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	WordCard*(*indexes);
	
	//10.1 ã�������츦 ���ش�.
	indexes = (WordCard*(*))GetWindowLongPtr(hWnd, GWLP_USERDATA);
	if (indexes != NULL) {
		free(indexes);
	}
	RemoveProp(hWnd, "PROP_CURRENT");
	RemoveProp(hWnd, "PROP_COUNT");

	EndDialog(hWnd, 0);

	return 0;
}



