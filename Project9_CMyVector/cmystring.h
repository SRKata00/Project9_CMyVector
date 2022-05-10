//Sándor-Rokaly Kata

#pragma once
#include <ostream>
#include "cmystringexception.h"

class CMyString
{
public:
	CMyString();
	CMyString(const char* psz);
	CMyString(char ch, unsigned nRepeat=1);
	CMyString(const CMyString& str);
	~CMyString();
	CMyString& operator=(const CMyString& string);
	unsigned GetLength() const;
	unsigned GetCapacity() const;
	const char* GetData() const;
	char GetAt(unsigned nIndex) const;
	void SetAt(unsigned nIndex, char ch);
	void Append(const char* psz);
	void Display() const;
	void Reverse();
//week 8
	CMyString(CMyString&& str);//move constr
	CMyString& operator=(CMyString&& str);//move ertekado op
	char& operator[](unsigned nIndex); //->ErrOutofRange
	bool operator==(const CMyString& s1);//=true;!=false
	bool operator<(const CMyString& s1);
	bool operator>(const CMyString& s1);
	operator const char* (); //cast
	CMyString& operator+=(const CMyString& str);
	CMyString& operator+=(const char* p);
	CMyString operator+(const CMyString& str1);//nem refet ad vissza
	CMyString SubString(unsigned pos, unsigned len = -1);
	void Swap(CMyString& r1);

#ifdef _DEBUG
	static unsigned GetObjectCount();
#endif

private:
	char* m_pchData;
	unsigned m_nDataLength;
	unsigned m_nAllocLength;
	void setValues(const char* text);
	//week 8
	CMyString& movetmp(CMyString& str);

#ifdef _DEBUG
	static unsigned m_iCounter;
#endif

	


};

std::ostream& operator << (std::ostream& os, CMyString& s);