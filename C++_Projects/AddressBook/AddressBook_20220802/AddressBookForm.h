#ifndef _ADDRESSBOOKFORM_H
#define _ADDRESSBOOKFORM_H

#include <afxwin.h>
#include "resource.h"

class AddressBook;

typedef signed long int Long;

class AddressBookForm : public CDialog {

public:
	enum {IDD = IDD_ADDRESSBOOKFORM};
public:
	AddressBook *addressBook;
public:
	AddressBookForm(CWnd *parent = NULL);
	virtual BOOL OnInitDialog();
	
	CString GetCode();
	void Load();
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

	DECLARE_MESSAGE_MAP()

};
#endif // !_ADDRESSBOOKFORM_H
