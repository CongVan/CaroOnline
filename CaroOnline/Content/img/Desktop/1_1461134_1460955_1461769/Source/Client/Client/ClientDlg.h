
// ClientDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include"HoaDonDlg.h"
#define PORT 50000
#define WM_SOCKET WM_USER+2

// CClientDlg dialog
class CClientDlg : public CDialogEx
{
// Construction
public:
	CClientDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_CLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLbnSelchangeDanhsach();
	CListBox data_product;
	afx_msg void OnLbnDblclkDanhsach();
	afx_msg void OnEnChangeTrangthai();
	afx_msg void OnBnClickedDangnhap();


	LRESULT SockMsg(WPARAM wParam, LPARAM lParam);
	char* ConvertToChar(const CString &s);
	void Split(CString src, CString des[2]);
	void mSend(CString Command);
	int mRecv(CString &Command);

	void LoadProduct();

	SOCKET sClient;
	sockaddr_in servAdd;
	CString Command;
	int	buffLength;
	CString strResult[2];
	CString userOnline;
	int level;
	int isLogon;

	CString m_msgString;
	CString IP;
	CString m_userName;
	CString m_email;
	CString m_status;
	afx_msg void OnBnClickedDangxuat();
	CString m_number;

	CFile product;

	int m_ktdangnhap;

	CString m_sanpham;

	afx_msg void OnBnClickedThongtinsp();
	CString m_masp;

	CString m_manganhang;
	CString m_Thongtin;

	afx_msg void OnBnClickedThanhtoan();

	HoaDonDlg* dHoaDon = new HoaDonDlg;
	afx_msg void OnBnClickedThoat();
};
