#include "stack.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[]){
	char *infix = "2*3-6/(2+1)";
	// postfix expression to be returned
	char postfix[100];
    // postfixindex shows the current index on postfix
	int postfixindex = 0;

	// infix to postfix conversion is done by using a stack
	struct Stack operatorstack;
	operatorstack.create();

    // scanning the infix expression from start to the end
	for (int i=0; infix[i]!='\0'; i++){
		// if current character is '(' then it is pushed directly into the stack
		if (infix[i] == '(')
            operatorstack.push(infix[i]);
        // if current character is '*' then it is pushed directly into the stack
		else if (infix[i] == '*')
			operatorstack.push(infix[i]);
        // '/' cannot be placed on '*' in the stack
		else if (infix[i] == '/'){
			if (!operatorstack.isEmpty())
				while (operatorstack.getHeadChar() == '*'){
					postfix[postfixindex] = operatorstack.pop();
					postfixindex++;
					if (operatorstack.isEmpty()) break;
				}
			operatorstack.push(infix[i]);
		}
		// '+' cannot be placed on '*' or '/' in the stack
		else if (infix[i] == '+'){
			if (!operatorstack.isEmpty())
				while (operatorstack.getHeadChar() == '*' 
					  || operatorstack.getHeadChar() == '/'){
					postfix[postfixindex] = operatorstack.pop();
					postfixindex++;
					if (operatorstack.isEmpty()) break;
				}
			operatorstack.push(infix[i]);
		}
		// '-' cannot be placed on any operator in the stack
		else if (infix[i] == '-'){
			if (!operatorstack.isEmpty())
				while (operatorstack.getHeadChar() == '*' 
					  || operatorstack.getHeadChar() == '/'
                      || operatorstack.getHeadChar() == '+'){
					postfix[postfixindex] = operatorstack.pop();
					postfixindex++;
					if (operatorstack.isEmpty()) break;
				}
			operatorstack.push(infix[i]);
		}
		// if current character is ')' then pop operators 
		// from stack to postfix until '('
		else if (infix[i] == ')'){
			while (operatorstack.getHeadChar() != '('){
				postfix[postfixindex] = operatorstack.pop();
				postfixindex++;
			}
			// '(' is popped from the stack without appending 
			// to the postfix string
			char buffer = operatorstack.pop();
		}
		// operands are directly appended to the postfix string
		else{
			postfix[postfixindex] = infix[i];
			postfixindex++;
		}
		// postfix string and contents of the stack are printed out 
		// on the screen at each step. '\0' is appended to prevent 
		// printing wrong characters in the end
		postfix[postfixindex] = '\0';
		cout << "Postfix string: " << postfix << "\t";
		operatorstack.print();
	}
	// remaining characters in the stack are added to the postfix 
	// string after the end of scan
	while (!operatorstack.isEmpty()){
		postfix[postfixindex] = operatorstack.pop();
		postfixindex++;
	}

    // postfix string is printed out on the screen
    // '\0' is appended to prevent printing wrong characters in the end
    postfix[postfixindex] = '\0';
	cout << endl << "Postfix string: " << postfix << endl;

	// allocated memory for the stack nodes is given back
	operatorstack.makeEmpty();
	struct Stack calculatorStack;
	calculatorStack.create();
	int index = 0;
	while(postfix[index] != '\0')
	{
		if(postfix[index] != '+' && postfix[index] != '-' && postfix[index] != '*' && postfix[index] != '/')
			calculatorStack.push(postfix[index]);
		else
		{
			char operand1 = calculatorStack.pop();
			char operand2 = calculatorStack.pop();
			int op1 = operand1 - 48; 
			int op2 = operand2 - 48;
			int result;
			if(postfix[index] == '+')
				result = op1 + op2;
			else if(postfix[index] == '-')
				result = op2 - op1;
			else if(postfix[index] == '*')
				result = op1 * op2;
			else if(postfix[index] == '/')
				result = op2 / op1;
			char res = result + 48;
			calculatorStack.push(res);
		}
		index++;
	}
	cout << "Result: " << calculatorStack.pop() << endl;
	system("pause");
	return 0;
}
