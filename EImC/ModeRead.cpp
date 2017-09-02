#include "ModeRead.h"

ModeRead::ModeRead()//��ʼ��
{
	file = NULL;
	lastch = '\0';
	memset(filePathName, '\0', sizeof(filePathName));
}

char ModeRead::scan() {      //��ȡ�ַ�
	if (readType == 1)
	{
		if (readPos + 1<in_content.size())
		{
			++readPos;
			return in_content[readPos];
		}
		else return -1;
	}
	if (readType == 2)
	{
		if (!file) {      //û���ļ�
			return -1;
		}
		if (readPos == lineLen - 1) {     //��������ȡ���
			lineLen = fread(line, 1, BUFLEN, file);  //���¼��ػ���������
			if (lineLen == 0) {     //û��������
				lineLen = 1;      //���ݳ���Ϊ1
				line[0] = -1;     //�ļ��������
			}
			readPos = -1;     //�ָ���ȡλ��
		}
		readPos++;      //�ƶ���ȡ��
		char ch = line[readPos];  //��ȡ�µ��ַ�
		if (lastch == '\n') {   //����
			lineNum++;  //�к��ۼ�
			colNum = 0;//�к����
		}
		if (ch == -1) { //�ļ������Զ��ر�
			fclose(file);
			file = NULL;
		}
		else if (ch == '\n') colNum++;     //���ǻ��У��кŵ���
		lastch = ch;      //��¼��һ���ַ�
		return ch;      //�����ַ�
	}
}

int ModeRead::readMode()
{
	cout << "��ѡ���ļ����뷽ʽ��" << endl;
	cout << "1.ֱ������  2.���ļ�" << endl;
	cin >> readType;
	if (readType == 1)//ֱ������
	{
		char in_char;
		getchar();
		while (scanf("%c", &in_char) != EOF)
		{
			in_content.push_back(in_char);
		}
		//output();
		return 0;
	}
	else if (readType == 2)//�ļ�����
	{
		cout << "�������ļ�·��" << endl;
		cin >> filePathName;
		file = fopen(filePathName, "r");
		if (!file)
		{
			cout << "�Ҳ������ļ�" << endl;
			return -1;
		}
		else
		{
			string line;
			ifstream in_file(filePathName);
			while (getline(in_file, line))
			{
				cout << line << endl;
			}
			return 0;
		}
	}
}

/*�鿴in_content������ݣ����ֶ����룩
void ModeRead::output()
{
int m=0;
while(m<in_content.size())
{
cout<<in_content[m];
m++;
}
}
*/
/*
int main()
{
    ModeRead a;
    int m=a.readMode();
    for(int i=0;i<5;i++) cout<<a.scan()<<endl;
    if(m==-1) {
        cout<<"����"<<endl;
        return -1;
    }
    return 0;
}
*/
