
// ClientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Client.h"
#include "ClientDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CClientDlg dialog



CClientDlg::CClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CClientDlg::IDD, pParent)

	, IP(_T(""))
	, m_email(_T(""))
	, m_status(_T(""))
	, m_sanpham(_T(""))

	, m_masp(_T(""))
	, m_manganhang(_T(""))
	, m_Thongtin(_T(""))

{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_ID, IP);
	DDX_Text(pDX, IDC_EMAIL, m_email);
	DDX_Text(pDX, IDC_TRANGTHAI, m_status);
	DDX_Text(pDX, IDC_SOLUONG, m_number);
	DDX_Text(pDX, IDC_SanPham, m_sanpham);

	DDX_Text(pDX, IDC_MASP, m_masp);
	DDX_Text(pDX, IDC_MANH, m_manganhang);
	DDX_Text(pDX, IDC_THONGTIN, m_Thongtin);
}

BEGIN_MESSAGE_MAP(CClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_SOCKET, SockMsg)
	ON_EN_CHANGE(IDC_TRANGTHAI, &CClientDlg::OnEnChangeTrangthai)
	ON_BN_CLICKED(IDC_DANGNHAP, &CClientDlg::OnBnClickedDangnhap)
	ON_BN_CLICKED(IDC_DANGXUAT, &CClientDlg::OnBnClickedDangxuat)

	ON_BN_CLICKED(IDC_THONGTINSP, &CClientDlg::OnBnClickedThongtinsp)
//	ON_EN_CHANGE(IDC_MASP, &CClientDlg::OnEnChangeMasp)
//ON_EN_ERRSPACE(IDC_MASP, &CClientDlg::OnEnErrspaceMasp)
//ON_EN_SETFOCUS(IDC_MASP, &CClientDlg::OnSetfocusMasp)
//ON_EN_UPDATE(IDC_MASP, &CClientDlg::OnEnUpdateMasp)
ON_BN_CLICKED(IDC_THANHTOAN, &CClientDlg::OnBnClickedThanhtoan)
ON_BN_CLICKED(IDC_THOAT, &CClientDlg::OnBnClickedThoat)
END_MESSAGE_MAP()


// CClientDlg message handlers

BOOL CClientDlg::OnInitDialog()
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

	m_ktdangnhap = 0;
	m_number = "0";
	IP = "127.0.0.1";
	UpdateData(FALSE);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CClientDlg::OnEnChangeTrangthai()
{

	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}

void CClientDlg::Split(CString src, CString des[2])
{
	int p1, p2;

	p1 = src.Find(_T("\r\n"), 0);
	des[0] = src.Mid(0, p1);

	p2 = src.Find(_T("\r\n"), p1 + 1);
	des[1] = src.Mid(p1 + 2, p2 - (p1 + 2));

}

char* CClientDlg::ConvertToChar(const CString &s)
{
	int nSize = s.GetLength();
	char *pAnsiString = new char[nSize + 1];
	memset(pAnsiString, 0, nSize + 1);
	wcstombs(pAnsiString, s, nSize + 1);
	return pAnsiString;
}

void CClientDlg::mSend(CString Command)
{
	int Len = Command.GetLength();
	Len += Len;
	PBYTE sendBuff = new BYTE[10000];
	memset(sendBuff, 0, 10000);
	memcpy(sendBuff, (PBYTE)(LPCTSTR)Command, Len);
	send(sClient, (char*)&Len, sizeof(Len), 0);
	send(sClient, (char*)sendBuff, Len, 0);
	delete sendBuff;
}

int CClientDlg::mRecv(CString &Command)
{
	PBYTE buffer = new BYTE[10000];
	memset(buffer, 0, 10000);
	recv(sClient, (char*)&buffLength, sizeof(int), 0);
	recv(sClient, (char*)buffer, buffLength, 0);
	TCHAR* ttc = (TCHAR*)buffer;
	Command = ttc;

	if (Command.GetLength() == 0)
		return -1;
	return 0;
}

void CClientDlg::LoadProduct(){

	CFile file;
	if (!file.Open(L"data.txt", CFile::modeRead)){
		MessageBox(_T("File chưa tồn tại"), _T("Thông báo"), MB_OK);
		return;
	}
	char text[10000];
	DWORD byteread = file.Read(&text, file.GetLength()*2);
	
	for (int i = 0; i < byteread; i++)
	{
		//if (CString(text[i])=="");
		m_sanpham += CString(text[i]); 
	
	}




}
void CClientDlg::OnBnClickedDangnhap()
{
	
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_email == "")
	{
		MessageBox(_T("Vui long nhap ten user"));
		return;
	}
	WSADATA wsadata;
	if (WSAStartup(MAKEWORD(2, 0), &wsadata) != 0){
		MessageBox(_T("Ham WSAStartup loi.\n"));
		return;
	}
	sClient = socket(AF_INET, SOCK_STREAM, 0);
	hostent* host = NULL;
	if (sClient == INVALID_SOCKET)
	{
		MessageBox(_T("socket() failed"), _T("ERROR"), 0);
		return;
	}

	servAdd.sin_family = AF_INET;
	servAdd.sin_port = htons(PORT);

	char* cIP = ConvertToChar(IP);

	servAdd.sin_addr.s_addr = inet_addr(cIP);

	CStringA cpy_IP(IP);

	if (servAdd.sin_addr.s_addr == INADDR_NONE)
	{
		host = (gethostbyname(cpy_IP));
		if (host == NULL)
		{
			MessageBox(_T("Khong the ket noi den server."), _T("ERROR"), 0);
		}
		CopyMemory(&servAdd.sin_addr, host->h_addr_list[0],host->h_length);
		return;
	}

	int err = connect(sClient, (struct sockaddr*)&servAdd, sizeof(servAdd));
	if (err == SOCKET_ERROR){
		MessageBox(_T("Ket noi that bai"), _T("ERROR"), 0);
		return;
	}

	Command = _T("1\r\n");
	Command += m_email + _T("\r\n");
	mSend(Command);
	WSAAsyncSelect(sClient, m_hWnd, WM_SOCKET, FD_READ | FD_CLOSE);
	UpdateData(FALSE);
}

LRESULT CClientDlg::SockMsg(WPARAM wParam, LPARAM lParam)
{

	if (WSAGETSELECTERROR(lParam))
	{
		// Display the error and close the socket
		closesocket(wParam);
	}
	switch (WSAGETSELECTEVENT(lParam))
	{
	case FD_READ:
	{
					CString temp;
					if (mRecv(temp)<0)
						break;

					Split(temp, strResult);
					int flag1 = _ttoi(strResult[0]);
					int flag2 = _ttoi(strResult[1]);
					switch (flag1)
					{
					case 1:
					{
							 
							  if (flag2 == 1)
							  {
								  m_status += _T("Đăng nhập thành công.\r\n");
								  GetDlgItem(IDC_DANGXUAT)->EnableWindow(TRUE);
								  GetDlgItem(IDC_DANGNHAP)->EnableWindow(FALSE);
								  mSend(_T("2\r\n "));
								  m_ktdangnhap = 1;
							  }
							  else{
								  m_status += _T("Đăng nhập thất bại.\r\n");
								 
							  }
							  
							  UpdateData(FALSE);
							  break;
					}

					case 2:
					{
							  UpdateData();
							  int p = temp.Find(_T("2\r\n-1\r\n"), 0);
							  CString list = temp.Mid(p + 7);
							  //mRecv(sResult);
							  m_sanpham = list;
							  UpdateData(FALSE);
							  break;
					}
					case 3:
					{
							  UpdateData();

							  m_Thongtin = _T("");
							  int p = temp.Find(_T("3\r\n-1\r\n"));
							  CString strTemp = temp.Mid(p + 7);
							  if (strTemp == _T("Ma San Pham Khong Ton Tai\r\nVui Long Kiem Tra Lai.")){
								  m_Thongtin = strTemp;
								  UpdateData(FALSE);
								  break;
							  }

							  int p1 = strTemp.Find(_T(" "));
							  m_Thongtin += _T("Ma SP: ") + strTemp.Mid(0, p1) + _T("\r\n");
							  int p2 = strTemp.Find(_T("-"), p1 + 1);
							  m_Thongtin += _T("Gia: ") + strTemp.Mid(p1 + 1, p2 - p1 - 1) + _T("\r\n");
							  int p3 = strTemp.Find(_T("-"), p2 + 1);
							  m_Thongtin += _T("Mau: ") + strTemp.Mid(p2 + 1, p3 - p2 - 1) + _T("\r\n");
							  int p4 = strTemp.Find(_T("-"), p3 + 1);
							  m_Thongtin += _T("Dung Luong: ") + strTemp.Mid(p3 + 1, p4 - p3 - 1) + _T("\r\n");
							  int p5 = strTemp.Find(_T("."), p4 + 1);
							  m_Thongtin += _T("Khac: ") + strTemp.Mid(p4 + 1, p5 - p4 - 1);

							  UpdateData(FALSE);
							  break;
					}
					case 4:
					{
							  UpdateData();
							  switch (flag2){
							  case 1:{
									  int p = temp.Find(_T("4\r\n1\r\n"));
									  CString strTemp = temp.Mid(p + 6);
									  MessageBox(strTemp, _T("Hoa Don"), MB_OK);-
									  UpdateData(FALSE);
									  break;
								  }
							  case 2:{
									  int p = temp.Find(_T("4\r\n2\r\n"));
									  CString strTemp = temp.Mid(p + 6);
									  MessageBox(strTemp, _T("Hoa Don"), MB_OK);
									  UpdateData(FALSE);
									  break;
								  }
							  case 3:{
									  int p = temp.Find(_T("4\r\n3\r\n"));
									  CString strTemp = temp.Mid(p + 6);
									  MessageBox(strTemp, _T("Hoa Don"), MB_OK);
									  UpdateData(FALSE);
									  break;
								  }
							  case 4:{
									  dHoaDon->m_hoadon = _T("");
									  int p = temp.Find(_T("4\r\n4\r\n"));
									  CString strTemp = temp.Mid(p + 6);
									  int p1 = strTemp.Find(_T(" "));
									  dHoaDon->m_hoadon += _T("Thong tin san pham\r\n");
									  dHoaDon->m_hoadon +=  _T("Ma SP: ") + strTemp.Mid(0, p1) + _T("\r\n");
									  int p2 = strTemp.Find(_T("-"), p1 + 1);
									  CString sGia = strTemp.Mid(p1 + 1, p2 - p1 - 1);
									  dHoaDon->m_hoadon += _T("Gia: ") + sGia + _T("\r\n");
									  int p3 = strTemp.Find(_T("-"), p2 + 1);
									  dHoaDon->m_hoadon += _T("Mau: ") + strTemp.Mid(p2 + 1, p3 - p2 - 1) + _T("\r\n");
									  int p4 = strTemp.Find(_T("-"), p3 + 1);
									  dHoaDon->m_hoadon += _T("Dung Luong: ") + strTemp.Mid(p3 + 1, p4 - p3 - 1) + _T("\r\n");
									  int p5 = strTemp.Find(_T("."), p4 + 1);
									  dHoaDon->m_hoadon += _T("Khac: ") + strTemp.Mid(p4 + 1, p5 - p4 - 1) + _T("\r\n");
									  dHoaDon->m_hoadon += _T("Thong tin don hang\r\n");
									  dHoaDon->m_hoadon += _T("So Luong: ") + m_number+_T("\r\n");
									  dHoaDon->m_hoadon += _T("Ma Ngan Hang: ") + m_manganhang + _T("\r\n");
									  int iTemp = _ttoi(sGia)*_ttoi(m_number);
									  CString sTongTien;
									  sTongTien.Format(_T("%d"), iTemp);
									  dHoaDon->m_hoadon += _T("Tong Tien: ") + sTongTien;
									  //hiện hóa đơn
									  /*this->ShowWindow(SW_HIDE);
									  if (dHoaDon->DoModal() == IDC_THANHTOAN){
									  dHoaDon->UpdateData(FALSE);
									  dHoaDon->ShowWindow(SW_SHOW);
									  }
									  else{
									  this->ShowWindow(SW_SHOW);
									  }*/
									  INT_PTR i = MessageBox(dHoaDon->m_hoadon, _T("Đặt Hàng"), MB_OKCANCEL);
									  if (i == IDCANCEL)
										  break;
									  Command = _T("6\r\n");
									  Command += m_masp + _T(" ") + m_number + _T("\r\n");
									  mSend(Command);
									  UpdateData(FALSE); 
									  break;

								  }
							  }
							 break;
					}
					case 5:{
							   INT_PTR i = MessageBox(_T("Thanh Toan Thanh Cong."), _T("Đặt Hàng"), MB_OK);
							   if (i == IDOK){
								   m_masp = _T("");
								   m_manganhang = _T("");
								   m_number = _T("");
								   m_sanpham = _T("");
								   m_Thongtin = _T("");
								   m_status += _T("Bạn đã đăng xuất!\r\n");
								   Command = _T("3\r\n");
								   mSend(Command);
								   UpdateData(FALSE);
							   }

							   break;
					}
					}
					break;
	}
	case FD_CLOSE:
	{
					 closesocket(sClient);
					 m_msgString += _T("Server da dong ket noi\r\n");
					 GetDlgItem(IDC_DANGXUAT)->EnableWindow(FALSE);
					 GetDlgItem(IDC_DANGNHAP)->EnableWindow(TRUE);
					 UpdateData(FALSE);
					 break;
	}

	}
	return 0;
}

void CClientDlg::OnBnClickedDangxuat()
{
	// TODO: Add your control notification handler code here

	INT_PTR i = MessageBox(_T("Bạn muốn đăng xuất?"), _T("Confirm"), MB_OKCANCEL);
	if (i == IDCANCEL)
		return;
	m_sanpham = _T("");
	m_Thongtin = _T("");
	Command = _T("3\r\n");
	mSend(Command);
	m_status+=_T("Bạn đã đăng xuất!\r\n");
	UpdateData(FALSE);
}




void CClientDlg::OnBnClickedThongtinsp()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	
	if (m_masp == _T("")){
		MessageBox(_T("Bạn chưa nhập mã sản phẩm!!!"), _T("Thông báo"),MB_OK);
		return;
	}
	if (m_ktdangnhap == 0){
		MessageBox(_T("Bạn chưa đăng nhập"), _T("Thông báo"), MB_OK);
		return;
	}
	//gởi mã sp cho server
	Command = _T("4\r\n");
	Command += m_masp + _T(" \r\n");
	mSend(Command);
	UpdateData(FALSE);
}
void CClientDlg::OnBnClickedThanhtoan()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	if (m_ktdangnhap == 0){
		MessageBox(_T("Bạn chưa đăng nhập"), _T("Thông báo"), MB_OK);
		return;
	}
	if (m_masp == L"" || m_manganhang == L"" || m_number == L""){
		MessageBox(_T("Thông tin còn thiếu vui lòng kiểm tra lại."), _T("Thông Báo"), MB_OK);
		return;
	}
	//kiểm tra đúng đắn của số lượng
	char *strNumber = ConvertToChar(m_number);
	int n = m_number.GetLength();
	for (int i = 0; i < n; i++){
		if (strNumber[i]<'0' || strNumber[i]>'9')
			MessageBox(_T("Vui lòng kiểm tra lại số lượng."), _T("Thông Báo"), MB_OK);
	}
	//gởi thông tin hóa đơn sản phẩm cho server
	Command = _T("5\r\n");
	Command += m_masp + _T(" ") + m_number + _T(" ") + m_manganhang + _T("\r\n");
	mSend(Command);
	UpdateData(FALSE);
}

void CClientDlg::OnBnClickedThoat()
{
	// TODO: Add your control notification handler code here
	OnCancel();
}
