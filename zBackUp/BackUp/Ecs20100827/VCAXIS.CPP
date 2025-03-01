// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


#include "stdafx.h"
#include "vcaxis.h"

// Dispatch interfaces referenced by this interface
#include "VcCategoryScale.h"
#include "vcaxisgrid.h"
#include "vcaxisscale.h"
#include "VcValueScale.h"
#include "vcaxistitle.h"
#include "vclabels.h"


/////////////////////////////////////////////////////////////////////////////
// CVcAxis properties

/////////////////////////////////////////////////////////////////////////////
// CVcAxis operations

LPDISPATCH CVcAxis::GetPen()
{
	LPDISPATCH result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

short CVcAxis::GetLabelLevelCount()
{
	short result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
	return result;
}

CVcCategoryScale CVcAxis::GetCategoryScale()
{
	LPDISPATCH pDispatch;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&pDispatch, NULL);
	return CVcCategoryScale(pDispatch);
}

CVcAxisGrid CVcAxis::GetAxisGrid()
{
	LPDISPATCH pDispatch;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&pDispatch, NULL);
	return CVcAxisGrid(pDispatch);
}

LPDISPATCH CVcAxis::GetIntersection()
{
	LPDISPATCH result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH CVcAxis::GetTick()
{
	LPDISPATCH result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CVcAxisScale CVcAxis::GetAxisScale()
{
	LPDISPATCH pDispatch;
	InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&pDispatch, NULL);
	return CVcAxisScale(pDispatch);
}

CVcValueScale CVcAxis::GetValueScale()
{
	LPDISPATCH pDispatch;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&pDispatch, NULL);
	return CVcValueScale(pDispatch);
}

CVcAxisTitle CVcAxis::GetAxisTitle()
{
	LPDISPATCH pDispatch;
	InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&pDispatch, NULL);
	return CVcAxisTitle(pDispatch);
}

CVcLabels CVcAxis::GetLabels()
{
	LPDISPATCH pDispatch;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&pDispatch, NULL);
	return CVcLabels(pDispatch);
}
