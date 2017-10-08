#ifndef APP_MAIN_H
#define APP_MAIN_H


#include "AppCore.h"
#include "AppEvent.h"
#include "UICore.h"
#include "Graphics.h"
#include "Style.h"
#include "MainWindow.h"
#include "Menu.h"
#include "TaskTray.h"
#include "MainPanel.h"
#include "Epg.h"
#include "Accelerator.h"
#include "Controller.h"
#include "NetworkDefinition.h"
#include "TSProcessorManager.h"
#include "OptionDialog.h"
#include "GeneralOptions.h"
#include "ViewOptions.h"
#include "OSDOptions.h"
#include "StatusOptions.h"
#include "SideBarOptions.h"
#include "MenuOptions.h"
#include "PanelOptions.h"
#include "ColorSchemeOptions.h"
#include "OperationOptions.h"
#include "DriverOptions.h"
#include "VideoOptions.h"
#include "AudioOptions.h"
#include "PlaybackOptions.h"
#include "RecordOptions.h"
#include "CaptureOptions.h"
#include "ChannelScan.h"
#include "EpgOptions.h"
#include "ProgramGuideOptions.h"
#include "TSProcessorOptions.h"
#include "TaskbarOptions.h"
#include "VideoDecoderOptions.h"
#include "Plugin.h"
#include "Logger.h"
#include "CommandLine.h"
#include "ChannelHistory.h"
#include "Favorites.h"
#include "FeaturedEvents.h"
#include "Help.h"
#include "StreamInfo.h"
#include "HomeDisplay.h"
#include "ChannelDisplay.h"
#include "Taskbar.h"
#include "ZoomOptions.h"
#include "PanAndScanOptions.h"
#include "AudioManager.h"
#include "LogoManager.h"
#include "EpgCapture.h"
#include "KeywordSearch.h"
#include "VariableManager.h"
#ifndef _DEBUG
#include "DebugHelper.h"
#endif


class CTotTimeAdjuster
{
	bool m_fEnable;
	DWORD m_TimeOut;
	DWORD m_StartTime;
	SYSTEMTIME m_PrevTime;

public:
	CTotTimeAdjuster()
		: m_fEnable(false)
	{
	}
	bool BeginAdjust(DWORD TimeOut = 10000UL);
	bool AdjustTime();
};

class CEpgLoadEventHandler
	: public TVTest::CEpgDataStore::CEventHandler
	, public CEpgOptions::CEDCBDataLoadEventHandler
{
// CEpgDataStore::CEventHandler
	void OnBeginLoading() override;
	void OnEndLoading(bool fSuccess) override;

// CEDCBDataLoadEventHandler
	void OnStart() override;
	void OnEnd(bool fSuccess, LibISDB::EPGDatabase *pEPGDatabase) override;
};

class CServiceUpdateInfo
{
public:
	LibISDB::AnalyzerFilter::ServiceList m_ServiceList;
	int m_CurService;
	WORD m_NetworkID;
	WORD m_TransportStreamID;
	bool m_fStreamChanged;
	bool m_fServiceListEmpty;

	CServiceUpdateInfo(LibISDB::TSEngine *pEngine, LibISDB::AnalyzerFilter *pAnalyzer);
};


class CAppMain
{
public:
	static const UINT WM_INTERPROCESS = WM_COPYDATA;
	static const UINT PROCESS_MESSAGE_EXECUTE = 0x54565400;

#ifndef _DEBUG
	static CDebugHelper DebugHelper;
#endif

	CAppCore Core;
	TVTest::CAppEventManager AppEventManager;
	CCoreEngine CoreEngine;
	CUICore UICore;
	CLogger Logger;
	TVTest::Graphics::CGraphicsCore GraphicsCore;
	TVTest::Style::CStyleManager StyleManager;
	TVTest::CDirectWriteSystem DirectWriteSystem;
	CMainMenu MainMenu;
	CCommandList CommandList;
	CCommandLineOptions CmdLineOptions;
	CPluginManager PluginManager;
	LibISDB::EPGDatabase EPGDatabase;
	CMainWindow MainWindow;
	CStatusView StatusView;
	CSideBar SideBar;
	CMainPanel Panel;
	CHtmlHelp HtmlHelpClass;
	CChannelMenu ChannelMenu;
	CIconMenu AspectRatioIconMenu;
	CTaskbarManager TaskbarManager;
	TVTest::CTaskTrayManager TaskTrayManager;
	CEventSearchOptions EventSearchOptions;
	CHomeDisplay HomeDisplay;
	CChannelDisplay ChannelDisplay;
	CBalloonTip NotifyBalloonTip;
	CTotTimeAdjuster TotTimeAdjuster;

	TVTest::CNetworkDefinition NetworkDefinition;
	CChannelManager ChannelManager;

	CDriverManager DriverManager;
	TVTest::CTSProcessorManager TSProcessorManager;
	TVTest::CAudioManager AudioManager;
	CLogoManager LogoManager;
	TVTest::CEpgCaptureManager EpgCaptureManager;

	TVTest::CEpg Epg;

	CStreamInfo StreamInfo;
	CCaptureWindow CaptureWindow;

	CZoomOptions ZoomOptions;
	CPanAndScanOptions PanAndScanOptions;
	CGeneralOptions GeneralOptions;
	CViewOptions ViewOptions;
	COSDOptions OSDOptions;
	COSDManager OSDManager;
	CStatusOptions StatusOptions;
	CSideBarOptions SideBarOptions;
	CMenuOptions MenuOptions;
	CPanelOptions PanelOptions;
	CColorSchemeOptions ColorSchemeOptions;
	COperationOptions OperationOptions;
	CAccelerator Accelerator;
	CControllerManager ControllerManager;
	CDriverOptions DriverOptions;
	CVideoOptions VideoOptions;
	CAudioOptions AudioOptions;
	CPlaybackOptions PlaybackOptions;
	CRecordOptions RecordOptions;
	CRecordManager RecordManager;
	CCaptureOptions CaptureOptions;
	CChannelScan ChannelScan;
	CEpgOptions EpgOptions;
	CProgramGuideOptions ProgramGuideOptions;
	TVTest::CTSProcessorOptions TSProcessorOptions;
	CPluginOptions PluginOptions;
	CTaskbarOptions TaskbarOptions;
	CVideoDecoderOptions VideoDecoderOptions;
	CRecentChannelList RecentChannelList;
	CChannelHistory ChannelHistory;
	TVTest::CFavoritesManager FavoritesManager;
	TVTest::CFavoritesMenu FavoritesMenu;
	TVTest::CKeywordSearch KeywordSearch;
	CFeaturedEvents FeaturedEvents;
	TVTest::CVariableManager VariableManager;

	struct {
		int Space;
		int Channel;
		int ServiceID;
		int TransportStreamID;
		bool fAllChannels;
	} RestoreChannelInfo;

	CEpgLoadEventHandler EpgLoadEventHandler;

	CAppMain();
	~CAppMain();

	CAppMain(const CAppMain &) = delete;
	CAppMain &operator=(const CAppMain &) = delete;

	HINSTANCE GetInstance() const;
	HINSTANCE GetResourceInstance() const;
	bool GetAppFilePath(TVTest::String *pPath) const;
	bool GetAppDirectory(TVTest::String *pDirectory) const;
	bool GetAppDirectory(LPTSTR pszDirectory) const;
	LPCTSTR GetIniFileName() const { return m_IniFileName.c_str(); }
	LPCTSTR GetFavoritesFileName() const { return m_FavoritesFileName.c_str(); }
	void AddLog(CLogItem::LogType Type, LPCTSTR pszText, ...);
	void AddLog(LPCTSTR pszText, ...);
	bool IsFirstExecute() const;
	int Main(HINSTANCE hInstance, LPCTSTR pszCmdLine, int nCmdShow);
	void Initialize();
	void Finalize();
	void Exit();
	bool LoadSettings();
	enum {
		SETTINGS_SAVE_STATUS  = 0x0001U,
		SETTINGS_SAVE_OPTIONS = 0x0002U,
		SETTINGS_SAVE_ALL     = SETTINGS_SAVE_STATUS | SETTINGS_SAVE_OPTIONS
	};
	bool SaveSettings(unsigned int Flags);
	bool ShowOptionDialog(HWND hwndOwner, int StartPage = -1);
	enum class CreateDirectoryResult {
		Success,
		Error,
		Cancelled,
		NoPath,
	};
	CreateDirectoryResult CreateDirectory(HWND hwnd, LPCTSTR pszDirectory, LPCTSTR pszMessage);
	bool SendInterprocessMessage(HWND hwnd, UINT Message, const void *pParam, DWORD ParamSize);
	LRESULT ReceiveInterprocessMessage(HWND hwnd, WPARAM wParam, LPARAM lParam);
	bool BroadcastControllerFocusMessage(
		HWND hwnd, bool fSkipSelf, bool fFocus, DWORD ActiveThreadID = 0);
	void SetEnablePlaybackOnStart(bool fEnable) { m_fEnablePlaybackOnStart = fEnable; }
	bool GetEnablePlaybackOnStart() const { return m_fEnablePlaybackOnStart; }

	static HICON GetAppIcon();
	static HICON GetAppIconSmall();

private:
	class CEngineEventListener
		: public CCoreEngine::EventListener
	{
	public:
		CEngineEventListener(CAppMain &App);

	private:
		CAppMain &m_App;

		// CCoreEngine::EventListener
		void OnServiceChanged(uint16_t ServiceID) override;
		void OnPATUpdated(LibISDB::AnalyzerFilter *pAnalyzer, bool StreamChanged) override;
		void OnPMTUpdated(LibISDB::AnalyzerFilter *pAnalyzer, uint16_t ServiceID) override;
		void OnSDTUpdated(LibISDB::AnalyzerFilter *pAnalyzer) override;
		void OnWriteError(LibISDB::RecorderFilter *pRecorder) override;
		void OnVideoStreamTypeChanged(uint8_t VideoStreamType) override;
		void OnVideoSizeChanged(LibISDB::ViewerFilter *pViewer) override;
		void OnEventChanged(LibISDB::AnalyzerFilter *pAnalyzer, uint16_t EventID) override;
		void OnEventUpdated(LibISDB::AnalyzerFilter *pAnalyzer) override;
		void OnTOTUpdated(LibISDB::AnalyzerFilter *pAnalyzer) override;
		void OnFilterGraphInitialize(LibISDB::ViewerFilter *pViewer, IGraphBuilder *pGraphBuilder) override;
		void OnFilterGraphInitialized(LibISDB::ViewerFilter *pViewer, IGraphBuilder *pGraphBuilder) override;
		void OnFilterGraphFinalize(LibISDB::ViewerFilter *pViewer, IGraphBuilder *pGraphBuilder) override;
		void OnFilterGraphFinalized(LibISDB::ViewerFilter *pViewer, IGraphBuilder *pGraphBuilder) override;
		void OnSPDIFPassthroughError(LibISDB::ViewerFilter *pViewer, HRESULT hr) override;

		// CEngineEventListener
		void OnServiceUpdated(LibISDB::AnalyzerFilter *pAnalyzer, bool fListUpdated, bool fStreamChanged);
		void OnServiceInfoUpdated(LibISDB::AnalyzerFilter *pAnalyzer);
	};

	class CStreamInfoEventHandler
		: public CStreamInfo::CEventHandler
	{
	public:
		CStreamInfoEventHandler(CAppMain &App);

	private:
		CAppMain &m_App;

		void OnRestoreSettings() override;
		bool OnClose() override;
	};

	class CCaptureWindowEventHandler
		: public CCaptureWindow::CEventHandler
	{
	public:
		CCaptureWindowEventHandler(CAppMain &App);

	private:
		CAppMain &m_App;

		void OnRestoreSettings() override;
		bool OnClose() override;
		bool OnSave(CCaptureImage *pImage) override;
		bool OnKeyDown(UINT KeyCode, UINT Flags) override;
	};

	struct ControllerFocusInfo {
		HWND hwnd;
		bool fSkipSelf;
		bool fFocus;
	};

	HINSTANCE m_hInst;
	TVTest::CFilePath m_IniFileName;
	TVTest::CFilePath m_FavoritesFileName;
	CSettings m_Settings;
	bool m_fFirstExecute;
	bool m_fInitialSettings;
	CEngineEventListener m_EngineEventListener;
	CStreamInfoEventHandler m_StreamInfoEventHandler;
	CCaptureWindowEventHandler m_CaptureWindowEventHandler;
	COptionDialog m_OptionDialog;
	unsigned int m_ExitTimeout;
	bool m_fEnablePlaybackOnStart;
	bool m_fIncrementNetworkPort;

	static HICON m_hicoApp;
	static HICON m_hicoAppSmall;

	void RegisterCommands();
	bool IsNoAcceleratorMessage(const MSG *pmsg);
	void ApplyEventInfoFont();
	bool GetAbsolutePath(LPCTSTR pszPath, LPTSTR pszAbsolutePath) const;
	bool ProcessCommandLine(LPCTSTR pszCmdLine);
	void ShowProgramGuideByCommandLine(const CCommandLineOptions &CmdLine);
	static BOOL CALLBACK ControllerFocusCallback(HWND hwnd, LPARAM Param);
};


CAppMain &GetAppClass();


#endif
