#include "WordBookApp.h"
#include "WordBookForm.h"

BOOL WordBookApp::InitInstance() {

	WordBookForm wordBookForm;
	
	this->m_pMainWnd = &wordBookForm;
	wordBookForm.DoModal();

	return TRUE;
}
WordBookApp wordBookApp;