#include "stdafx.h"
#include "Log.h"


static CLog* g_log;
CLog::CLog()
{
	m_hFile = INVALID_HANDLE_VALUE;
}


CLog::~CLog()
{
}

CLog* CLog::getInstance()
{
	if (g_log == NULL)
		g_log = new CLog();
	return g_log;
}

bool CLog::OpenFile()
{
  if (FileIsOpen())
			return true;

		if (!m_szFileName)
			return false;

		m_hFile = CreateFile(
			m_szFileName,
			GENERIC_WRITE,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL
		);

		if (!FileIsOpen() && GetLastError() == 2)//打开不成功，且因为文件不存在， 创建文件
			m_hFile = CreateFile(
				m_szFileName,
				GENERIC_WRITE,
				FILE_SHARE_READ | FILE_SHARE_WRITE,
				NULL,
				OPEN_ALWAYS,
				FILE_ATTRIBUTE_NORMAL,
				NULL
			);

		if (FileIsOpen())
			SetFilePointer(m_hFile, 0, NULL, FILE_END);

		return FileIsOpen();
}

bool CLog::FileIsOpen()
{
	if (m_hFile != INVALID_HANDLE_VALUE)
	{
		return false;
	}
	else
		return true;
}

void CLog::WriteLog(LPVOID lpBuffer, DWORD dwLength)
{
	time_t now;
	char temp[21];
	DWORD dwWriteLength;

	if (FileIsOpen())
	{
		struct tm* timeinfo =new tm;
		char timE[80];
		time(&now);
		localtime_s(timeinfo,&now);
		strftime(timE, 80, "Data:\n%Y-%m-%d\nTime:\n%I:%M:%S\n", timeinfo);

		WriteFile(m_hFile, "/xd/xa#-----------------------------", 32, &dwWriteLength, NULL);
		WriteFile(m_hFile, temp, 19, &dwWriteLength, NULL);
		WriteFile(m_hFile, "-----------------------------#/xd/xa", 32, &dwWriteLength, NULL);
		WriteFile(m_hFile, lpBuffer, dwLength, &dwWriteLength, NULL);
		WriteFile(m_hFile, "/xd/xa", 2, &dwWriteLength, NULL);

		FlushFileBuffers(m_hFile);

	}
}

