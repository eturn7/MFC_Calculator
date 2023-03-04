#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <stack>
#include <utility>
#include "pch.h"
using namespace std;

class Calcul
{
public:
	Calcul(string str);
	bool test();         // 外部接口，判断表达式是否合法
	double calculate();  // 外部接口，计算表达式的值 

private:
	vector<pair<string, int>> word;
	string expr;  // 算术表达式
	int idx;      // word下标
	int kind;      // 单词种别编码
	int err;      // 错误
	int word_analysis(vector<pair<string, int>>&, const string);
	void Next();
	void next_bracket();
	void next_add_sub();
	void next_mul_div();
	bool Right;   // 保存表达式test结果

private:
	int prior(int);        // 获取运算符的优先级
	bool isOperator(int);  // 通过 种别编码 判定是否是运算符
	vector<pair<string, int>> getPostfix(const vector<pair<string, int>>&);  // 中缀转后缀
	void popTwoNumbers(stack<double>&, double&, double&);  // 从栈中连续弹出两个操作数
	double stringToDouble(const string&);  // 把string转换为double
	double expCalculate(const vector<pair<string, int>>&);  // 计算后缀表达式的值
};