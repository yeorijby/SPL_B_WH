// Log.h : Defines the class behaviors for the application.

#ifndef __LOG_H__
#define __LOG_H__

#ifndef ASCII_CR
#define ASCII_CR        0x0D
#endif

#define LOG_DISP_MAX	50000

#define LOG_SYSTEM		9999
// Version 1.1
#define LOG_NUM_SYSTEM	9999
#define LOG_NUM_UNKNOWN	9999

#define	LOG_TYPE_ALL	0
#define	LOG_TYPE_JOB	1
#define	LOG_TYPE_EVENT	2
#define	LOG_TYPE_ERROR	3
#define	LOG_TYPE_DEBUG	4
#define	LOG_TYPE_CNT	5

#define LOG_POS_ALL		0
#define LOG_POS_SYSTEM	1
#define LOG_POS_SC		2
#define LOG_POS_CV		3
#define LOG_POS_RGV		4
#define LOG_POS_HOST	5
#define LOG_POS_ECS		6
#define LOG_POS_CNT		7

class CEcsDoc;

class CLogEvent : public CObject
{
protected:
//	DECLARE_DYNCREATE(CLogEvent)
	DECLARE_SERIAL(CLogEvent)

// constructor & destructor
public:
	CLogEvent() {};
	CLogEvent(int nType, int nLogPos, int nLuggNum, CString strContent);

// Attributes
public:
	int m_nPos;
	int m_nType;
	CString m_strTime;
	int	m_nLuggNum;
	CString	m_strContent;

	// Version 1.1
	int m_nPosIndex;
	CString m_strFunction;

// Operation
public:
	CString GetPosition();
	CString GetPosition(int nPos);

// Implementation
public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
};

class CLog
{
// constructor & destructor
public:
	CLog(CEcsDoc* pDoc, CString strLogDir, CString strLogName);
	~CLog();
	
// Attributes
protected:
	CEcsDoc* m_pDoc;
public:
	CString	m_strLogFile;
	CString	m_strLogName;
	CString m_strLogDir;

// operations
public:
	void ExpiredFileRemove();
	BOOL Start();
	BOOL Load(CListCtrl* pListCtrl, int nDay, int nType, int nPos, int nLuggNum, int nFrom, int nTo);
	void Job(int nLogPos, int nLuggNum, CString strContent);
	void Event(int nLogPos, int nLuggNum, CString strContent);
	void Error(int nLogPos, int nLuggNum, CString strContent);
	void Debug(int nLogPos, int nLuggNum, CString strContent);
	void Write(int nType, int nLogPos, int nLuggNum, CString strContent);
};

#endif // __LOG_H__
