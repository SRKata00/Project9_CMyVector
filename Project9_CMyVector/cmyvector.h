//Sándor-Rokaly Kata
//GHI00W

#pragma once
#include <iostream>
#include <algorithm>
#include "cmyvectorexception.h"
#include "cmystring.h"

template <class T>
class CMyVector
{ 
public:
	CMyVector();
	CMyVector(unsigned n);
	~CMyVector(); 
	T& operator[](unsigned n);
	CMyVector<T> & operator=(const CMyVector<T> & r);
	void clear();
	void push_back(const T& value); 
	void list(); 
	void sort(bool f); 
	void resize(unsigned n);
	unsigned size(); 
	unsigned capacity();
	void shrink_to_fit();

private:
	T * m_pData;
	unsigned m_nSize;
	unsigned m_nCapacity; 

	void remakeCapacity(unsigned n);
};

