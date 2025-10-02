// dibview.h : interface of the CDibView class
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

class CDibView : public CScrollView
{
protected: // create from serialization only
	CDibView();
	DECLARE_DYNCREATE(CDibView)

// Attributes
public:
	CDibDoc* GetDocument()
		{
			ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDibDoc)));
			return (CDibDoc*) m_pDocument;
		}
	CSize m_zoomedsize;
	int m_left;
	int m_top;
	int m_right;
	int m_bottom;
	int m_left_zoomed;
	int m_top_zoomed;
	int m_right_zoomed;
	int m_bottom_zoomed;

/* Summary from Copilot:

m_flag is an internal state variable used to track the current mouse interaction mode in the view,
especially for cropping, resizing, and moving operations.

Values and Their Meanings
| Value   | Meaning / Mode                                                                        | Where Set / Used                |
|---------|---------------------------------------------------------------------------------------|---------------------------------|
| 0       | Idle/None – No special mouse operation is active.                                     | On construction, after mouse
																									up,	or when resetting state.  |
| 1       | Crop/Selection Start – User has pressed the mouse button to start a crop/selection.   | OnLButtonDown, OnMouseMove    |
| 2       | Crop/Selection Drag – User is dragging to define the crop/selection rectangle.        | OnMouseMove                   |
| 4       | Left Edge Resize – User is resizing the left edge of the crop rectangle.              | OnMouseMove (edge detection)  |
| 5       | Top Edge Resize – User is resizing the top edge.                                      | OnMouseMove                   |
| 6       | Right Edge Resize – User is resizing the right edge.                                  | OnMouseMove                   |
| 7       | Bottom Edge Resize – User is resizing the bottom edge.                                | OnMouseMove                   |
| 8       | Top-Left Corner Resize – User is resizing the top-left corner (NWSE cursor).          | OnMouseMove                   |
| 9       | Top-Right Corner Resize – User is resizing the top-right corner (NESW cursor).        | OnMouseMove                   |
| 10      | Bottom-Right Corner Resize – User is resizing the bottom-right corner (NWSE cursor).  | OnMouseMove                   |
| 11      | Bottom-Left Corner Resize – User is resizing the bottom-left corner (NESW cursor).    | OnMouseMove                   |
| 100     | Move Crop/Frame Start – User has started moving the crop/frame (move cursor).         | OnPopup1MoveFrame, OnMouseMove|
| 101     | Move Crop/Frame Drag – User is dragging the crop/frame.                               | OnMouseMove                   |
---
How It Works in Practice
•	Mouse Down (OnLButtonDown):
•	If m_flag == 0, set to 1 (start crop/selection).
•	Mouse Move (OnMouseMove):
•	If m_flag == 1 and mouse moves, transition to 2 (dragging selection).
•	If m_flag == 2, update the selection rectangle as the mouse moves.
•	If m_flag == 100, start moving the crop/frame; transition to 101 as the mouse moves.
•	If m_flag == 101, update the crop/frame position as the mouse moves.
•	If not dragging, checks mouse position relative to crop rectangle edges/corners and sets m_flag to 4–11 for resizing,
	or 8–11 for corner resizing, updating the cursor accordingly.
•	Mouse Up (OnLButtonUp):
•	Resets m_flag to 0 (idle) and restores the cursor.
•	Move Frame Command (OnPopup1MoveFrame):
•	Sets m_flag to 100 to initiate move mode.


| m_flag Value | User Action / State                | Cursor
|--------------|------------------------------------|---------------
| 0            | Idle                               | Arrow
| 1            | Crop/selection started             | Arrow
| 2            | Crop/selection dragging            | Arrow
| 4, 6         | Left/Right edge resize             | Size WE
| 5, 7         | Top/Bottom edge resize             | Size NS
| 8, 10        | Top-left/Bottom-right corner resize| Size NWSE
| 9, 11        | Top-right/Bottom-left corner resize| Size NESW
| 100          | Move crop/frame started            | Size All
| 101          | Move crop/frame dragging           | Size All      |
*/
	int m_flag;

	int m_x;
	int m_y;
	int m_zoomval;
	int m_setcursor;
	int m_save_zoom;
	const TCHAR *m_format;

// Operations
public:

// Implementation
public:
	virtual ~CDibView();
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view

	virtual void OnInitialUpdate();
	virtual void OnUpdate(CView* pSender,
						  LPARAM lHint = 0L,
						  CObject* pHint = NULL);
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView,
					CView* pDeactiveView);

	// Printing support
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	void UpdateViewZoom_helper(CCmdUI* pCmdUI, int selectedLevel);
	void OnViewZoom_helper(int selectedLevel);
// Generated message map functions
// protected:
public:
	//{{AFX_MSG(CDibView)
	afx_msg void OnEditCopy();
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnEditPaste();
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	afx_msg void OnEditSelectAll();
	afx_msg void OnIndicatorPos();
	afx_msg void OnUpdateIndicatorPos(CCmdUI* pCmdUI);
	afx_msg LRESULT OnDoRealize(WPARAM wParam, LPARAM lParam);  // user message
	afx_msg void OnPopup1MoveFrame();
	afx_msg void OnPopup1DefineFrame();
	afx_msg void OnPopup1SaveFrameAs();
	afx_msg void OnViewZoom1();
	afx_msg void OnUpdateViewZoom1(CCmdUI* pCmdUI);
	afx_msg void OnViewZoom2();
	afx_msg void OnUpdateViewZoom2(CCmdUI* pCmdUI);
	afx_msg void OnViewZoom3();
	afx_msg void OnUpdateViewZoom3(CCmdUI* pCmdUI);
	afx_msg void OnViewZoom4();
	afx_msg void OnUpdateViewZoom4(CCmdUI* pCmdUI);
	afx_msg void OnViewZoom5();
	afx_msg void OnUpdateViewZoom5(CCmdUI* pCmdUI);
	afx_msg void OnViewZoom6();
	afx_msg void OnUpdateViewZoom6(CCmdUI* pCmdUI);
	afx_msg void OnViewZoom7();
	afx_msg void OnUpdateViewZoom7(CCmdUI* pCmdUI);
	afx_msg void OnViewZoom8();
	afx_msg void OnUpdateViewZoom8(CCmdUI* pCmdUI);
	afx_msg void OnViewZoom9();
	afx_msg void OnUpdateViewZoom9(CCmdUI* pCmdUI);
	afx_msg void OnViewZoom10();
	afx_msg void OnUpdateViewZoom10(CCmdUI* pCmdUI);
	afx_msg void OnViewZoom11();
	afx_msg void OnUpdateViewZoom11(CCmdUI* pCmdUI);
	afx_msg void OnViewZoom12();
	afx_msg void OnUpdateViewZoom12(CCmdUI* pCmdUI);
	afx_msg void OnViewZoom13();
	afx_msg void OnUpdateViewZoom13(CCmdUI* pCmdUI);
	afx_msg void OnViewZoom14();
	afx_msg void OnUpdateViewZoom14(CCmdUI* pCmdUI);
	afx_msg void OnViewZoom15();
	afx_msg void OnUpdateViewZoom15(CCmdUI* pCmdUI);
	afx_msg void OnViewZoom16();
	afx_msg void OnUpdateViewZoom16(CCmdUI* pCmdUI);
	afx_msg void OnUpdateToolbarScale(CCmdUI* pCmdUI);
	afx_msg void OnUpdateToolbarZoom(CCmdUI* pCmdUI);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnOptionsSaveZoom();
	afx_msg void OnUpdateOptionsSaveZoom(CCmdUI *pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
