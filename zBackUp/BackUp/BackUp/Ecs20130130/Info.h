// ScInfo.h : Defines the class behaviors for the application.

#ifndef __INFO_H__
#define __INFO_H__

#include "EcsDef.h"
#include <EcsEnv.h>

class CEcsDoc;

class CInfo : public CObject
{
protected:
	DECLARE_DYNCREATE(CInfo)

public:
	CEcsDoc* m_pDoc;
	CString m_strFileName;
	BOOL m_bModified;

	CString m_strErrMsg;

// constructor & destructor
public:
	CInfo();
	CInfo(CEcsDoc* pDoc, CString strFileName);
	~CInfo();

// operations
public:
	virtual BOOL Backup();
	virtual BOOL Restore();

// Implementation
public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
};

#endif



