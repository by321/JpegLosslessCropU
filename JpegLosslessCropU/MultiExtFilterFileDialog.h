#if !defined(AFX_MULTIDEFEXTFILEDIALOG_H__86B8D184_5DEE_11D2_985E_0060088F5D43__INCLUDED_)
#define AFX_MULTIDEFEXTFILEDIALOG_H__86B8D184_5DEE_11D2_985E_0060088F5D43__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MultiDefExtFileDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMultiExtFilterFileDialog dialog

class CMultiExtFilterFileDialog : public CFileDialog
{
	DECLARE_DYNAMIC(CMultiExtFilterFileDialog)

public:
	CMultiExtFilterFileDialog(BOOL bOpenFileDialog, // TRUE for FileOpen, FALSE for FileSaveAs
		LPCTSTR lpszDefExt = NULL,
		LPCTSTR lpszFileName = NULL,
		DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		LPCTSTR lpszFilter = NULL,
		CWnd* pParentWnd = NULL);

    // check file name
    virtual INT_PTR DoModal( );
	virtual BOOL OnFileNameOK();

protected:

    BOOL m_bFileMustExist;

	//{{AFX_MSG(CMultiExtFilterFileDialog)
	//}}AFX_MSG
    afx_msg LRESULT OnSetupFlags(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MULTIDEFEXTFILEDIALOG_H__86B8D184_5DEE_11D2_985E_0060088F5D43__INCLUDED_)
