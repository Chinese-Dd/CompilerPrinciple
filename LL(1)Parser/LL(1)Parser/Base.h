#ifndef _Base_H_
#define _Base_H_
#include<iostream>
#include<set>
#include<cstring>
#include<string>
#include<vector>
#include<iomanip>


using namespace std;
#define Limit  100

struct Production  //�������ʽ���ݽṹ
{
	char left;
	string right;
};

class Base
{
protected:
	int Num=0;
	Production  Analysis[Limit];                  //����ʽ
	vector<char> Terminal;           //�ս����
	vector<char> Not_Terminal;  //���ս����
	set<char> First_Set[Limit];            //First��
	set<char> Follow_Set[Limit];      //Follow��

public:
   void	init();//������Ĳ���ʽ��ʼ��,ȥ��  -��>
   bool is_Not_Terminal(char c);
   void Get_First(char c);
   void Get_Follow(char c);
   int Get_Tindex(char c);
   int Get_Nindex(char c);
   void Print_FirstAndFollow(); 

};

#endif