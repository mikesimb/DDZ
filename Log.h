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
	//�ļ�����
	char * m_szFileName;
	//�ļ����
	HANDLE m_hFile;

	
};

