//Sándor-Rokaly Kata

#include "cmyvector.h"
#define INIT_CAPACITY 4
#define INIT_SIZE 4

int main()
{
	CMyVector<int> iv1(INIT_CAPACITY);
	CMyVector<double> dv1(INIT_CAPACITY);
	CMyVector<char> cv1(INIT_CAPACITY);
	CMyVector<CMyString> sv1(INIT_CAPACITY);
	for (size_t i = 1; i <= INIT_SIZE; i=i+2)
	{
		dv1[i-1]=i + 1.2;
		dv1[i] = i - 1.2;
		iv1[i-1] = i + 1;
		iv1[i] = i - 1;
		cv1[i-1] = i + 68;
		cv1[i] = 90 - i;
	}
	CMyString s1("alma"), s2, s3("eper"), s4("kiwi");
	sv1[0] = s1;
	sv1[1] = s2;
	sv1[2] = s3;
	sv1[3] = s4;

	iv1.list();
	cv1.list();
	dv1.list();
	sv1.list();

	iv1.sort(true);
	cv1.sort(false);
	dv1.sort(false);
	sv1.sort(true);

	iv1.list();
	cv1.list();
	dv1.list();
	sv1.list();
	return 0;
}