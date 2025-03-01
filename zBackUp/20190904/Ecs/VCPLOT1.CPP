// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


#include "stdafx.h"
#include "vcplot1.h"

// Dispatch interfaces referenced by this interface
#include "vcbackdrop.h"
#include "vcrect1.h"
#include "vcview3d1.h"
#include "vcplotbase1.h"
#include "vcweighting.h"
#include "vcwall.h"
#include "vcseriescollection1.h"
#include "vclight1.h"
#include "vcaxis1.h"


/////////////////////////////////////////////////////////////////////////////
// CVcPlot properties

/////////////////////////////////////////////////////////////////////////////
// CVcPlot operations

long CVcPlot::GetAngleUnit()
{
	long result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CVcPlot::SetAngleUnit(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL CVcPlot::GetClockwise()
{
	BOOL result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CVcPlot::SetClockwise(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long CVcPlot::GetSort()
{
	long result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CVcPlot::SetSort(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CVcBackdrop CVcPlot::GetBackdrop()
{
	LPDISPATCH pDispatch;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&pDispatch, NULL);
	return CVcBackdrop(pDispatch);
}

float CVcPlot::GetStartingAngle()
{
	float result;
	InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void CVcPlot::SetStartingAngle(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long CVcPlot::GetSubPlotLabelPosition()
{
	long result;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CVcPlot::SetSubPlotLabelPosition(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

float CVcPlot::GetBarGap()
{
	float result;
	InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void CVcPlot::SetBarGap(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0xa, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float CVcPlot::GetXGap()
{
	float result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void CVcPlot::SetXGap(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0xb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL CVcPlot::GetAutoLayout()
{
	BOOL result;
	InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CVcPlot::SetAutoLayout(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xc, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

float CVcPlot::GetWidthToHeightRatio()
{
	float result;
	InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void CVcPlot::SetWidthToHeightRatio(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0xd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float CVcPlot::GetDepthToHeightRatio()
{
	float result;
	InvokeHelper(0xe, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void CVcPlot::SetDepthToHeightRatio(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0xe, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

CVcRect CVcPlot::GetLocationRect()
{
	LPDISPATCH pDispatch;
	InvokeHelper(0xf, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&pDispatch, NULL);
	return CVcRect(pDispatch);
}

long CVcPlot::GetProjection()
{
	long result;
	InvokeHelper(0x10, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CVcPlot::SetProjection(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x10, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

float CVcPlot::GetZGap()
{
	float result;
	InvokeHelper(0x11, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void CVcPlot::SetZGap(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x11, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

CVcView3d CVcPlot::GetView3d()
{
	LPDISPATCH pDispatch;
	InvokeHelper(0x12, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&pDispatch, NULL);
	return CVcView3d(pDispatch);
}

CVcPlotBase CVcPlot::GetPlotBase()
{
	LPDISPATCH pDispatch;
	InvokeHelper(0x13, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&pDispatch, NULL);
	return CVcPlotBase(pDispatch);
}

CVcWeighting CVcPlot::GetWeighting()
{
	LPDISPATCH pDispatch;
	InvokeHelper(0x16, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&pDispatch, NULL);
	return CVcWeighting(pDispatch);
}

CVcWall CVcPlot::GetWall()
{
	LPDISPATCH pDispatch;
	InvokeHelper(0x17, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&pDispatch, NULL);
	return CVcWall(pDispatch);
}

CVcSeriesCollection CVcPlot::GetSeriesCollection()
{
	LPDISPATCH pDispatch;
	InvokeHelper(0x19, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&pDispatch, NULL);
	return CVcSeriesCollection(pDispatch);
}

BOOL CVcPlot::GetDataSeriesInRow()
{
	BOOL result;
	InvokeHelper(0x1a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CVcPlot::SetDataSeriesInRow(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x1a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

CVcLight CVcPlot::GetLight()
{
	LPDISPATCH pDispatch;
	InvokeHelper(0x1b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&pDispatch, NULL);
	return CVcLight(pDispatch);
}

long CVcPlot::GetDefaultPercentBasis()
{
	long result;
	InvokeHelper(0x1d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

BOOL CVcPlot::GetUniformAxis()
{
	BOOL result;
	InvokeHelper(0x1e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CVcPlot::SetUniformAxis(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x1e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

CVcAxis CVcPlot::GetAxis(long axisID, const VARIANT& Index)
{
	LPDISPATCH pDispatch;
	static BYTE parms[] =
		VTS_I4 VTS_VARIANT;
	InvokeHelper(0x1f, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&pDispatch, parms,
		axisID, &Index);
	return CVcAxis(pDispatch);
}
