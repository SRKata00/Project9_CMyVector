//Sándor-Rokaly Kata
//GHI00W

#include "cmystring.h"

#ifdef _DEBUG
	unsigned CMyString::m_iCounter=0;
#endif

void CMyString::setValues(const char* text)
{
	if (strlen(text) > m_nDataLength)
	{
		m_nDataLength = (unsigned)strlen(text);
		m_nAllocLength = m_nDataLength + 1;
		delete[] m_pchData;
		m_pchData = new char[m_nAllocLength];
		strcpy_s(m_pchData, m_nAllocLength, text);
	}
	else
	{
		m_nDataLength = (unsigned)strlen(text);
		strcpy_s(m_pchData, m_nAllocLength, text);
	}
}

CMyString::CMyString()
{
#ifdef _DEBUG
	m_iCounter++;
#endif

	m_nDataLength = (unsigned)strlen("\0");
	m_nAllocLength = m_nDataLength + 1;
	m_pchData = new char[m_nAllocLength];
	strcpy_s(m_pchData, m_nAllocLength, "\0");
}

CMyString::CMyString(const char* psz):CMyString()
{
	if (psz != nullptr)
	{
		setValues(psz);
	}
}

CMyString::CMyString(char ch, unsigned nRepeat)
{
	if (nRepeat <= 0)
	{
		throw CMyStringException(CMyStringException::ErrCount);
	}
	else if (ch == '\0')
	{
		throw CMyStringException(CMyStringException::ErrInvalidChar);
	}
	else
	{
#ifdef _DEBUG
		m_iCounter++;
#endif

		m_nDataLength = nRepeat;
		m_nAllocLength = m_nDataLength + 1;
		m_pchData = new char[m_nAllocLength];
		for (size_t i = 0; i < m_nDataLength; i++)
		{
			m_pchData[i] = ch;
		}
		m_pchData[m_nAllocLength-1] = '\0';
	}
}

CMyString::CMyString(const CMyString& str):CMyString()
{
	m_nDataLength = str.GetLength();
	m_nAllocLength = m_nDataLength+1;
	delete[] m_pchData;
	m_pchData = new char[m_nAllocLength];
	strcpy_s(m_pchData, m_nAllocLength, str.GetData());
}

CMyString::~CMyString()
{
#ifdef _DEBUG
	m_iCounter--;
#endif

	delete m_pchData;
}


#ifdef _DEBUG
unsigned CMyString::GetObjectCount()
{
	return m_iCounter;
}
#endif

CMyString& CMyString::operator=(const CMyString& string)
{
	if (string.GetLength() > m_nDataLength)
	{
		m_nDataLength = string.GetLength();
		m_nAllocLength = m_nDataLength + 1;
		delete m_pchData;
		m_pchData = new char[m_nAllocLength];
		strcpy_s(m_pchData, m_nAllocLength, string.GetData());
	}
	else
	{
		m_nDataLength = string.GetLength();
		strcpy_s(m_pchData, m_nAllocLength, string.GetData());
	}
	return *this;
}

unsigned CMyString::GetLength() const
{
	return m_nDataLength;
}

unsigned CMyString::GetCapacity() const
{
	return m_nAllocLength;
}

const char* CMyString::GetData() const
{
	return m_pchData;
}

char CMyString::GetAt(unsigned nIndex) const
{
	if (nIndex < m_nDataLength)
	{
		return m_pchData[nIndex];
	}
	else
	{
		throw CMyStringException(CMyStringException::ErrOutOfRange);
		return '\0';
	}
}

void CMyString::SetAt(unsigned nIndex, char ch)
{
	if (nIndex < m_nDataLength)
	{
		m_pchData[nIndex] = ch;
	}
	else
	{
		throw CMyStringException(CMyStringException::ErrOutOfRange);
	}
}

void CMyString::Append(const char* psz)
{
	if (psz != nullptr)
	{
		if (m_nDataLength == 0)
		{
			setValues(psz);
		}
		else
		{
			m_nDataLength = m_nDataLength + (unsigned)strlen(psz);
			if (m_nAllocLength <= m_nDataLength)
			{
				char* text = new char[m_nAllocLength];
				strcpy_s(text, m_nAllocLength, m_pchData);
				m_nAllocLength = m_nDataLength + 1;
				delete[] m_pchData;
				m_pchData = new char[m_nAllocLength];
				strcpy_s(m_pchData, m_nAllocLength, text);
				delete[] text;

			}
			strcat_s(m_pchData, m_nAllocLength, psz);
		}
	}
}

void CMyString::Display() const
{
	if (m_nDataLength > 0)
	{
		std::cout << m_pchData;
	}
}

void CMyString::Reverse()
{
	char* revert = new char[m_nAllocLength];
	strcpy_s(revert, m_nAllocLength, m_pchData);
	for (size_t i = 0; i< m_nDataLength; i++)
	{
		m_pchData[i] = revert[m_nDataLength-i-1];
	}
	delete[] revert;
}

// week 8

CMyString& CMyString::movetmp(CMyString& str)
{
		m_pchData = str.m_pchData;
		m_nDataLength = str.m_nDataLength;
		m_nAllocLength = str.m_nAllocLength;
		str.m_nDataLength = 0;
		str.m_nAllocLength = 1;
		str.m_pchData = new char[m_nAllocLength];
		strcpy_s(str.m_pchData, m_nAllocLength, "\0");
		return *this;
}

CMyString::CMyString(CMyString&& str)
{
	movetmp(str);
}

CMyString& CMyString::operator=(CMyString&& str)
{
	if (*this != str)
	{
		delete[] m_pchData;
		movetmp(str);
		return *this;
	}
	return *this;
}

char& CMyString::operator[](unsigned nIndex)
{
	if (nIndex < m_nDataLength)
	{
		return m_pchData[nIndex];
	}
	else
	{
		throw CMyStringException(CMyStringException::ErrOutOfRange);
	}
}
bool CMyString::operator==(const CMyString& s1)
{
	if (strcmp(m_pchData,s1.m_pchData))
	{
		return false;
	}
	return true;
}
CMyString::operator const char* ()
{
	const char* c = m_pchData;
	return c;
}
CMyString& CMyString::operator+=(const CMyString& str)
{
	Append(str.GetData());
	return *this;
}
CMyString& CMyString::operator+=(const char* p)
{
	Append(p);
	return *this;
}
CMyString CMyString::operator+(const CMyString& str1)
{
	CMyString tmp(*this);
	tmp.Append(str1.m_pchData);
	return tmp;
}

bool CMyString::operator<(const CMyString& s1)
{
	return !operator>(s1);
}

bool CMyString::operator>(const CMyString& s1)
{
	return (strcmp(m_pchData, s1.GetData()) > 0);
}

CMyString CMyString::SubString(unsigned pos, unsigned len)
{
	if (pos == m_nDataLength)
	{
		return CMyString();
	}
	else if (pos < m_nDataLength)
	{
		if ((len > m_nDataLength) || (len == (unsigned)-1))
		{
			len= m_nDataLength;
		}
		CMyString temp('_', len);
		for (unsigned i = 0; i < len; i++)
		{
			temp.SetAt(i, m_pchData[i]);
		}
		return temp;
	}
	else
	{
		throw CMyStringException(CMyStringException::ErrOutOfRange);
		return CMyString();
	}
}
void CMyString::Swap(CMyString& r1)
{
	CMyString tmp;
	tmp = std::move(r1);
	r1 = std::move(*this);
	*this = std::move(tmp);
}
std::ostream& operator << (std::ostream& os, CMyString& s)
{
	s.Display();
	return os;
}