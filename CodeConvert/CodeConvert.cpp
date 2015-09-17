// CodeConvert.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CodeConvert.h"
#include "TCode.h"
#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CWinApp theApp;
using namespace std;
/** default file mode*/
char g_setcoding[5] = "-g2u";

/*!  detect if the fiel is UTF-8 code
\param LPCTSTR filename
\return true/false
*/
bool detect_utf8file(LPCTSTR filename)
{
	const unsigned char BOM[3] = {0xEF,0xBB,0xBF};
	int count_good_utf = 0;
	int count_bad_utf = 0;
	int begin = 0;
	char buf[3]={0,};
	CStdioFile file_r ;
	if(!file_r.Open((char*)(LPCTSTR)filename, CStdioFile::modeReadWrite))
		return false;
	
	file_r.Read(buf,3);
	if(!strncmp(buf,(char *)BOM,3)) {
		std::cout<<"this is utf(BOM). "<<endl;
		file_r.Close();
		return true;
	}
	else {    // detect the whole file 
		//	UTF-8 text encoding auto-detection
		//	count the following pairs of consecutive bytes as shown in the table:
		//	11..	10..	good
		//	00..	10..	bad
		//	10..	10..	don't care
		//	11..	00..	bad
		//	11..	11..	bad
		//	00..	00..	don't care
		//	10..	00..	don't care
		//	00..	11..	don't care
		//	10..	11..	don't care
		char current_byte,previous_byte;
		file_r.SeekToBegin();
		file_r.Read(&current_byte,1);
		previous_byte = current_byte;
		while(file_r.Read(&current_byte,1)) {
			if ((current_byte & 0xC0) == 0x80) {
				if ((previous_byte & 0xC0) == 0xC0) {
					count_good_utf ++;
				} else if ((previous_byte & 0x80) == 0x00) {
					count_bad_utf ++;
				}
			} else if ((previous_byte & 0xC0) == 0xC0 ){
				count_bad_utf ++;
			}
			previous_byte = current_byte;
		}
		//	the comparison ">=" handles pure ASCII files as UTF-8,
		//	replace it with ">" to change that
		
		if(count_good_utf > count_bad_utf) {
			file_r.Close();
			std::cout<<"the code of this file is utf(no BOM). "<<endl;
			return true;
		} else if(count_good_utf == count_bad_utf) {
			file_r.Close();
			std::cout<<"the code of this file is pure ASCII file as UTF-8. "<<endl;	
			return true;
		}
		else {
			file_r.Close();
			std::cout<<"the code of this file is not utf. "<<endl;
			return false;	
		}
	}
	
}

/////////////////////////////////////////////////////////////////////////////
// The one and only application object
bool code_convert_GB2UTF8(LPCTSTR filename)
{
	/** the convert file name*/
	CString strSave;
	strSave.Format("%s_bak",filename);
	DeleteFile((char*)(LPCTSTR)strSave);
	/** rename the oldfile*/
	CStdioFile::Rename(filename,strSave);
	/**open the oldfile*/
	CStdioFile stdiofile_r ,stdiofile_w;
	if(!stdiofile_r.Open(strSave, CStdioFile::modeReadWrite))
		return false;
	/**create the newfile*/
	if(!stdiofile_w.Open(filename, CStdioFile::modeReadWrite | CStdioFile ::modeCreate))
		return false;
	/**white loop read the file*/
	CString strValue;
	while(stdiofile_r.ReadString(strValue))
	{
		TCode m_tcode;
		m_tcode.gbk_to_utf8((char*)(LPCSTR)strValue);
		//	std::cout << m_tcode.m_data->m_buf <<endl;   
		char *p = (char*)m_tcode.m_data->m_buf;
		stdiofile_w.WriteString(p);
		stdiofile_w.WriteString("\n");
	}
	/**close all the handle of the cfile*/
	stdiofile_r.Close();     
	stdiofile_w.Close();   
	return true;
}
bool code_convert_UTF82GB(LPCTSTR filename)
{
	/** the convert file name*/
	CString strSave;
	strSave.Format("%s_bak",filename);
	DeleteFile((char*)(LPCTSTR)strSave);
	/** rename the oldfile*/
	CStdioFile::Rename(filename,strSave);
	
	// detect if the fiel is UTF-8 code
	if(detect_utf8file(strSave) == false) {
		CStdioFile::Rename(strSave,filename);  // restore
		return false;
	}
	
	
	
	/**open the oldfile*/
	CStdioFile stdiofile_r ,stdiofile_w;
	if(!stdiofile_r.Open(strSave, CStdioFile::modeReadWrite))
		return false;
	/**create the newfile*/
	if(!stdiofile_w.Open(filename, CStdioFile::modeReadWrite | CStdioFile ::modeCreate))
		return false;
	/**white loop read the file*/
	CString strValue;	
	while(stdiofile_r.ReadString(strValue))
	{
		TCode m_tcode;
		m_tcode.utf8_to_gbk((unsigned char *) (LPCSTR)strValue,strValue.GetLength());
		//	std::cout << m_tcode.m_data->m_buf <<endl;   
		char *p = (char*)m_tcode.m_data->m_buf;
		stdiofile_w.WriteString(p);
		stdiofile_w.WriteString("\n");
	}
	/**close all the handle of the cfile*/
	stdiofile_r.Close();     
	stdiofile_w.Close();   
	return true;
}
bool find_cpp_files(LPCTSTR DirName)
{
	CFileFind tempFind;//声明一个CFileFind类变量，以用来搜索
	char tempFileFind[200];//用于定义搜索格式
	
	sprintf(tempFileFind,"%s\\*.*",DirName);	//匹配格式为*.*,即该目录下的所有文件
	
	BOOL IsFinded=(BOOL)tempFind.FindFile(tempFileFind);	//查找第一个文件
	
	while(IsFinded)
	{
		IsFinded=(BOOL)tempFind.FindNextFile();	//递归搜索其他的文件
		if(!tempFind.IsDots())	//如果不是"."目录
		{
			char foundFileName[200];
			strcpy(foundFileName,tempFind.GetFileName().GetBuffer(200));
			if(tempFind.IsDirectory())//如果是目录，则递归地调用
			{
				char tempDir[MAX_PATH];
				sprintf(tempDir,"%s\\%s",DirName,foundFileName); 
				//				sprintf(tempDir,"%s",DirName);// zzl
				printf(tempDir);
				find_cpp_files(tempDir);
			}
			else
			{
				
				CString tempFileName = tempFind.GetFilePath();			
				TCHAR szDir[_MAX_DIR];
				_tsplitpath(tempFileName, NULL, NULL, NULL,  szDir);
				if (stricmp(szDir,".cpp") ==0||
					stricmp(szDir,".h") ==0||
					stricmp(szDir,".xml") ==0||
					stricmp(szDir,".cxx") ==0||
					stricmp(szDir,".java") ==0||
					stricmp(szDir,".c") ==0 ||
					stricmp(szDir,".txt") ==0)
				{
					std::cout << (char*)(LPCTSTR)tempFileName<< std::endl;
					if (strncmp(g_setcoding,"-u2g",2) == 0)
					{
						code_convert_UTF82GB(tempFileName);
					}
					else if (strncmp(g_setcoding,"-g2u",2) == 0)
					{
						code_convert_GB2UTF8(tempFileName);
					}
					
				}
				
			}
		}
	}
	tempFind.Close();
	return TRUE;
}

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	std::string filedir;
	
	std::cout << "/**************************************************"<< std::endl;
	std::cout << "*UTF-8/GB2312编码互换工具 CodeCervt ver 1.1"<< std::endl;
	std::cout << "*author :zuji.pan Email:apansoft@gmail.com  \n modify by zhangzhilong zealane@gmail.com \n 2009.10.13"<<std::endl;
	//std::cout << "请输入要转换的文件路径,eg: 'D:\\CodeConvert\\Debug\\',\n转换程序所在的当前目录请输入 '-'"<< std::endl;
	std::cout << "***************************************************/"<< std::endl;
	
	if (argc < 3 ) {
		std::cout<< "Usage:\n";
		std::cout<< argv[0] <<" <-mode> <SrcPath>\n";
		std::cout<< "parameter <Mode> \n";
		std::cout<< "u2g means Convert from UTF-8 to GB2312\n";
		std::cout<< "g2u means Convert from GB2312 to UTF-8\n";
		std::cout<< "parameter <SrcPath>\n";
		std::cout<< "Directory of files which is to be converted. '-' means current directory.";
		
		exit(1);
	}
	strcpy(g_setcoding,argv[1]);
	//	argv1=argv[1];
	filedir=argv[2];
	
	//	std::cin >> filedir;
	if (filedir == "-")
	{
		TCHAR szFull[_MAX_PATH];
		TCHAR szDrive[_MAX_DRIVE];
		TCHAR szDir[_MAX_DIR];
		TCHAR szFilePath[_MAX_PATH];
		::GetModuleFileName(NULL, szFull, sizeof(szFull)/sizeof(TCHAR));
		_tsplitpath(szFull, szDrive, szDir, NULL,  NULL);
		sprintf(szFilePath,"%s%s",szDrive,szDir);
		
		/*	CString strAppPath; 
		::GetModuleFileName(NULL,strAppPath.GetBuffer(_MAX_PATH), _MAX_PATH);   
		strAppPath.ReleaseBuffer();   
		int nPos = strAppPath.ReverseFind('\\');
		filedir = (LPTSTR)(LPCTSTR)strAppPath.Left(nPos + 1);*/
		filedir = szFilePath;
		std::cout << "你选择的目录是:"<<filedir<< std::endl;
	}
	std::cout <<"你选择的编码转换方式：";
	if (!strcmp(g_setcoding,"-u2g")) {
		std::cout<<" UTF8 to GB321"<<std::endl;
	} else if (!strcmp(g_setcoding,"-g2u")) {
		std::cout<<" GB321 to UTF8"<<std::endl;
	} else {
		std::cout<<"错误"<<std::endl;
		exit(1);
	}
	
	find_cpp_files(filedir.c_str());
	getchar();
	return 0;
}


