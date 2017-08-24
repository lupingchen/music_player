
// MP3_1Dlg.h : ͷ�ļ�
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
static int nflag;    //��ʾ��ǰ�б��ܵĸ�����
static int playlistnum;//��ǰ���ڲ����������б��е���
static BOOL isPlay;//�ж��ǲ��Ż�����ͣ
static BOOL isBegin;//�ж��Ƿ���˲���

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

// CMP3_1Dlg �Ի���
class CMP3_1Dlg : public CDialogEx
{
// ����
public:
	CMP3_1Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MP3_1_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	DECLARE_EVENTSINK_MAP()
public:
	vector<FILEINFO> my_vector_file;//��Ÿ�����Ϣ
	vector<FILEINFO> my_vector_file2;//���ڸ��´�Ÿ�����Ϣ
	afx_msg void OnBnClickedButtonMin();
	afx_msg void OnBnClickedButtonClose();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButtonAddsong();
	CListCtrl my_ListCtrl;
	CWMPControls control;
	CWMPPlayer4 mediaPlayer;
	MCIDEVICEID m_DeviceID;   //�豸��ID
    MCIDEVICEID m_ElementID;  
	CEdit my_edit1; 
	CEdit my_edit2;
	CMySliderCtrlTime my_SliderCtrlTime;  //���ֲ���ʱ�����
	CMySliderCtrlTime my_SliderCtrlVoice; //���ֲ��������Ķ���
	DWORD m_CurrentPos;//��ǰ����λ�ã�����Ϊ��λ��
	unsigned int m_Length;//��Ƶ���ŵĳ��ȣ�����Ϊ��λ��
	int iSecond;//���ŵ�����
	int iMinute;//���ŵķ�����
	ITaskbarList3* pTaskbar;          //����֧����������ʾ���Ž���
public:
	void InitCtrlLiat();//��ʼ�������б�
	DWORD InitDevice();//��ʼ��MCIDEVICEID
	void InitControls();//�ؼ��ĳ�ʼ������     
	void SetListCtrlData(vector<FILEINFO> &my_vector_file);//�����б�
	int PlayFile(HWND hWnd,CString szFileName);//�����ļ�
	void SetVolume(int Vol);         //����������С����
    void ConvertTime(unsigned int time);         //ת��ʱ�亯��
    void UpdatePosition(void);     //���²���λ��
	void GoAhead(void);              //�������
    void GoBack(void);               //���˺���
	afx_msg void OnBnClickedButton12();
	afx_msg void OnNMDblclkList2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton13();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton2();//���5�뺯��
	afx_msg void OnBnClickedButton3();//����5�뺯��
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
