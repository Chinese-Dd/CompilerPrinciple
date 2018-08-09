#include"Base.h"
void Base::init()
{
	cout << "����Ĳ���ʽ�ĸ�����" << endl;
	freopen("in.txt", "r", stdin);
	cin >> Num;
	string s;
	//����һ����ʱ���ս������ս��set��,���ڴ洢���ظ�Ԫ��
	set<char> Temp_Terminal;
	set<char> Temp_Not_Terminal;
	for (int i = 0; i < Num; i++)
	{
		cin >> s;
		int len = s.length();
		for (int j = 0; j < len; j++)
		{
			if (s[j] == '-' || s[j] == '>' || s[j] == ' ')//�Ƿ�����ֱ������
				continue;
			if (j == 0)  //��ʼ������ʽ
				Analysis[i].left = s[0];
			else
				Analysis[i].right += s[j];

			if (is_Not_Terminal(s[j]))  //��ʼ���ս��������ս��
				Temp_Not_Terminal.insert(s[j]);
			else
				Temp_Terminal.insert(s[j]);
		}
	}


	//�ٽ�set��Ԫ�ش洢��vector����
	for (set<char>::iterator it = Temp_Terminal.begin(); it != Temp_Terminal.end(); it++)//�������е��õ��ǿ��ս����,���Խ��ռ��ų�
	{
		if (*it != '$')
		Terminal.push_back(*it);
	}

	for (set<char>::iterator it = Temp_Not_Terminal.begin(); it != Temp_Not_Terminal.end(); it++)
		Not_Terminal.push_back(*it);

	Terminal.push_back('#');
	cout << "��ʼ������ʽ��:" << endl;
	cout << "��" << setw(10) << "�Ҳ�" << endl;
	for (int i = 0; i < Num; i++)
		cout << Analysis[i].left << setw(12) << Analysis[i].right << endl;

	cout << "�ս����:" << endl;
	for (int i = 0; i < Terminal.size(); i++)
		cout << Terminal[i] << " ";
	cout << endl;

	cout << "���ս����:" << endl;
	for (int i = 0; i < Not_Terminal.size(); i++)
		cout << Not_Terminal[i] << " ";
	cout << endl;



	for (int i = 0; i < Not_Terminal.size(); i++)
	{
		if (First_Set[i].empty())
			Get_First(Not_Terminal[i]);
	}

	for (int i = 0; i < Not_Terminal.size(); i++)
	{
		if (i == 0)
		{
			Follow_Set[0].insert('#');
			continue;
		}
		Get_Follow(Not_Terminal[i]);
	}
	return;
}

bool Base::is_Not_Terminal(char c)
{
	if (c >= 'A'&&c <= 'Z')
		return 1;
	return 0;
}

int Base::Get_Nindex(char Target)
{
	for (int i = 0; i < Not_Terminal.size(); i++)
	if (Not_Terminal[i] == Target)
		return i;
}

int Base::Get_Tindex(char Target)
{
	for (int i = 0; i < Terminal.size(); i++)
	if (Terminal[i] == Target)
		return i;
}

void Base::Get_First(char Target)
{
	for (int i = 0; i < Num; i++)
	{
		int temp = 0;//���ڼ�¼ÿ������ʽ�Ҳ�$�ĸ���
		if (Analysis[i].left == Target)
		{
			for (int j = 0; j < Analysis[i].right.length(); j++)
			{
				if (!is_Not_Terminal(Analysis[i].right[j])) //������ս��
				{
					First_Set[Get_Nindex(Target)].insert(Analysis[i].right[j]);
					break;
				}
				//����Ƿ��ս��
				int flag = -1;
				Get_First(Analysis[i].right[j]);
				for (set<char>::iterator it = First_Set[Get_Nindex(Analysis[i].right[j])].begin(); it != First_Set[Get_Nindex(Analysis[i].right[j])].end(); it++)
				{
					if (*it == '$')
						flag = 1;
					else
						First_Set[Get_Nindex(Target)].insert(*it);
				}
				if (flag == 1)  //������ֿռ�
					temp++;
				else
					break;
				if (temp == Analysis[i].right.length()) //���Ѿ��������ʽ�����Ҳ��ķ��ս��,��$�����󲿵�first��
					First_Set[Get_Nindex(Target)].insert('$');

			}
		}
	}

	return;
}

void Base::Get_Follow(char Target)
{
	for (int i = 0; i < Num; i++)
	{
		if (Target == Analysis[i].left)   //target������ͬʱ
			continue;
		int pos = -1;   //����ʽ�Ҳ���pos
		int target_pos = -1; //���ս��pos
		int len = Analysis[i].right.length();
		for (int j = 0; j < len; j++)
		{
			if (Analysis[i].right[j] == Target)
			{
				target_pos = j;
				pos = j;
				break;
			}
		}

		if (target_pos == -1)//���Ҳ�û�ҵ�targetʱ
			continue;

		//cout << "targetΪ" << target << "ĿǰΪ��" << i << "������ʽ" << endl;

		if (target_pos == len - 1) //�α�P60,���3ǰ��һ��
		{
			//	cout << "���3ǰ��һ��" << endl;
			Get_Follow(Analysis[i].left);
			for (set<char>::iterator it = Follow_Set[Get_Nindex(Analysis[i].left)].begin(); it != Follow_Set[Get_Nindex(Analysis[i].left)].end(); it++)
				Follow_Set[Get_Nindex(Target)].insert(*it);
		}

		int isHasEmpty = 1;//����Ƿ��пռ�,�еĻ��ͼ���ɨ����һ��,�����ж�
		while (pos + 1 < len&&isHasEmpty)
		{
			isHasEmpty = 0;
			pos++;
			char nxt = Analysis[i].right[pos];
			if (!is_Not_Terminal(nxt))  //������ս��,ֱ�Ӽ���,//�α�P60,���1
			{
				Follow_Set[Get_Nindex(Target)].insert(nxt);
				break;
			}
			else
			{
				for (set<char>::iterator it = First_Set[Get_Nindex(nxt)].begin(); it != First_Set[Get_Nindex(nxt)].end(); it++)//�α�P60,���2
				{
					//			cout << "���2ǰ��һ��" << endl;
					if (*it == '$')
						isHasEmpty = 1;
					else
						Follow_Set[Get_Nindex(Target)].insert(*it);
				}

				if (pos - target_pos == 1 && isHasEmpty&&pos == len - 1) //���3����һ��	
				{
					//			cout << "���3����һ��" << endl;
					Get_Follow(Analysis[i].left);
					for (set<char>::iterator it = Follow_Set[Get_Nindex(Analysis[i].left)].begin(); it != Follow_Set[Get_Nindex(Analysis[i].left)].end(); it++)
						Follow_Set[Get_Nindex(Target)].insert(*it);
				}
			}
		}

	}
	return;
}

void Base::Print_FirstAndFollow()
{
	cout << "First����:" << endl;
	for (int i = 0; i < Not_Terminal.size(); i++)
	{
		cout << Not_Terminal[i] << ": ";
		for (set<char>::iterator it = First_Set[i].begin(); it != First_Set[i].end(); it++)
			cout << *it << " ";
		cout << endl;
	}

	cout << "FOLLOW����" << endl;
	for (int i = 0; i<Not_Terminal.size(); i++)
	{
		cout << Not_Terminal[i] << ": ";
		for (set<char>::iterator it = Follow_Set[i].begin(); it != Follow_Set[i].end(); it++)
			cout << *it << "  ";
		cout << endl;
	}

	return;
}
