#include "stdafx.h"
#include "TCode.h"


//TCodeMember
TCodeMember::TCodeMember()
{
	memset(m_buf, 0, sizeof(m_buf));
	memset(m_wbuf, 0, sizeof(m_wbuf));
	m_nUTF8Len = 0;
}

TCodeMember::~TCodeMember()
{
	Clear();
}

TCodeMember& TCodeMember::operator = (TCodeMember& src)
{
	m_str = src.m_str;
	memcpy(m_buf, src.m_buf, BUF_LEN);
	memcpy(m_wbuf, src.m_wbuf, sizeof(m_wbuf));
	m_nUTF8Len = src.m_nUTF8Len;
	return *this;
}

void TCodeMember::Clear()
{
	m_str = "";
	memset(m_buf, 0, sizeof(m_buf));
	memset(m_wbuf, 0, sizeof(m_wbuf));
	m_nUTF8Len = 0;
}


//TCode
TCode::TCode()
{
	m_data = new TCodeMember;
}

TCode::TCode(TCode& src)
{
	if(this == &src)
		return;
	m_data = new TCodeMember;
	*m_data = *src.m_data;
}

TCode::~TCode()
{
	if(m_data)
	{
		delete m_data;
		m_data = 0;
	}
}

TCode & TCode::operator = (TCode & src)
{
	if(this == &src)
		return *this;
	*m_data = *src.m_data;
	return *this;
}

int TCode::ucslen(const unsigned short *ucs)
{
	const unsigned short *p;
	int ucs_len = 0;

	p = ucs;
	while(*p++)
	{
		ucs_len++;
	}

	return ucs_len;
}

int TCode::gbk_to_ucs2(const char *gbks)
{
	int gbks_len = 0;
	gbks_len = strlen(gbks);
	memset(m_data->m_wbuf, 0, sizeof(m_data->m_wbuf));
	return MultiByteToWideChar(0, 0, gbks, gbks_len, m_data->m_wbuf, BUF_LEN);
}

int TCode::ucs2_to_utf8(const unsigned short *ucs)
{
	int ucs_len;
	ucs_len = ucslen(ucs);
	memset(m_data->m_buf, 0, sizeof(m_data->m_buf));
	int nRet = 0;
	nRet = WideCharToMultiByte(CP_UTF8, 0, ucs, ucs_len, (char *)m_data->m_buf,
		BUF_LEN, NULL, NULL);
	if(nRet)
		m_data->m_nUTF8Len = nRet;
	return nRet;
}

int TCode::gbk_to_utf8(const char *gbks)
{
	gbk_to_ucs2(gbks);
	return ucs2_to_utf8(m_data->m_wbuf);
}

int TCode::utf8_to_ucs2(const unsigned char *s, int slen)
{
	memset(m_data->m_wbuf, 0, sizeof(m_data->m_wbuf));
	return MultiByteToWideChar(CP_UTF8, 0, (const char *)s, slen,
		m_data->m_wbuf, BUF_LEN);
}

int TCode::ucs2_to_gbk(const unsigned short *ucs)
{
	int ucs_len;
	ucs_len = ucslen(ucs);
	int nRet = 0;
	memset(m_data->m_buf, 0, sizeof(m_data->m_buf));
	nRet = WideCharToMultiByte(0, 0, ucs, ucs_len, (char *)m_data->m_buf,
		BUF_LEN, NULL, NULL);
	if(nRet)
		m_data->m_str = (const char*)m_data->m_buf;
	return nRet;
}

int TCode::utf8_to_gbk( const unsigned char *s, int slen)
{
	utf8_to_ucs2(s, slen);
	int nRet = 0;
	nRet = ucs2_to_gbk(m_data->m_wbuf);
	if(nRet)
		m_data->m_str = (const char*)m_data->m_buf;
	return nRet;
}
