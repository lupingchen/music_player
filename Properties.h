#pragma once
#include "afxwin.h"


// Properties 对话框

class Properties : public CDialogEx
{
	DECLARE_DYNAMIC(Properties)

public:
	Properties(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Properties();

// 对话框数据
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CStatic fileName;
	CStatic Size;
	CStatic date;
	CStatic location;
	virtual BOOL OnInitDialog();
};
