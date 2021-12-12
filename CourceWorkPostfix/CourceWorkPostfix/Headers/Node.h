#pragma once
//Holder class for lists
template <class T>
class Node
{
	Node<T>* next; T data;
public:
	~Node() {}
	Node() : next(nullptr) {}
	Node(const T value)
	{
		next = nullptr;
		data = value;
	}

	void SetNext(Node<T>* nextElement) { next = nextElement; }
	void SetData(T newData)
	{
		data = newData;
	}
	Node* GetNext() { return next; }
	T GetData() { return data; }
};