// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface
// (the "Fluent UI") and is provided only as referential material to supplement the
// Microsoft Foundation Classes Reference and related electronic documentation
// included with the MFC C++ library software.
// License terms to copy, use or distribute the Fluent UI are available separately.
// To learn more about our Fluent UI licensing program, please visit
// https://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// PatternGeneratorView.cpp : implementation of the CPatternGeneratorView class
//

#include "pch.h"

#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "PatternGenerator.h"
#endif
#include "PatternGeneratorDoc.h"
#include "PatternGeneratorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPatternGeneratorView

IMPLEMENT_DYNCREATE(CPatternGeneratorView, CView)

BEGIN_MESSAGE_MAP(CPatternGeneratorView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CPatternGeneratorView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_BUTTON_START, &CPatternGeneratorView::OnButtonStart)
	ON_COMMAND(ID_BUTTON_SUSPEND, &CPatternGeneratorView::OnButtonSuspend)
	ON_COMMAND(ID_BUTTON_RESUME, &CPatternGeneratorView::OnButtonResume)
END_MESSAGE_MAP()

// CPatternGeneratorView construction/destruction

CPatternGeneratorView::CPatternGeneratorView() noexcept
{
	// TODO: add construction code here
	m_pCurrentThread = NULL;
	a = 125;
	b = 125;
	c = 175;
	d = 175;
	theta = 0;
	m_iCounter = 0;
	x = 0;
	y = 0;
	speed = 100;
}

CPatternGeneratorView::~CPatternGeneratorView()
{
}

BOOL CPatternGeneratorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CPatternGeneratorView drawing
bool CPatternGeneratorView::OnEraseBkgnd(CDC* pDC)
{
	return false;
}
void CPatternGeneratorView::OnDraw(CDC* pDC)
{
	CPatternGeneratorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	//inner orbit
	
	for (int i = 0; i <= m_iCounter; i++)
	{
		
		theta = i;
		x = a * cos(speed * theta);
		y = b * sin(speed * theta);
		
	}
	
	for (int i = 0;i <= m_iCounter;i++)
	{
		CBrush brushred(RGB(255, 0, 0));
		CBrush* pOldbrush = pDC->SelectObject(&brushred);
		pDC->Ellipse(295 + x + 20, 290 + y + 20, 290 + x - 20, 290 + y - 20);
		Invalidate();
		pDC->SelectObject(pOldbrush);
	}
	CPen pen1;
	pen1.CreatePen(PS_SOLID, 5, RGB(0, 10, 0));
	CPen* p1 = pDC->SelectObject(&pen1);
	pDC->Ellipse(160, 160, 420, 420);;
	pDC->SelectObject(p1);

	//outer orbit
	for (int i = 0; i <= m_iCounter; i++)
	{
		theta = i;
		x = c * cos(speed * theta);
		y = d * sin(speed * theta);
	}

	for (int i = 0;i <= m_iCounter;i++)
	{
		CBrush brushred(RGB(0, 255, 0));
		CBrush* pOldbrush = pDC->SelectObject(&brushred);
		pDC->Ellipse(295 + x + 20, 290 + y + 20, 290 + x - 20, 290 + y - 20);
		Invalidate();
		pDC->SelectObject(pOldbrush);
	}
	CPen pen2;
	pen2.CreatePen(PS_SOLID, 5, RGB(0, 0, 255));
	CPen* p2 = pDC->SelectObject(&pen2);
	pDC->Ellipse(110, 110, 470, 470);
	pDC->SelectObject(p2);
	
	//sun
	CBrush brushred3(RGB(255, 255, 0));
	CBrush* pOldbrush3 = pDC->SelectObject(&brushred3);
	pDC->Ellipse(245,245,340,340);
	pDC->SelectObject(pOldbrush3);
	
}


// CPatternGeneratorView printing


void CPatternGeneratorView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CPatternGeneratorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}


void CPatternGeneratorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CPatternGeneratorView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CPatternGeneratorView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CPatternGeneratorView diagnostics

#ifdef _DEBUG
void CPatternGeneratorView::AssertValid() const
{
	CView::AssertValid();
}

void CPatternGeneratorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPatternGeneratorDoc* CPatternGeneratorView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPatternGeneratorDoc)));
	return (CPatternGeneratorDoc*)m_pDocument;
}
#endif //_DEBUG


// CPatternGeneratorView message handlers


void CPatternGeneratorView::OnButtonStart()
{
	// TODO: Add your command handler code here
	m_pCurrentThread = AfxBeginThread(CPatternGeneratorView::StartThread, this);
}


void CPatternGeneratorView::OnButtonSuspend()
{
	// TODO: Add your command handler code here
	m_pCurrentThread->SuspendThread();
	
}


void CPatternGeneratorView::OnButtonResume()
{
	// TODO: Add your command handler code here
	m_pCurrentThread->ResumeThread();
}

void CPatternGeneratorView::OnBeginPrinting(CDC* pDC,CPrintInfo* info)
{
	
}
UINT CPatternGeneratorView::StartThread(LPVOID Param)
{
	// TODO: Add your implementation code here.
	CPatternGeneratorView* pView = (CPatternGeneratorView*)Param;
	
	while (1)
	{
		
		pView->m_iCounter++;
		pView->Invalidate(false);
		Sleep(100);
	}
	return 0;
}
