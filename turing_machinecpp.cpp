#include<turing_machine.h>

TuringMachine::TuringMachine(string exp, bool step)
{
	this->_stepMode = step;
	this->_exp.push_back('@');
	for(char c : exp)
	{
		this->_exp.push_back(c);
	}

	for (int i = 0; i < 5; i++)
	{
		this->_exp.push_back('@');
	}
	this->_pos = 1;

	if (exp.find('+') != -1)
	{
		_addOp = true;
		_multiplyOp = false;
	}
	else if(exp.find('*') != -1)
	{
		_addOp = false;
		_multiplyOp = true;
	}
	else
	{
		throw exception();
	}
	_solve();
}

void TuringMachine::_moveLeft()
{
	_pos--;
}

void TuringMachine::_moveRight()
{
	if (_pos == _exp.size() - 1)
	{
		for(int i = 0; i < 5; i++)
			_exp.push_back('@');
	}
	_pos++;
}

char TuringMachine::_getCurrentChar()
{
	return _exp[_pos];
}

void TuringMachine::_writeCharToCurrentPos(char c)
{
	_exp[_pos] = c;
}

void TuringMachine::_add()
{
	State state = State::q0;
	char c = _getCurrentChar();
	while (true)
	{
		switch (state)
		{
			case State::q0:
				while (c != '@')
				{
					_moveLeft();
					_step();
					c = _getCurrentChar();
				}
				_moveRight();
				if (_getCurrentChar() == '1')
				{
					state = State::q1;
				}
				else if (_getCurrentChar() == '+')
				{
					_moveRight();
					state = State::q1;
				}
				else
				{
					return;
				}
				break;
			case State::q1:
				char tmp = _eraseCurrentChar();
				while (c != '@')
				{
					_moveRight();
					_step();
					c = _getCurrentChar();
				}
				_writeCharToCurrentPos(tmp);
				state = State::q0;
				break;
		}
		c = _getCurrentChar();
	}
}

void TuringMachine::_multiply()
{
	State state = State::q0;
	char tmp;
	char c = _getCurrentChar();
	while (true)
	{
		switch (state)
		{
			case State::q0:
			{
				while (_getCurrentChar() != '@')
				{
					_moveLeft();
					_step();
				}
				_moveRight();

				if (_getCurrentChar() == '1')
				{
					state = State::q1;
				}
				else if (_getCurrentChar() == '*')
				{
					return;
				}
				else
				{
					return;
				}
				break;
			}
			case State::q1:
			{
				_writeCharToCurrentPos('@');
				while (_getCurrentChar() != '*')
				{
					_moveRight();
					_step();
				}
				_moveRight();
				tmp = _getCurrentChar();
				state = State::q2;
				break;
			}

			case State::q2:
			{
				_writeCharToCurrentPos('&');
				while (_getCurrentChar() != '@')
				{
					_moveRight();
					_step();
				}
				_writeCharToCurrentPos(tmp);
				state = State::q3;
				break;
			}

			case State::q3:
			{
				while (_getCurrentChar() != '&')
				{
					_moveLeft();
					_step();
				}
				_moveRight();
				state = State::q2;
				if (_getCurrentChar() == '=')
				{
					state = State::q4;
				}
				break;
			}

			case State::q4:
			{
				_moveLeft();
				while (_getCurrentChar() == '&')
				{
					_writeCharToCurrentPos('1');
					_moveLeft();
					_step();
				}
				state = State::q0;
				break;
			}

		}
	}
}




char TuringMachine::_eraseCurrentChar()
{
	char c = _exp[_pos];
	_writeCharToCurrentPos('@');
	return c;
}


void TuringMachine::_getExpression()
{
	size_t spaces = _pos;
	for (char c : this->_exp)
	{
		cout << c;
	}
	cout << endl;
	while (spaces != 0)
	{
		spaces--;
		cout << " ";
	}
	cout << "^";

}


void TuringMachine::_solve()
{
	if (_addOp)
	{
		_add();
	}
	else
	{
		_multiply();
	}

}

void TuringMachine::_step()
{
	if(_stepMode)
		getchar();
	else
		Sleep(100);
	system("cls");
	_getExpression();
}
