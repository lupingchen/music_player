
// MP3_1Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MP3_1.h"
#include "MP3_1Dlg.h"
#include "afxdialogex.h"
#include "Digitalv.h"
#pragma comment(lib, "WINMM.LIB")


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CMP3_1Dlg 对话框

//构造函数

CMP3_1Dlg::CMP3_1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMP3_1Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	iMinute=0;
	iSecond=0;
	m_DeviceID=0;  
	m_ElementID=0;  
	isBegin=FALSE;
	isPlay=FALSE;
	playlistnum=-1;//-1表示当前没有播放
	nflag=-1;      //-1表示当前列表没有歌曲
}

void CMP3_1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, my_ListCtrl);
	DDX_Control(pDX, IDC_EDIT2, my_edit1);
	DDX_Control(pDX, IDC_EDIT3, my_edit2);
	DDX_Control(pDX, IDC_SLIDER2, my_SliderCtrlTime);
	DDX_Control(pDX, IDC_SLIDER1, my_SliderCtrlVoice);
}

BEGIN_MESSAGE_MAP(CMP3_1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	ON_BN_CLICKED(IDC_BUTTON_MIN, &CMP3_1Dlg::OnBnClickedButtonMin)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CMP3_1Dlg::OnBnClickedButtonClose)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_BUTTON_ADDSONG, &CMP3_1Dlg::OnBnClickedButtonAddsong)
	ON_BN_CLICKED(IDC_BUTTON12, &CMP3_1Dlg::OnBnClickedButton12)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST2, &CMP3_1Dlg::OnNMDblclkList2)
	ON_BN_CLICKED(IDC_BUTTON11, &CMP3_1Dlg::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON13, &CMP3_1Dlg::OnBnClickedButton13)
	ON_BN_CLICKED(IDC_BUTTON1, &CMP3_1Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON10, &CMP3_1Dlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON9, &CMP3_1Dlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON2, &CMP3_1Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMP3_1Dlg::OnBnClickedButton3)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CMP3_1Dlg 消息处理程序

BOOL CMP3_1Dlg::OnInitDialog()
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	InitDevice();
	InitCtrlLiat();
	InitControls();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMP3_1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMP3_1Dlg::OnPaint()
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
HCURSOR CMP3_1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BEGIN_EVENTSINK_MAP(CMP3_1Dlg, CDialogEx)

END_EVENTSINK_MAP()


bool fileTimeToString(/*__in */FILETIME ftFileTime, /*__out */CString& tmp)
{
	bool rc = false;
	CTime time(ftFileTime);//先把FILETIME类型的数据转换为CTime类型
	tmp.Format(L"%d年%d月%d日 %d点%d分%d秒",time.GetYear(),time.GetMonth(),time.GetDay(),time.GetHour(),time.GetMinute(),time.GetSecond());
	//再将CTime类型转换为CTime类型
	CString fileWriteTime(tmp);//为了能把字符串连接起来，用CString val（）的方法声明
	rc = true;

	return rc;
}
//初始化播放列表
void CMP3_1Dlg::InitCtrlLiat()
{
	DWORD dwStyle;
	dwStyle = my_ListCtrl.GetStyle();
	dwStyle |= LVS_EX_GRIDLINES |LVS_EX_FULLROWSELECT|LVS_SHOWSELALWAYS ;
	my_ListCtrl.SetExtendedStyle(dwStyle);
	my_ListCtrl.InsertColumn(0,_T("名字"),LVCFMT_LEFT,50,-1);
	my_ListCtrl.InsertColumn(1,_T("大小"),LVCFMT_LEFT,50,-1);
	my_ListCtrl.InsertColumn(2,_T("时间"),LVCFMT_LEFT,120,-1);
	my_ListCtrl.InsertColumn(3,_T("路径"),LVCFMT_LEFT,120,-1);
}
//初始化设备
DWORD CMP3_1Dlg::InitDevice()  
{  
	DWORD dwResult = 0;  
	if (m_DeviceID == 0)  
	{  
		MCI_OPEN_PARMS mciInitParms;  
		mciInitParms.lpstrDeviceType = (LPTSTR)MCI_DEVTYPE_WAVEFORM_AUDIO;  
		dwResult = mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_TYPE_ID | MCI_WAIT,   
			(DWORD)(LPVOID)&mciInitParms);  
		m_DeviceID = mciInitParms.wDeviceID;  
	}  
	return dwResult;  
}
//控件的初始化函数   
void CMP3_1Dlg::InitControls()
{
	my_SliderCtrlTime.SetPos(0);      //初始化播放进度控件滑块值
	my_SliderCtrlVoice.SetRange(0,100); //设置音量控件的范围
	my_SliderCtrlVoice.SetPos(0);      //初始化音量控件滑块值
	CString str;
	str.Format(TEXT("%d:%d"),iMinute,iSecond);
	SetDlgItemText(IDC_EDIT3,str);
	UpdateData(TRUE);
}

void CMP3_1Dlg::SetVolume(int Vol)        //设置音量大小函数
{
	MCI_DGV_SETAUDIO_PARMS mciSetAudioPara; //设置音量参数

	mciSetAudioPara.dwItem = MCI_DGV_SETAUDIO_VOLUME; 

	mciSetAudioPara.dwCallback = (DWORD_PTR)this->GetSafeHwnd();
	//设置音量大小
	mciSetAudioPara.dwValue = Vol * 10; //here is the value of the Volume(0--1000) 
	mciSendCommand(m_DeviceID, MCI_SETAUDIO, MCI_DGV_SETAUDIO_VALUE | MCI_DGV_SETAUDIO_ITEM, (DWORD)(LPVOID)&mciSetAudioPara);
}

void CMP3_1Dlg::ConvertTime(unsigned int time)        //转换时间函数
{
	iSecond = time / 1000;

	if (iSecond < 60)
	{
		iMinute = 0; 
		return ;
	}
	else {

		iMinute = iSecond / 60;

		iSecond = iSecond - iMinute * 60;
	}

}

void CMP3_1Dlg::UpdatePosition(void)     //更新播放位置
{
	MCI_STATUS_PARMS mciStatus;
	mciStatus.dwItem = MCI_STATUS_POSITION;
	mciSendCommand(m_DeviceID,MCI_STATUS,MCI_WAIT|MCI_STATUS_ITEM,(DWORD)(LPVOID)&mciStatus);

	int dCurrentPos = mciStatus.dwReturn;
	int sec = dCurrentPos / 1000; //获得文件的总秒数
	int min = sec / 60;           //将总秒数转换成 分钟

	sec = sec - min * 60;         //将总秒数转换成 秒数
	CString str;
	str.Format(TEXT("%d:%d"),min,sec);
	SetDlgItemText(IDC_EDIT2,str);
}

void CMP3_1Dlg::SetListCtrlData(vector<FILEINFO> &my_vector_file)
{
	//清空my_ListCtrl列表上的数据
	my_ListCtrl.DeleteAllItems();

	for(unsigned int i=0;i<my_vector_file.size();i++)
	{
		my_ListCtrl.InsertItem(i,(TCHAR *)my_vector_file[i].sFileName);
		char fileSize[10];
		sprintf_s(fileSize,"%d",my_vector_file[i].lFileSize);
		my_ListCtrl.SetItemText(i,1,(TCHAR *)fileSize);
		my_ListCtrl.SetItemText(i,2,my_vector_file[i].time);
		my_ListCtrl.SetItemText(i,3,my_vector_file[i].filePath);
	}
}

void CMP3_1Dlg::OnBnClickedButtonMin()
{
	// TODO: 在此添加控件通知处理程序代码
	//窗口最小化
	ShowWindow(SW_MINIMIZE);
}

void CMP3_1Dlg::OnBnClickedButtonClose()
{
	// TODO: 在此添加控件通知处理程序代码
	//退出程序
	//AfxGetMainWnd()->SendMessage(WM_CLOSE);
	if(IDOK==MessageBox(_T("Sure to quit?"),_T("isplay"),MB_OKCANCEL))
		//EndDialog(NULL);
			AfxGetMainWnd()->SendMessage(WM_CLOSE);
}

void CMP3_1Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM (point.x, point.y));
	CDialogEx::OnLButtonDown(nFlags, point);
}
//添加函数
void CMP3_1Dlg::OnBnClickedButtonAddsong()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog openFile(TRUE,_T("mp3"),_T("*.mp3"),OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,_T("mp3 Files (*.mp3)|*.mp3|All Files (*.*)|*.*||"),this);
	openFile.m_pOFN->lpstrTitle=_T("mp3 file");
	CString szMkvPath;
	if(openFile.DoModal()==IDOK)
	{
		szMkvPath = openFile.GetPathName();
		//szMkvPath.MakeUpper();
		FILEINFO info;
		WIN32_FIND_DATA findFileDate;
		HANDLE hFind=FindFirstFile(szMkvPath,&findFileDate);
		info.filePath=szMkvPath;
		strcpy_s(info.sFileName,(char*)findFileDate.cFileName);
		info.lFileSize=findFileDate.nFileSizeLow/1024;
		fileTimeToString(findFileDate.ftLastWriteTime,info.time);
		my_vector_file.push_back(info);
		nflag=my_vector_file.size();
		SetListCtrlData(my_vector_file);
	}
}

//播放函数
int CMP3_1Dlg::PlayFile(HWND hWnd,CString strFileName)
{
	if(0==nflag)
	{
		mciSendCommand(m_DeviceID,MCI_CLOSE, 0, NULL); //发送关闭命令
		isBegin=FALSE;
		isPlay=FALSE;
		MessageBox(_T("当前列表没有歌曲"));
		return 0;
	}
	//-------------------------------------------
	SetTimer(1,500,NULL); //初始化定时器，用于显示播放进度
	//----------------------------------------------------------
	isPlay=TRUE;
	MCI_OPEN_PARMS mciOpenParms;  //打开参数
	memset(&mciOpenParms, 0, sizeof(MCI_OPEN_PARMS));  
	mciOpenParms.lpstrElementName = strFileName;  
	mciSendCommand(m_DeviceID,MCI_CLOSE, 0, NULL); //发送关闭命令
	DWORD dwResult = 0;  
	dwResult = mciSendCommand(m_DeviceID, MCI_OPEN, MCI_OPEN_ELEMENT,  
		(DWORD)(LPVOID)&mciOpenParms);			   //发送打开命令
	if (!dwResult)  
	{  
		m_ElementID = mciOpenParms.wDeviceID;  

		MCI_PLAY_PARMS mciPlayParms;  
		mciPlayParms.dwCallback = (DWORD)hWnd;  
		dwResult = mciSendCommand(m_ElementID, MCI_PLAY, MCI_DGV_PLAY_REPEAT/*MCI_NOTIFY*/,   
			(DWORD)(LPVOID)&mciPlayParms);  
	}  

	//-------------------------------------------------
	
	//声明文件信息的结构体
	MCI_STATUS_PARMS mciStatus;

	mciStatus.dwItem = MCI_STATUS_LENGTH ; //得到文件的播放长度

	mciSendCommand(m_DeviceID,MCI_STATUS,MCI_WAIT |  MCI_STATUS_ITEM,(DWORD)(LPVOID)&mciStatus);

	//MCI_STATUS_ITEM 表示MCI_STATUS_PARMS的dwItem有效
	//mciSendCommand发送MCI_STATUS命令获得MIC_STATUS_LENGTH信息，并将信息保存在变量mciStatus中。
	//得到媒体的播放长度
	m_Length = mciStatus.dwReturn ;

	//打开文件后初始化各个控件的数值

	my_SliderCtrlTime.SetRange(0,m_Length); //设置播放进度控件的范围
	my_SliderCtrlTime.SetPos(0);            //初始化播放进度控件的滑块位置

	my_SliderCtrlVoice.SetPos(50);            //初始化音量控件的滑块位置

	// 设置音量编辑框的数值
	//CString temp;
	//temp.Format(TEXT("%d"),50);
	//this->SetDlgItemText(IDC_EDITVOL,temp);

	SetVolume(50);               //设置音频的初始音量大小

	
	ConvertTime(m_Length); //将获得音频长度转换成 分和秒的格式
	CString str;
	str.Format(TEXT("%d:%d"),iMinute,iSecond);
	SetDlgItemText(IDC_EDIT3,str);

	UpdateData(TRUE);

	//return dwResult;
	return 1;
}
//播放按钮
void CMP3_1Dlg::OnBnClickedButton12()   
{
	// TODO: 在此添加控件通知处理程序代码
	//判断isBegin是否第一次打开播放
	if(FALSE==isBegin)
	{
		isBegin=TRUE;
		int row=my_ListCtrl.GetSelectionMark();
		if(row<0||row>=nflag)
		{
			MessageBox(_T("当前列表没有歌曲"));
			return ;
		}
		CString strPath=my_vector_file[row].filePath;
		playlistnum=row;
		PlayFile(this->m_hWnd,strPath);
	}
	else
	{
		//判断isPlay是否为播放状态
		if(isPlay)
		{
			MCI_GENERIC_PARMS mciPause; //mci暂停参数
			//发送暂停命令
			mciSendCommand(m_DeviceID,MCI_PAUSE,0,(DWORD)(LPVOID)&mciPause);   //暂停
			//mciSendCommand(m_DeviceID, MCI_PAUSE, MCI_WAIT, NULL);
			isPlay = FALSE;
		}
		else
		{
			MCI_PLAY_PARMS mciPlay;
			mciSendCommand(m_DeviceID,MCI_PLAY,0,(DWORD)(LPVOID)&mciPlay);	//暂停处播放
			//mciSendCommand(m_DeviceID, MCI_RESUME, MCI_WAIT, NULL); 	
			isPlay = TRUE;
		}
	}

}

//双击左键的控件函数
void CMP3_1Dlg::OnNMDblclkList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	if (my_ListCtrl.GetItemCount()>0)
	{
		isBegin=TRUE;
		int Row=my_ListCtrl.GetSelectionMark();
		if(Row!=-1)
		{
			playlistnum = Row;//把鼠标点击处赋给全局变量
			CString strpath=my_vector_file[Row].filePath;
			PlayFile(this->m_hWnd,strpath);			
		}
		else
		{		
			AfxMessageBox(TEXT("请选择正确的文件"),MB_ICONINFORMATION,NULL);
		}
	}
	else
	{
		AfxMessageBox(TEXT("你没有打开文件"),MB_ICONINFORMATION,NULL);
	}
	*pResult = 0;
}

//上一曲 函数
void CMP3_1Dlg::OnBnClickedButton11()   
{
	// TODO: 在此添加控件通知处理程序代码
	if(-1==playlistnum)
	{
		return ;
	}
	int num=my_ListCtrl.GetItemCount();
	if(playlistnum == 0)  //如果播放的歌是当前列的最后一个，则跳转到第一个
	{
		playlistnum=num-1;
		CString strpath=my_vector_file[playlistnum].filePath;
		PlayFile(this->m_hWnd,strpath);
	}
	else
	{
		playlistnum-=1;    
		CString strpath=my_vector_file[playlistnum].filePath;
		PlayFile(this->m_hWnd,strpath);
	}
}

//下一曲 函数
void CMP3_1Dlg::OnBnClickedButton13()
{
	// TODO: 在此添加控件通知处理程序代码
	if(-1==playlistnum)
	{
		return ;
	}
	int num=my_ListCtrl.GetItemCount();
	if(playlistnum == num-1)  //如果播放的歌是当前列的最后一个，则跳转到第一个
	{
		CString strpath=my_vector_file[0].filePath;
		PlayFile(this->m_hWnd,strpath);
		playlistnum=0;
	}
	else
	{
		playlistnum+=1;    
		CString strpath=my_vector_file[playlistnum].filePath;
		PlayFile(this->m_hWnd,strpath);
	}
}

//删除音乐文件
void CMP3_1Dlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	my_vector_file2.clear(); 
	int row=my_ListCtrl.GetSelectionMark();
	if(playlistnum==row)  //判断删除的文件是不是正在播放的
	{
		//如果是则停止播放
		mciSendCommand(m_DeviceID,MCI_CLOSE, 0, NULL); //发送关闭命令
		playlistnum=-1;
		isBegin=FALSE;
		isPlay=FALSE;
	}
	//当前播放的音乐位于删除的下方，则将正在播放的歌曲所在位数更新
	if(playlistnum > row) 
	{
		playlistnum--;	
	}
	FILEINFO ite;
	for(int i=0;i<my_ListCtrl.GetItemCount();i++)
	{
		if(i!=row)
		{
			ite=my_vector_file[i];
			my_vector_file2.push_back(ite);
		}
	}
	my_vector_file.clear();
	for(int i=0;i<my_vector_file2.size();i++)
	{
		ite=my_vector_file2[i];
		my_vector_file.push_back(ite);
	}
	my_vector_file2.clear(); 
	nflag=my_vector_file.size();
	SetListCtrlData(my_vector_file);
}
//终止函数
void CMP3_1Dlg::OnBnClickedButton10()
{
	// TODO: 在此添加控件通知处理程序代码
	mciSendCommand(m_DeviceID,MCI_CLOSE, 0, NULL); //发送关闭命令
	playlistnum=-1;
	isBegin=FALSE;
	isPlay=FALSE;
}

//重播函数按钮
void CMP3_1Dlg::OnBnClickedButton9()  
{
	// TODO: 在此添加控件通知处理程序代码
	if(-1==playlistnum)
	{
		mciSendCommand(m_DeviceID,MCI_CLOSE, 0, NULL); //发送关闭命令
		return ;
	}
	mciSendCommand(m_DeviceID,MCI_CLOSE, 0, NULL); //发送关闭命令
	//int row=my_ListCtrl.GetSelectionMark();
	CString strPath=my_vector_file[playlistnum].filePath;
	PlayFile(this->m_hWnd,strPath);
}

//快进5秒函数
void CMP3_1Dlg::GoAhead(void)
{
	int iPosition = my_SliderCtrlTime.GetPos(); //先得到slider控件的滑块位置

	MCI_SEEK_PARMS mciSeek; //mci定位参数
	MCI_PLAY_PARMS mciPlay;

	mciSeek.dwTo = iPosition; //设置seek的位置
	mciSeek.dwTo += 5000;      //增加5秒

	mciPlay.dwFrom = mciSeek.dwTo ; //设置播放的位置dwFrom为seek后
	mciSendCommand (m_DeviceID, MCI_SEEK, MCI_TO,(DWORD)(LPVOID)&mciSeek);

	mciSendCommand(m_DeviceID,MCI_PLAY,MCI_FROM | MCI_NOTIFY, (DWORD)(LPVOID)&mciPlay);
	//MCI_FROM 使dwForm有效
	my_SliderCtrlTime.SetPos(mciPlay.dwFrom); //设置滑块的新位置

}
//快退5秒函数
void CMP3_1Dlg::GoBack(void)
{
	int iPosition = my_SliderCtrlTime.GetPos(); //得到slider控件的滑块位置

	MCI_SEEK_PARMS mciSeek; // 
	MCI_PLAY_PARMS mciPlay;

	mciSeek.dwTo = iPosition; //设置跳转后的位置
	mciSeek.dwTo -= 5000;

	mciPlay.dwFrom = mciSeek.dwTo ; //设置播放位置
	mciSendCommand (m_DeviceID, MCI_SEEK, MCI_TO,(DWORD)(LPVOID)&mciSeek);
	mciSendCommand(m_DeviceID,MCI_PLAY,MCI_FROM | MCI_NOTIFY, (DWORD)(LPVOID)&mciPlay);
	my_SliderCtrlTime.SetPos(mciPlay.dwFrom);
}
//快进5秒按钮
void CMP3_1Dlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	GoAhead();
}

//后退5秒函数按钮
void CMP3_1Dlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	GoBack();
}

//更新滑块的位置
void CMP3_1Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	MCI_STATUS_PARMS mciStatus;
	mciStatus.dwItem = MCI_STATUS_POSITION;

	mciSendCommand(m_DeviceID,MCI_STATUS,MCI_STATUS_ITEM,((DWORD)(LPVOID)&mciStatus));

	m_CurrentPos = mciStatus.dwReturn ; //获得当前的播放进度
	my_SliderCtrlTime.SetPos(m_CurrentPos);    //设置播放滑块的位置

	//pTaskbar->SetProgressState(this->GetSafeHwnd(), TBPF_INDETERMINATE);
	//pTaskbar->SetProgressValue(this->GetSafeHwnd(), m_CurrentPos, m_Length);


	UpdatePosition();

	if (my_SliderCtrlTime.GetPos() == m_Length) //播放结束文件后跳至下个一文件
	{
		//GoNext();
	}

	CDialogEx::OnTimer(nIDEvent);
}
