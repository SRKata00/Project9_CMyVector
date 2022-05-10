//Sándor-Rokaly Kata
//GHI00W

#include "cmystringexception.h"

CMyStringException::CMyStringException()
{
}

CMyStringException::CMyStringException(const char* s)
{
	error = s;
}

const char* CMyStringException::what(void)
{
	return error.c_str();
}
