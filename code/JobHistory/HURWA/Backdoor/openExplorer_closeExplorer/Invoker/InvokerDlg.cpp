
// InvokerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Invoker.h"
#include "InvokerDlg.h"
#include "afxdialogex.h"
#include <tchar.h>
#include <stdarg.h>
#include <time.h> 
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <process.h>
#include <TlHelp32.h>
#include <iphlpapi.h>
#include <string>
#include <ctime>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define _LOG(level, format, ...)\
	{ \
		char string1[255] = ""; \
		memset(string1,0,255); \
		char string2[255] = ""; \
		memset(string2,0,255); \
	struct tm t; \
		time_t now; \
		time(&now); \
		localtime_s(&t, &now); \
		sprintf_s(string1, 255, "%d:%d:%d:%d:%d:%d", t.tm_year + 1900, t.tm_mon + 1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec); \
		sprintf_s(string2, 255, "[%s] [%s %d]\n", string1, __FUNCTION__, __LINE__); \
		printf(string2); \
		ofstream _write("d:\\SampleServiceInvokerDlg.txt", ios::app); \
		_write << string2; \
		writeLog0(_write,level,format,##__VA_ARGS__); \
	_write.close();\
	}

static void writeLog0(ofstream& _write, int level, const char* format, ...)
{
	char str[1024 + 1] = "";
	memset(str, 0, 1024);
	va_list arg_ptr;
	va_start(arg_ptr, format);
	int size = vsnprintf_s(str, 1024, format, arg_ptr);
	if (size <= 0) {
		return;
	}
	do {
		if (_write.is_open())
		{
			printf("[%d] %s\n", level, str);
			_write << str;
			_write << "\n\n";
			printf("\n");
		}
	} while (0);
	va_end(arg_ptr);
}


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CInvokerDlg �Ի���

CInvokerDlg::CInvokerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CInvokerDlg::IDD, pParent)
	, m_isOpened(false)
	, m_isPwdRight(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CInvokerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_OpenExplorer, m_btnOpenExplorer);
	DDX_Control(pDX, IDC_BTN_removeExplorer, btn_repairExplorer);
	DDX_Control(pDX, IDC_EDIT2, m_editPwd);
	DDX_Control(pDX, IDC_BUTTON1, m_btnCheck);
}

BEGIN_MESSAGE_MAP(CInvokerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BTN_REBOOT, &CInvokerDlg::OnBnClickedBtnReboot)
	ON_BN_CLICKED(IDC_BTN_OpenExplorer, &CInvokerDlg::OnBnClickedBtnOpenexplorer)
	ON_BN_CLICKED(IDC_BTN_removeExplorer, &CInvokerDlg::OnBnClickedBtnremoveexplorer)
	ON_BN_CLICKED(IDC_BUTTON1, &CInvokerDlg::OnBnClickedPwdCheck)
END_MESSAGE_MAP()


// CInvokerDlg ��Ϣ�������

BOOL CInvokerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	m_btnOpenExplorer.EnableWindow(FALSE);
	btn_repairExplorer.EnableWindow(FALSE);

	CFont font;
	font.CreatePointFont(150, _T("����"));
	GetDlgItem(IDC_STATIC_HINT)->SetFont(&font);
	::SetWindowPos(m_hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CInvokerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CInvokerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CInvokerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

bool CreateCustomProgressAndGetResult(char* _pcCmdLine, char* _pcOutBuf,int _iMaxLen, int & _iOutLen)
{
	_iOutLen = 0;
	SECURITY_ATTRIBUTES sa;
	HANDLE hRead, hWrite;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;
	if (!CreatePipe(&hRead, &hWrite, &sa, 0))
	{
		return false;
	}
	STARTUPINFOA si;
	PROCESS_INFORMATION pi;
	si.cb = sizeof(STARTUPINFO);
	GetStartupInfoA(&si);
	si.hStdError = hWrite;            
	si.hStdOutput = hWrite;
	si.wShowWindow = SW_HIDE;
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;

	if (!CreateProcessA(NULL, _pcCmdLine, NULL, NULL, TRUE, NULL, NULL, NULL, &si, &pi))
	{
		DWORD dwErr = ::GetLastError();
		char arr[MAX_PATH] = { 0 };
		printf(arr, "Error = %d", dwErr);
		CloseHandle(hWrite);
		CloseHandle(hRead);
		return false;
	}
	CloseHandle(hWrite);
	char * p = _pcOutBuf;
	int total = 0;
	if (_pcOutBuf && _iMaxLen > 0)
	{
		char buffer[4096] = { 0 };

		while (true)
		{
			DWORD bytesRead = 0;
			if (total >= _iMaxLen || ReadFile(hRead, buffer, sizeof(buffer), &bytesRead, NULL) == NULL)
			{
				break;
			}
			int s = bytesRead;
			total += bytesRead;
			if (total > _iMaxLen)
			{
				s = _iMaxLen - (total - bytesRead);
			}
			memcpy(p, buffer, s);
			p += s;
		}
	}
	CloseHandle(hRead);
	_iOutLen = total;
	return true;
}


string getInstallDirection(string appName)
{
	string retStr = "";
	if (appName.empty() || appName.find(".exe") == -1) return "";

	char fileDirection[MAX_PATH] = { 0 };
	GetModuleFileNameA(NULL, fileDirection, MAX_PATH);

	char* pos = strstr(fileDirection, appName.c_str());
	_strset_s(pos, appName.size() + 1, 0);
	retStr = fileDirection;

	return retStr;
}

bool improvePv()
{
	HANDLE hToken;
	TOKEN_PRIVILEGES tkp;
	//�򿪵�ǰ���̵�Ȩ������
	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ALL_ACCESS, &hToken))
		return false;

	//���ĳһ�ض�Ȩ�޵�Ȩ�ޱ�ʶLUID��������tkp��
	//�鿴�����Ȩ��
	//��һ��������NULL��ʾҪ�鿴���ǵ�ǰ����ϵͳ
	//�ڶ���������ָ����Ȩ����
	//�������������������շ��ص���Ȩ������Ϣ
	if (!LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid))
		return false;

	//������Ȩ����ĸ���
	tkp.PrivilegeCount = 1;
	//SE_PRIVILEGE_ENABLE_BY_DEFAULT    ��ȨĬ������
	//SE_PRIVILEGE_ENABLED              ��Ȩ����
	//SE_PRIVILEGE_USER_FOR_ACCESS      ��������һ��������߷���
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;    //��Ȩ����

	//����AdjustTokenPrivileges������������Ҫ��ϵͳȨ��
	//�޸����Ƶ�Ȩ��
	//��һ��������������Ȩ�ľ��
	//�ڶ�����������ֹ����Ȩ�ޱ�ʾ
	if (!AdjustTokenPrivileges(hToken, FALSE, &tkp, NULL, NULL, NULL))
		return false;

	return true;
}

void CInvokerDlg::OnBnClickedBtnReboot()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (!improvePv() || !ExitWindowsEx(EWX_SHUTDOWN | EWX_FORCE, SHTDN_REASON_MAJOR_APPLICATION))
	{
		DWORD dwRet = GetLastError();
		char arr[256] = { 0 };
		sprintf_s(arr, "��������ϵͳʧ��,errorCode=%d", dwRet);
		_LOG(1, arr);
	}
	else
	{
		_LOG(1, "�ѳɹ���������ϵͳ");
	}
}

void CInvokerDlg::OnBnClickedBtnOpenexplorer()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int n = 0;
	
	// �޸�ע���
	std::string exePath = getInstallDirection("HHRBAssistTool.exe");
	char pCmd[512] = { 0 };
	sprintf_s(pCmd, "%s%s", exePath.c_str(), "repair.bat");
	char arrBuf[1024] = { 0 };
	int outLen = 0;
	CreateCustomProgressAndGetResult(pCmd, arrBuf, 1024, outLen);
	_LOG(1, arrBuf);

	// ˢ������
	::PostMessage(GetDesktopWindow()->m_hWnd, WM_KEYDOWN, VK_F5, 0);
	SHChangeNotify(SHCNE_ASSOCCHANGED, SHCNF_FLUSH, NULL, NULL);

	// ������
	CreateCustomProgressAndGetResult("C:\\Windows\\explorer.exe",nullptr,0,n);
	CreateCustomProgressAndGetResult("C:\\Windows\\explorer.exe", nullptr, 0, n);
}

void CInvokerDlg::OnBnClickedBtnremoveexplorer()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	std::string exePath = getInstallDirection("HHRBAssistTool.exe");
	char pCmd[512] = { 0 };
	sprintf_s(pCmd, "%s%s", exePath.c_str(), "removeExplorer.bat");
	char arrBuf[1024] = { 0 };
	int outLen = 0;
	CreateCustomProgressAndGetResult(pCmd, arrBuf, 1024, outLen);
	_LOG(1, arrBuf);
	MessageBoxA(this->GetSafeHwnd(), "�رղ���ϵͳ���������ã���ػ�������","��ʾ",MB_OK);
}

HBRUSH CInvokerDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	if (IDC_STATIC_HINT == pWnd->GetDlgCtrlID())
	{
		if (TRUE == m_isPwdRight)
		{
			pDC->SetTextColor(RGB(51, 153, 255));	//��ɫ
		}
		else
		{
			pDC->SetTextColor(RGB(255, 0, 0));	//��ɫ		
		}
	}

	return hbr;
}


void CInvokerDlg::OnBnClickedPwdCheck()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	CString pwdStr;
	m_editPwd.GetWindowText(pwdStr);
	
	time_t now = time(0);
    tm ltm;// = localtime(&now);
    localtime_s(&ltm, &now);

	CString strPwdDest;
	strPwdDest.Format(L"hurwa%d%d%d", (1900 + ltm.tm_year), (1+ltm.tm_mon), ltm.tm_mday);
	if (pwdStr.CompareNoCase(strPwdDest) != 0)
	{
		SetDlgItemText(IDC_STATIC_HINT,CString("��������Ч�����룡"));
		m_isPwdRight = false;
	}
	else 
	{
		m_isPwdRight = true;
		m_btnOpenExplorer.EnableWindow(TRUE);
		btn_repairExplorer.EnableWindow(TRUE);
		m_editPwd.EnableWindow(FALSE);
		m_btnCheck.EnableWindow(FALSE);
		SetDlgItemText(IDC_STATIC_HINT, CString("������֤ͨ����"));
	}
	UpdateData(FALSE);
	Invalidate(TRUE);
}


BOOL CInvokerDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  �ڴ����ר�ô����/����û���
	if (pMsg->message == WM_KEYDOWN&&pMsg->wParam == VK_RETURN)
		return TRUE;
	if (pMsg->message == WM_KEYDOWN&&pMsg->wParam == VK_ESCAPE)
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}
