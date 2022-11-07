#include <Windows.h>
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
#include <wtsapi32.h>
#include <userenv.h>
#include <vector>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"

using namespace std;
#include <assert.h>

#include "easylogging++.h"

INITIALIZE_EASYLOGGINGPP

typedef struct tagWNDINFO
{
    DWORD dwProcessId;
    HWND hWnd;
} WNDINFO, *LPWNDINFO;

/*wstring is converted to string*/
std::string t_ws2str_wcstombs_s(const wstring& wstr)
{
    size_t convertedChars = 0;
    string curLocale = setlocale(LC_ALL, NULL);				//curLocale="C"
    setlocale(LC_ALL, "chs");

    const wchar_t* source = wstr.c_str();
    size_t charNum = sizeof(wchar_t) * wstr.size() + 1;
    char* dest = new char[charNum];
    wcstombs_s(&convertedChars, dest, charNum, source, _TRUNCATE);
    string result = dest;
    delete[] dest;
    setlocale(LC_ALL, curLocale.c_str());
    return result;
}

/*get process ID according process name.*/
unsigned long GetProcessID(const std::vector<std::string>& mornitoredProcess)
{
    DWORD dwProcessID = 0;
    HANDLE hProcessSnap = NULL;
    PROCESSENTRY32 pe32 = { 0 };
    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (INVALID_HANDLE_VALUE == hProcessSnap)
    {
        return 0;
    }
    pe32.dwSize = sizeof(PROCESSENTRY32);
    if (Process32First(hProcessSnap, &pe32))
    {
        bool isFinded = false;
        do
        {
            string processingList = t_ws2str_wcstombs_s(pe32.szExeFile);
            for (int i = 0; i < mornitoredProcess.size(); i++) {
                if (_stricmp(processingList.c_str(), mornitoredProcess[i].c_str()) == 0)
                {
                    isFinded = true;
                    dwProcessID = pe32.th32ProcessID;
                    CloseHandle(hProcessSnap);
                    hProcessSnap = NULL;
                    break;
                }
            }
       
            if (isFinded) {
                break;
            }
        } while (Process32Next(hProcessSnap, &pe32));
    }
    if (hProcessSnap)
    {
        CloseHandle(hProcessSnap);
        hProcessSnap = NULL;
    }
    return dwProcessID;
}
///////////////////////////////////////////////End...assist functions//////////////////////////////////////////

SERVICE_STATUS        g_ServiceStatus = {0};
SERVICE_STATUS_HANDLE g_StatusHandle = NULL;
HANDLE                g_ServiceStopEvent = INVALID_HANDLE_VALUE;

const int CheckInterval = 10000;

VOID WINAPI ServiceMain (DWORD argc, LPTSTR *argv);
VOID WINAPI ServiceCtrlHandler (DWORD);
DWORD WINAPI ServiceWorkerThread (LPVOID lpParam);
#define SERVICE_NAME  _T("HHRBAssist") // service name

#define APPPROCESSNAME "SPExpert.exe"
#define ASSISTPROCESSNAME "HHRBAssistTool.exe"


string getInstallDirection()
{
	char exepath[MAX_PATH] = { 0 };
	GetModuleFileNameA(NULL, exepath, MAX_PATH);

	std::string path(exepath);
	std::size_t botDirPos = path.find_last_of("\\");
	// get directory
	std::string dir = path.substr(0, botDirPos + 1);

	return dir;
}

int processMoniteredParse(std::vector<std::string>& arrCell)
{
	string dir = getInstallDirection();
	const char* json_file = "AssistConfig.json";
	dir.append(json_file);
	
    std::ifstream in(dir);
    if (!in.is_open()) {
        LOG(WARNING) << "fail to read json file: " << dir;
        return -1;
    }

    std::string json_content((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    in.close();

    rapidjson::Document dom;
    if (!dom.Parse(json_content.c_str()).HasParseError()) {
        if (dom.HasMember("process_monitered") && dom["process_monitered"].IsArray()) {
            const rapidjson::Value& arr = dom["process_monitered"];

            fprintf(stdout, "process_monitered: \n");
            for (size_t i = 0; i < arr.Size(); ++i) {
                arrCell.push_back(arr[i].GetString());
                LOG(INFO) << i+1<<"st"<<" Process in json list: " << arrCell[i].c_str();
            }
        }
    }
    else {
        LOG(WARNING) << "fail to parse json file" << dir;
        return -1;
    }
    return 0;
}



void rolloutHandler(const char* filename, std::size_t size) {
    // SHOULD NOT LOG ANYTHING HERE BECAUSE LOG FILE IS CLOSED!
    std::cout << "************** Rolling out [" << filename << "] because it reached [" << size << " bytes]" << std::endl;

    // BACK IT UP
    std::stringstream ss;
    ss << filename << ".bak";

    std::string newfilename = ss.str();
    std::remove(newfilename.c_str()); // remove old bak file
    std::rename(filename, ss.str().c_str());
}

int _tmain (int argc, TCHAR *argv[])
{

    el::Loggers::addFlag(el::LoggingFlag::StrictLogFileSizeCheck);
    el::Loggers::reconfigureAllLoggers(el::ConfigurationType::Filename, getInstallDirection() + "AssistService.log");
    el::Loggers::reconfigureAllLoggers(el::ConfigurationType::MaxLogFileSize, "4096000"); // about 4M

    // Configure loggers
    el::Loggers::reconfigureAllLoggers(el::ConfigurationType::Format, "%datetime %level (%thread) [%loc] %msg");

    el::Helpers::installPreRollOutCallback(rolloutHandler);

    LOG(INFO) << "---- Service starting ----";
    LOG(INFO) << "Main: Entry";

    SERVICE_TABLE_ENTRY ServiceTable[] = 
    {
        {SERVICE_NAME, (LPSERVICE_MAIN_FUNCTION) ServiceMain},
        {NULL, NULL}
    };

    if (StartServiceCtrlDispatcher(ServiceTable) == FALSE)
    {
        LOG(ERROR) << "Main: StartServiceCtrlDispatcher returned error";
       return GetLastError ();
    }

    LOG(INFO) <<  "Main: Exit";

    el::Helpers::uninstallPreRollOutCallback();
    return 0;
}


VOID WINAPI ServiceMain (DWORD argc, LPTSTR *argv)
{ 

    LOG(INFO) << "ServiceMain: Entry";
    DWORD Status = E_FAIL;

    g_StatusHandle = RegisterServiceCtrlHandler (SERVICE_NAME, ServiceCtrlHandler);
    if (g_StatusHandle == NULL) 
    {
        LOG(ERROR) << "ServiceMain: RegisterServiceCtrlHandler returned error";
        goto EXIT;
    }

    // Tell the service controller we are starting
    ZeroMemory (&g_ServiceStatus, sizeof (g_ServiceStatus));
    g_ServiceStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
    g_ServiceStatus.dwControlsAccepted = 0;
    g_ServiceStatus.dwCurrentState = SERVICE_START_PENDING;
    g_ServiceStatus.dwWin32ExitCode = 0;
    g_ServiceStatus.dwServiceSpecificExitCode = 0;
    g_ServiceStatus.dwCheckPoint = 0;

    if (SetServiceStatus (g_StatusHandle, &g_ServiceStatus) == FALSE) 
    {
        LOG(WARNING) << "ServiceMain: SetServiceStatus returned error";
    }

    /* 
     * Perform tasks neccesary to start the service here
     */
    LOG(INFO) << "ServiceMain: Performing Service Start Operations";

    // Create stop event to wait on later.
    g_ServiceStopEvent = CreateEvent (NULL, TRUE, FALSE, NULL);
    if (g_ServiceStopEvent == NULL) 
    {
        LOG(INFO) << "ServiceMain: CreateEvent(g_ServiceStopEvent) returned error";

        g_ServiceStatus.dwControlsAccepted = 0;
        g_ServiceStatus.dwCurrentState = SERVICE_STOPPED;
        g_ServiceStatus.dwWin32ExitCode = GetLastError();
        g_ServiceStatus.dwCheckPoint = 1;

        if (SetServiceStatus (g_StatusHandle, &g_ServiceStatus) == FALSE)
	    {
            LOG(ERROR) << "ServiceMain: SetServiceStatus returned error";
	    }
        goto EXIT; 
    }    

    // Tell the service controller we are started
    LOG(INFO) << "Tell the service controller we are started";

    g_ServiceStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP;
    g_ServiceStatus.dwCurrentState = SERVICE_RUNNING;
    g_ServiceStatus.dwWin32ExitCode = 0;
    g_ServiceStatus.dwCheckPoint = 0;

    if (SetServiceStatus (g_StatusHandle, &g_ServiceStatus) == FALSE)
    {
        LOG(WARNING) << "ServiceMain: SetServiceStatus returned error";
    }

    // Start the thread that will perform the main task of the service
    HANDLE hThread = CreateThread (NULL, 0, ServiceWorkerThread, NULL, 0, NULL);

    LOG(INFO) << "ServiceMain: Waiting for Worker Thread to complete";

    // Wait until our worker thread exits effectively signaling that the service needs to stop
    WaitForSingleObject (hThread, INFINITE);
    
    LOG(INFO) << "ServiceMain: Worker Thread Stop Event signaled";
    
    
    /* 
     * Perform any cleanup tasks
     */
    LOG(INFO) << "ServiceMain: Performing Cleanup Operations";

    CloseHandle (g_ServiceStopEvent);

    g_ServiceStatus.dwControlsAccepted = 0;
    g_ServiceStatus.dwCurrentState = SERVICE_STOPPED;
    g_ServiceStatus.dwWin32ExitCode = 0;
    g_ServiceStatus.dwCheckPoint = 3;

    if (SetServiceStatus (g_StatusHandle, &g_ServiceStatus) == FALSE)
    {
        LOG(WARNING) << "ServiceMain: SetServiceStatus returned error";
    }
    
EXIT:
    LOG(INFO) << "ServiceMain: Exit";

    return;
}


VOID WINAPI ServiceCtrlHandler (DWORD CtrlCode)
{
    LOG(INFO) <<  "ServiceCtrlHandler: Entry";

    switch (CtrlCode) 
	{
     case SERVICE_CONTROL_STOP :

         LOG(INFO) << "ServiceCtrlHandler: SERVICE_CONTROL_STOP Request";

        if (g_ServiceStatus.dwCurrentState != SERVICE_RUNNING)
           break;

        /* 
         * Perform tasks neccesary to stop the service here 
         */
        
        g_ServiceStatus.dwControlsAccepted = 0;
        g_ServiceStatus.dwCurrentState = SERVICE_STOP_PENDING;
        g_ServiceStatus.dwWin32ExitCode = 0;
        g_ServiceStatus.dwCheckPoint = 4;

        if (SetServiceStatus (g_StatusHandle, &g_ServiceStatus) == FALSE)
		{
            LOG(WARNING) << "ServiceCtrlHandler: SetServiceStatus returned error";
		}

        // This will signal the worker thread to start shutting down
        SetEvent (g_ServiceStopEvent);

        break;

     default:
         break;
    }

    LOG(INFO) << "ServiceCtrlHandler: Exit";
}



bool StartPrcess(std::string strProcessName)
{
	SHELLEXECUTEINFOA shellInfo;
	memset(&shellInfo, 0, sizeof(SHELLEXECUTEINFO));
	shellInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	shellInfo.fMask = NULL;
	shellInfo.hwnd = NULL;
	shellInfo.lpVerb = NULL;
	shellInfo.lpFile = strProcessName.c_str();         // 执行的程序名(绝对路径)
	shellInfo.lpParameters = NULL;
	shellInfo.lpDirectory = NULL;
	shellInfo.nShow = SW_HIDE;                      //SW_SHOWNORMAL 全屏显示这个程序
	shellInfo.hInstApp = NULL;
	printf("程序自动重启中.... \n");
	ShellExecuteExA(&shellInfo);

	return true;
}



wchar_t* c2w(const char *str)
{
	size_t length = strlen(str) + 1;
	wchar_t *t = (wchar_t*)malloc(sizeof(wchar_t)*length);
	memset(t, 0, length*sizeof(wchar_t));
	MultiByteToWideChar(CP_ACP, 0, str, (int)strlen(str), t, (int)length);
	return t;
}

static BOOL CALLBACK EnumProc(HWND hWnd, LPARAM lParam)
{
	DWORD dwProcessId;
	GetWindowThreadProcessId(hWnd, &dwProcessId);
	LPWNDINFO pInfo = (LPWNDINFO)lParam;

	if (dwProcessId == pInfo->dwProcessId)
	{
		pInfo->hWnd = hWnd;
		return FALSE;
	}
	return TRUE;
}

void startProcess(char* appPath) {

	DWORD dwSessionID = WTSGetActiveConsoleSessionId();
	HANDLE hToken = NULL;
	HANDLE hTokenDup = NULL;
	LPVOID pEnv = NULL;
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	LOG(INFO) <<  "active console SessionID = " << dwSessionID;

	//获取当前处于活动状态用户的Token
	if (!WTSQueryUserToken(dwSessionID, &hToken))
	{
		DWORD nCode = GetLastError();
		LOG(ERROR) <<  "nCode" << nCode;

		CloseHandle(hToken);
		return;
	}

	//复制新的Token
	if (!DuplicateTokenEx(hToken, MAXIMUM_ALLOWED, NULL, SecurityIdentification, TokenPrimary, &hTokenDup))
	{
		DWORD nCode = GetLastError();
        LOG(ERROR) << "DuplicateTokenEx nCode=" << nCode;

		CloseHandle(hToken);
		return;
	}

	LOG(INFO) <<  "DuplicateToken sucessfully";

	//创建环境信息
	if (!CreateEnvironmentBlock(&pEnv, hTokenDup, FALSE))
	{
		DWORD nCode = GetLastError();
        LOG(INFO) << "CreateEnvironmentBlock nCode=" << nCode;

		CloseHandle(hTokenDup);
		CloseHandle(hToken);
		return;
	}

	LOG(INFO) <<  "CreateEnvironmentBlock sucessfully";

	//设置启动参数
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	si.lpDesktop = _TEXT("winsta0\\default");

	ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));

	//开始创建进程
	DWORD dwCreateFlag = NORMAL_PRIORITY_CLASS | CREATE_NEW_CONSOLE | CREATE_UNICODE_ENVIRONMENT;
	if (!CreateProcessAsUser(hTokenDup, c2w(appPath), NULL, NULL, NULL, FALSE, dwCreateFlag, pEnv, NULL, &si, &pi))
	{
		DWORD nCode = GetLastError();
		LOG(INFO) <<  "CreateProcessAsUser LastError Code= " << nCode;

		DestroyEnvironmentBlock(pEnv);
		CloseHandle(hTokenDup);
		CloseHandle(hToken);
		return;
	}
	LOG(INFO) <<  "CreateProcessAsUser sucessfully";

	WNDINFO wi;
	wi.dwProcessId = pi.dwProcessId;
	wi.hWnd = NULL;
	EnumWindows(EnumProc, (LPARAM)&wi);
	::SetWindowPos(wi.hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);

	//附加操作,回收资源
    LOG(INFO) << "process started ..." << appPath;

	DestroyEnvironmentBlock(pEnv);
	CloseHandle(hTokenDup);
	CloseHandle(hToken);
}

static void invokerAssistTool()
{
	std::string exePath = getInstallDirection();
	char pCmd[512] = { 0 };
	sprintf_s(pCmd, "%s%s", exePath.c_str(), ASSISTPROCESSNAME);
    LOG(INFO) << "invoke AssistTool " << pCmd;
	startProcess(pCmd);
}



DWORD WINAPI ServiceWorkerThread (LPVOID lpParam)
{
    std::vector<std::string> monitoredProcess;
    processMoniteredParse(monitoredProcess);
    std::vector<std::string> monitoringProcess;
    monitoringProcess.push_back(ASSISTPROCESSNAME);

    LOG(INFO) <<  "ServiceWorkerThread: Entry";

    int nCount = 0;
    //  Periodically check if the service has been requested to stop
    while (WaitForSingleObject(g_ServiceStopEvent, CheckInterval) != WAIT_OBJECT_0)
    {        
        /* 
         * Perform main service function here
         */

        if (GetProcessID(monitoredProcess) > 0) {
            // LOG(INFO) << "ServiceWorkerThread：find the process " << APPPROCESSNAME;
            continue;
        }
        else {
            if (GetProcessID(monitoringProcess) == 0)
            {
                invokerAssistTool();
            }
            else
            {
                //LOG(INFO) << APPPROCESSNAME << " is existing.";
            }
        }
    }

    LOG(INFO) << "ServiceWorkerThread: Exit";

    return ERROR_SUCCESS;
}