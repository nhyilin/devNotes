
// InvokerDlg.cpp : 实现文件
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


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CInvokerDlg 对话框

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


// CInvokerDlg 消息处理程序

BOOL CInvokerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	m_btnOpenExplorer.EnableWindow(FALSE);
	btn_repairExplorer.EnableWindow(FALSE);

	CFont font;
	font.CreatePointFont(150, _T("宋体"));
	GetDlgItem(IDC_STATIC_HINT)->SetFont(&font);
	::SetWindowPos(m_hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CInvokerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
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
	//打开当前进程的权限令牌
	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ALL_ACCESS, &hToken))
		return false;

	//获得某一特定权限的权限标识LUID，保存在tkp中
	//查看里面的权限
	//第一个参数：NULL表示要查看的是当前本地系统
	//第二个参数：指定特权名称
	//第三个参数：用来接收返回的特权名称信息
	if (!LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid))
		return false;

	//设置特权数组的个数
	tkp.PrivilegeCount = 1;
	//SE_PRIVILEGE_ENABLE_BY_DEFAULT    特权默认启动
	//SE_PRIVILEGE_ENABLED              特权启动
	//SE_PRIVILEGE_USER_FOR_ACCESS      用来访问一个对象或者服务
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;    //特权启动

	//调用AdjustTokenPrivileges来提升我们需要的系统权限
	//修改令牌的权限
	//第一个参数：调整特权的句柄
	//第二个参数：禁止所有权限表示
	if (!AdjustTokenPrivileges(hToken, FALSE, &tkp, NULL, NULL, NULL))
		return false;

	return true;
}

void CInvokerDlg::OnBnClickedBtnReboot()
{
	// TODO:  在此添加控件通知处理程序代码
	if (!improvePv() || !ExitWindowsEx(EWX_SHUTDOWN | EWX_FORCE, SHTDN_REASON_MAJOR_APPLICATION))
	{
		DWORD dwRet = GetLastError();
		char arr[256] = { 0 };
		sprintf_s(arr, "设置重启系统失败,errorCode=%d", dwRet);
		_LOG(1, arr);
	}
	else
	{
		_LOG(1, "已成功设置重启系统");
	}
}

void CInvokerDlg::OnBnClickedBtnOpenexplorer()
{
	// TODO: 在此添加控件通知处理程序代码
	int n = 0;
	
	// 修复注册表
	std::string exePath = getInstallDirection("HHRBAssistTool.exe");
	char pCmd[512] = { 0 };
	sprintf_s(pCmd, "%s%s", exePath.c_str(), "repair.bat");
	char arrBuf[1024] = { 0 };
	int outLen = 0;
	CreateCustomProgressAndGetResult(pCmd, arrBuf, 1024, outLen);
	_LOG(1, arrBuf);

	// 刷新桌面
	::PostMessage(GetDesktopWindow()->m_hWnd, WM_KEYDOWN, VK_F5, 0);
	SHChangeNotify(SHCNE_ASSOCCHANGED, SHCNF_FLUSH, NULL, NULL);

	// 打开桌面
	CreateCustomProgressAndGetResult("C:\\Windows\\explorer.exe",nullptr,0,n);
	CreateCustomProgressAndGetResult("C:\\Windows\\explorer.exe", nullptr, 0, n);
}

void CInvokerDlg::OnBnClickedBtnremoveexplorer()
{
	// TODO: 在此添加控件通知处理程序代码
	std::string exePath = getInstallDirection("HHRBAssistTool.exe");
	char pCmd[512] = { 0 };
	sprintf_s(pCmd, "%s%s", exePath.c_str(), "removeExplorer.bat");
	char arrBuf[1024] = { 0 };
	int outLen = 0;
	CreateCustomProgressAndGetResult(pCmd, arrBuf, 1024, outLen);
	_LOG(1, arrBuf);
	MessageBoxA(this->GetSafeHwnd(), "关闭操作系统桌面已设置，请关机重启！","提示",MB_OK);
}

HBRUSH CInvokerDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	if (IDC_STATIC_HINT == pWnd->GetDlgCtrlID())
	{
		if (TRUE == m_isPwdRight)
		{
			pDC->SetTextColor(RGB(51, 153, 255));	//蓝色
		}
		else
		{
			pDC->SetTextColor(RGB(255, 0, 0));	//红色		
		}
	}

	return hbr;
}


void CInvokerDlg::OnBnClickedPwdCheck()
{
	// TODO:  在此添加控件通知处理程序代码
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
		SetDlgItemText(IDC_STATIC_HINT,CString("请输入有效的密码！"));
		m_isPwdRight = false;
	}
	else 
	{
		m_isPwdRight = true;
		m_btnOpenExplorer.EnableWindow(TRUE);
		btn_repairExplorer.EnableWindow(TRUE);
		m_editPwd.EnableWindow(FALSE);
		m_btnCheck.EnableWindow(FALSE);
		SetDlgItemText(IDC_STATIC_HINT, CString("密码验证通过！"));
	}
	UpdateData(FALSE);
	Invalidate(TRUE);
}


BOOL CInvokerDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN&&pMsg->wParam == VK_RETURN)
		return TRUE;
	if (pMsg->message == WM_KEYDOWN&&pMsg->wParam == VK_ESCAPE)
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}
