#include<turing_machine.h>
#include<iostream>
using namespace std;

int main()
{
	string expr;
	cout << "Input expression: " << endl;
	int i = 0;
	do
	{
		if (i != 0)
			cout << "Entered expression is invalid" << endl;
		getline(cin, expr);
		i++;
	} 	while (expr.find('+') == -1 && expr.find('*') == -1);
	TuringMachine tm(expr, true);
}