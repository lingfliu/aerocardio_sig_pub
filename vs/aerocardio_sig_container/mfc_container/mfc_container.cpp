
// mfc_container.cpp: 定义应用程序的类行为。
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "mfc_container.h"
#include "MainFrm.h"

#include "ChildFrm.h"
#include "mfc_containerDoc.h"
#include "mfc_containerView.h"


//header for lib and mocks
#include "aerocardio_sig_libwin32.h"
#include <Windows.h>
#include <process.h>
#include <sys\timeb.h>
#include <iostream>
using std::cout;
using std::endl;
#include <fstream>
using std::fstream;
using std::ofstream;
using std::ifstream;
using std::ios;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CmfccontainerApp

BEGIN_MESSAGE_MAP(CmfccontainerApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CmfccontainerApp::OnAppAbout)
	// 基于文件的标准文档命令
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	// 标准打印设置命令
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
END_MESSAGE_MAP()


// CmfccontainerApp 构造

CmfccontainerApp::CmfccontainerApp()
{
	m_bHiColorIcons = TRUE;

	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// 如果应用程序是利用公共语言运行时支持(/clr)构建的，则: 
	//     1) 必须有此附加设置，“重新启动管理器”支持才能正常工作。
	//     2) 在您的项目中，您必须按照生成顺序向 System.Windows.Forms 添加引用。
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: 将以下应用程序 ID 字符串替换为唯一的 ID 字符串；建议的字符串格式
	//为 CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("mfccontainer.AppID.NoVersion"));

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}

// 唯一的 CmfccontainerApp 对象

CmfccontainerApp theApp;



static unsigned int __stdcall stream_file_demo(LPVOID p);
static unsigned int thrdMockId = 1001;

void onEcgRawReceived(UTKMEcg *ecg);
void onEcgFilteredReceived(UTKMEcg *ecg);
void onEcgMarkReceived(UTKMEcgMark *mark);
void onERIRawReceived(UTKMERI *eri);
void onByte2Device(unsigned char* bytes, int byteLen);
__int64 currentTimeInMilli();
static ofstream raw_ecg_fid;
static ofstream filtered_ecg_fid;

// mocks

// CmfccontainerApp 初始化
BOOL CmfccontainerApp::InitInstance()
{
	//Lib initialization
	//initFeComm();
	//int res = setDeviceModel(5);
	//startWork();
	//regCbOnEcgRawReceived(onEcgRawReceived);
	//regCbOnEcgFilteredReceived(onEcgFilteredReceived);
	//regCbOnEcgMarkReceived(onEcgMarkReceived);
	//regCbOnByte2Device(onByte2Device);
	//raw_ecg_fid.open("D:\\github\\aerocardio_sig\\vs\\aerocardio_sig_libwin32\\Debug\\raw_ecg.txt", ios::out);
	//filtered_ecg_fid.open("D:\\github\\aerocardio_sig\\vs\\aerocardio_sig_libwin32\\Debug\\filtered_ecg.txt", ios::out);
	//HANDLE thrdMock = (HANDLE) _beginthreadex(NULL, 0, msg_mock, NULL, 0, &thrdMockId);
	//HANDLE thrdMock = (HANDLE)_beginthreadex(NULL, 0, stream_file_demo, NULL, 0, &thrdMockId);

	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。  否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();


	// 初始化 OLE 库
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction();

	// 使用 RichEdit 控件需要 AfxInitRichEdit2()
	// AfxInitRichEdit2();

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));
	LoadStdProfileSettings(4);  // 加载标准 INI 文件选项(包括 MRU)


	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// 注册应用程序的文档模板。  文档模板
	// 将用作文档、框架窗口和视图之间的连接
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_mfccontainerTYPE,
		RUNTIME_CLASS(CmfccontainerDoc),
		RUNTIME_CLASS(CChildFrame), // 自定义 MDI 子框架
		RUNTIME_CLASS(CmfccontainerView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	// 创建主 MDI 框架窗口
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
		delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd = pMainFrame;


	// 分析标准 shell 命令、DDE、打开文件操作的命令行
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);



	// 调度在命令行中指定的命令。  如果
	// 用 /RegServer、/Register、/Unregserver 或 /Unregister 启动应用程序，则返回 FALSE。
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	// 主窗口已初始化，因此显示它并对其进行更新
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}


unsigned int __stdcall stream_file_demo(LPVOID p) {
	ifstream fid("byte_raw_correct.dat", ios::binary);
	if (!fid) {
		cout << "failed to read file." << endl;
		return 0;
	}
	char buff[139];
	int len = 139;
	while (true) {
		Sleep(20);
		fid.read(buff, len);
		if (fid) {
			len = 139;
			putBytes((unsigned char*)buff, len);
		}
		else {
			len = fid.gcount();
			if (len > 0) {
				putBytes((unsigned char*)buff, len);
			}
			break;
		}
	}
	cout << "finished reading file" << endl;

	fid.close();
	raw_ecg_fid.close();
	filtered_ecg_fid.close();

	stopWork();
	//Sleep(100);
	//destroyFeComm();
	return 0;
}


void onByte2Device(unsigned char* bytes, int byteLen) {
	//cout << "console: bytes out, len = " << byteLen << endl;
}

void onERIRawReceived(UTKMERI *eri) {
	//cout << "console: received raw eri, time = " << eri->startTime << endl;
	delete eri;
}
void onEcgMarkReceived(UTKMEcgMark *mark) {
	cout << "console: received ecg mark, type = " << mark->type << " value = " << mark->val << endl;
	delete mark;
}

void onEcgRawReceived(UTKMEcg* ecg) {
	//cout << "console: received raw ecg, time = " << ecg->startTime << endl;
	for (int m = 0; m < ecg->dataLen; m++) {
		raw_ecg_fid << ecg->data[m] << endl;
	}
	delete ecg;
}

void onEcgFilteredReceived(UTKMEcg *ecg) {
	//cout << "console: received filtered ecg, time = " << ecg->startTime << endl;

	for (int m = 0; m < ecg->dataLen; m++) {
		filtered_ecg_fid << ecg->data[m] << endl;
	}

	delete ecg;
}
__int64 currentTimeInMilli() {
	timeb t;
	ftime(&t);
	return t.time * 1000 + t.millitm;
}

int CmfccontainerApp::ExitInstance()
{
	//TODO: 处理可能已添加的附加资源
	AfxOleTerm(FALSE);

	return CWinAppEx::ExitInstance();
}

// CmfccontainerApp 消息处理程序


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// 用于运行对话框的应用程序命令
void CmfccontainerApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CmfccontainerApp 自定义加载/保存方法

void CmfccontainerApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
	bNameValid = strName.LoadString(IDS_EXPLORER);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EXPLORER);
}

void CmfccontainerApp::LoadCustomState()
{
}

void CmfccontainerApp::SaveCustomState()
{
}

// CmfccontainerApp 消息处理程序



