#ifndef _LEX_H_
#define _LEX_H_
#include "Base.h"

class Lex:public Base
{
          public:
			  FILE *fin;
			  FILE *fout;
			  Lex();
			  ~Lex();
			  char BufferCode[10000];    // �����洢����Ĵ���
			  int pos = 0;                 
			  void init(); //��ʼ�������뿽���� BufferCode������
			  void filter();//����BufferCode�еĴ���,ȥ��//��/*  */�����ݣ��Լ�һЩ���õġ�Ӱ�����ִ�еķ����绻�з����س������Ʊ���ȵ�
			  void Scanner(int &,int &,char[]);//ɨ��BufferCode,���Ĵ���,ʵ����ȷ�������Զ�����ĳЩ����		  

};
#endif