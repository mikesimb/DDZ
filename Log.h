#pragma once


class CLog
{
public:
	CLog();
	virtual ~CLog();
	static CLog* getInstance();

	bool OpenFile();
	bool FileIsOpen();
	void WriteLog(LPVOID lpBuffer,DWORD dwLength);
private:
	//文件名称
	char * m_szFileName;
	//文件句柄
	HANDLE m_hFile;

	
};

