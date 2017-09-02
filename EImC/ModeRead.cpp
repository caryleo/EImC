#include "ModeRead.h"

ModeRead::ModeRead()//初始化
{
	file = NULL;
	lastch = '\0';
	memset(filePathName, '\0', sizeof(filePathName));
}

char ModeRead::scan() {      //读取字符
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
		if (!file) {      //没有文件
			return -1;
		}
		if (readPos == lineLen - 1) {     //缓冲区读取完毕
			lineLen = fread(line, 1, BUFLEN, file);  //重新加载缓冲区数据
			if (lineLen == 0) {     //没有数据了
				lineLen = 1;      //数据长度为1
				line[0] = -1;     //文件结束标记
			}
			readPos = -1;     //恢复读取位置
		}
		readPos++;      //移动读取点
		char ch = line[readPos];  //获取新的字符
		if (lastch == '\n') {   //新行
			lineNum++;  //行号累加
			colNum = 0;//列号清空
		}
		if (ch == -1) { //文件结束自动关闭
			fclose(file);
			file = NULL;
		}
		else if (ch == '\n') colNum++;     //不是换行，列号递增
		lastch = ch;      //记录上一个字符
		return ch;      //返回字符
	}
}

int ModeRead::readMode()
{
	cout << "请选择文件输入方式：" << endl;
	cout << "1.直接输入  2.打开文件" << endl;
	cin >> readType;
	if (readType == 1)//直接输入
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
	else if (readType == 2)//文件输入
	{
		cout << "请输入文件路径" << endl;
		cin >> filePathName;
		file = fopen(filePathName, "r");
		if (!file)
		{
			cout << "找不到该文件" << endl;
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

/*查看in_content里的内容（即手动输入）
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
        cout<<"错误"<<endl;
        return -1;
    }
    return 0;
}
*/
