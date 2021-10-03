#include<iostream>
#include<vector>
#include <string>
#include "windows.h"
using namespace std;
enum class State
{
	q0 = 0, 
	q1, 
	q2, 
	q3, 
	q4
};
#pragma once
class TuringMachine
{
private:
	vector<char> _exp;
	size_t _pos;
	bool _stepMode;
	bool _multiplyOp = false;
	bool _addOp = false;
	void _moveRight();
	void _moveLeft();
	char _eraseCurrentChar();
	char _getCurrentChar();
	void _add();
	void _multiply();
	void _step();
	void _solve();
	void _getExpression();
	void _writeCharToCurrentPos(char c);

public:
	TuringMachine(string expr, bool step = false);

};
