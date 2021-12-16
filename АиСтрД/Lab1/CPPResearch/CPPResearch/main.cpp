#include <iostream>
#include "./Libraries/List/ListTasks.h"
using namespace std;

//var 7
int main()
{
	List<int> first, second;

	first.AddValues({ 1,1,1 });
	second.AddValues({ 2,2,2,2 });
	//second.AddValues({ 3,5,2,1 });

	first.PrintToConsole();
	second.PrintToConsole();

	first.PushFront(second);

	first.PrintToConsole();
	//cout << (int)second.FindFirst(first);

	cout << "Hello world!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
	return 1;
}


