#pragma once
#include <stdexcept>

//Holder class for lists
template <class T>
class Node
{
	Node<T>* next; T data;
public:
	~Node() {}
	Node() : next(nullptr) {}
	Node(T value) : data(value), next(nullptr) {}

	void SetNext(Node<T>* nextElement) {next = nextElement;}
	void SetData(T newData)
	{
		data = newData;
	}
	Node* GetNext() {return next;}
	T GetData() {return data;}
};

template <class T>
class List
{
	 size_t curElementIndex; size_t count;
	 Node<T> *head, *tail, *current;

private:
#pragma region Low-level private functions

	//Basic field accessors
	void SetHeadNode(Node<T>* node) { head = node; }
	void SetTailNode(Node<T>* node) { tail = node; }
	void SetCurrentNode(Node<T>* node) { current = node; }
	void SetCurrentValue(T node) { current->SetData(node); }
	Node<T>* GetHeadNode() { return head; }
	Node<T>* GetTailNode() { return tail; }
	Node<T>* GetCurrentNode() { return current; }
	T GetCurrentValue() { return GetCurrentNode()->GetData(); }

	//Some basic movement logic
	Node <T>* GetNode(size_t i)
	{
		if (i<0 || i > count - 1)
			return nullptr;

		if (curElementIndex > i)
			MoveToHead();

		for (size_t j = curElementIndex; j < i; j++)
			MoveForward();

		return GetCurrentNode();
	}
	void MoveForward()
	{
		SetCurrentNode(GetCurrentNode()->GetNext());
		curElementIndex++;
	}
	void MoveToHead()
	{
		SetCurrentNode(head);
		curElementIndex = 0;
	}
	void MoveToTail()
	{
		//+ MoveToHead();
		while (GetCurrentNode()->GetNext() != nullptr)
			MoveForward();
	}

	//and exception thrower
	void CheckBounds(size_t index)
	{
		if (index < 0 || index > count - 1 || count == 0)
			throw std::exception("Index is out of bounds");
	}
#pragma endregion

public:
	~List() {Clear();}
	List() : count(0), curElementIndex(0), head(nullptr), tail(nullptr), current(nullptr) {}

	template <class T>
	void AddValues(std::initializer_list<T> list)
	{
		for (auto elem : list)
		{
			PushBack(elem);
		}
	}

	void RemoveAll(T value)
	{
		for (size_t i = 0; i < GetSize(); i++)
			if (value == At(i))
			{
				Remove(i);
				i--;
			}
	}
	void RemoveFirst(T value)
	{
		for (size_t i = 0; i < GetSize(); i++)
			if (value == At(i))
			{
				Remove(i);
				return;
			}
	}
	T operator[] (size_t index) { return At(index); }


	//**************************************************************//
	//************ACHTUNG!!! HERE REAL FUNCTIONS COME!!!************//
	//**************************************************************//
	//**************************************************************//

	//CHECK IT OUT!!! IT IS NOT MY VARIANT BUT STILL PLS CHECK
	/*+*/void Swap(size_t i, size_t j)
	{
		CheckBounds(i);
		CheckBounds(j);

		//Our job is done here
		if (j == i)
			return;

		//Make i < j because it matters
		if (i > j)
		{
			size_t t = i;
			i = j;
			j = t;
		}

		//Get all usefull nodes
		Node<T>* iNodePrevious = GetNode(i - 1);
		Node<T>* iNode = GetNode(i);
		Node<T>* iNodeNext = GetNode(i + 1);

		Node<T>* jNodePrevious = GetNode(j - 1);
		Node<T>* jNode = GetNode(j);
		Node<T>* jNodeNext = GetNode(j + 1);

		
		

		//swap head/tail if needed
		if (iNode == head)
			head = jNode;
		if (jNode == tail)
			tail = iNode;

		//fix node link which was before iNode
		if (iNodePrevious != nullptr)
			iNodePrevious->SetNext(jNode);

		//if nodes are neighbours we just reassign links
		if (i + 1 == j)
		{
			//just swap
			jNode->SetNext(iNode);
			iNode->SetNext(jNodeNext);
		}
		else
		{
			//fix node link which was before jNode
			if (jNodePrevious != nullptr)
				jNodePrevious->SetNext(iNode);
			//swap
			jNode->SetNext(iNodeNext);
			iNode->SetNext(jNodeNext);
		}

		MoveToHead();
	}
	/*+*/size_t FindFirst(List<T>& other)
	{
		//1. go through this list and get first matching element
		//2. then check others in row -> if this contains all -> return first element's index or continue
		//2.5 Consider some special cases, when list is smaller/bigger than this
		size_t listLength = GetSize();
		size_t otherListLength = other.GetSize();

		if ((otherListLength > listLength) || (otherListLength == 0 || listLength == 0))
			return -1;

		for (size_t i = 0; i < listLength; i++)
		{

			for (size_t j = 0; j < otherListLength; j++)
			{
				// if elements count from list is already smaller than other's length, we know list doesnt contain other for sure
				if (listLength - i < otherListLength)
					return -1;

				T listElement = At(i);
				T otherListElement = other.At(j);

				//we have first elements
				if (listElement == otherListElement)
				{
					bool success = true;

					//check others
					for (size_t el = 1; el < otherListLength - j; el++)
					{
						T nextListElement = At(i + el);
						T nextOtherElement = other.At(j + el);
						if (nextListElement != nextOtherElement)
						{
							success = false;
							break;
						}
					}

					if (success)
						return i;
				}
				else
					break;

			}

		}
	}

	//My variant - 7
	/*+*/void PushFront(List<T>& value)
	{
		//1. get numbers
		//2. push numbers in reverse to front

		//std::cout << "second size: " << value.GetSize() << std::endl;
		for (int i = value.GetSize() - 1; i >= 0 ; i--)
		{
			//std::cout << "index: " << i << std::endl;
			PushFront(value[i]);
		}
	}

	/*+*/void PushBack(T value)
	{
		Node<T>* toAdd = new Node<T>(value);

		//Check if list is clean and if so, setup global pointers
		if(IsEmpty())
			head = current = tail = toAdd;
		else
		{
			//or just add new value to tail
			tail->SetNext(toAdd);
			tail = toAdd;
			MoveToHead();
		}
		count++;
		
	}
	/*+*/void PushFront(T value)
	{
		Node<T>* toAdd = new Node<T>(value);

		//Check if list is clean and if so, setup global pointers
		// OH IT IS SO GREAT TO HAVE FUNCTIONS, WHICH JUST WORK
		if (IsEmpty())
			head = current = tail = toAdd;
		else
		{
			toAdd->SetNext(head);
			head = toAdd;
			MoveToHead();
		}
		count++;
		
	}
	/*+*/void PopBack()
	{
		Remove(count - 1);

		//Do we really get a perfomance boost by implementing special case of Remove(count - 1) function???
		/*
		if(IsEmpty())
			throw std::invalid_argument("Tried to remove element from empty list");

		Node<T>* previousNode = GetNode(count - 2);
		Node<T>* toDelete = GetNode(count - 1);

		//Fix head/tail pointers if toDelete element is head/tail
		if (toDelete == head)
			head = nullptr;
		if (toDelete == tail)
			tail = previousNode;

		if (previousNode != nullptr)
			previousNode->SetNext(nullptr);

		//Fix curElement pointer (it might be toDelete node)
		MoveToHead();
		count--;
		delete toDelete;
		*/
	}
	/*+*/void PopFront()
	{
		Remove(0);

		//Do we really get a perfomance boost by implementing special case of Remove(0) function???
		/*
		if(IsEmpty())
			throw std::invalid_argument("Tried to remove element from empty list");

		Node<T>* toDelete = GetNode(index);
		Node<T>* nextNode = GetNode(index + 1);

		//Fix head/tail pointers if toDelete element is head/tail
		if (toDelete == head)
			head = nextNode;
		if (toDelete == tail)
			tail = nullptr;

		//Fix curElement pointer (it might be toDelete node)
		MoveToHead();
		count--;
		delete toDelete;
		*/
	}
	/*+*/void Insert(T value, size_t index)
	{
		//Check if index is ok
		CheckBounds(index);

		//+MoveToHead();

		//previous can be null!!!
		Node<T>* previousNode = GetNode(index - 1);
		Node<T>* moveNode = GetNode(index);
		Node<T>* toInsert = new Node<T>(value);

		//Set new links
		if(previousNode != nullptr)
			previousNode->SetNext(toInsert);
		toInsert->SetNext(moveNode);

		//set global pointers
		if (moveNode == head)
			head = toInsert;

		count++;
		//+MoveToHead();
	}
	T At(size_t index)
	{
		//Check if index is ok
		CheckBounds(index);

		return GetNode(index)->GetData();

		/*
		//We cant get this element from current position, so MOVE TO HEAD
		if (curElement > index)
			MoveToHead();

		//No need to MOVE TO HEAD every time, we can use curElement to iterate forward
		for (size_t j = curElement; j < index; j++)
			MoveForward();

		return GetCurrentValue();*/
	}
	/*+*/void Remove(size_t index)
	{
		//Check if index is ok
		CheckBounds(index);

		Node<T>* previousNode = GetNode(index - 1);
		Node<T>* toDelete = GetNode(index);
		Node<T>* nextNode = GetNode(index + 1);

		//Fix head/tail pointers if toDelete element is head/tail
		if (toDelete == head)
			head = nextNode;
		if (toDelete == tail)
			tail = previousNode;

		//Connect previousNode with nextNode
		if (previousNode != nullptr)
			previousNode->SetNext(nextNode);

		//Fix curElement pointer (it might be toDelete node)
		MoveToHead();
		count--;
		delete toDelete;
	}
	/*+*/size_t GetSize()
	{
		return count;
	}
	/*+*/void Clear()
	{
		//if head is null, that means list is BROKEN, or just clean
		//But it defenetly cant be broken, I'm sure
		//if (head != nullptr) ---> yeah! I'm so confident! YAY
		if (!IsEmpty())
		{
			//Delete all elements from head
			MoveToHead();
			
			do
			{
				Node<T>* ToDelete = GetCurrentNode();
				MoveForward();
				delete ToDelete;
			} while (GetCurrentNode() != nullptr);
		}
		count = 0;
	}
	/*+*/void Replace(T value, size_t index)
	{
		//Check if index is ok
		CheckBounds(index);

		GetNode(index)->SetData(value);
	}
	/*+*/bool IsEmpty()
	{
		return count < 1;
	} 
	
	
	
	//WHY IS IT HERE
	void PrintToConsole()
	{
		MoveToHead();
		for (size_t i = 0; i < GetSize(); i++)
		{
			std::cout << GetCurrentValue() << ' ';
			MoveForward();
		}
		std::cout << std::endl;
	}
	//for debug only
	void SelfCheck()
	{
		MoveToHead();
		for (size_t i = 0; i < GetSize(); i++)
		{
			T val = GetCurrentValue();
			MoveForward();
		}
	}
};