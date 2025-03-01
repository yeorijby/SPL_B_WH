// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


#include "stdafx.h"
#include "vclight.h"


/////////////////////////////////////////////////////////////////////////////
// CVcLight properties

/////////////////////////////////////////////////////////////////////////////
// CVcLight operations

float CVcLight::GetAmbientIntensity()
{
	float result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void CVcLight::SetAmbientIntensity(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float CVcLight::GetEdgeIntensity()
{
	float result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void CVcLight::SetEdgeIntensity(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL CVcLight::GetEdgeVisible()
{
	BOOL result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CVcLight::SetEdgeVisible(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

LPDISPATCH CVcLight::GetLightSources()
{
	LPDISPATCH result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}
