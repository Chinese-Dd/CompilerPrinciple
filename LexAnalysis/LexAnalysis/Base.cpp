#include "Base.h"

char KeyWord[35][20] = {     //ʹ��const,�޸ĺ�����������
	"auto", "break", "case", "char", "const", "continue",
	"default", "do", "double", "else", "enum", "extern",
	"float", "for", "goto", "if", "int", "long", "register",
	"return", "short", "signed", "sizeof", "static", "struct",
	"switch", "true", "false", "typedef", "union", "signed",
	"unsigned", "void", "volatile", "while" };

char OperatorOrDelimiter[37][10] = {
	"+", "-", "*", "/", "<", "<=", ">", ">=", "=", "==",    //    \\    ����һ����б���ַ�''\'
	"!=", ";", "(", ")", "^", ",", "\"", "\'", "#", "&",          //     \'    ����һ�������ţ�Ʋ�ţ��ַ�
	"&&", "|", "||", "%", "~", "<<", ">>", "[", "]", "{",   //     \"   ����һ��˫�����ַ�
	"}", "\\", ".", "\?", ":", "!" };


bool Base::is_Digtal(char c)
{
	if (c >= '0'&&c <= '9')
		return true;
	else
		  return false;
}

bool Base::is_Characters(char c)
{
	if ((c >= 'a'&&c <= 'z') || (c >= 'A'&&c <= 'Z')||c=='_')
		return true;
	else
		return	false;
}

bool Base::is_SingleOperatorOrDelimiter(char c)
{
	if (c == '+' || c == '-' || c == '*' || c == '/' || c == ';' || c == '(' || c == ')' || c == '^' ||
		c == ',' || c == '\"' || c == '\'' || c == '~' || c == '#' || c == '%' || c == '[' || c == ']'
		|| c == '{' || c == '}' || c == '\\' || c == '.' || c == '\?' || c == ':'||c=='$')
		return true;
	else
		return false;
}

int Base::SearchKeyWord(char KeyWord[][20],char token[])
{
	for (int i = 0; i < 35; i++)
	{
		if (strcmp(KeyWord[i], token) == 0)
			return i + 1;		
	}
	return -1;
	
}