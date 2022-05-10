//S�ndor-Rokaly Kata

#pragma once
#include <iostream>

class CMyVectorException
{
	std::string error;
public:
	static constexpr const char* ErrIndex = "Hiba: index hiba!";
	static constexpr const char* ErrEmpty = "Hiba: �res vektor";
	static constexpr const char* ErrUnexpected = "Hiba: nem v�rt hiba!";

	CMyVectorException();
	CMyVectorException(const char* s);
	//~CMyStringException();
	const char* what(void);
};

