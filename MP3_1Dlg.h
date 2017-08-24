
// MP3_1Dlg.h : 头文件
//

#pragma once
#include "ocx1.h"
#include "afxcmn.h"
#include "CWMPControls.h"
#include "CWMPPlayer4.h"
#include <vector>

//#include <MMSystem.h>
#include "mmsystem.h"
#include "afxwin.h"
#include "mysliderctrltime.h"
using namespace std;

static int nIndex;
static int nflag;    //表示当前列表总的歌曲数
static int playlistnum;//当前正在播放音乐在列表中的数
static BOOL isPlay;//判断是播放还是暂停
static BOOL isBegin;//判断是否打开了播放

typedef struct FileInfo
{
	char sFileName[200];
	CString time;
	DWORD lFileSize;
	CString filePath;
	struct FileInfo()
	{
		memset(sFileName,0,sizeof(char)*200);
		time="";
		lFileSize=0;
		filePath="";
	}
}FILEINFO;

// CMP3_1Dlg 对话框
class CMP3_1Dlg : public CDialogEx
{
// 构造
public:
	CMP3_1Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MP3_1_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	DECLARE_EVENTSINK_MAP()
public:
	vector<FILEINFO> my_vector_file;//存放歌曲信息
	vector<FILEINFO> my_vector_file2;//用于更新存放歌曲信息
	afx_msg void OnBnClickedButtonMin();
	afx_msg void OnBnClickedButtonClose();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButtonAddsong();
	CListCtrl my_ListCtrl;
	CWMPControls control;
	CWMPPlayer4 mediaPlayer;
	MCIDEVICEID m_DeviceID;   //设备的ID
    MCIDEVICEID m_ElementID;  
	CEdit my_edit1; 
	CEdit my_edit2;
	CMySliderCtrlTime my_SliderCtrlTime;  //音乐播放时间对象
	CMySliderCtrlTime my_SliderCtrlVoice; //音乐播放音量的对象
	DWORD m_CurrentPos;//当前播放位置（毫秒为单位）
	unsigned int m_Length;//音频播放的长度（毫秒为单位）
	int iSecond;//播放的秒数
	int iMinute;//播放的分钟数
	ITaskbarList3* pTaskbar;          //用于支持任务栏显示播放进度
public:
	void InitCtrlLiat();//初始化播放列表
	DWORD InitDevice();//初始化MCIDEVICEID
	void InitControls();//控件的初始化函数     
	void SetListCtrlData(vector<FILEINFO> &my_vector_file);//更新列表
	int PlayFile(HWND hWnd,CString szFileName);//播放文件
	void SetVolume(int Vol);         //设置音量大小函数
    void ConvertTime(unsigned int time);         //转换时间函数
    void UpdatePosition(void);     //更新播放位置
	void GoAhead(void);              //快进函数
    void GoBack(void);               //快退函数
	afx_msg void OnBnClickedButton12();
	afx_msg void OnNMDblclkList2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton13();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton2();//快进5秒函数
	afx_msg void OnBnClickedButton3();//后退5秒函数
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
