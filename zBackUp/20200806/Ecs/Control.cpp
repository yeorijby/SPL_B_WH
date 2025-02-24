// OCX Window Class Body

#include "stdafx.h"
#include "control.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/*// OP BOX Control
void COpBoxControl::SetValue(short nMode)
{
	static BYTE parms[] =
		VTS_I2;
	InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 nMode);
}

void COpBoxControl::SetID(short nID)
{
	static BYTE parms[] =
		VTS_I2;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 nID);
}
*/
// OP BOX Control
void COpBoxControl::SetValue(short nMode)
{
	static BYTE parms[] =
		VTS_I2;
	InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 nMode);
}

void COpBoxControl::SetID(short nID)
{
	static BYTE parms[] =
		VTS_I2;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 nID);
}

void COpBoxControl::SetValueEx(BOOL bAutoMode, BOOL bNormalStatus)
{
	static BYTE parms[] =
		VTS_BOOL VTS_BOOL;
	InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 bAutoMode, bNormalStatus);
}

void COpBoxControl::AboutBox()
{
	InvokeHelper(0xfffffdd8, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

// Conveyor Control
void CCvControl::SetID(short nID)
{
	static BYTE parms[] =
		VTS_I2;
	InvokeHelper(0xe, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 nID);
}

void CCvControl::SetValue(unsigned long clrCvColor, BOOL bHeightError, BOOL bStoStationReady, BOOL bRetStationReady, BOOL bPickingStationReady, BOOL bStoHomeStandReady, BOOL bRetHomeStandReady)
{
	static BYTE parms[] =
		VTS_I4 VTS_BOOL VTS_BOOL VTS_BOOL VTS_BOOL VTS_BOOL VTS_BOOL;
	InvokeHelper(0xf, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 clrCvColor, bHeightError, bStoStationReady, bRetStationReady, bPickingStationReady, bStoHomeStandReady, bRetHomeStandReady);
}

void CCvControl::AboutBox()
{
	InvokeHelper(0xfffffdd8, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}
/*
void CConveyorControl::SetValue(short nJobType, BOOL bHeightError, BOOL bHSReady, short nStatus)
{
	static BYTE parms[] =
		VTS_I2 VTS_BOOL VTS_BOOL VTS_I2;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 nJobType, bHeightError, bHSReady, nStatus);
}

void CConveyorControl::SetID(short nID)
{
	static BYTE parms[] =
		VTS_I2;
	InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 nID);
}

void CConveyorControl::AboutBox()
{
	InvokeHelper(0xfffffdd8, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}
*/

/////////////////////////////////////////////////////////////////////////////
// CRackControl properties

/////////////////////////////////////////////////////////////////////////////
// CRackControl operations

void CRackControl::SetProperty(short nID, short nDirection, short nBayCnt, short nBaySize)
{
	static BYTE parms[] =
		VTS_I2 VTS_I2 VTS_I2 VTS_I2;
	InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 nID, nDirection, nBayCnt, nBaySize);
}

void CRackControl::AboutBox()
{
	InvokeHelper(0xfffffdd8, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CStackerControl properties

/////////////////////////////////////////////////////////////////////////////
// CStackerControl operations

void CStackerControl::SetID(short nID)
{
	static BYTE parms[] =
		VTS_I2;
	InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 nID);
}

void CStackerControl::SetProperty(short nID, short nDirection, short nStackerType, short nForkSize, short nBayCnt, short nMaxDisplayPos)
{
	static BYTE parms[] =
		VTS_I2 VTS_I2 VTS_I2 VTS_I2 VTS_I2 VTS_I2;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 nID, nDirection, nStackerType, nForkSize, nBayCnt, nMaxDisplayPos);
}

void CStackerControl::SetValue(short nCurrentPos, short nJobType, BOOL bEstop, BOOL bInvoke, BOOL bProdLoad, short nStatus, short nSecondJobType, BOOL nSecondInvoke, BOOL nSecondProdLoad)
{
	static BYTE parms[] =
		VTS_I2 VTS_I2 VTS_BOOL VTS_BOOL VTS_BOOL VTS_I2 VTS_I2 VTS_BOOL VTS_BOOL;
	InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 nCurrentPos, nJobType, bEstop, bInvoke, bProdLoad, nStatus, nSecondJobType, nSecondInvoke, nSecondProdLoad);
}

void CStackerControl::AboutBox()
{
	InvokeHelper(0xfffffdd8, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

/////////////////////////////////////////////////////////////////////////////
// CRtv operations

void CScControl::SetID(short nID)
{
	static BYTE parms[] =
		VTS_I2;
	InvokeHelper(14, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 nID);
}

void CScControl::SetCurrentPosition(short nCurrentPos)
{
	static BYTE parms[] =
		VTS_I2;
	InvokeHelper(15, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 nCurrentPos);
}

void CScControl::SetScColor(OLE_COLOR FirstScColor, OLE_COLOR SecondScColor)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(16, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 FirstScColor, SecondScColor);
}

void CScControl::SetRailColor(OLE_COLOR RailColor)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(17, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 RailColor);
}

void CScControl::SetGoods(BOOL bFirstGoods, BOOL bSecondGoods)
{
	static BYTE parms[] =
		VTS_BOOL VTS_BOOL;
	InvokeHelper(18, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 bFirstGoods, bSecondGoods);
}

void CScControl::SetGoodsColor(OLE_COLOR clrGoodsColor)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(19, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 clrGoodsColor);
}


void CScControl::SetProperty(short nID, 
							 short nForkSize, 
							 short nScDirection, 
							 short nScType, 
							 short nBayCnt, 
							 short nMaxDisplayPos)
{
	static BYTE parms[] =
		VTS_I2 VTS_I2 VTS_I2 VTS_I2 VTS_I2 VTS_I2;
	InvokeHelper(20, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 nID, nForkSize, nScDirection, nScType, nBayCnt, nMaxDisplayPos);
}

void CScControl::SetValue(short nCurrentPosition, 
		          OLE_COLOR FirstScColor, 
				  OLE_COLOR SecondScColor, 
				  OLE_COLOR RailColor, 
				  BOOL bFirstGoods, 
				  BOOL bSecondGoods)
{
	static BYTE parms[] =
		VTS_I2 VTS_I4 VTS_I4 VTS_I4 VTS_BOOL VTS_BOOL;
	InvokeHelper(21, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 nCurrentPosition, FirstScColor, SecondScColor, RailColor, bFirstGoods, bSecondGoods);
}

void CScControl::AboutBox()
{
	InvokeHelper(0xfffffdd8, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}
/////////////////////////////////////////////////////////////////////////////
// CEcsGraphControl properties

/////////////////////////////////////////////////////////////////////////////
// CEcsGraphControl operations

void CEcsGraphControl::SetProperty(short nSize, LPCTSTR strLabel)
{
	static BYTE parms[] =
		VTS_I2 VTS_BSTR;
	InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 nSize, strLabel);
}

void CEcsGraphControl::SetValue(short nIndex, short nValue, short nCount)
{
	static BYTE parms[] =
		VTS_I2 VTS_I2 VTS_I2;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 nIndex, nValue, nCount);
}

void CEcsGraphControl::Draw()
{
	InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

/////////////////////////////////////////////////////////////////////////////
// CGmsBtn properties

short CGmsBtnControl::GetGmsButtonType()
{
	short result;
	GetProperty(0x4, VT_I2, (void*)&result);
	return result;
}

void CGmsBtnControl::SetGmsButtonType(short propVal)
{
	SetProperty(0x4, VT_I2, propVal);
}

unsigned long CGmsBtnControl::GetEnabledBtnColor()
{
	unsigned long result;
	GetProperty(0x1, VT_I4, (void*)&result);
	return result;
}

void CGmsBtnControl::SetEnabledBtnColor(unsigned long propVal)
{
	SetProperty(0x1, VT_I4, propVal);
}

unsigned long CGmsBtnControl::GetEnabledTextColor()
{
	unsigned long result;
	GetProperty(0x2, VT_I4, (void*)&result);
	return result;
}

void CGmsBtnControl::SetEnabledTextColor(unsigned long propVal)
{
	SetProperty(0x2, VT_I4, propVal);
}

unsigned long CGmsBtnControl::GetEnabledLineColor()
{
	unsigned long result;
	GetProperty(0x3, VT_I4, (void*)&result);
	return result;
}

void CGmsBtnControl::SetEnabledLineColor(unsigned long propVal)
{
	SetProperty(0x3, VT_I4, propVal);
}

BOOL CGmsBtnControl::GetGmsButtonStatus()
{
	BOOL result;
	GetProperty(0x5, VT_BOOL, (void*)&result);
	return result;
}

void CGmsBtnControl::SetGmsButtonStatus(BOOL propVal)
{
	SetProperty(0x5, VT_BOOL, propVal);
}

COleFont CGmsBtnControl::GetFont()
{
	LPDISPATCH pDispatch;
	GetProperty(DISPID_FONT, VT_DISPATCH, (void*)&pDispatch);
	return COleFont(pDispatch);
}

void CGmsBtnControl::SetFont(LPDISPATCH propVal)
{
	SetProperty(DISPID_FONT, VT_DISPATCH, propVal);
}

CString CGmsBtnControl::GetCaption()
{
	CString result;
	GetProperty(DISPID_CAPTION, VT_BSTR, (void*)&result);
	return result;
}

void CGmsBtnControl::SetCaption(LPCTSTR propVal)
{
	SetProperty(DISPID_CAPTION, VT_BSTR, propVal);
}

/////////////////////////////////////////////////////////////////////////////
// CGmsBtn operations

void CGmsBtnControl::SetID(short nID)
{
	static BYTE parms[] =
		VTS_I2;
	InvokeHelper(0x6, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 nID);
}

void CGmsBtnControl::AboutBox()
{
	InvokeHelper(0xfffffdd8, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

