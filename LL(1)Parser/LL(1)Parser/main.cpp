#include "Parser.h"

int main()
{
	Parser parser;
	parser.init();
	parser.Print_FirstAndFollow();//���First����Follow��
	parser.Get_Table();
	cout << "����������ַ���:"<<endl;
	cout << setw(15)<< "����ջ" << setw(15) << "ʣ�����봮" << setw(15) << "����ʽ" << endl;
	string str;
	cin >> str;
	parser.Analysis_Program(str);
	return 0;
}