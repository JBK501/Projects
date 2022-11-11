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



BOOL TestForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam) {	//윈도우가 생성될 때

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
	
	
	//단어카드바인더 윈도우를 찾는다.
	hWordCardBinder = FindWindow("#32770", "단어카드바인더");

	//단어카드바인더 윈도우의 트리뷰에서 루트항목을 찾는다.
	hRoot = (HTREEITEM)SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_GETNEXTITEM,
		(WPARAM)TVGN_ROOT, (LPARAM)0);

	//단어카드바인더 윈도우의 트리뷰를 접는다.
	SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), TVM_EXPAND, 
		(WPARAM)TVE_COLLAPSE, (LPARAM)hRoot);

	//단어카드바인더 윈도우의 트리뷰를 비활성화 한다.
	SendMessage(GetDlgItem(hWordCardBinder,IDC_TREE_WORDS), WM_ENABLE, (WPARAM)FALSE, (LPARAM)0);
	
	//단어카드바인더 윈도우의 단어를 지운다.
	SendMessage(GetDlgItem(hWordCardBinder, IDC_STATIC_EDITSPELLING), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
	SendMessage(GetDlgItem(hWordCardBinder, IDC_STATIC_EDITMEANING), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
	SendMessage(GetDlgItem(hWordCardBinder, IDC_STATIC_EDITWORDCLASS), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
	SendMessage(GetDlgItem(hWordCardBinder, IDC_STATIC_EDITEXAMPLESENTENCE), WM_SETTEXT, (WPARAM)0, (LPARAM)"");

	//단어카드바인더 윈도우의 단어카드바인더에서 첫번째 카드로 이동한다.
	wordCardBinder = (WordCardBinder*)GetWindowLongPtr(hWordCardBinder, GWLP_USERDATA);

	current = WordCardBinder_First(wordCardBinder);

	//단어카드의 시도횟수를 늘린다.
	current->tryCount++;

#if 0
	//다음 시험결과만 저장할 때(이전 시험결과는 삭제됨)
	//단어카드 배열과 외운개수를 초기화 한다.
	wordCards = (WordCard(*))GetProp(hWordCardBinder, "PROP_WORDCARDS");

	if (wordCards != NULL) {
		free(wordCards);
	}
	wordCards = (WordCard(*))calloc(wordCardBinder->length, sizeof(WordCard));

	SetProp(hWordCardBinder, "PROP_WORDCARDS", (HANDLE)wordCards);
	SetProp(hWordCardBinder, "PROP_LEARNCOUNT", (HANDLE)learnCount);
#endif

	//시험보기 윈도우에 해당카드의 철자를 출력한다..
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITSPELLING2), WM_SETTEXT, (WPARAM)0, (LPARAM)current->word.spelling);

	//시험보기 윈도우에 문제 번호를 출력한다.
	sprintf(pQuestionNumber, "%d\0", questionNumber);

	SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITQUESTIONNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)pQuestionNumber);

	//시험보기 윈도우에 문제 개수를 출력한다.
	sprintf(pQuestionCount, "%d\0", wordCardBinder->length);

	SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITQUESTIONCOUNT), WM_SETTEXT, (WPARAM)0, (LPARAM)pQuestionCount);

	SetProp(hWnd, "PROP_QUESTIONCOUNT", (HANDLE)wordCardBinder->length);

	//시험보기 윈도우에 정답 개수를 출력한다.
	sprintf(pCorrectCount, "%d\0", correctCount);

	SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITCORRECTCOUNT), WM_SETTEXT, (WPARAM)0, (LPARAM)pCorrectCount);

	//시험보기 윈도우의 의미를 비활성화 한다.
	SendMessage(GetDlgItem(hWnd, IDC_EDIT_MEANING), WM_ENABLE, (WPARAM)FALSE, (LPARAM)0);

	//시험보기 윈도우의 예문을 비활성화 한다.
	SendMessage(GetDlgItem(hWnd, IDC_EDIT_EXAMPLESENTENCE), WM_ENABLE, (WPARAM)FALSE, (LPARAM)0);

	//시험보기 윈도우의 채점하기 버튼을 비활성화 한다.
	SendMessage(GetDlgItem(hWnd, IDC_EDIT_EXAMPLESENTENCE), WM_ENABLE, (WPARAM)FALSE, (LPARAM)0);

	//타이머를 설정한다.
	SetTimer(hWnd,             // handle to main window 
		IDT_TIMER,            // timer identifier 
		1000,                 // 10-second interval 
		(TIMERPROC)NULL);     // no timer callback 
	SendMessage(hWnd, WM_TIMER, 1, 0);

	currentTime = wordCardBinder->length * 20;	//문제당 20초
	SetProp(hWnd, "PROP_CURRENTTIME", (HANDLE)currentTime);

	currentMinutes = currentTime / 60;
	currentSeconds = currentTime % 60;
	sprintf(strCuttentTime, "%d분 %d초", currentMinutes,currentSeconds);

	SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITTIMER), WM_SETTEXT, (WPARAM)0, (LPARAM)strCuttentTime);

	return TRUE;
}

BOOL TestForm_OnWordClassEditKillFocused(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	HWND hWordCardBinder;
	WordCardBinder *wordCardBinder;
	TCHAR wordClass[16];

	if (HIWORD(wParam) == EN_KILLFOCUS) {

		//시험보기 윈도우의 품사를 읽는다.
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_WORDCLASS), WM_GETTEXT, (WPARAM)16, (LPARAM)wordClass);

		//단어카드바인더 윈도우를 찾는다.
		hWordCardBinder = FindWindow("#32770", "단어카드바인더");

		//품사를 비교한다.
		wordCardBinder = (WordCardBinder*)GetWindowLongPtr(hWordCardBinder, GWLP_USERDATA);

		if (strcmp(wordCardBinder->current->word.wordClass, wordClass) == 0) {	//같으면

			//시험보기 윈도우의 의미를 활성화한다.
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

		//시험보기 윈도우의 의미를 읽는다.
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_MEANING), WM_GETTEXT, (WPARAM)128, (LPARAM)meaning);

		//단어카드바인더 윈도우를 찾는다.
		hWordCardBinder = FindWindow("#32770", "단어카드바인더");

		//의미를 비교한다.
		wordCardBinder = (WordCardBinder*)GetWindowLongPtr(hWordCardBinder, GWLP_USERDATA);

		if (strcmp(wordCardBinder->current->word.meaning, meaning) == 0) {	//같으면

			//시험보기 윈도우의 예문을 활성화한다.
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

		//시험보기 윈도우의 예문을 읽는다.
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_EXAMPLESENTENCE), WM_GETTEXT, (WPARAM)256, (LPARAM)exampleSentence);

		//단어카드바인더 윈도우를 찾는다.
		hWordCardBinder = FindWindow("#32770", "단어카드바인더");

		wordCardBinder = (WordCardBinder*)GetWindowLongPtr(hWordCardBinder, GWLP_USERDATA);

		//예문을 비교한다.
		if (strcmp(wordCardBinder->current->word.exampleSentence, exampleSentence) == 0) {

			//같으면
			//단어카드의 성공횟수를 늘린다.
			wordCardBinder->current->successfulCount++;

			//시험보기 윈도우에 정답 개수를 늘린다..
			correctCount = (Long)GetProp(hWnd, "PROP_CORRECTCOUNT");
			correctCount++;
			SetProp(hWnd, "PROP_CORRECTCOUNT", (HANDLE)correctCount);
			
			sprintf(pCorrectCount, "%d\0", correctCount);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITCORRECTCOUNT), WM_SETTEXT, (WPARAM)0, (LPARAM)pCorrectCount);

			//단어카드 바인더 윈도우에서 꺼낸다.

			//색인철에서 꺼내기위한 단어카드링크저장
			current = wordCardBinder->current;

			//단어카드바인더 윈도우의 단어카드바인더에서 꺼낸다.
			wordCard = TakeOut(wordCardBinder, wordCardBinder->current);

			//꺼낸 카드를 저장한다.
			wordCards = (WordCard(*))GetProp(hWordCardBinder, "PROP_WORDCARDS");

			learnCount = (Long)GetProp(hWordCardBinder, "PROP_LEARNCOUNT");

			wordCards[learnCount] = wordCard;

			//암기한 개수를 늘린다.
			learnCount++;
			SetProp(hWordCardBinder, "PROP_LEARNCOUNT", (HANDLE)learnCount);

			//색인철에서 꺼낸다.
			indexCardBinder = (IndexCardBinder*)GetProp(hWordCardBinder, "PROP_INDEXCARDBINDER");

			indexCardIndex = IndexCardBinder_TakeOut(indexCardBinder, current, wordCard.word.spelling[0]);

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
#if 0
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
			else {

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
#endif

			questionCount = (Long)GetProp(hWnd, "PROP_QUESTIONCOUNT");
			//문제 번호가 전체 문제 개수 보다 작을 때
			questionNumber = (Long)GetProp(hWnd, "PROP_QUESTIONNUMBER");
			if (questionNumber < questionCount) {

				//단어카드바인더에서 다음카드로 이동한다.
				//current = WordCardBinder_Next(wordCardBinder);
				current = wordCardBinder->current;

				//단어카드의 시도횟수를 늘린다.
				current->tryCount++;

				//시험보기 윈도우에 해당카드의 철자를 출력한다..
				SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITSPELLING2), WM_SETTEXT,
					(WPARAM)0, (LPARAM)current->word.spelling);

				//시험보기 윈도우에 문제 번호를 출력한다.
				questionNumber++;
				SetProp(hWnd, "PROP_QUESTIONNUMBER", (HANDLE)questionNumber);

				sprintf(pQuestionNumber, "%d\0", questionNumber);
				SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITQUESTIONNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)pQuestionNumber);

				//시험보기 윈도우의 품사를 지운다.
				SendMessage(GetDlgItem(hWnd, IDC_EDIT_WORDCLASS), WM_SETTEXT, (WPARAM)0, (LPARAM)"");

				//시험보기 윈도우의 의미를 비활성화 한다.
				SendMessage(GetDlgItem(hWnd, IDC_EDIT_MEANING), WM_ENABLE, (WPARAM)FALSE, (LPARAM)0);
				SendMessage(GetDlgItem(hWnd, IDC_EDIT_MEANING), WM_SETTEXT, (WPARAM)0, (LPARAM)"");

				//시험보기 윈도우의 예문을 비활성화 한다.
				SendMessage(GetDlgItem(hWnd, IDC_EDIT_EXAMPLESENTENCE), WM_ENABLE, (WPARAM)FALSE, (LPARAM)0);
				SendMessage(GetDlgItem(hWnd, IDC_EDIT_EXAMPLESENTENCE), WM_SETTEXT, (WPARAM)0, (LPARAM)"");


				//시험보기 윈도우의 채점하기 버튼을 비활성화 한다.
				SendMessage(GetDlgItem(hWnd, IDC_EDIT_EXAMPLESENTENCE), WM_ENABLE, (WPARAM)FALSE, (LPARAM)0);
			}
			else {
				//문제 번호와 전체 문제 개수가 같을 때
				TestForm_OnClose(hWnd, wParam, lParam);
			}
		}
		else {
			//다르면
			//예문을 지운다.
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

	sprintf(strCurrentTime, "%d분 %d초", currentMinutes, currentSeconds);

	//sprintf(strCurrentTime, "%d초", currentTime);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDITTIMER), WM_SETTEXT, (WPARAM)0, (LPARAM)strCurrentTime);
	if (currentTime == 0) {
		TestForm_OnClose(hWnd, wParam, lParam);
	}

	return TRUE;
}


BOOL TestForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam) {	//닫기 컨트롤을 클릭했을 때

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


	//단어카드바인더 윈도우를 찾는다.
	hWordCardBinder = FindWindow("#32770", "단어카드바인더");

	//단어카드바인더 윈도우의 트리뷰를 활성화 한다.
	SendMessage(GetDlgItem(hWordCardBinder, IDC_TREE_WORDS), WM_ENABLE, (WPARAM)TRUE, (LPARAM)0);

	wordCardBinder = (WordCardBinder*)GetWindowLongPtr(hWordCardBinder, GWLP_USERDATA);

	//메시지 박스를 출력한다.
	correctCount = (Long)GetProp(hWnd,"PROP_CORRECTCOUNT");

	score = correctCount / ((wordCardBinder->length + correctCount) * 1.0F) * 100;
	sprintf(pScore, "%.0f점", score);

	message = MessageBox(hWnd, (LPCSTR)pScore, (LPCSTR)"시험결과",MB_OK);

	if (message = IDOK) {

		
		if (wordCardBinder->length > 0) {

			//단어카드바인더 윈도우의 단어카드바인더에서 첫번째 카드로 이동한다.
			current = WordCardBinder_First(wordCardBinder);

			//해당카드를 출력한다.
			SendMessage(GetDlgItem(hWordCardBinder, IDC_STATIC_EDITSPELLING), WM_SETTEXT,
				(WPARAM)0, (LPARAM)current->word.spelling);
			SendMessage(GetDlgItem(hWordCardBinder, IDC_STATIC_EDITMEANING), WM_SETTEXT,
				(WPARAM)0, (LPARAM)current->word.meaning);
			SendMessage(GetDlgItem(hWordCardBinder, IDC_STATIC_EDITWORDCLASS), WM_SETTEXT,
				(WPARAM)0, (LPARAM)current->word.wordClass);
			SendMessage(GetDlgItem(hWordCardBinder, IDC_STATIC_EDITEXAMPLESENTENCE), WM_SETTEXT,
				(WPARAM)0, (LPARAM)current->word.exampleSentence);


			

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

			//단어카드바인더 윈도우의 트리뷰에서 품사 항목을 찾는다.
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
		else {
			
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
		
		RemoveProp(hWnd, "PROP_CORRECTCOUNT");
		RemoveProp(hWnd, "PROP_QUESTIONNUMBER");
		RemoveProp(hWnd, "PROP_QUESTIONCOUNT");
		RemoveProp(hWnd, "PROP_CURRENTTIME");

		KillTimer(hWnd, IDT_TIMER);

		EndDialog(hWnd, 0);
	}
	return TRUE;
}
