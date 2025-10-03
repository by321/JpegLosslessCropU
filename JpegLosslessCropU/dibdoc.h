// dibdoc.h : interface of the CDibDoc class
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-1998 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#include "dibapi.h"

class CDibDoc : public CDocument
{
protected: // create from serialization only
	CDibDoc();
	DECLARE_DYNCREATE(CDibDoc)

// Attributes
public:
	HDIB GetHDIB() const
		{ return m_hDIB; }
	CPalette* GetDocPalette() const
		{ return m_palDIB; }
	CSize GetDocSize() const
		{ return m_sizeDoc; }

// Operations
public:
	void ReplaceHDIB(HDIB hDIB);
	void InitDIBData();
	void DoTransform();
	int m_image_width;
	int m_image_height;
	int m_MCUwidth;
	int m_MCUheight;
	int m_crop_xoffset;
	int m_crop_yoffset;
	int m_crop_width;
	int m_crop_height;
	int m_crop_width_set;
	
/*According to Copilot:

CDibDoc::m_transform is an integer that represents the current image transformation applied to the document. 
Its value determines which geometric operation (like rotation or flip) is active. The value is set by user 
actions (menu commands) and is used to control how the image is displayed and processed.

Values and Their Meanings
•	0: Original (no transformation)
•	1: Horizontal flip
•	2: Vertical flip
•	3: Transpose (swap X and Y axes)
•	4: Transverse (swap X and Y axes, then flip both)
•	5: Rotate 90 degrees
•	6: Rotate 180 degrees
•	7: Rotate 270 degrees
•	8: Wipe (special mode, often disables crop mask)

When and How It's Set
•	m_transform is set in response to user commands, such as menu actions for rotate or flip. For example:
•	OnTransformFlipH() sets m_transform = 1
•	OnTransformRot90() sets m_transform = 5
•	OnTransformOriginal() sets m_transform = 0
•	OnTransformWipe() sets m_transform = 8
•	After setting, the code may call a helper function to perform the actual transformation or update the view.

How It's Used
•	The value of m_transform is checked in drawing and cropping logic (e.g., in CDibView) 
	to determine how to interpret or display the image.
•	The DoTransform() method uses m_transform to dispatch the correct transformation function.

Summary Table:
| Value | Meaning                | Set By Function              | 
|-------|------------------------|------------------------------| 
| 0     | Original               | OnTransformOriginal          | 
| 1     | Flip Horizontal        | OnTransformFlipH             | 
| 2     | Flip Vertical          | OnTransformFlipV             | 
| 3     | Transpose              | OnTransformTranspose         | 
| 4     | Transverse             | OnTransformTransverse        | 
| 5     | Rotate 90°             | OnTransformRot90             | 
| 6     | Rotate 180°            | OnTransformRot180            | 
| 7     | Rotate 270°            | OnTransformRot270            | 
| 8     | Wipe                   | OnTransformWipe              |

Gotcha:
Changing m_transform does not always immediately apply the transformation;
it may just update the state, and the actual image data is transformed when needed.
*/
	int m_transform;

/*	From Copilot:
Indicates whether the current image data has already been dithered.
  0: Not dithered yet.
  1: Dithered.

Set to 0 when a new image is loaded, or when the image is reloaded or transformed.
Set to 1 after dithering is performed in CDibView::OnDraw, or dithering is not needed.
*/
	int m_dithered;
	
	// m_scale and m_scale_denom are set when a new image is loaded or when grayscale mode is toggled, 
	// and together they represent the scaling factor as a fraction(m_scale / m_scale_denom).
	int m_scale, m_scale_denom;
	
	int m_force_grayscale;
	int m_save_scale;

// Implementation
protected:
	virtual ~CDibDoc();

	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);

protected:
	HDIB m_hDIB;
	CPalette* m_palDIB;
	CSize m_sizeDoc;

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
protected:
	virtual BOOL    OnNewDocument();

// Generated message map functions
protected:
	//{{AFX_MSG(CDibDoc)
	afx_msg void OnFileSaveCopyAs();
	afx_msg void OnTransformRot90();
	afx_msg void OnUpdateTransformRot90(CCmdUI *pCmdUI);
	afx_msg void OnTransformRot270();
	afx_msg void OnUpdateTransformRot270(CCmdUI *pCmdUI);
	afx_msg void OnTransformFlipH();
	afx_msg void OnUpdateTransformFlipH(CCmdUI *pCmdUI);
	afx_msg void OnTransformFlipV();
	afx_msg void OnUpdateTransformFlipV(CCmdUI *pCmdUI);
	afx_msg void OnTransformRot180();
	afx_msg void OnUpdateTransformRot180(CCmdUI *pCmdUI);
	afx_msg void OnTransformTranspose();
	afx_msg void OnUpdateTransformTranspose(CCmdUI *pCmdUI);
	afx_msg void OnTransformTransverse();
	afx_msg void OnUpdateTransformTransverse(CCmdUI *pCmdUI);
	afx_msg void OnTransformOriginal();
	afx_msg void OnUpdateTransformOriginal(CCmdUI *pCmdUI);
	afx_msg void OnTransformWipe();
	afx_msg void OnUpdateTransformWipe(CCmdUI *pCmdUI);
	afx_msg void OnOptionsGrayscale();
	afx_msg void OnUpdateOptionsGrayscale(CCmdUI *pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
