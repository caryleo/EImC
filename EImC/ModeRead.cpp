#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <fstream>
#include <string>
#define BUFLEN 80       //��������С
using namespace std;
class ModeRead
{
private:
    int readType;           //���뷽ʽ���ļ���ֱ������
    int lineLen=0;          //�������ڵ����ݳ���
    int readPos=-1;         //��ȡλ��
    char line[BUFLEN];      //������
    int lineNum=-1;         //�к�
    int colNum=0;           //�к�
    char lastch;         //��һ���ַ�
    FILE *file;         //�ļ�ָ��
    vector <char> in_content;//ֱ����������
    char filePathName[1024];//�ļ�·��
public:
    ModeRead();
    void readMode();//����ģ�����
    char scan();//��ȡ�ַ�
    //void output();
};

ModeRead::ModeRead()//��ʼ��
{
    file=NULL;
    lastch='\0';
    memset(filePathName,'\0',sizeof(filePathName));
}

char ModeRead::scan(){      //��ȡ�ַ�
    if(readType==1)
    {
        if(readPos+1<in_content.size())
        {
            ++readPos;
            return in_content[readPos];
        }
    }
    if(readType==2)
    {
        if(!file){      //û���ļ�
        return -1;
	}
	if(readPos==lineLen-1){     //��������ȡ���
        lineLen=fread(line,1,BUFLEN,file);  //���¼��ػ���������
        if(lineLen==0){     //û��������
            lineLen=1;      //���ݳ���Ϊ1
            line[0]=-1;     //�ļ��������
        }
        readPos=-1;     //�ָ���ȡλ��
	}
	readPos++;      //�ƶ���ȡ��
	char ch=line[readPos];  //��ȡ�µ��ַ�
	if(lastch=='\n'){   //����
        lineNum++;  //�к��ۼ�
        colNum=0;//�к����
	}
	if(ch==-1){ //�ļ������Զ��ر�
        fclose(file);
        file=NULL;
	}
	else if(ch=='\n') colNum++;     //���ǻ��У��кŵ���
	lastch=ch;      //��¼��һ���ַ�
	return ch;      //�����ַ�
    }
}

void ModeRead::readMode()
{
    cout<<"��ѡ���ļ����뷽ʽ��"<<endl;
    cout<<"1.ֱ������  2.���ļ�"<<endl;
    cin>>readType;
    if(readType==1)//ֱ������
    {
        char in_char;
        getchar();
        while(scanf("%c",&in_char)!=EOF)
        {
            in_content.push_back(in_char);
        }
        //output();
    }
    else if(readType==2)//�ļ�����
    {
        cout<<"�������ļ�·��"<<endl;
        cin>>filePathName;
        file=fopen(filePathName,"r");
        if(!file)
        {
            cout<<"�Ҳ������ļ�"<<endl;
            return;
        }
        else
        {
            string line;
            ifstream in_file(filePathName);
            while(getline(in_file,line))
            {
                cout<<line<<endl;
            }
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
    a.readMode();
    //for(int i=0;i<5;i++) cout<<a.scan()<<endl;
    return 0;
}
*/
