

/*
#include <iostream>
//#include "Libraries/BinTree.h"
#include "Libraries/Sorting.h"


#include <cstdio>
#include <ctime>
#include <random>

using namespace std;

void TestBinarySearch(size_t dataSize, size_t iteraions);
void TestQuickSort(size_t dataSize, size_t iteraions);
void TestInsertionSort(size_t dataSize, size_t iteraions);
void TestBogoSort(size_t dataSize, size_t iteraions);
void TestBubbleSort(size_t dataSize, size_t iteraions);
void TestTreeSort(size_t dataSize, size_t iteraions);
void TestHeapSort(size_t dataSize, size_t iteraions);
void TestCountingSort(size_t dataSize, size_t iteraions);

char getRandomChar()
{
	int rand2 = rand() % 2;
	if (rand2)
		return 'A' + rand() % 26;
	else
		return 'a' + rand() % 26;
}

int main()
{
	cout << CLOCKS_PER_SEC << endl;
	srand(time(0));
	size_t dataSize = 1000;
	size_t iterations = 10;
	//TestBinarySearch(dataSize,iterations);
	//TestQuickSort(dataSize, iterations);
	//TestTreeSort(dataSize, iterations);
	//TestBogoSort(dataSize, iterations);
	//TestInsertionSort(dataSize, iterations);
	//TestHeapSort(dataSize, iterations);
	TestCountingSort(dataSize, iterations);
	//TestBubbleSort(dataSize, iterations);
}

void TestBinarySearch(size_t dataSize, size_t iteraions)
{
	for (size_t a = 0; a < iteraions; a++)
	{
		int* data = new int[dataSize];
		for (size_t i = 0; i < dataSize; i++)
			data[i] = i;

		//randomize
		random_device generator;
		uniform_int_distribution<int> distribution(1, (int)dataSize);
		int toFind = distribution(generator);

		//int toFind = data[rand() % dataSize];
		clock_t watch;
		watch = clock();

		size_t index = -1;
		//do linear search
		for (size_t i = 0; i < dataSize; i++)
		{
			if (data[i] == toFind)
			{
				index = i;
				break;
			}

		}
		double duration = (clock() - watch) / (double)CLOCKS_PER_SEC;

		cout << "linear took " << duration << " seconds with index " << index << endl;

		//do binary search
		watch = clock();

		index = Sort::BinarySearch(data, dataSize, toFind);

		duration = (clock() - watch) / (double)CLOCKS_PER_SEC;
		cout << "binary search took " << duration << " seconds with index " << index << endl;

		delete[] data;
	}

}

void TestQuickSort(size_t dataSize, size_t iteraions)
{
	for (size_t a = 0; a < iteraions; a++)
	{

		int* data = new int[dataSize];
		for (size_t i = 0; i < dataSize; i++)
			data[i] = rand();

		clock_t watch = clock();


		Sort::QuickSort(data, 0, dataSize - 1);

		double duration = (clock() - watch) / (double)CLOCKS_PER_SEC;

		cout << "quicksort took " << duration << " seconds" << endl;
		delete[] data;
	}
}

void TestBogoSort(size_t dataSize, size_t iteraions)
{
	for (size_t a = 0; a < iteraions; a++)
	{
		int* data = new int[dataSize];
		for (size_t i = 0; i < dataSize; i++)
		{
			data[i] = rand();
		}
		cout << endl;


		clock_t watch = clock();

		Sort::BogoSort(data, dataSize);

		double duration = (clock() - watch) / (double)CLOCKS_PER_SEC;

		cout << endl;
		cout << "bogosort took " << duration << " seconds" << endl;

		delete[] data;
	}
}

void TestInsertionSort(size_t dataSize, size_t iterations)
{
	for (size_t a = 0; a < iterations; a++)
	{
		int* data = new int[dataSize];
		for (size_t i = 0; i < dataSize; i++)
			data[i] = (int)(rand());

		clock_t watch = clock();


		Sort::InsertionSort(data, dataSize);

		double duration = (clock() - watch) / (double)CLOCKS_PER_SEC;

		cout << "insertionSort took " << duration << " seconds" << endl;
		delete[] data;
	}
}

void TestBubbleSort(size_t dataSize, size_t iteraions)
{
	for (size_t a = 0; a < iteraions; a++)
	{

		int* data = new int[dataSize];
		for (size_t i = 0; i < dataSize; i++)
			data[i] = rand();

		clock_t watch = clock();


		Sort::BubbleSort(data, dataSize);

		//for (size_t i = 0; i < dataSize; i++)
		//{
		//	cout << data[i] << " ";
		//}
		double duration = (clock() - watch) / (double)CLOCKS_PER_SEC;

		cout << "bubbleSort took " << duration << " seconds" << endl;
		delete[] data;
	}
}

void TestTreeSort(size_t dataSize, size_t iteraions)
{
	for (size_t a = 0; a < iteraions; a++)
	{

		int* data = new int[dataSize];
		for (size_t i = 0; i < dataSize; i++)
			data[i] = rand();

		clock_t watch = clock();


		Sort::TreeSort(data, dataSize);

		double duration = (clock() - watch) / (double)CLOCKS_PER_SEC;

		cout << "treesort took " << duration << " seconds" << endl;
		delete[] data;
	}
}

void TestHeapSort(size_t dataSize, size_t iteraions)
{
	for (size_t a = 0; a < iteraions; a++)
	{

		int* data = new int[dataSize];
		for (size_t i = 0; i < dataSize; i++)
			data[i] = rand();

		clock_t watch = clock();


		Sort::HeapSort(data, dataSize);

		double duration = (clock() - watch) / (double)CLOCKS_PER_SEC;

		cout << "heapsort took " << duration << " seconds" << endl;
		delete[] data;
	}
}

void TestCountingSort(size_t dataSize, size_t iteraions)
{
	int symbolRange = 24;
	for (size_t a = 0; a < iteraions; a++)
	{
		char* data = new char[dataSize];
		for (size_t i = 0; i < dataSize; i++)
			data[i] = getRandomChar();

		clock_t watch = clock();


		Sort::CountingSort(data, dataSize);

		for (size_t i = 0; i < dataSize; i++)
		{
			cout << data[i] << " ";
		}

		double duration = (clock() - watch) / (double)CLOCKS_PER_SEC;

		cout << "couningsort took " << duration << " seconds" << endl;
		delete[] data;
	}
}*/



#include <iostream>
#include <ctime>

#include "Libraries/BinTree.h"
using namespace std;

int main()
{
	Tree tree;
	srand(time(0));
	for (size_t i = 1; i < 8; i++)
		tree.Insert(rand()%10);


	tree.Print();

	tree.Remove(1);
	cout << "\n\n\n";
	tree.Print();

	cout << "\n\n\n";
	Iterator* i = tree.CreateBFTIterator();
	while (i->HasNext())
	{
		cout << i->Next() << " ";
	}

}




