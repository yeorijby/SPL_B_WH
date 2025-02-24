// Statistic.h : Defines the class behaviors for the application.

#ifndef __STATISTIC_H__
#define __STATISTIC_H__

#include "EcsDef.h"

struct SStatisticErrorCnt
{
	int		nScNum;
	int		nErrorCode;
	int		nCount;
};

struct SStatisticInfo
{
	time_t	tBeginTime;
	time_t	tOnlineWorkTime;
	time_t	tOfflineWorkTime;
	time_t	tOnlineTroubleTime;
	time_t	tOfflineTroubleTime;
	int		nOnlineJobSum;
	int		nOfflineJobSum;
	int		nErrorSum;

	int     nTempOnlineJobSum;
	time_t	tTempOnlineWorkTime;
	time_t	tTempOnlineTroubleTime;
	time_t	tTempOnlineWaitTime;
};

class CEcsDoc;
class CStatistic : public CObject
{
protected:
	DECLARE_DYNCREATE(CStatistic)

// constructor & destructor
public:
	CStatistic();
	CStatistic(CEcsDoc* pDoc, CString strDir, CString strStcFileName, CString strErrFileName);
	~CStatistic();

// Attributes
public:
	CEcsDoc* m_pDoc;
	CString	m_strDir;
	CString	m_strStcFileName;
	CString	m_strErrFileName;
	SStatisticInfo	m_sSTC[SC_CNT];
	SStatisticErrorCnt	m_sCode[SC_CNT][SC_ERROR_KIND_CNT];

// operations
public:
	void	Restore();
	void	Backup();
	void	ExpiredFileRemove();
	time_t	InitProfile();
	void	WriteProfile();
	void	WriteErrCodeFile();
	void	Load(CListCtrl *pListCtrl, int nDay, int nScNuum, int nErrCode);
	void	RegistErrCode(int nScNum, int nErrCode);
	void	ResetStatisticInfo();

// Implementation
public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
};

#endif // __STATISTIC_H__
