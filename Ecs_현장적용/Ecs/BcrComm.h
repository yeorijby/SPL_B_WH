// PLC Melsec Class

#ifndef __PLC_H__
#define __PLC_H__

#include "Serial.h"
#include "Thread.h"
#include "ConveyorTrackInfo.h"
#include "EcsDoc.h"

class CBcr : public CSerial
{
// constructor & destructor
public:
	CBcr() : CSerial() { m_byAddr = 0xFF; };
	CBcr(int nNum, CEcsDoc* pDoc);

// Attributes
public:
	CEcsDoc* m_pDoc;
	int m_nNum;

// Attributes
protected:
public:
	BYTE m_byAddr;

// operations
public:
	BOOL Connect(LPSTR strCommName,
  			     DWORD dwBaudRate = (DWORD)9600,
				 BYTE byByteSize = (BYTE)8,
				 BYTE byParity = NOPARITY,
				 BYTE byStopBits = ONESTOPBIT,
				 BYTE byFlowCtrl = 0);
	int  ReadStatus();
	BOOL Response();
    void ParsingFrame(BYTE *, int nLen);
	void ParsingFrame2();

	
// Overrides
};

#endif // __PLC_H__
