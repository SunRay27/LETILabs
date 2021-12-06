#include "stdafx.h"
#include "../C++Research/Libraries/ListTasks.h"
#include "../C++Research/Libraries/Stack.h"
#include "../C++Research/Libraries/Sorting.h"



#include <cstdio>
#include <ctime>
#include <random>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Lists
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

	};
}
namespace Stacks
{
	TEST_CLASS(BasicTests)
	{
		Stack<int> a;
		TEST_METHOD(Size)
		{
			for (size_t i = 0; i < 25; i++)
				a.Push(1);
			for (size_t i = 0; i < 25; i++)
				a.Pop();

			Assert::AreEqual((int)a.GetSize(), 0);
		}
		TEST_METHOD(PushPop)
		{
			for (size_t i = 0; i < 25; i++)
				a.Push(i);

			Assert::AreEqual(a.Pop(), 24);
		}
		TEST_METHOD(PushPeek)
		{
			for (size_t i = 0; i < 25; i++)
				a.Push(i);

			Assert::AreEqual(a.Peek(), 24);
		}

	};
}
namespace BinaryTree
{
	TEST_CLASS(SampleText)
	{
		TEST_METHOD(InsertTest)
		{
			Tree t;
			t.InsertKeys({ 5,3,2,4,10,20,15,30 });

			bool a1 = t.GetRoot()->GetLeft()->GetLeft()->GetKey() == 2;
			bool a2 = t.GetRoot()->GetLeft()->GetRight()->GetKey() == 4;
			bool a3 = t.GetRoot()->GetLeft()->GetKey() == 3;
			
			bool a4 = t.GetRoot()->GetRight()->GetRight()->GetRight()->GetKey() == 30;
			bool a5 = t.GetRoot()->GetRight()->GetRight()->GetLeft()->GetKey() == 15;

			bool a6 = t.GetRoot()->GetRight()->GetRight()->GetKey() == 20;
			bool a7 = t.GetRoot()->GetRight()->GetKey() == 10;

			Assert::IsTrue(a1 && a2 && a3 && a4 && a5 && a6 && a7);
		}
		TEST_METHOD(ContainsEmpty)
		{
			Tree t;
			Assert::IsTrue(!t.Contains(5));
		}
		TEST_METHOD(ContainsSampleTest)
		{
			Tree t;
			t.InsertKeys({1,2,3,4,5,6,7,8,9,10});
			Assert::IsTrue(t.Contains(5));
		}
		TEST_METHOD(RemoveEmpty)
		{
			try
			{
				Tree t;
				t.Remove(10);
				Assert::Fail();
			}
			catch(exception)
			{
				
			}
		}
		TEST_METHOD(RemoveNonPresent)
		{
			try
			{
				Tree t;
				t.InsertKeys({1,2,3,4,5,6,7,8,9,11,12,13,14});
				t.Remove(10);
				Assert::Fail();
			}
			catch (exception)
			{

			}
		}
		TEST_METHOD(RemoveAll)
		{
			Tree t;
			t.InsertKeys({ 1,2,3,4,5,6,7,8,9,11,12,13,14 });
			t.RemoveKeys({1,2,3,4,5,6,7,8,9,11,12,13,14});
			Assert::IsTrue(t.GetRoot() == nullptr);
		}
		TEST_METHOD(RemoveSome)
		{
			Tree t;
			t.InsertKeys({ 1,2,3,4,5,7,9 });
			t.RemoveKeys({ 1,5,7,9 });
			Assert::IsTrue(!t.Contains(1) && !t.Contains(5) && !t.Contains(7) && !t.Contains(9) && t.Contains(2) && t.Contains(3) && t.Contains(4));
		}
		TEST_METHOD(DFTEmptyTest)
		{
			Tree t;
			Iterator* i = t.CreateDFTIterator();
			while (i->HasNext())
				i->Next();

		}
		TEST_METHOD(DFTTest)
		{
			Tree t;
			t.InsertKeys({ 5,3,2,4,10,20,15,30 });
			Iterator* i = t.CreateDFTIterator();

			int size = t.GetSize();
			int* vals = new int[size];

			int c = 0;
			while (i->HasNext())
			{
				vals[c] = i->Next();
				c++;
			}

			bool res = vals[0] == 2 && vals[1] == 3 && vals[2] == 4 && vals[3] == 5 && vals[4] == 10 && vals[5] == 15 && vals[6] == 20 && vals[7] == 30;
			Assert::IsTrue(res);

		}
		TEST_METHOD(BFTEmptyTest)
		{
			Tree t;
			Iterator* i = t.CreateBFTIterator();
			while (i->HasNext())
				i->Next();

		}
		TEST_METHOD(BFTTest)
		{
			Tree t;
			t.InsertKeys({ 5,3,2,4,10,20,15,30 });
			Iterator* i = t.CreateBFTIterator();

			int size = t.GetSize();
			int* vals = new int[size];

			int c = 0;
			while (i->HasNext())
			{
				vals[c] = i->Next();
				c++;
			}

			bool res = vals[0] == 5 && vals[1] == 3 && vals[2] == 10 && vals[3] == 2 && vals[4] == 4 && vals[5] == 20 && vals[6] == 15 && vals[7] == 30;
			Assert::IsTrue(res);

		}
	};
}
namespace Sorting
{
	TEST_CLASS(RandomTests)
	{
		char getRandomChar()
		{
			int rand2 = rand() % 2;
			if (rand2)
				return 'A' + rand() % 26;
			else
				return 'a' + rand() % 26;
		}
		int iterations = 1;
		int dataSize = 1000;
		TEST_METHOD(BinSearch)
		{
			for (size_t a = 0; a < iterations; a++)
			{
				int* data = new int[dataSize];
				for (size_t i = 0; i < dataSize; i++)
					data[i] = i;

				//randomize
				random_device generator;
				uniform_int_distribution<int> distribution(1, (int)dataSize);
				int toFind = distribution(generator);

				size_t index = -1;
				//do binary search
				index = Sort::BinarySearch(data, dataSize, toFind);

				if (data[index] != toFind)
					Assert::Fail();

				delete[] data;
			}
		}
		TEST_METHOD(QuickSort)
		{
			for (size_t a = 0; a < iterations; a++)
			{
				int* data = new int[dataSize];
				for (size_t i = 0; i < dataSize; i++)
					data[i] = rand();

				Sort::QuickSort(data, 0, dataSize - 1);
				if (!Sort::isSorted(data, dataSize))
					Assert::Fail();
				delete[] data;
			}
		}
		TEST_METHOD(BogoSort)
		{
			dataSize = 5;
			for (size_t a = 0; a < iterations; a++)
			{
				int* data = new int[dataSize];
				for (size_t i = 0; i < dataSize; i++)
					data[i] = rand();

				Sort::BogoSort(data, dataSize);

				if (!Sort::isSorted(data, dataSize))
					Assert::Fail();
				delete[] data;
			}
		}
		TEST_METHOD(InsertionSort)
		{
			for (size_t a = 0; a < iterations; a++)
			{
				int* data = new int[dataSize];
				for (size_t i = 0; i < dataSize; i++)
					data[i] = (int)(rand());

				Sort::InsertionSort(data, dataSize);

				if (!Sort::isSorted(data, dataSize))
					Assert::Fail();
				delete[] data;
			}
		}
		TEST_METHOD(BubbleSort)
		{
			for (size_t a = 0; a < iterations; a++)
			{

				int* data = new int[dataSize];
				for (size_t i = 0; i < dataSize; i++)
					data[i] = rand();


				Sort::BubbleSort(data, dataSize);
				if (!Sort::isSorted(data, dataSize))
					Assert::Fail();

				delete[] data;
			}
		}
		TEST_METHOD(TreeSort)
		{
			for (size_t a = 0; a < iterations; a++)
			{

				int* data = new int[dataSize];
				for (size_t i = 0; i < dataSize; i++)
					data[i] = rand();


				Sort::TreeSort(data, dataSize);
				if (!Sort::isSorted(data, dataSize))
					Assert::Fail();
				delete[] data;
			}
		}
		TEST_METHOD(HeapSort)
		{
			for (size_t a = 0; a < iterations; a++)
			{

				int* data = new int[dataSize];
				for (size_t i = 0; i < dataSize; i++)
					data[i] = rand();


				Sort::HeapSort(data, dataSize);

				if (!Sort::isSorted(data, dataSize))
					Assert::Fail();
				delete[] data;
			}
		}
		TEST_METHOD(CountingSort)
		{
			int symbolRange = 24;
			for (size_t a = 0; a < iterations; a++)
			{
				char* data = new char[dataSize];
				for (size_t i = 0; i < dataSize; i++)
					data[i] = getRandomChar();


				Sort::CountingSort(data, dataSize);

				if (!Sort::isSorted(data, dataSize))
					Assert::Fail();

				delete[] data;
			}

		}
	};
}