#include<string>
#include<fstream>//文件读写头文件声明
#include<iostream>
#include<iomanip>//这里面iomanip的作用:
                 //主要是对cin,cout之类的一些操纵运算子，比如setfill,setw,setbase,setprecision等等。它是I/O流控制头文
                 //件,就像C里面的格式化输出一样.
                 //setw(2)表示输出的数占两位
                 
#define NUM1 128
#define NUM2 50
using namespace std;


 class CBook
 {
 public:
	 CBook(){};
	 CBook(char*cName,char*clsbn,char*cPrice,char*cAuthor);
	 ~CBook(){}
	 char*GetName();//获取图书名称
	 void SetName(char*cName);//设置图书名称
	 char*Getlsbn();//获取图书编号
	 void Setlsbn(char*clsbn);//设置图书编号
	 char*GetPrice();//获取图书价格
	 void SetPrice(char*cPrice);//设置图书价格
	 char*GetAuthor();//获取作者
	 void SetAuthor(char*cAuthor);//设置作者
	 void WriteData();//将图书对象写入到文件中
	 void DeleteData(int iCount);//从文件中删除
	 void GetBookFromFile(int iCount);//从文件中读取图书对象
 protected:
	 char m_cName[NUM1];//数据成员，图书属性
	 char m_clsbn[NUM1];
	 char m_cPrice[NUM2];
	 char m_cAuthor[NUM2];
 };
 CBook::CBook(char*cName,char*clsbn,char*cPrice,char*cAuthor)
{
	strncpy(m_cName,cName,NUM1);
    strncpy(m_clsbn,clsbn,NUM1);
	strncpy(m_cPrice,cPrice,NUM2);
	strncpy(m_cAuthor,cAuthor,NUM2);

}
char*CBook::GetName()
{
	return m_cName;
}
void CBook::SetName(char*cName)
{
	strncpy(m_cName,cName,NUM1);
}
char*CBook::Getlsbn()
{return m_clsbn;
}
void CBook::Setlsbn(char*clsbn)
{
strncpy(m_clsbn,clsbn,NUM1);
}
char*CBook::GetPrice()
{return m_cPrice;
}
void CBook::SetPrice(char*cPrice)
{strncpy(m_cPrice,cPrice,NUM2);
}
char*CBook::GetAuthor()
{return m_cAuthor;
}
void CBook::SetAuthor(char*cAuthor)
{strncpy(m_cAuthor,cAuthor,NUM2);
}
//WriteData,GetBookFromFile和DeleteData是类对象读写文件的函数，相当于操作数据库的接口
void CBook::WriteData()
{ofstream ofile;//定义输出文件流对象ofile
ofile.open("book.dat",ios::binary|ios::app);//打开一个能将数据输入文件尾部的二进制文件
try{                      //异常处理
ofile.write(m_cName,NUM1);//向磁盘文件输出图书信息
ofile.write(m_clsbn,NUM1);
ofile.write(m_cPrice,NUM2);
ofile.write(m_cAuthor,NUM2);
}
catch(...)
{
	throw "file error occurred";
	ofile.close();
}
ofile.close();
}
//成员函数GetBookFromFile能够实现从文件中读取数据来构建对象。
void CBook::GetBookFromFile(int iCount)
{char cName[NUM1];
char clsbn[NUM1];
char cPrice[NUM2];
char cAuthor[NUM2];
ifstream ifile;//建立输入文件流对象ifile
ifile.open("book.dat",ios::binary);//打开文件book.dat
try
{ifile.seekg(iCount*(NUM1+NUM1+NUM2+NUM2),ios::beg);//以从文件开头计算要移动的字节数为基准移动iCount*（NUM1+NUM1+NUM2+NUM2）
ifile.read(cName,NUM1);//读取图书信息
if(ifile.tellg()>0)//tellg（）返回输出文件读指针的当前位置
strncpy(m_cName,cName,NUM1);
ifile.read(clsbn,NUM1);
if(ifile.tellg()>0)
strncpy(m_clsbn,clsbn,NUM1);
ifile.read(cPrice,NUM2);
if(ifile.tellg()>0)
   strncpy(m_clsbn,clsbn,NUM2);
ifile.read(cAuthor,NUM2);
if(ifile.tellg()>0)
strncpy(m_cAuthor,cAuthor,NUM2);
}
catch(...)
{
	throw "file error occurred";
	ifile.close();
}
ifile.close();
}
//成员函数DeleteData负责将图书信息从文件里删除。
void CBook::DeleteData(int iCount)
{

	long respos;
	int iDataCount=0;
	fstream file;//建立输入输出文件流对象file,tmpfile
	fstream tmpfile;
	ofstream ofile;//输出文件流对象ofile
	char cTempBuf[NUM1+NUM1+NUM2+NUM2];
	file.open("book.dat",ios::binary|ios::out);//打开文本文件，以便进行输出操作
	tmpfile.open("temp.dat",ios::binary|ios::in|ios::out|ios::trunc);//打开（新建文件）temp.dat，若已存在则删除全部数据不存在建立此文件
	file.seekg(0,ios::end);//文件末尾
	respos=file.tellg();//返回输入文件读指针的当前位置
	iDataCount=respos/(NUM1+NUM1+NUM2+NUM2);
	if(iCount<0&&iCount>iDataCount)
	{
		throw"input number error";
	}
	else
	{
		file.seekg((iCount)*(NUM1+NUM1+NUM2+NUM2),ios::beg);//从文件开头移动位移量
		for(int j=0;j<(iDataCount-iCount);j++)
		{
			memset(cTempBuf,0,NUM1+NUM1+NUM2+NUM2);//把前NUM1+....项置为0
			file.read(cTempBuf,NUM1+NUM1+NUM2+NUM2);
			tmpfile.write(cTempBuf,NUM1+NUM1+NUM2+NUM2);
		}
		file.close();
		tmpfile.seekg(0,ios::beg);
		ofile.open("book.dat");
		ofile.seekp((iCount-1)*(NUM1+NUM1+NUM2+NUM2),ios::beg);
		for(int i=0;i<(iDataCount-iCount);i++)
		{
			memset(cTempBuf,0,NUM1+NUM1+NUM2+NUM2);
			tmpfile.read(cTempBuf,NUM1+NUM1+NUM2+NUM2);
			ofile.write(cTempBuf,NUM1+NUM1+NUM2+NUM2);

		}

		}
	tmpfile.close();
	ofile.close();
	remove("temp.dat");
}
