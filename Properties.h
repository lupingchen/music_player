#pragma once
#include "afxwin.h"


// Properties �Ի���

class Properties : public CDialogEx
{
	DECLARE_DYNAMIC(Properties)

public:
	Properties(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Properties();

// �Ի�������
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CStatic fileName;
	CStatic Size;
	CStatic date;
	CStatic location;
	virtual BOOL OnInitDialog();
};
