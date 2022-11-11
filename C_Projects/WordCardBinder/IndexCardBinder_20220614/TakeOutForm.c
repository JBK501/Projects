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

//1. �����찡 ������ ��
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

	//�ܾ�ī����δ� �����츦 ã�´�.
	hWordCardBinder = FindWindow("#32770", "�ܾ�ī����δ�");

	wordCardBinder = (WordCardBinder*)GetWindowLongPtr(hWordCardBinder, GWLP_USERDATA);

	//����ö���� ���������� �ܾ�ī�帵ũ����
	current = wordCardBinder->current;

	//�ܾ�ī����δ� �������� �ܾ�ī����δ����� ������.
	wordCard = TakeOut(wordCardBinder, wordCardBinder->current);

	//�ܾ�ī���� �õ�Ƚ��, ����Ƚ���� �����Ѵ�.
	SetProp(hWnd, "PROP_TRYCOUNT", (HANDLE)wordCard.tryCount);
	SetProp(hWnd, "PROP_SUCCESSFUL", (HANDLE)wordCard.successfulCount);

	//����ö���� ������.
	indexCardBinder = (IndexCardBinder*)GetProp(hWordCardBinder, "PROP_INDEXCARDBINDER");
	
	indexCardIndex = IndexCardBinder_TakeOut(indexCardBinder, current,wordCard.word.spelling[0]);

	//���� ī�带 ����Ѵ�.
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITSPELLING), WM_SETTEXT,
		(WPARAM)0, (LPARAM)wordCard.word.spelling);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITMEANING), WM_SETTEXT,
		(WPARAM)0, (LPARAM)wordCard.word.meaning);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITWORDCLASS), WM_SETTEXT,
		(WPARAM)0, (LPARAM)wordCard.word.wordClass);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITEXAMPLESENTENCE), WM_SETTEXT,
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
	else{

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
	return TRUE;
}

//2. ��Ű ��Ʈ���� Ŭ������ ��
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


	//2.1 �޽��� �ڽ��� ����Ѵ�.
	message = MessageBox(hWnd, "����ðڽ��ϱ�?", "�˸�", MB_YESNOCANCEL);

	//2.2 �� ��ư�� Ŭ������ ��
	if (message == IDYES) {

		//���� ī�带 �д´�.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITSPELLING), WM_GETTEXT,
			(WPARAM)32, (LPARAM)wordCard.word.spelling);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITWORDCLASS), WM_GETTEXT,
			(WPARAM)16, (LPARAM)wordCard.word.wordClass);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITMEANING), WM_GETTEXT,
			(WPARAM)128, (LPARAM)wordCard.word.meaning);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITEXAMPLESENTENCE), WM_GETTEXT,
			(WPARAM)256, (LPARAM)wordCard.word.exampleSentence);

		//������ ����Ƚ��, ����Ƚ���� �����´�.
		wordCard.tryCount = (Long)GetProp(hWnd, "PROP_TRYCOUNT");
		wordCard.successfulCount = (Long)GetProp(hWnd, "PROP_SUCCESSFUL");
	

		//�ܾ�ī����δ� �����츦 ã�´�.
		hWordCardBinder = FindWindow("#32770", "�ܾ�ī����δ�");

		wordCardBinder = (WordCardBinder*)GetWindowLongPtr(hWordCardBinder, GWLP_USERDATA);

		//�ܾ�ī����δ� �������� �ܾ�ī����δ����� �����.
		current = TakeIn(wordCardBinder, wordCard);

		//�ܾ�ī����δ� �������� ����ö���� �����.
		indexCardBinder = (IndexCardBinder*)GetProp(hWordCardBinder, "PROP_INDEXCARDBINDER");

		indexCardIndex = IndexCardBinder_TakeIn(indexCardBinder, current);

#if 0
		//�ܾ�ī����δ� �����쿡 ���� ī�带 ����Ѵ�.
		SendMessage(GetDlgItem(hWordCardBinder, IDC_STATIC_EDITSPELLING), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->word.spelling);
		SendMessage(GetDlgItem(hWordCardBinder, IDC_STATIC_EDITMEANING), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->word.meaning);
		SendMessage(GetDlgItem(hWordCardBinder, IDC_STATIC_EDITWORDCLASS), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->word.wordClass);
		SendMessage(GetDlgItem(hWordCardBinder, IDC_STATIC_EDITEXAMPLESENTENCE), WM_SETTEXT,
			(WPARAM)0, (LPARAM)current->word.exampleSentence);
#endif
		//���� ī�带 ����Ѵ�
		SendMessage(GetDlgItem(hWordCardBinder, IDC_STATIC_EDITSPELLING), WM_SETTEXT,
			(WPARAM)0, (LPARAM)wordCard.word.spelling);
		SendMessage(GetDlgItem(hWordCardBinder, IDC_STATIC_EDITWORDCLASS), WM_SETTEXT,
			(WPARAM)0, (LPARAM)wordCard.word.wordClass);
		SendMessage(GetDlgItem(hWordCardBinder, IDC_STATIC_EDITMEANING), WM_SETTEXT,
			(WPARAM)0, (LPARAM)wordCard.word.meaning);
		SendMessage(GetDlgItem(hWordCardBinder, IDC_STATIC_EDITEXAMPLESENTENCE), WM_SETTEXT,
			(WPARAM)0, (LPARAM)wordCard.word.exampleSentence);

		


		//�ܾ�ī����δ� �������� ����ö���� �����Ѵ�.
		IndexCardBinder_Arrange(indexCardBinder);

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

		//��ã������
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

		//��ã������
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

		//�ܾ�ī������� �������� Ʈ���信�� ǰ���׸��� �߰��Ѵ�.

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

		//����� �����츦 ���ش�.
		EndDialog(hWnd, 0);
	}
	else if (message == IDNO) {
		EndDialog(hWnd, 0);
	}

	RemoveProp(hWnd, "PROP_TRYCOUNT");
	RemoveProp(hWnd, "PROP_SUCCESSFUL");

	return TRUE;
}

