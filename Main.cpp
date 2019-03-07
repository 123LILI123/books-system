#include<iostream>
#include"Book.h"
#include<iomanip>
#include<stdlib.h>//system调用要用到的头文件
#include<conio.h>
#include<string.h>
#include<fstream>
#define CMD_COLS 80
#define CMD_LINES 25
using namespace std;
void SetScreenGrid()//设置屏幕显示的行数和列数
{
	char sysSetBuf[80];
	sprintf(sysSetBuf,"mode con cols=%d lines=%d",CMD_COLS,CMD_LINES);
		system(sysSetBuf);//?
}
void SetSysCaption()//设置窗体标题栏上
{
	system("title Sample");
}
void ClearScreen()//清除屏幕信息
{
	system("cls");

}
void SetSysCaption(const char*pText)
{
	char sysSetBuf[80];
	sprintf(sysSetBuf,"title %s",pText);
	system(sysSetBuf);
}
void ShowWelcome()//欢迎信息屏幕
{
	for(int i=0;i<7;i++)
	{
		cout<<endl;//空行使之尽量显示在正中间
	}
	cout<<setw(40);//setw(40)表示输出的数占40位
	cout<<"***********"<<endl;
	cout<<setw(40);
	cout<<"图书管理系统"<<endl;
	cout<<setw(40);
	cout<<"***********"<<endl;
}
void ShowRootMenu()//显示主菜单
{
	cout<<setw(40);
	cout<<"请选择功能"<<endl;
	cout<<endl;
	cout<<setw(38);
	cout<<"1 添加新书"<<endl;
	cout<<endl;
	cout<<setw(38);
	cout<<"2 浏览全部"<<endl;
	cout<<endl;
	cout<<setw(38);
	cout<<"3 删除图书"<<endl;
}
void WaitUser()
{
	int ilnputPage=0;
	cout<<"enter 返回主菜单 q退出"<<endl;
	char buf[256];
	gets(buf);//输入
	if(buf[0]=='q')
		system("exit");//退出系统
}
//main函数是程序的入口，主要调用了SetScreenGrid、SetSysCaption和mainloop主函数
int GetSelect()//主要负责用户在菜单中的选择
{
	char buf[256];
	gets(buf);
	return atoi(buf);
}
//添加新书模块
void GuideInput()
{
	char inName[NUM1];
	char inlsbn[NUM1];
	char inPrice[NUM2];
	char inAuthor[NUM2];
	cout<<"输入书名"<<endl;
	cin>>inName;
	cout<<"输入ISBN"<<endl;
	cin>>inlsbn;
	cout<<"输入价格"<<endl;
	cin>>inPrice;
	cout<<"输入作者"<<endl;
	cin>>inAuthor;
	CBook book(inName,inlsbn,inPrice,inAuthor);
    book.WriteData();
	cout<<"Write Finish"<<endl;
	WaitUser();
}
long GetFileLength(ifstream &ifs)
{
	long tmppos;
	long respos;
	tmppos=ifs.tellg();
	ifs.seekg(0,ios::end);
	respos=ifs.tellg();
	ifs.seekg(tmppos,ios::beg);
	return respos;
}
//浏览全部模板设计
void ViewData(int iSelPage=1)
{
	int iPage=0;
	int iCurPage=0;
	int iDataCount=0;
	char inName[NUM1];
	char inlsbn[NUM1];
	char price[NUM2];
	char inAuthor[NUM2];
	bool blndex=false;
	int iFileLength;
	iCurPage=iSelPage;
	ifstream ifile;
	ifile.open("book.dat",ios::binary);//
	iFileLength=GetFileLength(ifile);
iDataCount=iFileLength/(NUM1+NUM1+NUM2+NUM2);//根据文件长度，计算文件中总的记录数
if(iDataCount>=1)
blndex=true;
iPage=iDataCount/20+1;
ClearScreen();
cout<<"共有记录"<<iDataCount<<"";
cout<<"共有页数"<<iPage<<"";
cout<<"当前页数"<<iCurPage<<"";
cout<<"n显示下一页m返回"<<endl;
cout<<setw(5)<<"index";//setw(n) 设域宽为n个字符
//这个控制符的意思是保证输出宽度为n
cout<<setw(22)<<"Name"<<setw(22)<<"lsbn";
cout<<setw(15)<<"Price"<<setw(15)<<"Author";
cout<<endl;
try{
	//根据图书记录编号查找在文件中的位置
	ifile.seekg((iCurPage-1)*20*(NUM1+NUM1+NUM2+NUM2),ios::beg);
	if(!ifile.fail())
	{
		for(int i=1;i<21;i++)
		{
           memset(inName,0,128);
		   memset(inlsbn,0,128);
		   memset(price,0,50);
		   memset(inAuthor,0,50);
		   if(blndex)
			   cout<<setw(3)<<((iCurPage-1)*20+i);
		   ifile.read(inName,NUM1);
		   cout<<setw(24)<<inName;
		   ifile.read(inlsbn,NUM1);
		   cout<<setw(24)<<inName;
		   ifile.read(price,NUM2);
		   cout<<setw(12)<<price;
		   ifile.read(inAuthor,NUM2);
		   cout<<setw(12)<<inAuthor;
		   cout<<endl;
		   if(ifile.tellg()<0)
			   blndex=false;
		   else
			   blndex=true;
		}
	}
}
catch(...)
{
	cout<<"throw file exception"<<endl;
	throw "file error occurred";
	ifile.close();
}
if(iCurPage<iPage)
{
	iCurPage=iCurPage+1;
	WaitUser();//WaitView(iCurPage);
}
else
{
	WaitUser();//WaitView(iCurPage);

}
ifile.close();

}
//删除图书模块
void DeleteBookFromFile()
{
	int iDelCount;
	cout<<"input delete index"<<endl;
	cin>>iDelCount;
	CBook tmpbook;
	tmpbook.DeleteData(iDelCount);
	cout<<"Delete Finish"<<endl;
	WaitUser();
} 
int main()//主循环
{
	ShowWelcome();
	while(1)
	{
		ClearScreen();
		ShowWelcome();
		ShowRootMenu();
		switch(GetSelect())
		{
case 1:
		ClearScreen();
		GuideInput();//添加新书
		break;
case 2:
		ClearScreen();
		ViewData();//浏览全部
		break;
case 3:
		ClearScreen();
		DeleteBookFromFile();//删除图书
		break;
		}
	}
	return 0;
}

