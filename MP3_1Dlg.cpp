
// MP3_1Dlg.cpp : ʵ���ļ�
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


// CMP3_1Dlg �Ի���

//���캯��

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
	playlistnum=-1;//-1��ʾ��ǰû�в���
	nflag=-1;      //-1��ʾ��ǰ�б�û�и���
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


// CMP3_1Dlg ��Ϣ�������

BOOL CMP3_1Dlg::OnInitDialog()
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	InitDevice();
	InitCtrlLiat();
	InitControls();
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMP3_1Dlg::OnPaint()
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
HCURSOR CMP3_1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BEGIN_EVENTSINK_MAP(CMP3_1Dlg, CDialogEx)

END_EVENTSINK_MAP()


bool fileTimeToString(/*__in */FILETIME ftFileTime, /*__out */CString& tmp)
{
	bool rc = false;
	CTime time(ftFileTime);//�Ȱ�FILETIME���͵�����ת��ΪCTime����
	tmp.Format(L"%d��%d��%d�� %d��%d��%d��",time.GetYear(),time.GetMonth(),time.GetDay(),time.GetHour(),time.GetMinute(),time.GetSecond());
	//�ٽ�CTime����ת��ΪCTime����
	CString fileWriteTime(tmp);//Ϊ���ܰ��ַ���������������CString val�����ķ�������
	rc = true;

	return rc;
}
//��ʼ�������б�
void CMP3_1Dlg::InitCtrlLiat()
{
	DWORD dwStyle;
	dwStyle = my_ListCtrl.GetStyle();
	dwStyle |= LVS_EX_GRIDLINES |LVS_EX_FULLROWSELECT|LVS_SHOWSELALWAYS ;
	my_ListCtrl.SetExtendedStyle(dwStyle);
	my_ListCtrl.InsertColumn(0,_T("����"),LVCFMT_LEFT,50,-1);
	my_ListCtrl.InsertColumn(1,_T("��С"),LVCFMT_LEFT,50,-1);
	my_ListCtrl.InsertColumn(2,_T("ʱ��"),LVCFMT_LEFT,120,-1);
	my_ListCtrl.InsertColumn(3,_T("·��"),LVCFMT_LEFT,120,-1);
}
//��ʼ���豸
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
//�ؼ��ĳ�ʼ������   
void CMP3_1Dlg::InitControls()
{
	my_SliderCtrlTime.SetPos(0);      //��ʼ�����Ž��ȿؼ�����ֵ
	my_SliderCtrlVoice.SetRange(0,100); //���������ؼ��ķ�Χ
	my_SliderCtrlVoice.SetPos(0);      //��ʼ�������ؼ�����ֵ
	CString str;
	str.Format(TEXT("%d:%d"),iMinute,iSecond);
	SetDlgItemText(IDC_EDIT3,str);
	UpdateData(TRUE);
}

void CMP3_1Dlg::SetVolume(int Vol)        //����������С����
{
	MCI_DGV_SETAUDIO_PARMS mciSetAudioPara; //������������

	mciSetAudioPara.dwItem = MCI_DGV_SETAUDIO_VOLUME; 

	mciSetAudioPara.dwCallback = (DWORD_PTR)this->GetSafeHwnd();
	//����������С
	mciSetAudioPara.dwValue = Vol * 10; //here is the value of the Volume(0--1000) 
	mciSendCommand(m_DeviceID, MCI_SETAUDIO, MCI_DGV_SETAUDIO_VALUE | MCI_DGV_SETAUDIO_ITEM, (DWORD)(LPVOID)&mciSetAudioPara);
}

void CMP3_1Dlg::ConvertTime(unsigned int time)        //ת��ʱ�亯��
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

void CMP3_1Dlg::UpdatePosition(void)     //���²���λ��
{
	MCI_STATUS_PARMS mciStatus;
	mciStatus.dwItem = MCI_STATUS_POSITION;
	mciSendCommand(m_DeviceID,MCI_STATUS,MCI_WAIT|MCI_STATUS_ITEM,(DWORD)(LPVOID)&mciStatus);

	int dCurrentPos = mciStatus.dwReturn;
	int sec = dCurrentPos / 1000; //����ļ���������
	int min = sec / 60;           //��������ת���� ����

	sec = sec - min * 60;         //��������ת���� ����
	CString str;
	str.Format(TEXT("%d:%d"),min,sec);
	SetDlgItemText(IDC_EDIT2,str);
}

void CMP3_1Dlg::SetListCtrlData(vector<FILEINFO> &my_vector_file)
{
	//���my_ListCtrl�б��ϵ�����
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//������С��
	ShowWindow(SW_MINIMIZE);
}

void CMP3_1Dlg::OnBnClickedButtonClose()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//�˳�����
	//AfxGetMainWnd()->SendMessage(WM_CLOSE);
	if(IDOK==MessageBox(_T("Sure to quit?"),_T("isplay"),MB_OKCANCEL))
		//EndDialog(NULL);
			AfxGetMainWnd()->SendMessage(WM_CLOSE);
}

void CMP3_1Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM (point.x, point.y));
	CDialogEx::OnLButtonDown(nFlags, point);
}
//��Ӻ���
void CMP3_1Dlg::OnBnClickedButtonAddsong()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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

//���ź���
int CMP3_1Dlg::PlayFile(HWND hWnd,CString strFileName)
{
	if(0==nflag)
	{
		mciSendCommand(m_DeviceID,MCI_CLOSE, 0, NULL); //���͹ر�����
		isBegin=FALSE;
		isPlay=FALSE;
		MessageBox(_T("��ǰ�б�û�и���"));
		return 0;
	}
	//-------------------------------------------
	SetTimer(1,500,NULL); //��ʼ����ʱ����������ʾ���Ž���
	//----------------------------------------------------------
	isPlay=TRUE;
	MCI_OPEN_PARMS mciOpenParms;  //�򿪲���
	memset(&mciOpenParms, 0, sizeof(MCI_OPEN_PARMS));  
	mciOpenParms.lpstrElementName = strFileName;  
	mciSendCommand(m_DeviceID,MCI_CLOSE, 0, NULL); //���͹ر�����
	DWORD dwResult = 0;  
	dwResult = mciSendCommand(m_DeviceID, MCI_OPEN, MCI_OPEN_ELEMENT,  
		(DWORD)(LPVOID)&mciOpenParms);			   //���ʹ�����
	if (!dwResult)  
	{  
		m_ElementID = mciOpenParms.wDeviceID;  

		MCI_PLAY_PARMS mciPlayParms;  
		mciPlayParms.dwCallback = (DWORD)hWnd;  
		dwResult = mciSendCommand(m_ElementID, MCI_PLAY, MCI_DGV_PLAY_REPEAT/*MCI_NOTIFY*/,   
			(DWORD)(LPVOID)&mciPlayParms);  
	}  

	//-------------------------------------------------
	
	//�����ļ���Ϣ�Ľṹ��
	MCI_STATUS_PARMS mciStatus;

	mciStatus.dwItem = MCI_STATUS_LENGTH ; //�õ��ļ��Ĳ��ų���

	mciSendCommand(m_DeviceID,MCI_STATUS,MCI_WAIT |  MCI_STATUS_ITEM,(DWORD)(LPVOID)&mciStatus);

	//MCI_STATUS_ITEM ��ʾMCI_STATUS_PARMS��dwItem��Ч
	//mciSendCommand����MCI_STATUS������MIC_STATUS_LENGTH��Ϣ��������Ϣ�����ڱ���mciStatus�С�
	//�õ�ý��Ĳ��ų���
	m_Length = mciStatus.dwReturn ;

	//���ļ����ʼ�������ؼ�����ֵ

	my_SliderCtrlTime.SetRange(0,m_Length); //���ò��Ž��ȿؼ��ķ�Χ
	my_SliderCtrlTime.SetPos(0);            //��ʼ�����Ž��ȿؼ��Ļ���λ��

	my_SliderCtrlVoice.SetPos(50);            //��ʼ�������ؼ��Ļ���λ��

	// ���������༭�����ֵ
	//CString temp;
	//temp.Format(TEXT("%d"),50);
	//this->SetDlgItemText(IDC_EDITVOL,temp);

	SetVolume(50);               //������Ƶ�ĳ�ʼ������С

	
	ConvertTime(m_Length); //�������Ƶ����ת���� �ֺ���ĸ�ʽ
	CString str;
	str.Format(TEXT("%d:%d"),iMinute,iSecond);
	SetDlgItemText(IDC_EDIT3,str);

	UpdateData(TRUE);

	//return dwResult;
	return 1;
}
//���Ű�ť
void CMP3_1Dlg::OnBnClickedButton12()   
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//�ж�isBegin�Ƿ��һ�δ򿪲���
	if(FALSE==isBegin)
	{
		isBegin=TRUE;
		int row=my_ListCtrl.GetSelectionMark();
		if(row<0||row>=nflag)
		{
			MessageBox(_T("��ǰ�б�û�и���"));
			return ;
		}
		CString strPath=my_vector_file[row].filePath;
		playlistnum=row;
		PlayFile(this->m_hWnd,strPath);
	}
	else
	{
		//�ж�isPlay�Ƿ�Ϊ����״̬
		if(isPlay)
		{
			MCI_GENERIC_PARMS mciPause; //mci��ͣ����
			//������ͣ����
			mciSendCommand(m_DeviceID,MCI_PAUSE,0,(DWORD)(LPVOID)&mciPause);   //��ͣ
			//mciSendCommand(m_DeviceID, MCI_PAUSE, MCI_WAIT, NULL);
			isPlay = FALSE;
		}
		else
		{
			MCI_PLAY_PARMS mciPlay;
			mciSendCommand(m_DeviceID,MCI_PLAY,0,(DWORD)(LPVOID)&mciPlay);	//��ͣ������
			//mciSendCommand(m_DeviceID, MCI_RESUME, MCI_WAIT, NULL); 	
			isPlay = TRUE;
		}
	}

}

//˫������Ŀؼ�����
void CMP3_1Dlg::OnNMDblclkList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (my_ListCtrl.GetItemCount()>0)
	{
		isBegin=TRUE;
		int Row=my_ListCtrl.GetSelectionMark();
		if(Row!=-1)
		{
			playlistnum = Row;//�������������ȫ�ֱ���
			CString strpath=my_vector_file[Row].filePath;
			PlayFile(this->m_hWnd,strpath);			
		}
		else
		{		
			AfxMessageBox(TEXT("��ѡ����ȷ���ļ�"),MB_ICONINFORMATION,NULL);
		}
	}
	else
	{
		AfxMessageBox(TEXT("��û�д��ļ�"),MB_ICONINFORMATION,NULL);
	}
	*pResult = 0;
}

//��һ�� ����
void CMP3_1Dlg::OnBnClickedButton11()   
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(-1==playlistnum)
	{
		return ;
	}
	int num=my_ListCtrl.GetItemCount();
	if(playlistnum == 0)  //������ŵĸ��ǵ�ǰ�е����һ��������ת����һ��
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

//��һ�� ����
void CMP3_1Dlg::OnBnClickedButton13()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(-1==playlistnum)
	{
		return ;
	}
	int num=my_ListCtrl.GetItemCount();
	if(playlistnum == num-1)  //������ŵĸ��ǵ�ǰ�е����һ��������ת����һ��
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

//ɾ�������ļ�
void CMP3_1Dlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	my_vector_file2.clear(); 
	int row=my_ListCtrl.GetSelectionMark();
	if(playlistnum==row)  //�ж�ɾ�����ļ��ǲ������ڲ��ŵ�
	{
		//�������ֹͣ����
		mciSendCommand(m_DeviceID,MCI_CLOSE, 0, NULL); //���͹ر�����
		playlistnum=-1;
		isBegin=FALSE;
		isPlay=FALSE;
	}
	//��ǰ���ŵ�����λ��ɾ�����·��������ڲ��ŵĸ�������λ������
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
//��ֹ����
void CMP3_1Dlg::OnBnClickedButton10()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	mciSendCommand(m_DeviceID,MCI_CLOSE, 0, NULL); //���͹ر�����
	playlistnum=-1;
	isBegin=FALSE;
	isPlay=FALSE;
}

//�ز�������ť
void CMP3_1Dlg::OnBnClickedButton9()  
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(-1==playlistnum)
	{
		mciSendCommand(m_DeviceID,MCI_CLOSE, 0, NULL); //���͹ر�����
		return ;
	}
	mciSendCommand(m_DeviceID,MCI_CLOSE, 0, NULL); //���͹ر�����
	//int row=my_ListCtrl.GetSelectionMark();
	CString strPath=my_vector_file[playlistnum].filePath;
	PlayFile(this->m_hWnd,strPath);
}

//���5�뺯��
void CMP3_1Dlg::GoAhead(void)
{
	int iPosition = my_SliderCtrlTime.GetPos(); //�ȵõ�slider�ؼ��Ļ���λ��

	MCI_SEEK_PARMS mciSeek; //mci��λ����
	MCI_PLAY_PARMS mciPlay;

	mciSeek.dwTo = iPosition; //����seek��λ��
	mciSeek.dwTo += 5000;      //����5��

	mciPlay.dwFrom = mciSeek.dwTo ; //���ò��ŵ�λ��dwFromΪseek��
	mciSendCommand (m_DeviceID, MCI_SEEK, MCI_TO,(DWORD)(LPVOID)&mciSeek);

	mciSendCommand(m_DeviceID,MCI_PLAY,MCI_FROM | MCI_NOTIFY, (DWORD)(LPVOID)&mciPlay);
	//MCI_FROM ʹdwForm��Ч
	my_SliderCtrlTime.SetPos(mciPlay.dwFrom); //���û������λ��

}
//����5�뺯��
void CMP3_1Dlg::GoBack(void)
{
	int iPosition = my_SliderCtrlTime.GetPos(); //�õ�slider�ؼ��Ļ���λ��

	MCI_SEEK_PARMS mciSeek; // 
	MCI_PLAY_PARMS mciPlay;

	mciSeek.dwTo = iPosition; //������ת���λ��
	mciSeek.dwTo -= 5000;

	mciPlay.dwFrom = mciSeek.dwTo ; //���ò���λ��
	mciSendCommand (m_DeviceID, MCI_SEEK, MCI_TO,(DWORD)(LPVOID)&mciSeek);
	mciSendCommand(m_DeviceID,MCI_PLAY,MCI_FROM | MCI_NOTIFY, (DWORD)(LPVOID)&mciPlay);
	my_SliderCtrlTime.SetPos(mciPlay.dwFrom);
}
//���5�밴ť
void CMP3_1Dlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GoAhead();
}

//����5�뺯����ť
void CMP3_1Dlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GoBack();
}

//���»����λ��
void CMP3_1Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	MCI_STATUS_PARMS mciStatus;
	mciStatus.dwItem = MCI_STATUS_POSITION;

	mciSendCommand(m_DeviceID,MCI_STATUS,MCI_STATUS_ITEM,((DWORD)(LPVOID)&mciStatus));

	m_CurrentPos = mciStatus.dwReturn ; //��õ�ǰ�Ĳ��Ž���
	my_SliderCtrlTime.SetPos(m_CurrentPos);    //���ò��Ż����λ��

	//pTaskbar->SetProgressState(this->GetSafeHwnd(), TBPF_INDETERMINATE);
	//pTaskbar->SetProgressValue(this->GetSafeHwnd(), m_CurrentPos, m_Length);


	UpdatePosition();

	if (my_SliderCtrlTime.GetPos() == m_Length) //���Ž����ļ��������¸�һ�ļ�
	{
		//GoNext();
	}

	CDialogEx::OnTimer(nIDEvent);
}
