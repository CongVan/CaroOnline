#pragma once


// HoaDonDlg dialog

class HoaDonDlg : public CDialogEx
{
	DECLARE_DYNAMIC(HoaDonDlg)

public:
	HoaDonDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~HoaDonDlg();

// Dialog Data
	enum { IDD = IDD_HOADON };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_hoadon;
	afx_msg void OnBnClickedDathang();
};
