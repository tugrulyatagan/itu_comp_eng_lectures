#include <iostream>
#include <string>
#include "stack.h"
#define MAXELEMENT 20
using namespace std;

int precedence(char);
bool isoperation(char op);

int main(){
	char infix[MAXELEMENT];
	char postfix[MAXELEMENT];
	int p = 0;

	Stack s;
	s.create();
	
	cout << "Infix-Postfix Converter and Calculator" << endl;
	cout << "Write an expression and then press enter" << endl;
	cout << "Infix: ";
	cin >> infix;


	// postfix donusumu
	char next;
	for(int i=0; i < strlen(infix); i++){
		if(infix[i] == '(') // sol parantez
			s.push(infix[i]);
		else if(infix[i] == ')') // sag parantez
			while((next = s.pop())!='(')
				postfix[p++] = next;
		else if(!isoperation(infix[i])) //operand
			postfix[p++] = infix[i];
		else if(isoperation(infix[i])){ //operator
			while((!s.isempty()) && (precedence(infix[i]) <= precedence(s.head->data)))
				postfix[p++] = s.pop();
			s.push(infix[i]);
		}
	}// dongu
	while(!s.isempty())
		postfix[p++] = s.pop();
	postfix[p] = '\0';

	if (!s.isempty()){
		cout << "Bi pislik var" << endl;
		//bosalana kadar sil s.pop();
		//s.close();
		//return EXIT_FAILURE;
	}
	cout << "Postfix is: " << postfix << endl;
	s.close();

	//hesaplama
	Stack c;
	c.create();

	float result;
	int num1, num2;
	for(int i=0 ; postfix[i]!='\0'; i++){
		if(!isoperation(postfix[i])) //opreand ise stack e at
			c.push(postfix[i]);
		else if(isoperation(postfix[i])){ //operator ise hesap yap
			if(postfix[i] == '+'){
				num1 = int(c.pop() - '0');
				num2 = int(c.pop() - '0');
				result = num2 + num1;
			}
			else if(postfix[i] == '-'){
				num1 = int(c.pop() - '0');
				num2 = int(c.pop() - '0');
				result = num2 - num1;
			}
			else if(postfix[i] == '/'){
				num1 = int(c.pop() - '0');
				num2 = int(c.pop() - '0');
				result = num2 / num1;
			}
			else if(postfix[i] == '*'){
				num1 = int(c.pop() - '0');
				num2 = int(c.pop() - '0');
				result = num2 * num1;
			}
			c.push(char(result + '0'));
		}
	}
	result = c.pop();
	cout << "Calculation is:" << int(result - '0') << endl;
	c.close();
	return EXIT_SUCCESS;
}

int precedence(char c){
	if((c == '*') || (c == '/'))
		return 2;
	else if((c == '+') || (c == '-'))
		return 1;
	else if((c == '(') || (c == ')'))
		return 0;
}

bool isoperation(char op){
    if (op == '+' || op == '-' || op == '/' || op == '*')
        return 1;
	return 0;
}
