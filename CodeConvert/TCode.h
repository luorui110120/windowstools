#ifndef __TCode_H
#define __TCode_H

#include <string>

using namespace std;

#define BUF_LEN 2048

class TCodeMember
{
public:
	TCodeMember();
	virtual ~TCodeMember();
	TCodeMember& operator = (TCodeMember& src);

	void Clear();

public:
	string m_str; //GBK�ַ���
	unsigned char m_buf[BUF_LEN]; //���ֽڻ���
	unsigned short m_wbuf[BUF_LEN]; //˫�ֽڻ���
	int m_nUTF8Len; //����UTF8�ַ����ĳ���
};

class  TCode
{
public:
	TCode();
	TCode(TCode&);
	virtual ~TCode();
	TCode& operator = (TCode&);

	int ucslen(const unsigned short *ucs);
	int gbk_to_ucs2(const char *gbks);
	int ucs2_to_utf8(const unsigned short *ucs);
	int gbk_to_utf8(const char *gbks);
	int utf8_to_ucs2(const unsigned char *s, int slen);
	int ucs2_to_gbk(const unsigned short *ucs);
	int utf8_to_gbk(const unsigned char *s, int slen);

public:
	TCodeMember* m_data;
};

#endif
