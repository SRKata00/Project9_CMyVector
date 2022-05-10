//Sándor-Rokaly Kata

#pragma once
#include <iostream>

class CMyStringException
{
	std::string error;
public:
	static constexpr const char* ErrOutOfRange = "Hiba: index hiba!";
	static constexpr const char* ErrInvalidChar = "Hiba: érvénytelen karakter!";
	static constexpr const char* ErrCount = "Hiba: cnt 0";
	static constexpr const char* ErrUnexpected = "Hiba: nem várt hiba!";

	CMyStringException();
	CMyStringException(const char* s);
	//~CMyStringException();
	const char* what(void);
};

