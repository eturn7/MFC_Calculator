#include"pch.h"
#include "Calcul.h"

// ���캯��
Calcul::Calcul(string str) :
	expr(str),
	idx(0),
	err(0),
	Right(true)
{

}

// �жϱ��ʽ�Ƿ�Ϸ�
bool Calcul::test()
{
	if (!word.empty())  // �Ѿ�test����
	{
		return Right;
	}

	int err_num = word_analysis(word, expr);
	if (-1 == err_num)
	{
		Right = false;
	}
	else
	{
		// �ʷ���ȷ�������﷨����
		Next();
		next_bracket();
		if (kind == 0 && err == 0)
			Right = true;
		else
			Right = false;
	}
	return Right;
}

// ������ʽ��ֵ
double Calcul::calculate()
{
	if (test())
	{
		return expCalculate(getPostfix(word));
	}
	else
	{
		exit(0);
	}
}



//����������ݽ����ж���ʶ�����ͬ���ź�����
int Calcul::word_analysis(vector<pair<string, int>>& word, const string expr)
				//pair��Ϊ�ַ����������ߵ���ϣ�vector�Ѷ��pair����
{
	for (unsigned int i = 0; i < expr.length(); ++i)
	{
		// ����� + - x �� ( )
		if (expr[i] == '(' || expr[i] == ')' || expr[i] == '+'
			|| expr[i] == '-' || expr[i] == '*' || expr[i] == '/')
		{
			string tmp;
			tmp.push_back(expr[i]);//��expr[i]�ӵ�tmp��β��
			switch (expr[i])
			{
			case '+':
				word.push_back(make_pair(tmp, 1));
				break;
			case '-':
				word.push_back(make_pair(tmp, 2));
				break;
			case '*':
				word.push_back(make_pair(tmp, 3));
				break;
			case '/':
				word.push_back(make_pair(tmp, 4));
				break;
			case '(':
				word.push_back(make_pair(tmp, 6));
				break;
			case ')':
				word.push_back(make_pair(tmp, 7));
				break;
			}
		}
		// ��������ֿ�ͷ
		else if (expr[i] >= '0' && expr[i] <= '9')
		{
			string tmp;
			while (expr[i] >= '0' && expr[i] <= '9')
			{
				tmp.push_back(expr[i]);
				++i;
			}
			//����С��
			if (expr[i] == '.')
			{
				++i;
				if (expr[i] >= '0' && expr[i] <= '9')
				{
					tmp.push_back('.');
					while (expr[i] >= '0' && expr[i] <= '9')
					{
						tmp.push_back(expr[i]);
						++i;
					}
				}
				else
				{
					return -1;  // .���治�����֣��ʷ�����
				}
			}
			word.push_back(make_pair(tmp, 5));
			--i;
		}
		// �����.��ͷ
		else
		{
			return -1;  // ��.��ͷ���ʷ�����
		}
	}
	return 0;
}


// ����һ���ʵ��ֱ����
void Calcul::Next()
{
	if (idx < word.size())
		kind = word[idx++].second;
	else
		kind = 0;
}

// next_bracket �� next_add_sub
void Calcul::next_bracket()
{
	next_add_sub();
	while (kind == 1 || kind == 2)
	{
		Next();
		next_add_sub();
	}
}

// next_add_sub �� next_mul_div
void Calcul::next_add_sub()
{
	next_mul_div();
	while (kind == 3 || kind == 4)
	{
		Next();
		next_mul_div();
	}
}

// next_mul_div �� (next_bracket) | d
void Calcul::next_mul_div()
{
	if (kind == 5)
	{
		Next();
	}
	else if (kind == 6)
	{
		Next();
		next_bracket();
		if (kind == 7)
		{
			Next();
		}
		else
		{
			err = -1;
		}
	}
	else
	{
		err = -1;
	}
}

//�жϱ��ʽ�����ȼ�
int Calcul::prior(int sym)
{
	switch (sym)
	{
	case 1:
	case 2:
		return 1;
	case 3:
	case 4:
		return 2;
	default:
		return 0;
	}
}

//�ж��Ƿ��������
bool Calcul::isOperator(int sym)
{
	switch (sym)
	{
	case 1:
	case 2:
	case 3:
	case 4:
		return true;
	default:
		return false;
	}
}











//----------��׺���ʽת�ɺ�׺���ʽ----------
vector<pair<string, int>> Calcul::getPostfix(const vector<pair<string, int>>& expr)
{
	vector<pair<string, int>> output;  //���
	stack<pair<string, int>> s;   //������ջ
	for (int i = 0; i < expr.size(); i++)
	{
		pair<string, int> c = expr[i];
		//�����Ϊ'+','-','*','/'
		if (isOperator(c.second))
		{
			//��ջ�ǿա�ɨ�赽�������ջ��Ԫ�ص����ȼ����ڱ�ɨ��Ԫ��ʱ
			while (!s.empty() && isOperator(s.top().second) && prior(s.top().second) >= prior(c.second))
			{
				//��ջ��Ԫ�س�ջ
				output.push_back(s.top());
				s.pop();
			}
			s.push(c);
		}
		//�����Ϊ'('
		else if (c.second == 6)
		{
			s.push(c);//ֱ����ջ
		}
		//�����Ϊ')'
		else if (c.second == 7)
		{
			//��ջ�������š�(�����ϵ������������ջ
			while (s.top().second != 6)
			{
				output.push_back(s.top());
				s.pop();
			}
			s.pop();
		}
		else
		{
			output.push_back(c);
		}
	}
	//ɨ���������ջ������ʣ���������ջ
	while (!s.empty())
	{
		output.push_back(s.top());
		s.pop();
	}
	return output;
}

//��ջ��������������������
void Calcul::popTwoNumbers(stack<double>& s, double& first, double& second)
{
	first = s.top();
	s.pop();
	second = s.top();
	s.pop();
}

//��stringת��Ϊdouble
double Calcul::stringToDouble(const string& str)
{
	double d;
	stringstream ss;
	ss << str;
	ss >> d;
	return d;
}


//--------------�����׺���ʽ---------------------
double Calcul::expCalculate(const vector<pair<string, int>>& postfix)
{
	double first, second;//ջ��������Ԫ��
	stack<double> s;
	for (int i = 0; i < postfix.size(); ++i)
	{
		pair<string, int> p = postfix[i];
		switch (p.second)
		{
		case 1:
			popTwoNumbers(s, first, second);
			s.push(second + first);//ɨ�赽��+���ţ�ջ������Ԫ�ؽ��мӷ�����
			break;
		case 2:
			popTwoNumbers(s, first, second);
			s.push(second - first);
			break;
		case 3:
			popTwoNumbers(s, first, second);
			s.push(second * first);
			break;
		case 4:
			popTwoNumbers(s, first, second);
			s.push(second / first);
			break;
		default://ɨ�赽��+-*/�����������Ϊ���֣�ֱ����ջ��ת����double��ʽ
			s.push(stringToDouble(p.first));
			break;
		}
	}
	double result = s.top();//ջ������Ԫ�ؼ�Ϊ������
	s.pop();
	return result;
}
