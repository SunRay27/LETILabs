#include <iostream>
#include "InfixToPostfixSolver.h";

using namespace std;
int main()
{
	/*
	* YAY! Check it out! My String implementation literally makes NO garbage!!!
	* This is incredible, luckily i haven't forgotten how to profile and google stuff
	* 
	* NO SERIOUSLY! This is my first c++ program, which includes self-made Stack, List and String classes and makes no garbage AT ALL!!!
	* 
	* ...
	* 
	* Kill me please
	*/
	//cout << "\nmemtest break point\n";

	
	InfixToPostfixSolver c(true);
	

	printf("Welcome to my POSTFIXIFICATOR3000+EVALUATOR3000 program\nType infix formula to make it postfix and to get its result:\n-->");
	while (1)
	{
		char inputBuffer[512];
		gets_s(inputBuffer, 512);
		try
		{
			c.PrintPostfixEval(inputBuffer);
			printf("\n\n\n\n\n\nType new formula?\n-->");
		}
		catch (exception ex)
		{
			printf("\n\n\n\n\n\nSomething went wrong... <%s>\n", ex.what());
			printf("Type new formula?\n-->");
		}
	}

	//cout << "\nmemtest break point\n";
}

