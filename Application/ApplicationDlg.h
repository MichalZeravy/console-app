
// ApplicationDlg.h : header file
//

#pragma once
#pragma comment( lib, "gdiplus.lib" ) 
#include <Gdiplus.h>

class CStaticImage : public CStatic
{
public:
	// Overridables (for owner draw only)
	void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) override;
};

class CStaticHistogram : public CStatic
{
public:
	// Overridables (for owner draw only)
	void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) override;
};

// CApplicationDlg dialog
class CApplicationDlg : public CDialogEx
{
// Construction
public:
	enum
	{
		WM_DRAW_IMAGE = (WM_USER + 1),
		WM_DRAW_HISTOGRAM
				
	};

	CApplicationDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_APPLICATION_DIALOG };
#endif

	protected:
	void DoDataExchange(CDataExchange* pDX) override;	// DDX/DDV support

	void OnOK() override {}
	void OnCancel() override {}


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	BOOL OnInitDialog() override;
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	CString path_name;
	CImage *m_pImage = nullptr;
	CImage *m_pImage1 = nullptr;
	CImage *m_pImage2 = nullptr;
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	int m_histogramR[255] = {0};
	int m_histogramG[255] = {0};
	int m_histogramB[255] = {0};	
	BOOL m_rozmazanie = false;
	BOOL m_checkred=false;
	BOOL m_checkgreen=false;
	BOOL m_checkblue=false;
	int tmp[255] = { 0 };
	BOOL b=false;
	BYTE *pbyteImage;
	BYTE *pbyteImage1;
	float w, h;
	int nPitch;
	int nPitch1;
	UINT_PTR id=0;

public:
	afx_msg void OnFileOpen();
	afx_msg void OnUpdateFileOpen(CCmdUI *pCmdUI);
	afx_msg void OnFileClose();
	afx_msg void OnUpdateFileClose(CCmdUI *pCmdUI);
	afx_msg void OnClose();
	afx_msg LRESULT OnDrawImage(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnDrawHistogram(WPARAM wParam, LPARAM lParam);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	void vypocet_histogram();
	afx_msg void draw_histogram(COLORREF color,float min, float sx, float sy, int *pole, CDC *pDC, CRect rect);
	afx_msg void OnHistogramRed();
	afx_msg void OnHistogramGreen();
	afx_msg void OnHistogramBlue();
	afx_msg void OnEditRozmazanie();
	afx_msg void OnTimer(UINT_PTR id);
	void Blur();

protected:
	CStaticImage m_ctrlImage;
	CStaticHistogram m_ctrlHistogram;
	CPoint m_ptHistogram;
	CPoint m_ptImage;
};
