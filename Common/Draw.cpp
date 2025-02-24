// Draw Function Collection Header

#include "stdafx.h"
//#include <afxwin.h>         // MFC core and standard components
#include <color.h>

void DrawButtonDown(CDC* pDC, CRect rect, COLORREF Color)
{
	CPen	penWhite(PS_SOLID, 1, WHITE), penBlack(PS_SOLID, 1, BLACK), penDarkGray(PS_SOLID, 1, DARK_GRAY);
	CBrush	brushFill, brushWhite;

	CPen* ppenOld = (CPen *)pDC->SelectObject(&penWhite);
	CBrush* pbrushOld = pDC->SelectObject(&brushWhite);

	pDC->Rectangle(rect);

	pDC->SelectObject(&penBlack);
	pDC->MoveTo(rect.right - 1, rect.top);
	pDC->LineTo(rect.left, rect.top);
	pDC->LineTo(rect.left, rect.bottom);

	brushFill.CreateSolidBrush(Color);

	rect.InflateRect(-1, -1);
	pDC->FillRect(rect, &brushFill);

	pDC->SelectObject(&penDarkGray);
	pDC->MoveTo(rect.right - 1, rect.top);
	pDC->LineTo(rect.left, rect.top);
	pDC->LineTo(rect.left, rect.bottom);

//	penWhite.DeleteObject();
//	penBlack.DeleteObject();
//	penDarkGray.DeleteObject();
	if (ppenOld != NULL) pDC->SelectObject(ppenOld);

//	brushWhite.DeleteObject();
//	brushFill.DeleteObject();
	if (pbrushOld != NULL) pDC->SelectObject(pbrushOld);
}

void DrawButton(CDC* pDC, CRect rect, COLORREF Color)
{
	CPen	penWhite(PS_SOLID, 1, WHITE), penBlack(PS_SOLID, 1, BLACK), penDarkGray(PS_SOLID, 1, DARK_GRAY), penLightGray(PS_SOLID, 1, LIGHT_GRAY);
	CBrush	brushWhite, brushFill;

	CPen* ppenOld = (CPen *)pDC->SelectObject(&penWhite);
	CBrush* pbrushOld = pDC->SelectObject(&brushWhite);

	pDC->Rectangle(rect);

	pDC->SelectObject(&penBlack);
	pDC->MoveTo(rect.left, rect.bottom - 1);
	pDC->LineTo(rect.right - 1, rect.bottom - 1);
	pDC->LineTo(rect.right - 1, rect.top - 1);

	brushFill.CreateSolidBrush(Color);

	rect.InflateRect(-1, -1);
	pDC->FillRect(rect, &brushFill);

	pDC->SelectObject(&penDarkGray);
	pDC->MoveTo(rect.right - 1, rect.top);
	pDC->LineTo(rect.right - 1, rect.bottom - 1);
	pDC->LineTo(rect.left - 1, rect.bottom - 1);

//	penWhite.DeleteObject();
//	penBlack.DeleteObject();
//	penDarkGray.DeleteObject();
	if (ppenOld != NULL) pDC->SelectObject(ppenOld);

//	brushWhite.DeleteObject();
//	brushFill.DeleteObject();
	if (pbrushOld != NULL) pDC->SelectObject(pbrushOld);
}
