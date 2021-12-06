#include "stdafx.h"
#include "../CPPResearch/Libraries/List/ListTasks.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(SimpleTests)
	{
	public:

		TEST_METHOD(IsEmpty_0)
		{
			List<int> t;
			Assert::AreEqual(t.IsEmpty(), true);
		}
		TEST_METHOD(IsEmpty_1)
		{
			List<int> t;
			t.PushBack(10);
			Assert::AreEqual(t.IsEmpty(), false);
		}
		TEST_METHOD(IsEmpty_5000)
		{
			List<int> t;
			for (size_t i = 0; i < 5000; i++)
				t.PushBack(i);
			
			Assert::AreEqual(t.IsEmpty(), false);
		}

		TEST_METHOD(GetSize_0)
		{
			List<int> t;
			Assert::AreEqual(t.GetSize(), (size_t)0);
		}
		TEST_METHOD(GetSize_1000)
		{
			List<int> t;
			for (size_t i = 0; i < 1000; i++)
				t.PushBack(i);
			Assert::AreEqual(t.GetSize(), (size_t)1000);
		}

		TEST_METHOD(Clear_dirty)
		{
			List<int> t;
			for (size_t i = 0; i < 5000; i++)
				t.PushBack(i);
			t.Clear();
			Assert::AreEqual(t.GetSize(), (size_t)0);

		}
	};
	TEST_CLASS(PushPopTests)
	{
	public:
		
		//DAMN IDK WHAT TO TEST
		TEST_METHOD(PopBack_emptyEx)
		{
			List<int> t;
			try
			{
				t.PopBack();
			}
			catch (const std::exception&)
			{
				return;
			}
			Assert::Fail();
			
		}
		TEST_METHOD(PopFront_emptyEx)
		{
			List<int> t;
			try
			{
				t.PopFront();
			}
			catch (const std::exception&)
			{
				return;
			}
			Assert::Fail();
		}
		TEST_METHOD(PopFront_1)
		{
			List<int> t;
			t.PushBack(1);
			t.PopFront();
		}
		TEST_METHOD(PopBack_1)
		{
			List<int> t;
			t.PushBack(1);
			t.PopFront();
		}
		TEST_METHOD(PopFront_50)
		{
			List<int> t;
			for (size_t i = 0; i < 50; i++)
				t.PushBack(i);
			t.PopFront();
		}
		TEST_METHOD(PopBack_50)
		{
			List<int> t;
			for (size_t i = 0; i < 50; i++)
				t.PushBack(i);
			t.PopBack();
		}

	};
	TEST_CLASS(AdvancedTests)
	{
	public:
		//insert
		TEST_METHOD(Insert_1element)
		{
			List<int> a;
			a.PushBack(1);
			a.Insert(-1, 0);
			Assert::AreEqual(-1, a[0]);
		}
		TEST_METHOD(Insert_0element)
		{
			List<int> a;
			try
			{
				a.Insert(120, 0);
			}
			catch(std::exception)
			{
				return;
			}
			Assert::Fail();
			
		}
		TEST_METHOD(Insert_lastElement)
		{
			List<int> a;
			for (size_t i = 0; i < 500; i++)
			{
				a.PushFront(i);
			}

			a.Insert(-50, 499);

			Assert::AreEqual(-50, a[499]);
		}
		//reomve
		TEST_METHOD(Remove_1element)
		{
			List<int> a;
			a.PushBack(1);
			a.Remove(0);

			a.SelfCheck();
			Assert::AreEqual((int)a.GetSize(),0);
		}
		TEST_METHOD(Remove_0element)
		{
			List<int> a;
			try
			{
				a.Remove(0);
			}
			catch (std::exception)
			{
				return;
			}
			Assert::Fail();

		}
		TEST_METHOD(Remove_lastElement)
		{
			List<int> a;
			for (size_t i = 0; i < 500; i++)
			{
				a.PushFront(i);
			}

			a.Remove(499);

			a.SelfCheck();
		}
		//replace
		TEST_METHOD(Replace_1element)
		{
			List<int> a;
			a.PushBack(1);
			a.Replace(0,0);

			a.SelfCheck();
			Assert::AreEqual(a[0], 0);
		}
		TEST_METHOD(Replace_0element)
		{
			List<int> a;
			try
			{
				a.Replace(12,0);
			}
			catch (std::exception)
			{
				return;
			}
			Assert::Fail();

		}
		//swap
		TEST_METHOD(Swap_lastFirst)
		{
			List<int> a;
			for (size_t i = 0; i < 500; i++)
			{
				a.PushBack(i);
			}

			a.Swap(0, 499);
			a.SelfCheck();
			if (a[0] != 499 || a[499] != 0)
				Assert::Fail();

			
		}
		TEST_METHOD(Swap_ff)
		{
			List<int> a;
			for (size_t i = 0; i < 500; i++)
			{
				a.PushBack(i);
			}

			a.Swap(0, 0);
			a.SelfCheck();
			if (a[0] != 0)
				Assert::Fail();
			
		}
		TEST_METHOD(Swap_ll)
		{
			List<int> a;
			for (size_t i = 0; i < 500; i++)
			{
				a.PushBack(i);
			}
			a.Swap(499, 499);
			a.SelfCheck();
			if (a[499] != 499)
				Assert::Fail();
		}
		//find first
		TEST_METHOD(FindFirst1)
		{
			List<int> first, second;

			first.AddValues({ 1, 2, 3, 4, 5, 6, 7 });
			second.AddValues({ 0, 1, 2, 3, 4, 5, 6, 7 });

			Assert::AreEqual(1,(int)second.FindFirst(first));

		}
		TEST_METHOD(FindFirst2)
		{
			List<int> first, second;

			first.AddValues({ 1,2,3 });
			second.AddValues({ 1,1,2,3 });

			Assert::AreEqual(1, (int)second.FindFirst(first));

		}
		TEST_METHOD(FindFirst3)
		{
			List<int> first, second;

			first.AddValues({ 1,2,3,8 });
			second.AddValues({ 1,2,2,1,1,2,3 });

			Assert::AreEqual(-1, (int)second.FindFirst(first));

		}
		TEST_METHOD(FindFirst4)
		{
			List<int> first, second;

			first.AddValues({ 1,2,4 });
			second.AddValues({ 1,2,2});

			Assert::AreEqual(-1, (int)second.FindFirst(first));

		}
		TEST_METHOD(FindFirst5)
		{
			List<int> first, second;

			first.AddValues({ 1,2,4 });
			second.AddValues({ 1,2 });

			Assert::AreEqual(-1, (int)second.FindFirst(first));

		}
		TEST_METHOD(FindFirst6)
		{
			List<int> first, second;

			first.AddValues({ 11,10 });
			second.AddValues({ 1,2, 5, 6 , 7, 9 , 10, 11 , 10 , 11 });

			Assert::AreEqual(7, (int)second.FindFirst(first));

		}
		TEST_METHOD(PushFrontList_PushToEmpty)
		{
			List<int> first, second;

			for (size_t i = 1; i <= 50; i++)
				first.PushBack(i);

			second.PushFront(first);

			Assert::AreEqual(50, (int)second.GetSize());
		}
		TEST_METHOD(PushFrontList_PushEmpty)
		{
			List<int> first, second;

			for (size_t i = 1; i <= 50; i++)
				second.PushBack(i);

			second.PushFront(first);

			Assert::AreEqual(50, (int)second.GetSize());
		}
		TEST_METHOD(PushFrontListBigSizeTest)
		{
			List<int> first, second;

			for (size_t i = 1; i <= 5000; i++)
				first.PushBack(i);

			for (size_t i = 1; i <= 15000; i++)
				second.PushBack(i);

			second.PushFront(first);

			Assert::AreEqual(20000, (int)second.GetSize());
		}


	};
}