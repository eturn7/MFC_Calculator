#include"pch.h"
#include "Calcul.h"

// 构造函数
Calcul::Calcul(string str) :
	expr(str),
	idx(0),
	err(0),
	Right(true)
{

}

// 判断表达式是否合法
bool Calcul::test()
{
	if (!word.empty())  // 已经test过了
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
		// 词法正确，进行语法分析
		Next();
		next_bracket();
		if (kind == 0 && err == 0)
			Right = true;
		else
			Right = false;
	}
	return Right;
}

// 计算表达式的值
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



//对输入的内容进行判定，识别出不同符号和数字
int Calcul::word_analysis(vector<pair<string, int>>& word, const string expr)
				//pair作为字符和数字两者的组合，vector把多个pair整合
{
	for (unsigned int i = 0; i < expr.length(); ++i)
	{
		// 如果是 + - x ÷ ( )
		if (expr[i] == '(' || expr[i] == ')' || expr[i] == '+'
			|| expr[i] == '-' || expr[i] == '*' || expr[i] == '/')
		{
			string tmp;
			tmp.push_back(expr[i]);//把expr[i]加到tmp的尾部
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
		// 如果是数字开头
		else if (expr[i] >= '0' && expr[i] <= '9')
		{
			string tmp;
			while (expr[i] >= '0' && expr[i] <= '9')
			{
				tmp.push_back(expr[i]);
				++i;
			}
			//存在小数
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
					return -1;  // .后面不是数字，词法错误
				}
			}
			word.push_back(make_pair(tmp, 5));
			--i;
		}
		// 如果以.开头
		else
		{
			return -1;  // 以.开头，词法错误
		}
	}
	return 0;
}


// 读下一单词的种别编码
void Calcul::Next()
{
	if (idx < word.size())
		kind = word[idx++].second;
	else
		kind = 0;
}

// next_bracket → next_add_sub
void Calcul::next_bracket()
{
	next_add_sub();
	while (kind == 1 || kind == 2)
	{
		Next();
		next_add_sub();
	}
}

// next_add_sub → next_mul_div
void Calcul::next_add_sub()
{
	next_mul_div();
	while (kind == 3 || kind == 4)
	{
		Next();
		next_mul_div();
	}
}

// next_mul_div → (next_bracket) | d
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

//判断表达式的优先级
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

//判断是否是运算符
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











//----------中缀表达式转成后缀表达式----------
vector<pair<string, int>> Calcul::getPostfix(const vector<pair<string, int>>& expr)
{
	vector<pair<string, int>> output;  //输出
	stack<pair<string, int>> s;   //操作符栈
	for (int i = 0; i < expr.size(); i++)
	{
		pair<string, int> c = expr[i];
		//运算符为'+','-','*','/'
		if (isOperator(c.second))
		{
			//当栈非空、扫描到运算符、栈顶元素的优先级高于被扫描元素时
			while (!s.empty() && isOperator(s.top().second) && prior(s.top().second) >= prior(c.second))
			{
				//将栈顶元素出栈
				output.push_back(s.top());
				s.pop();
			}
			s.push(c);
		}
		//运算符为'('
		else if (c.second == 6)
		{
			s.push(c);//直接入栈
		}
		//运算符为')'
		else if (c.second == 7)
		{
			//将栈中左括号“(”以上的所有运算符出栈
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
	//扫描结束，将栈中所有剩余运算符出栈
	while (!s.empty())
	{
		output.push_back(s.top());
		s.pop();
	}
	return output;
}

//从栈中连续弹出两个操作数
void Calcul::popTwoNumbers(stack<double>& s, double& first, double& second)
{
	first = s.top();
	s.pop();
	second = s.top();
	s.pop();
}

//把string转换为double
double Calcul::stringToDouble(const string& str)
{
	double d;
	stringstream ss;
	ss << str;
	ss >> d;
	return d;
}


//--------------计算后缀表达式---------------------
double Calcul::expCalculate(const vector<pair<string, int>>& postfix)
{
	double first, second;//栈顶的两个元素
	stack<double> s;
	for (int i = 0; i < postfix.size(); ++i)
	{
		pair<string, int> p = postfix[i];
		switch (p.second)
		{
		case 1:
			popTwoNumbers(s, first, second);
			s.push(second + first);//扫描到“+”号，栈顶两个元素进行加法运算
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
		default://扫描到非+-*/的运算符，则为数字，直接入栈并转换成double形式
			s.push(stringToDouble(p.first));
			break;
		}
	}
	double result = s.top();//栈中最后的元素即为运算结果
	s.pop();
	return result;
}
