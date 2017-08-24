// Properties.cpp : 实现文件
//

#include "stdafx.h"
#include "Iplayer.h"
#include "Properties.h"
#include "afxdialogex.h"
#include "IplayerDlg.h"

extern FileInfo fileProperty;
// Properties 对话框

IMPLEMENT_DYNAMIC(Properties, CDialogEx)

Properties::Properties(CWnd* pParent /*=NULL*/)
	: CDialogEx(Properties::IDD, pParent)
{

}

Properties::~Properties()
{
}

void Properties::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC1, fileName);
	DDX_Control(pDX, IDC_STATIC2, Size);
	DDX_Control(pDX, IDC_STATIC3, date);
	DDX_Control(pDX, IDC_STATIC4, location);
}


BEGIN_MESSAGE_MAP(Properties, CDialogEx)
END_MESSAGE_MAP()


// Properties 消息处理程序


BOOL Properties::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetDlgItemText(IDC_STATIC1,fileProperty.sFileName);
	CString s;
	s.Format(_T("%d kb"),fileProperty.lFileSize);
	SetDlgItemText(IDC_STATIC2,s);
	SetDlgItemText(IDC_STATIC3,fileProperty.time);
	SetDlgItemText(IDC_STATIC4,fileProperty.filePath);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
