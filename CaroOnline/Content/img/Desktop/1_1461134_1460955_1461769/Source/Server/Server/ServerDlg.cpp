
// ServerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Server.h"
#include "ServerDlg.h"
#include "afxdialogex.h"
#include "afxsock.h"
#include "afxwin.h"
#include "winsock.h"


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


// CServerDlg dialog



CServerDlg::CServerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CServerDlg::IDD, pParent)
	, m_msgString(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_BOX_CHAT, m_msgString);
}

BEGIN_MESSAGE_MAP(CServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_SOCKET, SockMsg)
	ON_BN_CLICKED(IDC_LISTEN, &CServerDlg::OnBnClickedListen)
	ON_BN_CLICKED(IDCANCEL, &CServerDlg::OnBnClickedCancel)
	ON_EN_CHANGE(IDC_BOX_CHAT, &CServerDlg::OnEnChangeBoxChat)
END_MESSAGE_MAP()


// CServerDlg message handlers

BOOL CServerDlg::OnInitDialog()
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

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CServerDlg::OnPaint()
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
HCURSOR CServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CServerDlg::Split(CString src, CString des[2])
{
	int p1, p2;

	p1 = src.Find(_T("\r\n"), 0);
	des[0] = src.Mid(0, p1);

	p2 = src.Find(_T("\r\n"), p1 + 1);
	des[1] = src.Mid(p1 + 2, p2 - (p1 + 2));

}

char* CServerDlg::ConvertToChar(const CString &s)
{
	int nSize = s.GetLength();
	char *pAnsiString = new char[nSize + 1];
	memset(pAnsiString, 0, nSize + 1);
	wcstombs(pAnsiString, s, nSize + 1);
	return pAnsiString;
}

void CServerDlg::mSend(SOCKET sk, CString Command)
{
	int Len = Command.GetLength();
	Len += Len;
	PBYTE sendBuff = new BYTE[10000];
	memset(sendBuff, 0, 10000);
	memcpy(sendBuff, (PBYTE)(LPCTSTR)Command, Len);
	send(sk, (char*)&Len, sizeof(Len), 0);
	send(sk, (char*)sendBuff, Len, 0);
	delete sendBuff;
}

int CServerDlg::mRecv(SOCKET sk, CString &Command)
{
	PBYTE buffer = new BYTE[10000];
	memset(buffer, 0, 10000);
	recv(sk, (char*)&buffLength, sizeof(int), 0);
	recv(sk, (char*)buffer, buffLength, 0);
	TCHAR* ttc = (TCHAR*)buffer;
	Command = ttc;

	if (Command.GetLength() == 0)
		return -1;
	return 0;

}
void CServerDlg::OnBnClickedListen()
{
	UpdateData();
	WSADATA wsadata;
	//khởi tạo thư viện winsock ,phiên bản 2.0
	if (WSAStartup(MAKEWORD(2, 0), &wsadata) != 0){
		MessageBox(_T("Ham WSAStartup loi.\n"));
		return;
	}
	//khởi tạo socket (TCP/IP, TCP,mặc định của giao thức)
	sockServer = socket(AF_INET, SOCK_STREAM, 0);
	if (sockServer == SOCKET_ERROR){
		MessageBox(_T("Không thể tạo socket"));
		return;
	}
	//gán các thông tin cho socket
	serverAdd.sin_family = AF_INET;
	serverAdd.sin_port = htons(PORT);
	serverAdd.sin_addr.s_addr = inet_addr("127.0.0.1");
	int i = 0;
	//setsockopt(sockServer, SOL_SOCKET, SO_KEEPALIVE, (char*)&i, sizeof(i)); bỏ
	//gọi hàm bind gán các thông số trên
	if (bind(sockServer, (SOCKADDR*)&serverAdd, sizeof (serverAdd)) < 0){
		MessageBox(_T("Lỗi hàm Bind"));
	}
	//tạo hàng đợi cho các kết nối, tối đa 10 client
	if (listen(sockServer, 10) >= 0){
		m_msgString = _T("Server đang lắng nghe kết nối...\r\n");
		UpdateData(FALSE);
	}
	//khởi tạo cơ chế sử lý thông điệp của windows, đối tượng theo dõi sockServer, m_hWnd cửa sổ nhận thông điệp
	int err = WSAAsyncSelect(sockServer, m_hWnd, WM_SOCKET, FD_READ | FD_ACCEPT | FD_CLOSE);
	if (err)
		MessageBox((LPCTSTR)_T("Lỗi hàm WSAAsyncSelect"));
	GetDlgItem(IDC_LISTEN)->EnableWindow(FALSE);

	number_Socket = 0;
	pSock = new SockName[200];
}
void CServerDlg::LoadProduct(CString &sRet){
	CFile file;

	if (!file.Open(L"MaTenSP.txt", CFile::modeRead)){
		return;
	}

	char text[10000];

	DWORD byteread = file.Read(&text, file.GetLength() * 2);
	for (int i = 0; i < byteread; i++)
	{
		sRet += CString(text[i]);
	}
	file.Close();
}
CString CServerDlg::DetailProduct(CString sCode){
	CFile file;
	if (!file.Open(L"MaThongTinSP.txt", CFile::modeRead)){
		return NULL;
	}
	char text[10000];
	CString Temp,sRet;
	DWORD byteread = file.Read(&text, file.GetLength() * 2);
	for (int i = 0; i < byteread; i++)
	{
		Temp += CString(text[i]);
	}
	int p1 = Temp.Find(sCode,0);
	if (p1 == -1){
		sRet = _T("Ma San Pham Khong Ton Tai\r\nVui Long Kiem Tra Lai.");
	}
	else{
		int p2 = Temp.Find(_T("\r\n"), p1 + 1);
		sRet = Temp.Mid(p1, p2 - p1);
	}
	return sRet;
	file.Close();
}
int CServerDlg::CheckDetail(CString strDetail){
	CFile file;
	if (!file.Open(L"MaSoLuongSP.txt", CFile::modeRead)){
		return NULL;
	}
	char text[10000];
	CString Temp;
	DWORD byteread = file.Read(&text, file.GetLength() * 2);
	for (int i = 0; i < byteread; i++)
	{
		Temp += CString(text[i]);
	}
	//Lấy mã sp từ input
	int a = strDetail.Find(_T(" "));
	CString m_masp = strDetail.Mid(0, a);
	//	CẦN CẬP NHẬT LẠI XỬ LÝ CODE 
	if (m_masp.GetLength() < 2)
		return 1;
	//kiểm tra masp
	int p1 = Temp.Find(m_masp);
	if (p1 == -1)
		return 1;
	//lấy sô lượng từ input
	//CString strNum = strDetail.Mid(4, strDetail.Find(_T(" "), 4)-4);
	int b = strDetail.Find(_T(" "),a+1);
	CString strNum = strDetail.Mid(a, b-a);
	int iNum = _ttoi(strNum);
	int p2 = Temp.Find(_T("\r\n"), p1 + 1);
	//Lấy số lượng từ data
	int p = Temp.Find(_T(" "), p1 + 1);
	CString strNum2 = Temp.Mid(p, p2 - p);
	int iNum2 = _ttoi(strNum2);
	if (iNum2 == 0)
		return 3;
	if (iNum > iNum2)
		return 2;
	return 4;

}
void CServerDlg::UpdateNumber(CString strNum){
	CFile file;
	if (!file.Open(L"MaSoLuongSP.txt", CFile::modeRead)){
		return;
	}
	char text[10000];
	CString Temp;
	DWORD byteread = file.Read(&text, file.GetLength() * 2);
	for (int i = 0; i < byteread; i++)
	{
		Temp += CString(text[i]);
	}
	file.Close();
	CFile::Remove(L"MaSoLuongSP.txt");
	CFile filenew;
	filenew.Open(L"MaSoLuongSP.txt", CFile::modeCreate | CFile::modeWrite);
	//lấy mã sp từ input
	CString sNum = strNum.Mid(0, strNum.Find(_T(" "))+1);
	//lấy số lượng từ input
	CString nNum1 = strNum.Mid(strNum.Find(_T(" ")) + 1, strNum.Find(_T("\r\n")) - strNum.Find(_T(" ")) - 1);
	//tìm mã sp trong data
	int p = Temp.Find(sNum);
	//Lấy số lượng từ data
	CString nNum2 = Temp.Mid(p + 4, Temp.Find(_T("\r\n"), p) - p-4);
	int iNum1 = _ttoi(nNum1);
	int iNum2 = _ttoi(nNum2);
	int kq = iNum2 - iNum1;
	CString sTemp;
	sTemp.Format(sNum + _T("%d"), kq);//chuỗi cần thay thế
	//cập nhật lại số lượng và mã sp
	CString sTemp1 = sNum + nNum2;
	Temp.Replace(sTemp1, sTemp);
	//ghi vào Temp vào tập tin
	filenew.Write(Temp+_T("\r\n"), (Temp.GetLength()+2) * 2);
	filenew.Close();
}
LRESULT CServerDlg::SockMsg(WPARAM wParam, LPARAM lParam)
{
	if (WSAGETSELECTERROR(lParam))
	{
		// Display the error and close the socket
		closesocket(wParam);
	}
	switch (WSAGETSELECTEVENT(lParam))
	{
	case FD_ACCEPT:
	{
					  pSock[number_Socket].sockClient = accept(wParam, NULL, NULL);
					  GetDlgItem(IDC_LISTEN)->EnableWindow(FALSE);
					  break;
	}
	case FD_READ:
	{

					int post = -1, dpos = -1;

					for (int i = 0; i<number_Socket; i++)
					{
						if (pSock[i].sockClient == wParam)
						{
							if (i<number_Socket)
								post = i;
						}
					}

					CString temp;
					if (mRecv(wParam, temp) < 0)
						break;
					Split(temp, strResult);
					int flag = _ttoi(strResult[0]);
					char* tem = ConvertToChar(strResult[1]);
					switch (flag)
					{
					case 1://Login
					{
							   int t = 0;
							   if (number_Socket>0)
							   {
								   for (int i = 0; i<number_Socket; i++)
								   {
									   if (strcmp(tem, pSock[i].Name) == 0)//Trung ten user
									   {
										   t = 1;
										   break;
									   }
								   }
							   }

							   if (t == 0)
							   {
								   strcpy(pSock[number_Socket].Name, tem);
								   Command = _T("1\r\n1\r\n");
								   m_msgString += _T("Email: ") + strResult[1] + _T(" đăng nhập.\r\n");
								   UpdateData(FALSE);
								   number_Socket++;
								 
							   }
							   else
								   Command = _T("1\r\n0\r\n");
							   mSend(wParam, Command);
							   UpdateData(FALSE);
							   break;
					}
						// Load danh sách sản phẩm
					case 2:
					{
							 int post = -1;
							  for (int i = 0; i<number_Socket; i++)
							  {
								  if (pSock[i].sockClient == wParam)
								  {
									  if (i<number_Socket)
										  post = i;
								  }
							  }
							  CString sResult = _T("2\r\n-1\r\n");
							  LoadProduct(sResult);						
							  mSend(wParam, sResult);
							 
							  UpdateData(FALSE);

							  break;
					}
						//Đăng xuất
					case 3:
					{
							  int post = -1;
							  for (int i = 0; i<number_Socket; i++)
							  {
								  if (pSock[i].sockClient == wParam)
								  {
									  if (i<number_Socket)
										  post = i;
								  }
							  }


							  m_msgString += "Email: ";
							  m_msgString += pSock[post].Name;
							  m_msgString += _T(" đăng xuất.\r\n");
							  closesocket(wParam);
							  for (int j = post; j < number_Socket; j++)
							  {
								  pSock[post].sockClient = pSock[post + 1].sockClient;
								  strcpy(pSock[post].Name, pSock[post + 1].Name);
							  }
							  number_Socket--;
							  UpdateData(FALSE);
							  break;
					}
						//Lấy thông tin sản phẩm
					case 4:{
							   UpdateData();
							   CString sDetail = _T("3\r\n-1\r\n");
							   sDetail += DetailProduct(strResult[1]);
							   mSend(wParam,sDetail);
							   UpdateData(FALSE);
							   break;
					}
						//Gởi hóa đơn sản phẩm
					case 5:{
							   UpdateData();
							   int iCheck = CheckDetail(strResult[1]);
							   //Kiểm tra số lượng hàng tồn trong kho
							   CString sCheck;
							   switch (iCheck){
								   
							   case 1:{
									   sCheck = _T("4\r\n1\r\n");
									   sCheck += _T("Ma San Pham Khong Ton Tai\nVui Long Kiem Tra Lai.");
									   mSend(wParam, sCheck);
									   UpdateData(FALSE);
									   break;
								   }
							   case 2:{
									   sCheck = _T("4\r\n2\r\n");
									   sCheck += _T("So Luong Trong Kho Khong Du De Dat Hang.");
									   mSend(wParam, sCheck);
									   UpdateData(FALSE);
									   break;
								   }
							   case 3:{
									   sCheck = _T("4\r\n3\r\n");
									   sCheck += _T("San Pham Nay Tam Thoi Da Het Hang.");
									   mSend(wParam, sCheck);
									   UpdateData(FALSE);
									   break;
								   }
							   case 4:{
										sCheck = _T("4\r\n4\r\n");
										int p = strResult[1].Find(_T(" "));
										CString sTemp = strResult[1].Mid(0,p);
										sCheck += DetailProduct(sTemp);
										
										mSend(wParam, sCheck);
										UpdateData(FALSE);
										break;
							   }
							   }
							   break;
					}
						//cập nhật số lượng
					case 6:{
							   CString sRet = _T("5\r\n");
							   UpdateNumber(strResult[1]+_T("\r\n"));
							   mSend(wParam,sRet);
							   UpdateData(FALSE);
							   break;
					}
					}
					break;
	}

	case FD_CLOSE:
	{
					 UpdateData();
					 int post = -1;
					 for (int i = 0; i<number_Socket; i++)
					 {
						 if (pSock[i].sockClient == wParam)
						 {
							 if (i<number_Socket)
								 post = i;
						 }
					 }

					 m_msgString += _T("Email: ");
					 m_msgString += pSock[post].Name;
					 m_msgString += _T(" đăng xuât.\r\n");
					 closesocket(wParam);
					 for (int j = post; j < number_Socket; j++)
					 {
						 pSock[post].sockClient = pSock[post + 1].sockClient;
						 strcpy(pSock[post].Name, pSock[post + 1].Name);
					 }
					 number_Socket--;
					 UpdateData(FALSE);
					 break;
	}

	}
	return 0;
}


void CServerDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


void CServerDlg::OnEnChangeBoxChat()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}
