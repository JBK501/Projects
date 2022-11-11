#ifndef _WORDBOOKFORM_H
#define _WORDBOOKFORM_H

#include <afxwin.h>
#include "resource.h"

typedef signed long int Long;

class WordBook;
class WordBookForm : public CDialog {

public:
	enum {IDD = IDD_WORDBOOKFORM};
public:
	WordBook *wordBook;
public:
	WordBookForm(CWnd *parent = NULL);
	virtual BOOL OnInitDialog();
	void Load();
	CString GetGode();
	void Insert(Long index);
	void Modify(Long index);
	void Delete(Long index);
	void Save();

protected:
	afx_msg void OnRecordButtonClicked();
	afx_msg void OnFindButtonClicked();
	afx_msg void OnCorrectButtonClicked();
	afx_msg void OnEraseButtonClicked();
	afx_msg void OnArrangeButtonClicked();
	afx_msg void OnListViewItemDoubleClicked(NMHDR *pNotifyStruct, LRESULT *result);
	afx_msg void OnClose();
	DECLARE_MESSAGE_MAP();
};

#endif // !_WORDBOOKFORM_H
