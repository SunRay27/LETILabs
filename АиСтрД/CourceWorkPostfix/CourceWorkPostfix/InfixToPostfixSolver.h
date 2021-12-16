#pragma once

#include "Headers/Defines.h";
#include "Headers/Stack.h";
#include "Headers/List.h";
#include "Headers/String.h";


class InfixToPostfixSolver
{
	bool verbose = false;


	void PackInput(String& source)
	{
		source.ReplaceAll(" ", "");
		source.ReplaceAll("sin", SIN);
		source.ReplaceAll("cos", COS);
		source.ReplaceAll("tg", TG);
		source.ReplaceAll("ctg", CTG);
		source.ReplaceAll("ln", LN);
		source.ReplaceAll("log", LOG);
		source.ReplaceAll("sqrt", SQRT);
		source.ReplaceAll("abs", ABS);
		source.ReplaceAll("pi", PI);
		source.ReplaceAll("e", E);
	}
	String GetUnpackedInput(String source)
	{
		source.ReplaceAll(E, "e");
		source.ReplaceAll(PI, "pi");
		source.ReplaceAll(UPLUS, "+");
		source.ReplaceAll(UMINUS, "-");
		source.ReplaceAll(ABS, "abs");
		source.ReplaceAll(SQRT, "sqrt");
		source.ReplaceAll(LOG, "log");
		source.ReplaceAll(LN, "ln");
		source.ReplaceAll(CTG, "ctg");
		source.ReplaceAll(TG, "tg");
		source.ReplaceAll(COS, "cos");
		source.ReplaceAll(SIN, "sin");

		return source;
	}

	int GetOperatorPriority(char op)
	{
		switch (op)
		{

		case PLUS:
		case MINUS: return 1;

		case MUL:
		case DIV: return 2;

		case POW: return 3;

			//unar operators
		case COS:
		case SIN:
		case TG:
		case CTG:
		case LN:
		case LOG:
		case SQRT:
		case ABS:
		case UMINUS:
		case UPLUS: return 4;

		default:
			return -1;
		}
	}

	bool IsOperator(char c)
	{
		return GetOperatorPriority(c) >= 0 ? true : false;
	}
	bool IsBinarOperator(char op)
	{
		return IsOperator(op) && GetOperatorPriority(op) < 4;
	}
	bool IsUnarOperator(char op)
	{
		return IsOperator(op) && !IsBinarOperator(op);
	}


	//check if string represents const or number
	bool IsNumber(String string)
	{
		//exception for constants
		if (string.Length() == 1)
			if (string[0] == PI || string[0] == E)
				return true;



		for (size_t i = 0; i < string.Length(); i++)
			if ((string[i] < 48 || string[i] > 57) && (string[i] != '.'))
				return false;

		//special check for merget float values
		size_t dotCount = 0;
		for (size_t i = 0; i < string.Length(); i++)
		{
			if (string[i] == '.')
				dotCount++;
			if (dotCount > 1)
				return false;
		}

		return true;
	}

	//get double from string
	double GetValue(String string)
	{

		if (string[0] == PI)
			return M_PI;
		else if (string[0] == E)
			return M_E;
		else
		{
			char* array = string.GetArrayCopy();
			double value = atof(array);

			//printf("\nstring <%s> -> number <%lf>\n", array, value);


			delete[] array;
			return value;
		}
	}

	//evaluate binary operation
	double Eval(char op, double o1, double o2)
	{
		switch (op)
		{
		case MINUS: return o1 - o2;
		case PLUS: return o1 + o2;
		case DIV: return o1 / o2;
		case MUL: return o1 * o2;
		case POW: return pow(o1, o2);
		default: printf("invalid operator: operand <%f> <%f> operator <%s>", o1, o2, GetUnpackedInput(op).GetArrayCopy());
			throw invalid_argument("Unknown operator exception. How did you manage to get here?");
		}
	}
	//evaluate unary operation
	double Eval(char op, double o)
	{
		switch (op)
		{
		case UMINUS: return -o;
		case UPLUS: return o;
		case COS: return cos(o);
		case SIN: return sin(o);
		case TG: return tan(o);
		case CTG: return 1 / tan(o);
		case LN: return log(o);
		case LOG: return log10(o);
		case SQRT: return sqrt(o);
		case ABS: return abs(o);
		default: printf("invalid operator: operand <%f> operator <%s>", o, GetUnpackedInput(op).GetArrayCopy());
			throw invalid_argument("Unknown operator exception. How did you manage to get here?");
		}
	}

public:
	InfixToPostfixSolver(bool verbose = true) : verbose(verbose) {};

	//evaluate postfix format formula from string
	double EvaluatePostfix(String s)
	{
		//we need to separate operators and operands (we added White Spaces in GetPrefixForm() )
		List<String> tokens = String::LazySplitv2(s, ' ');
		//now we begin the operation
		Stack<double> stack;

		if (verbose)
		{
			printf("\n----------------Parsed tokens: ----------------\n");
			for (size_t i = 0; i < tokens.GetSize(); i++)
				printf("<%s> ", tokens.At(i).GetArrayPointer());

			printf("\n");
		}

		//check if there are invalid tokens
		for (size_t i = 0; i < tokens.GetSize(); i++)
		{
			String curToken = tokens.At(i);
			char firstChar = curToken[0];

			//if this is not an operator
			if (!IsOperator(firstChar))
			{
				//and not a number... + 9
				if (!IsNumber(curToken))
				{
					printf("Critical failure! Token #%zu <%s> hasn't been recognized!", i, curToken.GetArrayPointer());
					throw invalid_argument("token failure");
				}
			}

		}



		if (verbose)
			cout << "\nEvaluation steps: \n";

		size_t operationNumber = 0;

		for (size_t i = 0; i < tokens.GetSize(); i++)
		{
			char operatorChar = (tokens.At(i)[0]);
			if (IsBinarOperator(operatorChar))
			{
				if (stack.GetSize() > 1)
				{
					operationNumber++;
					//binary operator
					char operatorChar = tokens.At(i)[0];

					double operand2 = stack.Pop();
					double operand1 = stack.Pop();
					double result = Eval(operatorChar, operand1, operand2);
					if (verbose)
						printf("#%zu %f %c %f = %f\n", operationNumber, operand1, operatorChar, operand2, result);

					stack.Push(result);
				}
			}
			else if (IsUnarOperator(operatorChar))
			{
				//process unar operator
				operationNumber++;
				char operatorChar = tokens.At(i)[0];

				double operand = stack.Pop();
				double result = Eval(operatorChar, operand);
				if (verbose)
				{
					printf("#%zu %s (%f) = %f\n", operationNumber, GetUnpackedInput(operatorChar).GetArrayPointer(), operand, result);
				}

				stack.Push(result);

			}
			else
			{
				//we read operand, so add it to stack
				stack.Push(GetValue(tokens.At(i)));
			}
		}

		double result = stack.IsEmpty() ? NAN : stack.Peek();

		if (verbose)
		{
			printf("\n Evalutaion result: %f\n", result);
		}

		return result;

	}
	String GetPostfixForm(String s)
	{
		Stack<char> operatorStack;
		String result;

		if (verbose)
		{
			printf("Input: %s\n", s.GetArrayPointer());
		}

		//replace functions with unar symbol
		PackInput(s);
		if (verbose)
		{
			printf("Packed input: %s\n", s.GetArrayPointer());
		}

		bool previousCharWasMarker = false;

		// previous element was operand?
		bool wasOperand = false;

		//are we processed bin operator and now waiting for operand? (index of waiting operator)
		long long waitingForOperandIndex = -1;
		//long long waitingForOperatorIndex = -1;

		//things to catch sbracket incorrect input
		size_t bracketLevel = 0;
		List<size_t> sbracketIndexes;

		//process string
		for (size_t i = 0; i < s.Length(); i++)
		{
			if (IsOperator(s[i]))
			{
				char toPush = s[i];

				if (i == 0 || previousCharWasMarker)
				{
					//this operator is unar!!!
					if (s[i] == MINUS)
						toPush = UMINUS;
					if (s[i] == PLUS)
						toPush = UPLUS;

					//but if it is a binary operator... +1
					if (IsBinarOperator(toPush))
					{
						printf("Wrong input at #%zu (expected: unar operator) (read: binar operator)\n", i);
						throw invalid_argument("Wrong operator input");
					}
				}

				previousCharWasMarker = true;

				if (IsBinarOperator(toPush))
				{
					if (waitingForOperandIndex >= 0)
					{
						//+8
						printf("Wrong input at #%zu (expected: operand) (read: operator)\n", waitingForOperandIndex);
						throw invalid_argument("Wrong operator input");
					}
					waitingForOperandIndex = i;
					while (!operatorStack.IsEmpty() && GetOperatorPriority(toPush) <= GetOperatorPriority(operatorStack.Peek()))
					{
						//add all operators, which are weaker than this one to result
						result += ' ';
						result += operatorStack.Pop();
					}
				}
				else
				{
					waitingForOperandIndex = i;
					if (wasOperand)
					{
						//+6
						printf("Wrong input at #%zu (expected: binar operator) (read: unar operator)\n", i);
						throw invalid_argument("Wrong operator input");
					}
				}
				//add this one
				operatorStack.Push(toPush);
				wasOperand = false;
			}
			else if (s[i] == SBRACKET)
			{
				sbracketIndexes.Add(i);
				bracketLevel++;
				previousCharWasMarker = true;
				operatorStack.Push(SBRACKET);
			}
			else if (s[i] == EBRACKET)
			{
				if (operatorStack.IsEmpty())
				{
					//wrong closing bracket +4
					printf("Wrong closing bracket input at #%zu (has no starting bracket)\n", i);
					throw invalid_argument("Wrong closing bracket input");
				}

				previousCharWasMarker = false;
				bracketLevel--;
				//add all operators we had before
				while (operatorStack.Peek() != SBRACKET)
				{

					result += ' ';
					result += operatorStack.Pop();

					if (operatorStack.IsEmpty())
					{
						//wrong closing bracket +5
						printf("Wrong closing bracket input at #%zu (has no starting bracket)\n", i);
						throw invalid_argument("Wrong closing bracket input");
					}
				}
				operatorStack.Pop();
			}
			else
			{
				if (wasOperand)
				{
					//+7
					printf("Wrong input at #%zu (operator expected)\n", i);
					throw invalid_argument("Wrong operand input");
				}
				//this is an operand

				previousCharWasMarker = false;
				result += ' ';
				waitingForOperandIndex = -1;

				//plz forgive me for this masterpiece
				//read it until end
				while (i < s.Length() && !IsOperator(s[i]) && s[i] != SBRACKET && s[i] != EBRACKET)
				{
					result += s[i];
					i++;
				}
				i--;

				wasOperand = true;
			}
		}

		while (!operatorStack.IsEmpty())
		{
			result += ' ';
			result += operatorStack.Pop();
		}
		if (waitingForOperandIndex >= 0)
		{
			// +2
			printf("Wrong input at #%zu (operand expected)\n", waitingForOperandIndex);
			throw invalid_argument("Wrong operator input");
		}
		if (bracketLevel > 0)
		{
			// +3
			printf("Wrong starting bracket input at #%zu (has no closing bracket)\n", sbracketIndexes[bracketLevel - 1]);
			throw invalid_argument("Wrong starting bracket input");
		}

		if (verbose)
		{
			printf("Output: %s\n", result.GetArrayPointer());

			String beautifulForm = GetUnpackedInput(result);

			printf("Postfix: %s\n", beautifulForm.GetArrayPointer());
		}

		return result;
	}

	void PrintPostfixEval(String s)
	{
		String postfixForm = GetPostfixForm(s);
		double result = EvaluatePostfix(postfixForm);
	}
};