//Sándor-Rokaly Kata
//GHI00W

#include "cmyvectorexception.h"
CMyVectorException::CMyVectorException()
{
}

CMyVectorException::CMyVectorException(const char* s)
{
	error = s;
}

const char* CMyVectorException::what(void)
{
	return error.c_str();
}
