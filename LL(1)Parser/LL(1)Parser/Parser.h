#ifndef _Parser_H_
#define _Parser_H_
#include "Base.h"

class Parser:public Base
{
	int Analysis_Table[Limit][Limit];
	vector<char> Left_Analysis_Str;//���������ַ���
	vector<char> S;//����ջ,��vectorģ��stack.���������������

public:
	void Get_Table();
	void Print_Table();
	void Analysis_Program(string s);

};
#endif