//Sándor-Rokaly Kata

#pragma once
#include <iostream>

class CMyVectorException
{
	std::string error;
public:
	static constexpr const char* ErrIndex = "Hiba: index hiba!";
	static constexpr const char* ErrEmpty = "Hiba: üres vektor";
	static constexpr const char* ErrUnexpected = "Hiba: nem várt hiba!";

	CMyVectorException();
	CMyVectorException(const char* s);
	//~CMyStringException();
	const char* what(void);
};

