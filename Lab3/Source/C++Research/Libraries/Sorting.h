#pragma once
#include "BinTree.h";

 class Sort
{
public:
	
	static size_t BinarySearch(int* data, int dataSize , int match)
	{
		size_t start = 0, end = dataSize - 1;
		while (start <= end)
		{
			size_t middleElement = start + (end - start) / 2;
			if (data[middleElement] == match)
				return middleElement;
			if (data[middleElement] < match)
				start = middleElement + 1; // shift start to right
			else
				end = middleElement - 1; // shift end to left
		}
		return -1;
	}
	static void QuickSort(int* data, int first, int last)
	{
		if (first < last)
		{
			int left = first, right = last, middle = data[(left + right) / 2];
			do
			{
				while (data[left] < middle) left++;
				while (data[right] > middle) right--;
				if (left <= right)
				{
					swap(&data[left], &data[right]);
					left++;
					right--;
				}
			} while (left <= right);


			QuickSort(data, first, right);
			QuickSort(data, left, last);
		}
	}
	static void InsertionSort(int* data, size_t dataSize)
	{
		for (int i = 1; i < dataSize; i++) 
		{
			int key = data[i];
			int j = i - 1;

			// Move elements of arr[0..i-1], 
			// that are greater than key, 
			// to one position ahead of 
			// their current position 
			while (j >= 0 && data[j] > key) 
			{
				data[j + 1] = data[j];
				j--;
			}
			data[j + 1] = key;
		}
	}
	static void BubbleSort(int* data, size_t dataSize)
	{
		for (size_t i = 0; i < dataSize - 1; i++)
		{
			for (size_t j = 0; j < dataSize - i - 1; j++)
			{
				if (data[j + 1] < data[j])
					swap(&data[j], &data[j+1]);
			}
		}
	}
	static void TreeSort(int* data, size_t dataSize)
	{
		Tree tree;
		for (size_t i = 0; i < dataSize; i++)
			tree.Insert(data[i]);

		Iterator* dft = tree.CreateDFTIterator();

		size_t i = 0;
		while (dft->HasNext())
		{
			data[i] = dft->Next();
			i++;
		}
			
	}
	static void HeapSort(int* data, size_t dataSize)
	{
		// Build heap (rearrange array) 
		for (int i = dataSize / 2 - 1; i >= 0; i--)
			heapify(data, dataSize, i);

		// One by one extract an element from heap 
		for (int i = dataSize - 1; i >= 0; i--)
		{
			// Move current root to end 
			swap(&data[0], &data[i]);

			// call max heapify on the reduced heap 
			heapify(data, i, 0);
		}
	}
	static void BogoSort(int* data, size_t dataSize)
	{
		while (!isSorted(data, dataSize))
			shuffle(data, dataSize);

	}
	static void CountingSort(char* data, size_t dataSize)
	{
		/*
		//get max char int
		size_t maxChar = data[0];
		for (size_t i = 0; i < dataSize; i++)
			if (maxChar < data[i])
				maxChar = data[i];

		size_t countSize = maxChar + 1;
		size_t* count = new size_t[countSize];

		for (size_t i = 0; i < countSize; i++)
			count[i] = 0;


		//get count
		for (size_t i = 0; i < dataSize; i++)
			count[data[i]]++;

		for (size_t i = 1; i < maxChar; ++i)
			count[i] += count[i - 1];

		char* output = new char[dataSize];
		for (size_t i = 0; i < dataSize; i++)
		{
			output[count[data[i]] - 1] = data[i];
			count[data[i]]--;
		}

		for (size_t i = 0; i < dataSize; i++)
		{
			data[i] = output[i];
		}

		delete[] output;
		delete[] count;*/

		char* output = new char[dataSize];
		int count[256];
		for (int i = 0; i < 256; i++)
			count[i] = 0;

		for (int i = 0; i < dataSize; i++)
			count[data[i]]++;

		for (int i = 1; i < 256; i++)
			count[i] += count[i - 1];

		for (int i = dataSize-1; i >= 0; i--)
		{
			output[count[data[i]] - 1] = data[i];
			count[data[i]]--;
		}

		for (int i = 0; i < dataSize; i++)
			data[i] = output[i];

		delete[] output;
	}

	static bool isSorted(int* data, size_t dataSize)
	{
		while (dataSize > 1)
		{
			dataSize--;
			if (data[dataSize] < data[dataSize - 1])
				return false;
		}

		return true;
	}
	static bool isSorted(char* data, size_t dataSize)
	{
		while (dataSize > 1)
		{
			dataSize--;
			if (data[dataSize] < data[dataSize - 1])
				return false;
		}

		return true;
	}
private:
	//helpers
	static void shuffle(int* data, size_t dataSize)
	{
		for (size_t i = 0; i < dataSize; i++)
		{
			swap(&data[i], &data[rand() % dataSize]);
		}
	}
	static void swap(int* a, int* b)
	{
		int temp = *a;
		*a = *b;
		*b = temp;
	}
	static void heapify(int* data, int n, int i)
	{
		int largest = i; // Initialize largest as root 
		int l = 2 * i + 1; // left = 2*i + 1 
		int r = 2 * i + 2; // right = 2*i + 2 

		// If left child is larger than root 
		if (l < n && data[l] > data[largest])
			largest = l;

		// If right child is larger than largest so far 
		if (r < n && data[r] > data[largest])
			largest = r;

		// If largest is not root 
		if (largest != i)
		{
			swap(&data[i], &data[largest]);

			// Recursively heapify the affected sub-tree 
			heapify(data, n, largest);
		}
	}

};