// OCX Window Class Header

class CCvControl : public CWnd
{
// Operations
public:
	void SetID(short nID);
	void SetValue(unsigned long clrCvColor, BOOL bHeightError, BOOL bStoStationReady, BOOL bRetStationReady, BOOL bPickingStationReady, BOOL bStoHomeStandReady, BOOL bRetHomeStandReady);
	void AboutBox();
};
/*
class CConveyorControl : public CWnd
{
public:
	void SetValue(short nJobType, BOOL bHeightError, BOOL bHSReady, short nStatus);
	void SetID(short nID);
	void AboutBox();
};
*/
class CStackerControl : public CWnd
{
public:
	void SetID(short nID);
	void SetValue(short nCurrentPos, short nJobType, BOOL bEstop, BOOL bInvoke, BOOL bProdLoad, short nStatus, short nSecondJobType = 0, BOOL nSecondInvoke = FALSE, BOOL nSecondProdLoad = FALSE);
	void SetProperty(short nID, short nDirection, short nStackerType, short nForkSize, short nBayCnt, short nMaxDisplayPos);
	void AboutBox();
};


class CScControl : public CWnd
{
// Operations
public:

	void SetID(short nID);
	void SetCurrentPosition(short nCurrentPos);
	void SetScColor(OLE_COLOR FirstScColor, OLE_COLOR SecondScColor);
	void SetRailColor(OLE_COLOR RailColor);
	void SetGoods(BOOL bFirstGoods, BOOL bSecondGoods);
	void SetGoodsColor(OLE_COLOR clrGoodsColor);
	void SetProperty(short nID, short nForkSize, short nScDirection, short nScType, short nBayCnt, short nMaxDisplayPos);
	void SetValue(short nCurrentPosition, 
		          OLE_COLOR FirstScColor, 
				  OLE_COLOR SecondScColor, 
				  OLE_COLOR RailColor, 
				  BOOL bFirstGoods, 
				  BOOL bSecondGoods);
	void AboutBox();
};


/*
class COpBoxControl : public CWnd
{
public:
	void SetValue(short nMode);
	void SetID(short nID);
	void AboutBox();
};
*/
class COpBoxControl : public CWnd
{
public:

	void SetValueEx(BOOL bAutoMode, BOOL bNormalStatus);
	void SetValue(short nMode);
	void SetID(short nID);
	void AboutBox();
};

class CRackControl : public CWnd
{
public:
	void SetProperty(short nID, short nDirection, short nBayCnt, short nBaySize);
	void AboutBox();
};

class CEcsGraphControl : public CWnd
{
public:
	void SetProperty(short nSize, LPCTSTR strLabel);
	void SetValue(short nIndex, short nValue, short nCount);
	void Draw();
};

/////////////////////////////////////////////////////////////////////////////
// CGmsBtn wrapper class
// Dispatch interfaces referenced by this interface
#include "font.h"

class COleFont;
class CGmsBtnControl : public CWnd
{
public:
	short GetGmsButtonType();
	void SetGmsButtonType(short);
	unsigned long GetEnabledBtnColor();
	void SetEnabledBtnColor(unsigned long);
	unsigned long GetEnabledTextColor();
	void SetEnabledTextColor(unsigned long);
	unsigned long GetEnabledLineColor();
	void SetEnabledLineColor(unsigned long);
	BOOL GetGmsButtonStatus();
	void SetGmsButtonStatus(BOOL);
	COleFont GetFont();
	void SetFont(LPDISPATCH);
	CString GetCaption();
	void SetCaption(LPCTSTR);

// Operations
public:
	void SetID(short nID);
	void AboutBox();
};

