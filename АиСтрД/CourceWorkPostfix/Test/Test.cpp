#include "pch.h"
#include "CppUnitTest.h"
#include "../C++PursachV3/InfixToPostfixSolver.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(ExceptionTests)
	{
	private:
		float eps = 0.001;
		bool AreSame(double a, double b)
		{
			return abs(a - b) < eps;
		}
	public:
		InfixToPostfixSolver c;

		//1
		//Wrong operator input at #%zu (expected: unar operator) (read: binar operator)
		TEST_METHOD(WrongOperator1)
		{
			try {
				String newForm = c.GetPostfixForm("*sin(20)");
				double result = c.EvaluatePostfix(newForm);
			}
			catch (exception ex){}
		}


		//2
		//Wrong operator input at #%zu (operand expected)
		//binar operator without 2nd operand
		TEST_METHOD(WrongOperator2)
		{
			try {
				String newForm = c.GetPostfixForm("sin(20)*");
				double result = c.EvaluatePostfix(newForm);
			}
			catch (exception ex) {}
		}

		//3
		//Wrong starting bracket input at #%zu (has no closing bracket)
		TEST_METHOD(WrongSBracket)
		{
			try {
				String newForm = c.GetPostfixForm("(20+59");
				double result = c.EvaluatePostfix(newForm);
			}
			catch (exception ex) {}
		}

		//4
		// Wrong closing bracket input at #%zu (has no starting bracket) case#1
		TEST_METHOD(WrongClosingBracket1)
		{
			try {
				String newForm = c.GetPostfixForm("(20+59))");
				double result = c.EvaluatePostfix(newForm);
			}
			catch (exception ex) {}
		}


		//5
		// Wrong closing bracket input at #%zu (has no starting bracket) case#2
		TEST_METHOD(WrongClosingBracket2)
		{
			try {
				String newForm = c.GetPostfixForm("(20+59)+20)");
				double result = c.EvaluatePostfix(newForm);
			}
			catch (exception ex) {}
		}
		//6
		//Wrong operator input at #%zu (expected: binar operator) (read: unar operator)
		TEST_METHOD(WrongOperator3)
		{
			try {
				String newForm = c.GetPostfixForm("20 sin 20");
				double result = c.EvaluatePostfix(newForm);
			}
			catch (exception ex) {}
		}


		//7
		//Wrong operand input at #%zu (operator expected)
		TEST_METHOD(WrongOperand)
		{
			try {
				String newForm = c.GetPostfixForm("(20 + 20)20*1");
				double result = c.EvaluatePostfix(newForm);
			}
			catch (exception ex) {}
		}


		//8
		//Wrong operator input at #%zu (expected: operand) (read: operator)
		TEST_METHOD(WrongOperand2)
		{
			try {
				String newForm = c.GetPostfixForm("(15*15*)*5");
				double result = c.EvaluatePostfix(newForm);
			}
			catch (exception ex) {}
		}


		//9
		//Critical failure! Token #%zu <%s> hasn't been recognized!
		TEST_METHOD(WrongTokenTest)
		{
			try {
				String newForm = c.GetPostfixForm("5+123+5/x");
				double result = c.EvaluatePostfix(newForm);
			}
			catch (exception ex) {}
		}
		TEST_METHOD(MergedNumberTest)
		{
			try
			{
				String newForm = c.GetPostfixForm("1.5 1.1 + e - 20 /");
				double result = c.EvaluatePostfix(newForm);
			}
			catch (exception ex)
			{

			}
		}
		TEST_METHOD(EmptyInputTest)
		{
			String newForm = c.GetPostfixForm("");
			double result = c.EvaluatePostfix(newForm);

			Assert::IsTrue(isnan(result));
			
		}
	};

	TEST_CLASS(MainTests)
	{
	private:
		float eps = 0.001;
		bool AreSame(double a, double b)
		{
			return abs(a - b) < eps;
		}
	public:
		InfixToPostfixSolver c;

		TEST_METHOD(IntTest)
		{
			String newForm = c.GetPostfixForm("1+2+3*20-10*20+100/5");
			int result = (int)c.EvaluatePostfix(newForm);
			Assert::IsTrue(AreSame(result, -117));
		}
		TEST_METHOD(DoubleFormatTest)
		{
			String newForm = c.GetPostfixForm(".5 + 1.5 + 1.0 + 1");
			double result = c.EvaluatePostfix(newForm);
			Assert::IsTrue(AreSame(result, 4));
		}
		TEST_METHOD(UnarMadnessTest)
		{
			String newForm = c.GetPostfixForm("-+------+-(-+-+2+--+-+(++-+-+-+10)^-+---+-2++++++1)");
			double result = c.EvaluatePostfix(newForm);
			Assert::IsTrue(AreSame(result, 3.01));
		}
		TEST_METHOD(HardTest)
		{
			String newForm = c.GetPostfixForm("-(((((((8^2-1)/(5^2+1))/(1+ (-5)^6)) + (((8^2.1-1)/(5^2/5+1.1))/(1+ (-5)^6)))^2)*(10^5)/20.5)+e/pi+pi^2)^5");
			double result = c.EvaluatePostfix(newForm);
			Assert::IsTrue(AreSame(result, -142860.622));
		}
		TEST_METHOD(HardTest2)
		{
			String newForm = c.GetPostfixForm("tg(-sin(-(((((((8^2-1)/(5^2+1))/(1+ (-5)^6)) + (((8^2.1-1)/(5^2/5+1.1))/(1+ (-5)^6)))^2)*(10^5)/20.5)+e/pi+pi^2)^5)*(ln(5^(-.5)))*(-1)+20/5.99999999999999999999999999999999999999999999999999)");
			double result = c.EvaluatePostfix(newForm);
			Assert::IsTrue(AreSame(result, 0.0623));
		}
	};
}
