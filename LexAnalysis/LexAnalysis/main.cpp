#include<iostream>
#include"Lex.h"
using namespace std;

int main()
{
	Lex lex;
	lex.init();  
	cout << "����ǰ�Ĵ���:" << endl;
	cout << lex.BufferCode<< endl;
	fprintf(lex.fout, "����ǰ�Ĵ���    %s\n", lex.BufferCode);
	lex.filter();
	cout << "���˺�ĵĴ���:" << endl;
	cout << lex.BufferCode <<endl; //����ַ�������"/0"��ͣ��
	fprintf(lex.fout, "���˺�Ĵ���    %s\n", lex.BufferCode);
	
	char token[MaxLen];//ÿ��ɨ����ַ�����token��
	int state =-1;//��ʼ�� �ֱ���
	lex.pos = 0;
	while (state != 0) //�ֱ��� Ϊ0ʱ˵��ɨ�赽�� EOF,���ļ�������־
	{

	//	printf("lex.pos=%d   %c\n", lex.pos, lex.BufferCode[lex.pos]);
		lex.Scanner(state,lex.pos,token); 
		if (state >= 1 && state <= 35)//�ֱ���Ϊ�ؼ���
		{
			fprintf(lex.fout, "�ؼ���    %s\n", token);
		}
		else if (state >= 36 && state <= 71)//�ֱ�����޷�
		{
			fprintf(lex.fout, "���޷�    %s\n", token);
		}
		else if (state == 99)//�ֱ���Ϊ����
		{
		   fprintf(lex.fout, "����    %s\n",token);
		}
		else if (state == 100)//�ֱ���Ϊ��ʶ��
		{
			fprintf(lex.fout, "��ʶ��    %s\n", token);
		}

	}

	return 0;
}