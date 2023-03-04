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
	bool test();         // �ⲿ�ӿڣ��жϱ��ʽ�Ƿ�Ϸ�
	double calculate();  // �ⲿ�ӿڣ�������ʽ��ֵ 

private:
	vector<pair<string, int>> word;
	string expr;  // �������ʽ
	int idx;      // word�±�
	int kind;      // �����ֱ����
	int err;      // ����
	int word_analysis(vector<pair<string, int>>&, const string);
	void Next();
	void next_bracket();
	void next_add_sub();
	void next_mul_div();
	bool Right;   // ������ʽtest���

private:
	int prior(int);        // ��ȡ����������ȼ�
	bool isOperator(int);  // ͨ�� �ֱ���� �ж��Ƿ��������
	vector<pair<string, int>> getPostfix(const vector<pair<string, int>>&);  // ��׺ת��׺
	void popTwoNumbers(stack<double>&, double&, double&);  // ��ջ��������������������
	double stringToDouble(const string&);  // ��stringת��Ϊdouble
	double expCalculate(const vector<pair<string, int>>&);  // �����׺���ʽ��ֵ
};