// MultiDefExtFileDialog.cpp : implementation file
//

#include "pch.h"
#include "MultiExtFilterFileDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define WM_SETUP_FLAGS  WM_APP+0x500

/////////////////////////////////////////////////////////////////////////////
// CMultiExtFilterFileDialog

IMPLEMENT_DYNAMIC(CMultiExtFilterFileDialog, CFileDialog)

CMultiExtFilterFileDialog::CMultiExtFilterFileDialog(BOOL bOpenFileDialog, LPCTSTR lpszDefExt, LPCTSTR lpszFileName,
		DWORD dwFlags, LPCTSTR lpszFilter, CWnd* pParentWnd) :
		CFileDialog(bOpenFileDialog, lpszDefExt, lpszFileName, dwFlags, lpszFilter, pParentWnd)
{
}


INT_PTR CMultiExtFilterFileDialog::DoModal()
{
    // if opening a file, and multi select is enabled, and no default extension is specified
    if (m_bOpenFileDialog && !(m_ofn.Flags & OFN_ALLOWMULTISELECT) && !m_ofn.lpstrDefExt)
    {
        m_bFileMustExist = m_ofn.Flags & OFN_FILEMUSTEXIST;
        m_ofn.Flags &= ~OFN_FILEMUSTEXIST;
    }

    return CFileDialog::DoModal();
}

    BOOL CMultiExtFilterFileDialog::OnFileNameOK()
    {
        // if saving, or multi select enabled, preserve original functionality
        if (!m_bOpenFileDialog || 
            (m_ofn.Flags & OFN_ALLOWMULTISELECT) ||
            (m_ofn.lpstrDefExt))
            return CFileDialog::OnFileNameOK();

        CString strFName = GetPathName();
        WIN32_FIND_DATA fd;

        // if the file exists as specified in the filename edit box
        if (::FindFirstFile(strFName, &fd) != INVALID_HANDLE_VALUE)
        {
            // accept file name
            return 0;
        }
        // if a file extension was specified
        if (strFName.ReverseFind('.') > strFName.ReverseFind('\\'))
        {
            // reject file name
            return 1;
        }

        CString strMultiExt, strExt;

        // get current filter extensions
        AfxExtractSubString(strMultiExt, m_ofn.lpstrFilter, 2*m_ofn.nFilterIndex - 1, (TCHAR)'\0');

        // for every extension in the filter
        for (int i = 0; AfxExtractSubString(strExt, strMultiExt, i, (TCHAR)';'); i++)
        {
            // no '*' allowed in filter extensions
            if (_tcsrchr((LPCTSTR)strExt + 1, (TCHAR)'*'))
                continue;
            if (::FindFirstFile(strFName+((LPCTSTR)strExt+1), &fd) != INVALID_HANDLE_VALUE)
            {
                unsigned int flen = _tcslen(m_ofn.lpstrFile);
                // if the buffer is not big enough ignore this extension
                if (flen + strExt.GetLength() > m_ofn.nMaxFile)
                    continue;

                _tcscpy(m_ofn.lpstrFile + flen, (LPCTSTR)strExt+1);
                // accept file name
                return 0;
            }
        }

        // to get FileMustExist validation we reset the flag
        if (m_bFileMustExist)
        {
            // set the file exist check back to original
            m_ofn.Flags |= OFN_FILEMUSTEXIST;
            // get default processing (i.e. file must exist message box)
            PostMessage(WM_KEYDOWN, (WPARAM)(VK_RETURN), (LPARAM)(1));
            // reset the file exist check
            PostMessage(WM_SETUP_FLAGS);
            return 1;
        }
        else
            return 0;
    }


BEGIN_MESSAGE_MAP(CMultiExtFilterFileDialog, CFileDialog)
	//{{AFX_MSG_MAP(CMultiExtFilterFileDialog)
	//}}AFX_MSG_MAP
    ON_MESSAGE(WM_SETUP_FLAGS, OnSetupFlags)
END_MESSAGE_MAP()


LRESULT CMultiExtFilterFileDialog::OnSetupFlags(WPARAM, LPARAM)
{
    if (m_bFileMustExist)
        m_ofn.Flags &= ~OFN_FILEMUSTEXIST;
    return 0;
}

