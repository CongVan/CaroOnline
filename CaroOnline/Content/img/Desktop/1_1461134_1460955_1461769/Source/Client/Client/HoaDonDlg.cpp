// HoaDonDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Client.h"
#include "HoaDonDlg.h"
#include "afxdialogex.h"
#include "ClientDlg.h"


// HoaDonDlg dialog

IMPLEMENT_DYNAMIC(HoaDonDlg, CDialogEx)

HoaDonDlg::HoaDonDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(HoaDonDlg::IDD, pParent)
	, m_hoadon(_T(""))
{

}

HoaDonDlg::~HoaDonDlg()
{
}

void HoaDonDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_hoadon);
}


BEGIN_MESSAGE_MAP(HoaDonDlg, CDialogEx)
	ON_BN_CLICKED(IDC_DATHANG, &HoaDonDlg::OnBnClickedDathang)
END_MESSAGE_MAP()


// HoaDonDlg message handlers


void HoaDonDlg::OnBnClickedDathang()
{
	// TODO: Add your control notification handler code here
	
}
