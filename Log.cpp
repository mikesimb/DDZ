#include "stdafx.h"
#include "Log.h"


static CLog* g_log;
CLog::CLog()
{
	m_hFile = INVALID_HANDLE_VALUE;
	m_szFileName = new char[MAX_PATH];
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

void CLog::InitializeLogFile()
{
	char path[MAX_PATH];
	GetModuleFileName(NULL, path, MAX_PATH);
	//首先要获取到当前的模块文件路径
	char drive[_MAX_DRIVE], dir[_MAX_DIR], fname[_MAX_FNAME], ext[_MAX_EXT];
	_splitpath_s(path, drive, dir, fname, ext);
	char curpath[MAX_PATH];
	sprintf_s(curpath, MAX_PATH, "%s%s", drive, dir);
	SetCurrentDirectory(curpath);
	char filename[MAX_PATH];
	//文件名是一个以日期为核心的文件名
	time_t rawtime;
	struct tm* timeinfo =new tm;
	char timE[MAX_PATH];
	time(&rawtime);
	localtime_s(timeinfo,&rawtime);
	strftime(timE, 80, "Log%Y-%m-%d.log", timeinfo);
	sprintf_s(filename, MAX_PATH, "%s%s", curpath, timE);

	setLogFilename(filename);
	OpenFile();
}

void CLog::setLogFilename(char* pFilename)
{
	memcpy_s(m_szFileName, MAX_PATH, pFilename, MAX_PATH);
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
		return true;
	}
	else
		return false;
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

