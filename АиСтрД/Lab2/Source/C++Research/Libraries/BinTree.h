#include <stdexcept>
#include <iostream>
#include <string>
#include "Queue.h";
#include "Stack.h";

using namespace std;

class TreeNode
{
	TreeNode* right, * left;
	int key;
public:
	~TreeNode() { delete right, left; }
	TreeNode() : right(nullptr), left(nullptr), key(-1) {}
	TreeNode(int value) : key(value), right(nullptr), left(nullptr) {}
	TreeNode(int value, TreeNode* right, TreeNode* left, TreeNode* parent) : key(value), right(right), left(left) {}

	void SetRight(TreeNode* rightElement) { right = rightElement;}
	void SetLeft(TreeNode* leftElement) { left = leftElement;}
	void SetKey(int key) { this->key = key; }

	TreeNode* GetRight() { return right; }
	TreeNode* GetLeft() { return left; }
	int GetKey() { return key; }
};

class Iterator
{
public:
	virtual int Next() = 0;
	virtual bool HasNext() = 0;
};
class TreeDFTIterator : public Iterator
{
private:
	Stack<TreeNode*> stack;

	void pushToLeft(TreeNode* node)
	{
		if (node == nullptr)
			return;

		stack.Push(node);
		pushToLeft(node->GetLeft());
	}
public:
	TreeDFTIterator(TreeNode* start)
	{
		pushToLeft(start);
	}
	int Next() override
	{
		TreeNode* node = stack.Pop();
		pushToLeft(node->GetRight());
		return node->GetKey();
	}
	bool HasNext() override
	{
		return stack.GetSize() != 0;
	}
};
class TreeBFTIterator : public Iterator
{
private:
	Queue<TreeNode*> queue;
public:
	TreeBFTIterator(TreeNode* start)
	{
		if (start == nullptr)
			return;

		queue.Enqueue(start);
	}
	int Next() override
	{
		TreeNode* next = queue.Dequeue();
		if (next->GetLeft() != nullptr)
			queue.Enqueue(next->GetLeft());

		if (next->GetRight() != nullptr)
			queue.Enqueue(next->GetRight());

		return next->GetKey();
	}
	bool HasNext() override
	{
		return queue.GetSize() != 0;
	}
};

class Tree
{
private:
	TreeNode* root;
	int size = 0;
	TreeNode* deleteRecursive(TreeNode* root, int key)
	{
		if (root == nullptr)
			return root;

		//move down
		if (key < root->GetKey())
			root->SetLeft(deleteRecursive(root->GetLeft(), key));
		else if (key > root->GetKey())
			root->SetRight(deleteRecursive(root->GetRight(), key));
		else
		{
			//we found target node

			// node with only one child or no child  
			if (root->GetLeft() == nullptr)
				return root->GetRight();
			else if (root->GetRight() == nullptr)
				return root->GetLeft();

			//set smallest key from right subtree
			root->SetKey(minValue(root->GetRight()));

			// Delete smallest key in right subtree
			TreeNode* newNode = deleteRecursive(root->GetRight(), root->GetKey());
			delete root->GetRight();
			root->SetRight(newNode);
		}
		return root;
	}
	int minValue(TreeNode* root)
	{
		int minv = root->GetKey();
		while (root->GetLeft() != nullptr)
		{
			minv = root->GetLeft()->GetKey();
			root = root->GetLeft();
		}
		return minv;
	}
	void print(TreeNode* root, int depth = 0, int pos = 0)
	{
		//print itself
		if (root == nullptr)
			return;
		cout << endl;

		for (size_t i = 0; i < depth; i++)
		{
			if (i != depth - 1)
				cout << "   ";
			else

				cout << "|__";
		}

		cout << "";
		if (pos == 0)
			cout << "ROOT:";
		if (pos == 1)
			cout << "R:";
		if (pos == -1)
			cout << "L:";

		cout << root->GetKey();

		//print left
		print(root->GetLeft(), depth + 1, -1);
		//print right
		print(root->GetRight(), depth + 1, 1);
	}

public:

	~Tree() { delete root; }
	Tree(TreeNode* root) : root(root) { }
	Tree() : root(nullptr) { }

	Iterator* CreateDFTIterator() { return new TreeDFTIterator(root); }
	Iterator* CreateBFTIterator() { return new TreeBFTIterator(root); }

	int GetSize()
	{
		return size;
	}
	TreeNode* GetRoot()
	{
		return root;
	}
	//template <class T>
	void InsertKeys(std::initializer_list<int> list)
	{
		for (auto elem : list)
		{
			Insert(elem);
		}
	}
	void RemoveKeys(std::initializer_list<int> list)
	{
		for (auto elem : list)
		{
			Remove(elem);
		}
	}
	bool Contains(int key)
	{
		TreeNode* current = root;
		while (current != nullptr) {
			if (key == current->GetKey())
				return true;
			else
			{
				if (key < current->GetKey())
					current = current->GetLeft();
				else
					current = current->GetRight();
			}
		}
		return false;
	}
	void Insert(int key)
	{
		size++;
		TreeNode* currentNode = root;
		if (root == nullptr)
		{
			root = new TreeNode(key);
			return;
		}
		else
			while (true)
			{
				if (key < currentNode->GetKey())
				{
					if (currentNode->GetLeft() == nullptr)
					{
						currentNode->SetLeft(new TreeNode(key));
						break;
					}
					else
						currentNode = currentNode->GetLeft();
				}
				else
				{
					if (currentNode->GetRight() == nullptr)
					{
						currentNode->SetRight(new TreeNode(key));
						break;
					}
					else
						currentNode = currentNode->GetRight();
				}
			}
	}
	void Remove(int key)
	{ 
		if (!Contains(key))
			throw exception("key is not present in collection");
		root = deleteRecursive(root, key); 
		size--;
	}
	void Print() {print(root);}
};
