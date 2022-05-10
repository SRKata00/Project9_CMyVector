//Sándor-Rokaly Kata

#include "cmyvector.h"

template CMyVector <int>;
template CMyVector <double>;
template CMyVector <char>;
template CMyVector <CMyString>;

template <class T>
CMyVector<T>::CMyVector():m_nCapacity(0),m_nSize(0),m_pData(nullptr)
{}

template <class T>
CMyVector<T>::CMyVector(unsigned n):m_nSize(n), m_nCapacity(n)
{
	m_pData = new T[n];
	for (size_t i = 0; i < n; i++)
	{
		m_pData[i] = T();
	}
}

template <class T>
CMyVector<T>::~CMyVector(void)
{
	delete[] m_pData;
}

template <class T>
T& CMyVector<T>::operator[](unsigned n)// Index operátor, m_nSize! 
{
	if (m_nSize == 0)
	{
		throw CMyVectorException(CMyVectorException::ErrEmpty);
	}
	if (n >= m_nSize)
	{
		throw CMyVectorException(CMyVectorException::ErrIndex);
	}
	return m_pData[n];
}

template <class T>
CMyVector<T>& CMyVector<T>::operator=(const CMyVector<T>& r) // Értékadás, m_nCapacity csak akkor változik, ha szükséges
{
	if (r.m_nSize > m_nCapacity)
	{
		delete[] m_pData;
		m_nCapacity = r.m_nSize;
		m_pData = new T[m_nCapacity];
	}
	for (size_t i = 0; i < r.m_nSize; i++)
	{
		m_pData[i] = r.m_pData[i];
	}
	m_nSize = r.m_nSize;
	return *this;
}

// Törli az elemeket -> m_nSize=0, m_nCapacity értéke marad, de újra foglalja a memóriát 
template <class T>
void CMyVector<T>::clear()
{
	m_nSize = 0;
	delete[] m_pData;
	m_pData = new T[m_nCapacity];
}

// Tömb végéhez fûzi az értéket, m_nSize növekszik, ha lehet, különben új memória -> 1,5*m_nCapacity, de min. 4 elem!
// def. konstuktor hívódik az új elemnél! 
template <class T>
void CMyVector<T>::push_back(const T& value)
{
	if (m_nCapacity == m_nSize)
	{
		unsigned p = (m_nCapacity * 1.5 > 4) ? m_nCapacity * 1.5 : 4;
		remakeCapacity(p);
	}
	m_pData[m_nSize++] = value;
	for (size_t i = m_nSize; i < m_nCapacity; i++)
	{
		m_pData[i] = T();
	}
}

// Listázza képernyõre az elemeket (m_nSize!), forma: index.: elem, ha üres , nem ír ki semmit! 
template <class T>
void CMyVector<T>::list()
{
	std::cout << std::endl;
	for (size_t i=0;i<m_nSize;i++)
	{
		std::cout << m_pData[i] << " ";
	}
}

// Tömböt rendezi csökkenõ (false), növekvõ(true) sorrendben
template <class T>
void CMyVector<T>::sort(bool f)
{
	if (f)
	{
		std::sort(m_pData, m_pData + m_nSize, [](T a, T b) {return a < b; });
	}
	else
	{
		std::sort(m_pData, m_pData + m_nSize, [](T a, T b) {return a > b; });
	}
}

// Beállítja új méretre (m_nSize!), ha nagyobb bõvíti (ha kell újra foglalja), ha kisebb lecsökkenti az elemszámot. 
template <class T>
void CMyVector<T>::resize(unsigned n) // m_nCapacity csak akkor változik, ha szükséges 
{
	if (m_nCapacity < n)
	{
		remakeCapacity(n);
	}
	m_nSize = n;
}

template <class T>
unsigned CMyVector<T>::size() // Tömb felhasznált mérete, T-ben, nem byte-ban! 
{
	return m_nSize;
}

template <class T>
unsigned CMyVector<T>::capacity() // Tömb valós mérete, T-ben, nem byte-ban! 
{
	return m_nCapacity;
}

template <class T>
void CMyVector<T>::shrink_to_fit()
{
	if (m_nCapacity > m_nSize)
	{
		remakeCapacity(m_nSize);
	}
}

template <class T>
void CMyVector<T> :: remakeCapacity(unsigned n)
{
	m_nCapacity = n;
	T* newData = m_pData;
	m_pData = new T[m_nCapacity];
	for (size_t i = 0; i < m_nSize; i++)
	{
		m_pData[i]=newData[i];
	}
}