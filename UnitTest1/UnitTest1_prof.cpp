#include "pch.h"
#include "CppUnitTest.h"

#include <iostream>
#include <string.h>
#include <stdlib.h>

#include "..\Project9_CMyVector\cmystring.h"
#include "..\Project9_CMyVector\cmyvector.h"
#include "..\Project9_CMyVector\cmystringexception.h"
#include "..\Project9_CMyVector\cmyvectorexception.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

//using namespace MyString;


//char, int, double, CMyString
//.cpp-ben példányosítva!

extern template CMyVector <char>;
extern template CMyVector <int>;
extern template CMyVector <double>;
extern template CMyVector <CMyString>;

//Így egyszerûbb...
typedef CMyVector<char> CharVector;
typedef CMyVector<int> IntVector;
typedef CMyVector<double> DoubleVector;
typedef CMyVector<CMyString> CMyStringVector;

#define _MAXTEST  5u

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		//********************************************
		TEST_METHOD(Testchar)
		{
			struct test_char {
				char ori[_MAXTEST] = { '5','1', '3','4', '1' };
				char growing[_MAXTEST] = { '1','1', '3','4', '5' };
				char decreasing[_MAXTEST] = { '5','4', '3','1', '1' };
			} Test;

			//WRITE("********* TestChar  **");

			try 
			{
				int i;
				//WRITE("> t, Def  ");
				CharVector t;
				Assert::AreEqual(0u, t.size());
				Assert::AreEqual(0u, t.capacity());

				//WRITE("resize");
				t.resize(_MAXTEST);
				Assert::AreEqual(_MAXTEST, t.size());
				Assert::AreEqual(_MAXTEST, t.capacity());

				//WRITE("Ori");
				for (i = 0; i < _MAXTEST; i++)
				{
					t[i] = Test.ori[i];
				}

				//WRITE("Decreasing");
				t.sort(false);
				for (i = 0; i < _MAXTEST; i++)
				{
					Assert::AreEqual(Test.decreasing[i], t[i]);
				}

				//WRITE("Growing");
				t.sort(true);
				for (i = 0; i < _MAXTEST; i++)
				{
					Assert::AreEqual(Test.growing[i], t[i]);
				}


				//WRITE("> t2, 2 items");
				CharVector t2(2);
				Assert::AreEqual(2u, t2.size());
				Assert::AreEqual(2u, t2.capacity());

				t2[0] = Test.ori[0];
				t2[1] = Test.ori[1];

				//WRITE("resize");
				t2.resize(_MAXTEST);
				Assert::AreEqual(_MAXTEST, t2.size());
				Assert::AreEqual(_MAXTEST, t2.capacity());

				//WRITE("Ori");
				for (i = 2; i < _MAXTEST; i++)
				{
					t2[i] = Test.ori[i];
				}

				//WRITE("Decreasing");
				t2.sort(false);
				for (i = 0; i < _MAXTEST; i++)
				{
					Assert::AreEqual(Test.decreasing[i], t2[i]);
				}

				//WRITE("Growing");
				t2.sort(true);
				for (i = 0; i < _MAXTEST; i++)
				{
					Assert::AreEqual(Test.growing[i], t2[i]);
				}


				//WRITE("resize2");
				CharVector t3(_MAXTEST);
				for (i = 0; i < _MAXTEST; i++)
				{
					t3[i] = Test.ori[i];
				}
				t3.resize(_MAXTEST); //nem változhat semmi!
				for (i = 0; i < _MAXTEST; i++)
				{
					Assert::AreEqual(Test.ori[i], t3[i]);
				}
				Assert::AreEqual(_MAXTEST, t3.size());
				Assert::AreEqual(_MAXTEST, t3.capacity());

				t3.resize(1u); //capacity nem változhat!
				Assert::AreEqual(Test.ori[0u], t3[0u]);
				Assert::AreEqual(1u, t3.size());
				Assert::AreEqual(_MAXTEST, t3.capacity());

				//WRITE("clear");
				t3.clear();
				Assert::AreEqual(0u, t3.size());
				Assert::AreEqual(_MAXTEST, t3.capacity());

				//WRITE("resize3");
				t3.resize(_MAXTEST); 
				for (i = 0; i < _MAXTEST; i++)
				{
					t3[i] = Test.ori[i];
				}
				Assert::AreEqual(_MAXTEST, t3.size());
				Assert::AreEqual(_MAXTEST, t3.capacity());

				//WRITE("operator=");
				CharVector t4(2u);
				for (i = 0; i < 2u; i++)
				{
					t4[i] = Test.ori[i+2]; //0->2, 1->3 !
				}
				t3 = t4;  //t3-ban _MAXTEST capacity!
				Assert::AreEqual(2u, t3.size());
				Assert::AreEqual(_MAXTEST, t3.capacity());

				for (i = 0; i < 2u; i++)
				{
					Assert::AreEqual(Test.ori[i+2], t3[i]);
				}

				//WRITE("push_back");
				t4.resize(_MAXTEST);
				for (i = 0; i < _MAXTEST; i++)
				{
					t4[i] = Test.ori[i];
				}
				t4.push_back(Test.ori[0]);
				Assert::AreEqual(_MAXTEST+1u, t4.size());
				Assert::AreEqual(7u, t4.capacity()); // 5 * 1,5 -> 7!  , min. 4 !
				Assert::AreEqual(Test.ori[0], t4[_MAXTEST]);

				//WRITE("> exceptions");
				//WRITE("Empty");
				try {
					CharVector t; 
					t[0] = '1';
					Assert::IsTrue(false);
				}
				catch (CMyVectorException & e){ Assert::AreEqual(CMyVectorException::ErrEmpty, e.what());}
				catch (...)	{ //WRITE("catch(...)");	
					Assert::IsTrue(false);}

				//WRITE("Index");
				try {
					CharVector t(5);
					t[10] = '1';
					Assert::IsTrue(false);
				}
				catch (CMyVectorException& e) { Assert::AreEqual(CMyVectorException::ErrIndex, e.what()); }
				catch (...) { //WRITE("catch(...)");	
					Assert::IsTrue(false); }

				//WRITE("shrink");
				CharVector t5(_MAXTEST);
				for (i = 0; i < _MAXTEST; i++)
				{
					t5[i] = Test.ori[i];
				}

				t5.push_back(Test.ori[0]);

				Assert::AreEqual(_MAXTEST + 1u, t5.size());
				Assert::AreEqual((unsigned)(_MAXTEST * 1.5), t5.capacity());
				t5.shrink_to_fit();
				Assert::AreEqual(_MAXTEST + 1, t5.size());
				Assert::AreEqual(_MAXTEST + 1, t5.capacity());

			}
			catch (CMyVectorException &e)
			{
				//WRITE("catch (CMyVectorException & e)");
				//WRITE(e.what());
				Assert::IsTrue(false);
			}
			catch (...)
			{
				//WRITE("catch (...)");
				Assert::IsTrue(false);
			}

			//WRITE("** done **");

		}

		//********************************************
		TEST_METHOD(Testint)
		{
			struct test_int {
				int ori[_MAXTEST] = { -12, 345, 0, 5, -16000 };
				int growing[_MAXTEST] = { -16000, -12, 0, 5, 345 };
				int decreasing[_MAXTEST] = { 345, 5, 0, -12, -16000 };
			} Test;

			//WRITE("********* TestInt  **");

			try 
			{
				int i;
				//WRITE("> t, Def  ");
				IntVector t;
				Assert::AreEqual(0u, t.size());
				Assert::AreEqual(0u, t.capacity());

				//WRITE("resize");
				t.resize(_MAXTEST);
				Assert::AreEqual(_MAXTEST, t.size());
				Assert::AreEqual(_MAXTEST, t.capacity());

				//WRITE("Ori");
				for (i = 0; i < _MAXTEST; i++)
				{
					t[i] = Test.ori[i];
				}

				//WRITE("Decreasing");
				t.sort(false);
				for (i = 0; i < _MAXTEST; i++)
				{
					Assert::AreEqual(Test.decreasing[i], t[i]);
				}

				//WRITE("Growing");
				t.sort(true);
				for (i = 0; i < _MAXTEST; i++)
				{
					Assert::AreEqual(Test.growing[i], t[i]);
				}


				//WRITE("> t2, 2 items");
				IntVector t2(2);
				Assert::AreEqual(2u, t2.size());
				Assert::AreEqual(2u, t2.capacity());

				t2[0] = Test.ori[0];
				t2[1] = Test.ori[1];

				//WRITE("resize");
				t2.resize(_MAXTEST);
				Assert::AreEqual(_MAXTEST, t2.size());
				Assert::AreEqual(_MAXTEST, t2.capacity());

				//WRITE("Ori");
				for (i = 2; i < _MAXTEST; i++)
				{
					t2[i] = Test.ori[i];
				}

				//WRITE("Decreasing");
				//for (j = 0; j < _MAXTEST; j++) //WRITE(t[j]);
				t2.sort(false);
				//for (j = 0; j < _MAXTEST; j++) //WRITE(t[j]);

				for (i = 0; i < _MAXTEST; i++)
				{
					Assert::AreEqual(Test.decreasing[i], t2[i]);
				}

				//WRITE("Growing");
				t2.sort(true);
				for (i = 0; i < _MAXTEST; i++)
				{
					Assert::AreEqual(Test.growing[i], t2[i]);
				}



				//WRITE("resize2");
				IntVector t3(_MAXTEST);
				for (i = 0; i < _MAXTEST; i++)
				{
					t3[i] = Test.ori[i];
				}
				t3.resize(_MAXTEST); //nem változhat semmi!
				for (i = 0; i < _MAXTEST; i++)
				{
					Assert::AreEqual(Test.ori[i], t3[i]);
				}
				Assert::AreEqual(_MAXTEST, t3.size());
				Assert::AreEqual(_MAXTEST, t3.capacity());

				t3.resize(1u); //capacity nem változhat!
				Assert::AreEqual(Test.ori[0u], t3[0u]);
				Assert::AreEqual(1u, t3.size());
				Assert::AreEqual(_MAXTEST, t3.capacity());

				//WRITE("clear");
				t3.clear();
				Assert::AreEqual(0u, t3.size());
				Assert::AreEqual(_MAXTEST, t3.capacity());

				//WRITE("resize3");
				t3.resize(_MAXTEST);
				for (i = 0; i < _MAXTEST; i++)
				{
					t3[i] = Test.ori[i];
				}
				Assert::AreEqual(_MAXTEST, t3.size());
				Assert::AreEqual(_MAXTEST, t3.capacity());

				//WRITE("operator=");
				IntVector t4(2u);
				for (i = 0; i < 2u; i++)
				{
					t4[i] = Test.ori[i + 2]; //0->2, 1->3 !
				}
				t3 = t4;  //t3-ban _MAXTEST elem!
				Assert::AreEqual(2u, t3.size());
				Assert::AreEqual(_MAXTEST, t3.capacity());

				for (i = 0; i < 2u; i++)
				{
					Assert::AreEqual(Test.ori[i + 2], t3[i]);
				}

				//WRITE("push_back");
				t4.resize(_MAXTEST);
				for (i = 0; i < _MAXTEST; i++)
				{
					t4[i] = Test.ori[i];
				}
				t4.push_back(Test.ori[0]);
				Assert::AreEqual(_MAXTEST + 1u, t4.size());
				Assert::AreEqual(7u, t4.capacity()); // 5 * 1,5 -> 7! 
				Assert::AreEqual(Test.ori[0], t4[_MAXTEST]);

				//WRITE("> exceptions");
				//WRITE("Empty");
				try {
					IntVector t;
					t[0] = 1;
					Assert::IsTrue(false);
				}
				catch (CMyVectorException& e) { Assert::AreEqual(CMyVectorException::ErrEmpty, e.what()); }
				catch (...) { //WRITE("catch(...)");	
					Assert::IsTrue(false); }

				//WRITE("Index");
				try {
					IntVector t(5);
					t[10] = 1;
					Assert::IsTrue(false);
				}
				catch (CMyVectorException& e) { Assert::AreEqual(CMyVectorException::ErrIndex, e.what()); }
				catch (...) { //WRITE("catch(...)");	
					Assert::IsTrue(false); }


				//WRITE("shrink");
				IntVector t5(_MAXTEST);
				for (i = 0; i < _MAXTEST; i++)
				{
					t5[i] = Test.ori[i];
				}

				t5.push_back(Test.ori[0]);

				Assert::AreEqual(_MAXTEST + 1u, t5.size());
				Assert::AreEqual((unsigned)(_MAXTEST * 1.5), t5.capacity());
				t5.shrink_to_fit();
				Assert::AreEqual(_MAXTEST + 1, t5.size());
				Assert::AreEqual(_MAXTEST + 1, t5.capacity());

			}
			catch (CMyVectorException& e)
			{
				//WRITE("catch (CMyVectorException & e)");
				//WRITE(e.what());
				Assert::IsTrue(false);
			}
			catch (...)
			{
				//WRITE("catch (...)");
				Assert::IsTrue(false);
			}

			//WRITE("** done **");

		}

		//********************************************
		TEST_METHOD(Testdouble)
		{
			struct test_double {
				double ori[_MAXTEST] = { -12.0, 345.0, 0.0, 5.0, -16000.0 };
				double growing[_MAXTEST] = { -16000.0, -12.0, 0.0, 5.0, 345.0 };
				double decreasing[_MAXTEST] = { 345.0, 5.0, 0.0, -12.0, -16000.0 };
			} Test;

			//WRITE("********* TestDouble  **");

			try
			{
				int i;
				//WRITE("> t, Def  ");
				DoubleVector t;
				Assert::AreEqual(0u, t.size());
				Assert::AreEqual(0u, t.capacity());

				//WRITE("resize");
				t.resize(_MAXTEST);
				Assert::AreEqual(_MAXTEST, t.size());
				Assert::AreEqual(_MAXTEST, t.capacity());

				//WRITE("Ori");
				for (i = 0; i < _MAXTEST; i++)
				{
					t[i] = Test.ori[i];
				}

				//WRITE("Decreasing");
				t.sort(false);
				for (i = 0; i < _MAXTEST; i++)
				{
					Assert::AreEqual(Test.decreasing[i], t[i]);
				}

				//WRITE("Growing");
				t.sort(true);
				for (i = 0; i < _MAXTEST; i++)
				{
					Assert::AreEqual(Test.growing[i], t[i]);
				}


				//WRITE("> t2, 2 items");
				DoubleVector t2(2);
				Assert::AreEqual(2u, t2.size());
				Assert::AreEqual(2u, t2.capacity());

				t2[0] = Test.ori[0];
				t2[1] = Test.ori[1];

				//WRITE("resize");
				t2.resize(_MAXTEST);
				Assert::AreEqual(_MAXTEST, t2.size());
				Assert::AreEqual(_MAXTEST, t2.capacity());

				//WRITE("Ori");
				for (i = 2; i < _MAXTEST; i++)
				{
					t2[i] = Test.ori[i];
				}

				//WRITE("Decreasing");
				t2.sort(false);
				for (i = 0; i < _MAXTEST; i++)
				{
					Assert::AreEqual(Test.decreasing[i], t2[i]);
				}

				//WRITE("Growing");
				t2.sort(true);
				for (i = 0; i < _MAXTEST; i++)
				{
					Assert::AreEqual(Test.growing[i], t2[i]);
				}


				//WRITE("resize2");
				DoubleVector t3(_MAXTEST);
				for (i = 0; i < _MAXTEST; i++)
				{
					t3[i] = Test.ori[i];
				}
				t3.resize(_MAXTEST); //nem változhat semmi!
				for (i = 0; i < _MAXTEST; i++)
				{
					Assert::AreEqual(Test.ori[i], t3[i]);
				}
				Assert::AreEqual(_MAXTEST, t3.size());
				Assert::AreEqual(_MAXTEST, t3.capacity());

				t3.resize(1u); //capacity nem változhat!
				Assert::AreEqual(Test.ori[0u], t3[0u]);
				Assert::AreEqual(1u, t3.size());
				Assert::AreEqual(_MAXTEST, t3.capacity());

				//WRITE("clear");
				t3.clear();
				Assert::AreEqual(0u, t3.size());
				Assert::AreEqual(_MAXTEST, t3.capacity());

				//WRITE("resize3");
				t3.resize(_MAXTEST);
				for (i = 0; i < _MAXTEST; i++)
				{
					t3[i] = Test.ori[i];
				}
				Assert::AreEqual(_MAXTEST, t3.size());
				Assert::AreEqual(_MAXTEST, t3.capacity());

				//WRITE("operator=");
				DoubleVector t4(2u);
				for (i = 0; i < 2u; i++)
				{
					t4[i] = Test.ori[i + 2]; //0->2, 1->3 !
				}
				t3 = t4;  //t3-ban _MAXTEST elem!
				Assert::AreEqual(2u, t3.size());
				Assert::AreEqual(_MAXTEST, t3.capacity());

				for (i = 0; i < 2u; i++)
				{
					Assert::AreEqual(Test.ori[i + 2], t3[i]);
				}

				//WRITE("push_back");
				t4.resize(_MAXTEST);
				for (i = 0; i < _MAXTEST; i++)
				{
					t4[i] = Test.ori[i];
				}
				t4.push_back(Test.ori[0]);
				Assert::AreEqual(_MAXTEST + 1u, t4.size());
				Assert::AreEqual(7u, t4.capacity()); // 5 * 1,5 -> 7! 
				Assert::AreEqual(Test.ori[0], t4[_MAXTEST]);

				//WRITE("> exceptions");
				//WRITE("Empty");
				try {
					DoubleVector t;
					t[0] = 1.0;
					Assert::IsTrue(false);
				}
				catch (CMyVectorException& e) { Assert::AreEqual(CMyVectorException::ErrEmpty, e.what()); }
				catch (...) { //WRITE("catch(...)");	
					Assert::IsTrue(false); }

				//WRITE("Index");
				try {
					DoubleVector t(5);
					t[10] = 1.0;
					Assert::IsTrue(false);
				}
				catch (CMyVectorException& e) { Assert::AreEqual(CMyVectorException::ErrIndex, e.what()); }
				catch (...) { //WRITE("catch(...)");	
					Assert::IsTrue(false); }


				//WRITE("shrink");
				DoubleVector t5(_MAXTEST);
				for (i = 0; i < _MAXTEST; i++)
				{
					t5[i] = Test.ori[i];
				}

				t5.push_back(Test.ori[0]);

				Assert::AreEqual(_MAXTEST + 1u, t5.size());
				Assert::AreEqual((unsigned)(_MAXTEST * 1.5), t5.capacity());
				t5.shrink_to_fit();
				Assert::AreEqual(_MAXTEST + 1, t5.size());
				Assert::AreEqual(_MAXTEST + 1, t5.capacity());


			}
			catch (CMyVectorException& e)
			{
				//WRITE("catch (CMyVectorException & e)");
				//WRITE(e.what());
				Assert::IsTrue(false);
			}
			catch (...)
			{
				//WRITE("catch (...)");
				Assert::IsTrue(false);
			}

			//WRITE("** done **");

		}

		//********************************************
		TEST_METHOD(Testcmystring)
		{
			struct test_cmystring {
				CMyString ori[_MAXTEST] = { "narancs", "banán", "alma", "körte", "dió" };
				CMyString growing[_MAXTEST] = { "alma", "banán", "dió", "körte", "narancs" };
				CMyString decreasing[_MAXTEST] = { "narancs", "körte", "dió", "banán", "alma" };
			} Test;

			//WRITE("********* TestCMyString  **");

			try {
				int i;
				//WRITE("> t, Def  ");
				CMyStringVector t;
				Assert::AreEqual(0u, t.size());
				Assert::AreEqual(0u, t.capacity());

				//WRITE("size");
				t.resize(_MAXTEST);
				Assert::AreEqual(_MAXTEST, t.size());
				Assert::AreEqual(_MAXTEST, t.capacity());

				//WRITE("Ori");
				for (i = 0; i < _MAXTEST; i++)
				{
					t[i] = Test.ori[i];
				}

				//WRITE("Decreasing");
				//for(j=0; j<_MAXTEST; j++) //WRITE(t[j]);
				t.sort(false);
				//WRITE("Sort OK");
				//for (j = 0; j < _MAXTEST; j++) //WRITE(t[j]);

				for (i = 0; i < _MAXTEST; i++)
				{
					//WRITE(Test.decreasing[i]);
					//WRITE(t[i]);
					Assert::AreEqual( (const char*) Test.decreasing[i],  (const char*) t[i]);
				}

				//WRITE("Growing");
				t.sort(true);
				for (i = 0; i < _MAXTEST; i++)
				{
					//WRITE(Test.growing[i]);
					//WRITE(t[i]);
					Assert::AreEqual( (const char*) Test.growing[i], (const char*) t[i]);
				}


				//WRITE("> t2, 2 items");
				CMyStringVector t2(2);
				Assert::AreEqual(2u, t2.size());
				Assert::AreEqual(2u, t2.capacity());
				
				t2[0] = Test.ori[0];
				t2[1] = Test.ori[1];
				
				//WRITE("resize");
				t2.resize(_MAXTEST);
				Assert::AreEqual(_MAXTEST, t2.size());
				Assert::AreEqual(_MAXTEST, t2.capacity());

				//WRITE("Ori");
				for (i = 2; i < _MAXTEST; i++)
				{
					t2[i] = Test.ori[i];
					//WRITE(t2[i]);
				}
				
				//WRITE("Decreasing");
				t2.sort(false);
				for (i = 0; i < _MAXTEST; i++)
				{
					//WRITE(Test.decreasing[i]);
					//WRITE(t2[i]);
					Assert::AreEqual((const char*)Test.decreasing[i], (const char*)t2[i]);
				}

				//WRITE("Growing");
				t2.sort(true);
				for (i = 0; i < _MAXTEST; i++)
				{
					//WRITE(Test.growing[i]);
					//WRITE(t2[i]);
					Assert::AreEqual((const char*)Test.growing[i], (const char*)t2[i]);
				}

				//WRITE("resize2");
				CMyStringVector t3(_MAXTEST);
				for (i = 0; i < _MAXTEST; i++)
				{
					t3[i] = Test.ori[i];
				}
				t3.resize(_MAXTEST); //nem változhat semmi!
				for (i = 0; i < _MAXTEST; i++)
				{
					Assert::AreEqual((const char*)Test.ori[i], (const char*)t3[i]);
				}
				Assert::AreEqual(_MAXTEST, t3.size());
				Assert::AreEqual(_MAXTEST, t3.capacity());

				t3.resize(1u); //capacity nem változhat!
				Assert::AreEqual((const char*)Test.ori[0u], (const char*)t3[0u]);
				Assert::AreEqual(1u, t3.size());
				Assert::AreEqual(_MAXTEST, t3.capacity());

				//WRITE("clear");
				t3.clear();
				Assert::AreEqual(0u, t3.size());
				Assert::AreEqual(_MAXTEST, t3.capacity());

				//WRITE("resize3");
				t3.resize(_MAXTEST);
				for (i = 0; i < _MAXTEST; i++)
				{
					t3[i] = Test.ori[i];
				}
				Assert::AreEqual(_MAXTEST, t3.size());
				Assert::AreEqual(_MAXTEST, t3.capacity());

				//WRITE("operator=");
				CMyStringVector t4(2u);
				for (i = 0; i < 2u; i++)
				{
					t4[i] = Test.ori[i + 2]; //0->2, 1->3 !
				}
				t3 = t4;  //t3-ban _MAXTEST elem!
				Assert::AreEqual(2u, t3.size());
				Assert::AreEqual(_MAXTEST, t3.capacity());

				for (i = 0; i < 2u; i++)
				{
					Assert::AreEqual((const char*)Test.ori[i + 2], (const char*)t3[i]);
				}

				//WRITE("push_back");
				t4.resize(_MAXTEST);
				for (i = 0; i < _MAXTEST; i++)
				{
					t4[i] = Test.ori[i];
				}
				t4.push_back(Test.ori[0]);
				Assert::AreEqual(_MAXTEST + 1u, t4.size());
				Assert::AreEqual(7u, t4.capacity()); // 5 * 1,5 -> 7! 
				Assert::AreEqual((const char*)Test.ori[0], (const char*)t4[_MAXTEST]);
				
				//WRITE("> exceptions");
				//WRITE("Empty");
				try {
					CMyStringVector t;
					t[0] = "alma";
					Assert::IsTrue(false);
				}
				catch (CMyVectorException& e) { Assert::AreEqual(CMyVectorException::ErrEmpty, e.what()); }
				catch (...) { //WRITE("catch(...)");	
					Assert::IsTrue(false); }

				//WRITE("Index");
				try {
					CMyStringVector t(5);
					t[10] = "alma";
					Assert::IsTrue(false);
				}
				catch (CMyVectorException& e) { Assert::AreEqual(CMyVectorException::ErrIndex, e.what()); }
				catch (...) { //WRITE("catch(...)");	
					Assert::IsTrue(false); }

				//WRITE("shrink");
				CMyStringVector t5(_MAXTEST);
				for (i = 0; i < _MAXTEST; i++)
				{
					t5[i] = Test.ori[i];
				}

				t5.push_back(Test.ori[0]);

				Assert::AreEqual(_MAXTEST+1u, t5.size());
				Assert::AreEqual( (unsigned)(_MAXTEST*1.5), t5.capacity());
				t5.shrink_to_fit();
				Assert::AreEqual(_MAXTEST + 1, t5.size());
				Assert::AreEqual(_MAXTEST + 1, t5.capacity());


			}
			catch (CMyStringException& e)
			{
				//WRITE("catch (CMYSTRINGEXCEPTION & e)");
				//WRITE(e.what());
				Assert::IsTrue(false);
			}
			catch (CMyVectorException& e)
			{
				//WRITE("catch (CMyVectorException & e)");
				//WRITE(e.what());
				Assert::IsTrue(false);
			}
			catch (...)
			{
				//WRITE("catch (...)");
				Assert::IsTrue(false);
			}

			//WRITE("** done **");

		}
	};
}
