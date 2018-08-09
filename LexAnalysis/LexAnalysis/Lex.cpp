#include "Lex.h"
#include<cstring>

Lex::Lex()
{
	fin = fopen("Test_In.txt", "r"); //fopen�ɹ����򷵻�һ��FILE*ָ��,���򷵻�NULL
	fout = fopen("Test_Out.txt", "w");
}

Lex::~Lex()
{
	fclose(fin);
	fclose(fout);
}

void Lex::init()
{
	if (fin == NULL)
	{
		printf("��Test_In�ļ�ʧ��\n");
		exit(0);
	}

	BufferCode[pos] = fgetc(fin);
	while (BufferCode[pos] != EOF)
	{
		pos++;
		BufferCode[pos] = fgetc(fin);
	}
	BufferCode[pos] = '\0';
}

void Lex::filter()
{
	char TempCode[10000];
	int count = 0;

	for (int i = 0; i <= pos; i++)
	{
		if (BufferCode[i] == '/'&&BufferCode[i+ 1] == '/')
		{
			while (BufferCode[i] != '\n')
				i++;
		}

		if (BufferCode[i] == '/'&&BufferCode[i + 1] == '*')
		{
			i += 2;
			while (BufferCode[i] != '*' || BufferCode[i + 1] != '/')
			{
				i++;
				if (BufferCode[i] ==EOF)
				{
					printf("����ʧ��!ע�ͷ�����!\n");
					exit(0);
				}
			}
			i += 2;
		}

			if (BufferCode[i] != '\n'&&BufferCode[i] != '\r'&&BufferCode[i] != '\t'&&BufferCode[i] != '\v')
				TempCode[count++] = BufferCode[i];		
		}

	TempCode[count] = '\0';
	strcpy(BufferCode, TempCode);
	}

void Lex::Scanner(int &state, int &pos, char token[])//����state, lex.posΪ��������
{
	char temp = BufferCode[pos];
	for (int i = 0; i <MaxLen; i++) //ÿ��ɨ��ʱ��� �洢����token
		token[i]= '\0';
	int count = 0;

	while (temp == ' ')   //�ص�:�ո���Ҫ����,ɨ�赽�ո�ʱֱ������,ֱ�����ǿո�ͣ��
	{
		pos++;
		temp = BufferCode[pos];
	}

	if (is_Digtal(temp))//��ͷΪ����
	{
		while (is_Digtal(BufferCode[pos]))
		{
			token[count++] = BufferCode[pos];
			pos++;
		}
		token[count] = '\0';
		state =99;
		return;
	}
	else if (is_Characters(temp))//��ͷΪ��ĸ�����»���
	{
		while (is_Digtal(BufferCode[pos]) || is_Characters((BufferCode[pos])))
		{
			token[count++] = BufferCode[pos];
	//	printf("%c   %c    pos=%d   count=%d\n", token[count], BufferCode[pos], pos,count);
			pos++;	
		}	

		token[count] = '\0';	  //��β�����ϸ�'\0'
		state = SearchKeyWord(KeyWord, token);
		if (state == -1)  //�Ҳ�����Ӧ�Ķ�Ӧ������,˵�� tokenΪ��ʶ��
		{
			state = 100;
		}
		return;
	}
	else if (is_SingleOperatorOrDelimiter(temp))//��ͷΪ�Ƿ��ǳ���Ϊ1�Ľ��޷�
	{
		token[0] =temp;
		token[1] = '\0';

		for (int i = 0; i < 37; i++)
		{
			if (strcmp(token, OperatorOrDelimiter[i]) == 0)
			{
				state = i + 35;
				break;
			}
		}
		pos++;
		return;
	}
	else if (temp == '<')  //  ���Ϊ'<' ��ͷ,�п���Ϊ <,<=,<<
	{
		token[0] = '<';
		pos++;
		if (BufferCode[pos] == '=')
		{
			token[1] = '=';
			token[2] = '\0';
			pos++;
			state = 41;
			return;
		}
		else if (BufferCode[pos] == '<')
		{
			token[1] = '<';
			token[2] = '\0';
			pos++;
			state = 61;
			return;
		}
		token[1] = '\0';
		state = 40;
		return;
	}
	else if (temp == '>')//  ���Ϊ'<' ��ͷ,�п���Ϊ >,>=,>>
	{
		token[0] = '>';
		pos++;
		if (BufferCode[pos] == '=')
		{
			token[1] = '=';
			token[2] = '\0';
			pos++;
			state = 43;
			return;
		}
		else if (BufferCode[pos] == '>')
		{
			token[1] = '>';
			token[2] = '\0';
			pos++;
			state = 62;
			return;
		}
		token[1] = '\0';
		state = 42;
		return;
	}
	else if (BufferCode[pos] == '!')//  ���Ϊ'!' ��ͷ,�п���Ϊ!,!=
	{
		token[0] = '!';
		pos++;
		if (BufferCode[pos] == '=')
		{
			token[1] = '=';
			token[2] = '\0';
			pos++;
			state = 46;
			return;
		}
		token[1] = '\0';
		state = 71;
		return;
	}
	else if (BufferCode[pos] == '=')//  ���Ϊ'=' ��ͷ,�п���Ϊ=,==
	{
		token[0] = '=';
		pos++;
		if (BufferCode[pos] == '=')
		{
			token[1] = '=';
			token[2] = '\0';
			pos++;
			state = 45;
			return;
		}
		token[1] = '\0';
		state = 44;
		return;
	}
	else if (BufferCode[pos] == '|')//  ���Ϊ'\' ��ͷ,�п���Ϊ|,||
	{
		token[0] = '|';
		pos++;
		if (BufferCode[pos] == '|')
		{
			token[1] = '|';
			token[2] = '\0';
			pos++;
			state = 58;
			return;
		}
		token[1] = '\0';
		state = 57;
		return;

	}
	else if (BufferCode[pos] == '&')//  ���Ϊ'&' ��ͷ,�п���Ϊ&,&&
	{
		token[0] = '&';
		pos++;
		if (BufferCode[pos] == '&')
		{
			token[1] = '&';
			token[2] = '\0';
			pos++;
			state = 56;
			return;
		}
		token[1] = '\0';
		state = 55;
		return;
	}
	else if (BufferCode[pos] =='\0')
	{
		state = 0;
		 return;
	}	
	else
	{
		printf("%d�޷�ʶ����ַ�,���򼴽��˳�!\n", temp);
		exit(0);
	}

	return;
}

