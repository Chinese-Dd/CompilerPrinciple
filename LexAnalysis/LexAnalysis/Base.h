#ifndef _Base_H_
#define _Base_H_
#include<cstdio>
#include<cstdlib>
#include<cstring>

#define MaxLen 100
//ȫ�ֱ������ؼ��ֱ�,
//state��ֵ��Ӧ�ؼ���,��1��35
extern char KeyWord[35][20];

 //���޷���
 //state��ֵ��Ӧ�ؼ���,��36��72
extern char OperatorOrDelimiter[37][10];
class Base
{
   public:
	   bool is_Digtal(char);  //�ַ��Ƿ�������	
	   bool is_Characters(char);//�ַ��Ƿ��Ǵ�Сд��ĸ
	   bool is_SingleOperatorOrDelimiter(char);//�ַ��Ƿ���  ����Ϊ1�Ľ��޷�
	   int SearchKeyWord(char [][20],char []);
};
#endif