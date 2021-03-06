
// mfc_containerView.cpp: CmfccontainerView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "mfc_container.h"
#endif

#include "mfc_containerDoc.h"
#include "mfc_containerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CmfccontainerView

IMPLEMENT_DYNCREATE(CmfccontainerView, CView)

BEGIN_MESSAGE_MAP(CmfccontainerView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CmfccontainerView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CmfccontainerView 构造/析构

CmfccontainerView::CmfccontainerView()
{
	// TODO: 在此处添加构造代码

}

CmfccontainerView::~CmfccontainerView()
{
}

BOOL CmfccontainerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CmfccontainerView 绘图

void CmfccontainerView::OnDraw(CDC* /*pDC*/)
{
	CmfccontainerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CmfccontainerView 打印


void CmfccontainerView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CmfccontainerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CmfccontainerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CmfccontainerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CmfccontainerView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CmfccontainerView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CmfccontainerView 诊断

#ifdef _DEBUG
void CmfccontainerView::AssertValid() const
{
	CView::AssertValid();
}

void CmfccontainerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CmfccontainerDoc* CmfccontainerView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CmfccontainerDoc)));
	return (CmfccontainerDoc*)m_pDocument;
}
#endif //_DEBUG


// CmfccontainerView 消息处理程序
