﻿
// ApplicationDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Application.h"
#include "ApplicationDlg.h"
#include "afxdialogex.h"
#include <utility>
#include <tuple>
#include <vector>
#include <Gdiplus.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#ifndef MIN_SIZE
#define MIN_SIZE 300
#endif
using namespace std;

void CStaticImage::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	GetParent()->SendMessage( CApplicationDlg::WM_DRAW_IMAGE, (WPARAM)lpDrawItemStruct);
}

void CStaticHistogram::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	GetParent()->SendMessage(CApplicationDlg::WM_DRAW_HISTOGRAM, (WPARAM)lpDrawItemStruct);
}

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg() : CDialogEx(IDD_ABOUTBOX) {}

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	void DoDataExchange(CDataExchange* pDX) override    // DDX/DDV support
	{
		CDialogEx::DoDataExchange(pDX);
	}

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
	

};

void CApplicationDlg::OnSize(UINT nType, int cx, int cy)
{
	Invalidate();
	__super::OnSize(nType,cx,cy);
	CWnd *pWnd;

	if (m_ctrlImage)
		m_ctrlImage.MoveWindow(CRect((cx*0.2),0,cx,cy));

	if (m_ctrlHistogram)
		m_ctrlHistogram.MoveWindow(CRect(0, (cy*0.5), (cx*0.2), cy));
}


BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// CApplicationDlg dialog

CApplicationDlg::CApplicationDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_APPLICATION_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CApplicationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IMAGE, m_ctrlImage);
	DDX_Control(pDX, IDC_HISTOGRAM, m_ctrlHistogram);
}

BEGIN_MESSAGE_MAP(CApplicationDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_UPDATE_COMMAND_UI(ID_FILE_OPEN, OnUpdateFileOpen)
	ON_COMMAND(ID_FILE_CLOSE, OnFileClose)
	ON_UPDATE_COMMAND_UI(ID_FILE_CLOSE, OnUpdateFileClose)
	ON_WM_CLOSE()
	ON_WM_SIZE()
	ON_WM_SIZING()
	ON_MESSAGE(WM_DRAW_IMAGE, OnDrawImage)
	ON_MESSAGE(WM_DRAW_HISTOGRAM, OnDrawHistogram)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


void CApplicationDlg::OnDestroy()
{
	Default();
}

LRESULT CApplicationDlg::OnDrawImage(WPARAM wParam, LPARAM lParam)
{
	LPDRAWITEMSTRUCT lpDI = (LPDRAWITEMSTRUCT)wParam;

	CDC * pDC = CDC::FromHandle(lpDI->hDC);

	//DRAW BITMAP
	if (m_pImage != nullptr) {
		CBitmap bmp;
		CDC bmDC;
		CBitmap *pOldbmp;
		BITMAP  bi;

		bmp.Attach(m_pImage->Detach());
		bmDC.CreateCompatibleDC(pDC);

		CRect r(lpDI->rcItem);

		pOldbmp = bmDC.SelectObject(&bmp);
		bmp.GetBitmap(&bi);

		pDC->FillSolidRect(r.left, r.top, r.Width(), r.Height(), RGB(255, 255, 255));

		double dWtoH = (double)bi.bmWidth / (double)bi.bmHeight;
		UINT nHeight = r.Height();
		UINT nWidth = (UINT)(dWtoH * (double)nHeight);

		if (nWidth > (UINT)r.Width())
		{
			nWidth = r.Width();
			nHeight = (UINT)(nWidth / dWtoH);
			_ASSERTE(nHeight <= (UINT)r.Height());
		}

		pDC->SetStretchBltMode(HALFTONE);

		pDC->StretchBlt(r.left + (r.Width() - nWidth) / 2, r.top + (r.Height() - nHeight) / 2, nWidth, nHeight, &bmDC, 0, 0, bi.bmWidth, bi.bmHeight, SRCCOPY);
		bmDC.SelectObject(pOldbmp);


		m_pImage->Attach((HBITMAP)bmp.Detach());

		return S_OK;
	}

}
		
void CApplicationDlg::vypocet_histogram(int h, int w)
{
	if (m_pImage != nullptr) {

		int *Redcolor = new int[(h*w)];
		int *Greencolor = new int[(h*w)];
		int *Bluecolor = new int[(h*w)];
		COLORREF ccolor = 0;
		BYTE bcolor;
		
		for (int i = 0; i < w; i++)
			for (int j = 0; j < h; j++)
			{// Here you get the RGB value
				ccolor=m_pImage->GetPixel(i, j);
				// In this way you get one byte for each color
				bcolor = GetRValue(ccolor);
				Redcolor[(w*j)+i] = (int)bcolor;
				bcolor = GetGValue(ccolor);
				Greencolor[(w*j) + i] = (int)bcolor;
				bcolor = GetBValue(ccolor);
				Bluecolor[(w*j) + i] = (int)bcolor;

			}

		for (int i = 0; i < h*w; i++)
		{
			m_histogramR[Redcolor[i]]++;
			m_histogramG[Greencolor[i]]++;
			m_histogramB[Bluecolor[i]]++;
		}
		
	}
}

void CApplicationDlg::draw_histogram(COLORREF color, float sx, float sy, int *pole, CDC *pDC, CRect rect)
{
		
	for (int i = 0; i < 255; i++)
	{
		pDC->FillSolidRect(sx*i,rect.Height()-sy*pole[i],1,sy*pole[i], color);	

	}
}

LRESULT CApplicationDlg::OnDrawHistogram(WPARAM wParam, LPARAM lParam)
{
	LPDRAWITEMSTRUCT lpDI = (LPDRAWITEMSTRUCT)wParam;

	CDC * pDC = CDC::FromHandle(lpDI->hDC);

	//DRAW BITMAP
	if (m_pImage != nullptr) {
		
		CBitmap bmp;
		CDC bmDC;
		BITMAP  bi;
		CRect rect(lpDI->rcItem);
		float maxr, maxg, maxb, maxh=0;
		float sx, syr,syb,syg;

		bmp.Attach(m_pImage->Detach());
		bmDC.CreateCompatibleDC(pDC);
		bmp.GetBitmap(&bi);
		m_pImage->Attach((HBITMAP)bmp.Detach());

		

		
		CPen penr(PS_SOLID, 1, RGB(255, 0, 0));
		CPen peng(PS_SOLID, 1, RGB(0, 255, 0));
		CPen penb(PS_SOLID, 1, RGB(0, 0, 255));
		
		maxr = m_histogramR[0];
		maxg = m_histogramG[0];
		maxb = m_histogramB[0];
	
		for (int i = 0; i <255; i++)
			{
				if (maxr < m_histogramR[i])
					maxr = m_histogramR[i];

				if (maxg < m_histogramG[i])
					maxg = m_histogramG[i];

				if (maxb < m_histogramB[i])
					maxb = m_histogramB[i];
			}
		/*if ((maxh < maxr) || (maxh < maxg) || (maxh < maxb))
		{
			maxh = maxr;
			if (maxh < maxg)
				maxh = maxg;

			if (maxh < maxb)
				maxh = maxb;
		}*/
	
		sx =(float) rect.Width()/256 ;
		syr = (float) rect.Height() / maxr;
		syg = (float)rect.Height() / maxg;
		syb = (float)rect.Height() / maxb;

		COLORREF red=RGB(255, 0, 0);
		COLORREF green=RGB(0, 255, 0);
		COLORREF blue=RGB(0, 0, 255);

		draw_histogram(red, sx, syr, m_histogramR, pDC, rect);
		draw_histogram(green, sx, syg, m_histogramG, pDC, rect);
		draw_histogram(blue, sx, syb, m_histogramB, pDC, rect);
		
	}
	else
	{
		CRect rect(lpDI->rcItem);
		CBrush brush;
		brush.CreateSolidBrush(RGB(255, 255, 255));

		pDC->FillRect(&rect, &brush);

		DeleteObject(brush);

	}
	

		return S_OK;
}


void CApplicationDlg::OnClose()
{

	EndDialog(0);
}

BOOL CApplicationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	CRect rct;

	CRect rctClient;
	GetClientRect(&rctClient);
	
	m_ctrlImage.GetWindowRect(&rct);
	m_ptImage.x = rctClient.Width() - rct.Width();
	m_ptImage.y = rctClient.Height() - rct.Height();

	m_ctrlHistogram.GetWindowRect(&rct);
	m_ptHistogram.x = rctClient.Width() - rct.Width();
	m_ptHistogram.y = rctClient.Height() - rct.Height();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CApplicationDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CApplicationDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cx_icon = GetSystemMetrics(SM_CXICON);
		int cy_icon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);		
		int x = (rect.Width() - cx_icon + 1) / 2;
		int y = (rect.Height() - cy_icon + 1) / 2;
		
		// Draw the icon
		dc.DrawIcon(x,y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();

	}
		
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CApplicationDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CApplicationDlg::OnFileOpen()
{

	CFileDialog file_dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("Jpg Files (*.jpg)|*.jpg|Png Files (*.png)|*.png||"));

	if (file_dlg.DoModal() == IDOK) {
		path_name = file_dlg.GetPathName();
		SetWindowText(file_dlg.GetFileTitle());
		m_pImage =new CImage();
		
		if (m_pImage->Load(path_name)) //s_ok
		{
			delete m_pImage;
			m_pImage = nullptr;
		}

		vypocet_histogram(m_pImage->GetHeight(), m_pImage->GetWidth());

		Invalidate();
		
	}
	else {
		::MessageBox(NULL, __T("Chyba pri zobrazeni file dialogu."), __T("Error"), MB_OK);
	}
}

void CApplicationDlg::OnUpdateFileOpen(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TRUE);
}


void CApplicationDlg::OnFileClose()
{

	
	if (m_pImage != nullptr)
	{
		delete m_pImage;
		m_pImage = nullptr;
	}

	Invalidate();
}


void CApplicationDlg::OnUpdateFileClose(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TRUE);
}