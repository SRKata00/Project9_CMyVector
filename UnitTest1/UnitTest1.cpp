#include "pch.h"
#include "CppUnitTest.h"

#include "..\Project9_CMyVector\cmystring.h"
#include "..\Project9_CMyVector\cmyvector.h"
#include "..\Project9_CMyVector\cmystringexception.h"
#include "..\Project9_CMyVector\cmyvectorexception.h"

#define INIT_CAPACITY 6
#define INIT_SIZE 4

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	CMyVector<int> iv1;
	CMyVector<double> dv1;
	CMyVector<char> cv1;
	CMyVector<CMyString> sv1;
	TEST_CLASS(UnitTest1)
	{
	public:
		void initTest()
		{
			dv1.resize(INIT_CAPACITY);
			dv1.shrink_to_fit();
			dv1.clear();
			iv1.resize(INIT_CAPACITY);
			iv1.shrink_to_fit();
			iv1.clear();
			cv1.resize(INIT_CAPACITY);
			cv1.shrink_to_fit();
			cv1.clear();
			sv1.resize(INIT_CAPACITY);
			sv1.shrink_to_fit();
			sv1.clear();
			
			for (size_t i = 1; i <= INIT_SIZE / 2; i++)
			{
				dv1.push_back(i + 1.2);
				dv1.push_back(i - 1.2);
				iv1.push_back(i + 1);
				iv1.push_back(i - 1);
				cv1.push_back(i + 68);
				cv1.push_back(90 - i);
			}
			CMyString ss1("alma"), ss2, ss3("eper"), ss4("kiwi");
			sv1.push_back(ss1);
			sv1.push_back(ss2);
			sv1.push_back(ss3);
			sv1.push_back(ss4);
		}
		TEST_METHOD(Testempty)
		{
			CMyVector<double> dve1;
			Assert::AreEqual(0u, dve1.capacity());
			Assert::AreEqual(0u, dve1.size());
			CMyVector<CMyString> sve1;
			Assert::AreEqual(0u, sve1.capacity());
			Assert::AreEqual(0u, sve1.size());
		}
		TEST_METHOD(TestPushBack)
		{
			initTest();
			Assert::AreEqual((unsigned)INIT_CAPACITY, dv1.capacity());
			Assert::AreEqual((unsigned)INIT_SIZE, dv1.size());
			Assert::AreEqual((unsigned)INIT_CAPACITY, sv1.capacity());
			Assert::AreEqual((unsigned)INIT_SIZE, sv1.size());
			for (size_t i = 0; i < INIT_CAPACITY; i++)
			{
				dv1.push_back(2.2);
				sv1.push_back("narancs");
			}
			Assert::AreEqual((unsigned)((INIT_CAPACITY*1.5)*1.5), sv1.capacity());
			Assert::AreEqual((unsigned)INIT_CAPACITY+INIT_SIZE, sv1.size());
			Assert::AreEqual((unsigned)((INIT_CAPACITY * 1.5) * 1.5), dv1.capacity());
			Assert::AreEqual((unsigned)INIT_CAPACITY + INIT_SIZE, dv1.size());
		}
		TEST_METHOD(Testposition)
		{
			initTest();
			Assert::AreEqual(2.2, dv1[0]);
			Assert::AreEqual("kiwi", sv1[3]);
			CMyString s("narancs");
			sv1.push_back(s);
			Assert::AreEqual(s.GetData(), sv1[4]);
			try 
			{
				sv1[5];
				Assert::Fail();
			}
			catch (CMyVectorException ex)
			{
				Assert::AreEqual(CMyVectorException::ErrIndex, ex.what());
			}
			try
			{
				CMyVector<double> dve1;
				dve1[0];
				Assert::Fail();
			}
			catch (CMyVectorException ex)
			{
				Assert::AreEqual(CMyVectorException::ErrEmpty, ex.what());
			}
		}

		TEST_METHOD(Testassignment)
		{
			initTest();
			CMyVector<int> ive1;
			ive1.push_back(100);
			ive1.push_back(200);
			iv1 = ive1;
			Assert::AreEqual((unsigned)INIT_CAPACITY, iv1.capacity());
			Assert::AreEqual(ive1.size(), iv1.size());
			Assert::AreEqual(ive1[0], iv1[0]);
			Assert::AreEqual(ive1[1], iv1[1]);
			iv1.push_back(300);
			iv1.push_back(400);
			ive1=iv1;
			Assert::AreEqual(iv1.size(), ive1.capacity());
			Assert::AreEqual(iv1.size(), ive1.size());
			Assert::AreEqual(300, iv1[2]);
			Assert::AreEqual(400, iv1[3]);

			CMyVector<CMyString> sve1;
			sve1.push_back("szilva");
			sve1.push_back("citrom");
			sv1 = sve1;
			Assert::AreEqual((unsigned)INIT_CAPACITY, sv1.capacity());
			Assert::AreEqual(sve1.size(), sv1.size());
			Assert::AreEqual(sve1[0].GetData(), sv1[0].GetData());
			Assert::AreEqual(sve1[1].GetData(), sv1[1].GetData());
			sv1.push_back("dinnye");
			sv1.push_back("barack");
			sve1 = sv1;
			Assert::AreEqual(sv1.size(), sve1.capacity());
			Assert::AreEqual(sv1.size(), sve1.size());
			Assert::AreEqual("dinnye", sv1[2].GetData());
			Assert::AreEqual("barack", sv1[3].GetData());
		}

		TEST_METHOD(Testclear)
		{
			initTest();
			sv1.clear();
			Assert::AreEqual((unsigned)INIT_CAPACITY, sv1.capacity());
			Assert::AreEqual(0u, sv1.size());
			try
			{
				sv1[5];
				Assert::Fail();
			}
			catch (CMyVectorException ex)
			{
				Assert::AreEqual(CMyVectorException::ErrEmpty, ex.what());
			}
		}
		TEST_METHOD(Testresize)
		{
			initTest();
			sv1.resize(2);
			Assert::AreEqual(2u, sv1.size());
			Assert::AreEqual((unsigned)INIT_CAPACITY, sv1.capacity());
			sv1.resize(10);
			Assert::AreEqual(10u, sv1.size());
			Assert::AreEqual(10u, sv1.capacity());
		}
		TEST_METHOD(Testshrinktofit)
		{
			initTest();
			cv1.shrink_to_fit();
			Assert::AreEqual((unsigned)INIT_SIZE, cv1.size());
			Assert::AreEqual((unsigned)INIT_SIZE, cv1.capacity());
		}
		TEST_METHOD(Testsort)
		{
			//2 0 3 1
			initTest();
			Assert::AreEqual(2, iv1[0]);
			Assert::AreEqual(0, iv1[1]);
			Assert::AreEqual(3, iv1[2]);
			Assert::AreEqual(1, iv1[3]);
			iv1.sort(true);
			Assert::AreEqual(0, iv1[0]);
			Assert::AreEqual(1, iv1[1]);
			Assert::AreEqual(2, iv1[2]);
			Assert::AreEqual(3, iv1[3]);
			iv1.sort(false);
			Assert::AreEqual(3, iv1[0]);
			Assert::AreEqual(2, iv1[1]);
			Assert::AreEqual(1, iv1[2]);
			Assert::AreEqual(0, iv1[3]);
		}
	};
}
