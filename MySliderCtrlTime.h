#pragma once


// CMySliderCtrlTime

class CMySliderCtrlTime : public CSliderCtrl
{
	DECLARE_DYNAMIC(CMySliderCtrlTime)

public:
	CMySliderCtrlTime();
	virtual ~CMySliderCtrlTime();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
public:
	bool SetThumb(const CPoint& pt);
    void PostMessageToParent(const int nTBCode) const;
    bool m_bDragging;
    bool m_bDragChanged;
};


