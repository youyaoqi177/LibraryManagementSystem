#define _CRT_SECURE_NO_WARNINGS
#include "Book.h"
#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <string.h>
#include <conio.h>
#include <fstream>

#define CMD_COLS 80
#define CMD_LINES 25
using namespace std;

void SetScreenGrid();
void ClearScreen();
void SetSysCaption();
void SetSysCaption(const char *pText);
void ShowWelcome();
void ShowRootMenu();
void WaitView(int  iCurPage);
void WaitUser();
void GuideInput();
int GetSelect();
long GetFileLength(ifstream & ifs);
void ViewData(int iSelPage);
void DeleteBookFromFile();
void mainloop();

//ͨ��mode����������ʾ��Ϣ����������������ɫ��
void SetScreenGrid()
{
	char sysSetBuf[80];
	sprintf(sysSetBuf, "mode con cols=%d line=%d", CMD_COLS, CMD_LINES);
	system(sysSetBuf);
}
//ͨ��title�������ñ���������ʾ��Ϣ
void SetSysCaption()
{
	system("title sample");
}
//�ڱ���������ʾָ���ַ�
void SetSysCaption(const char * pText)
{
	char sysSetBuf[80];
	sprintf(sysSetBuf, "title %s", pText);
	system(sysSetBuf);
}
//ִ��cls��������Ļ��Ϣ�����
void ClearScreen()
{
	system("cls");
}
//��ʾ��ӭ����
void ShowWelcome()
{
	for (int i = 0;i < 7;i++)
	{
		cout << endl;
	}
	cout << setw(40);
	cout << "******************" << endl;
	cout << setw(40);
	cout << "ͼ�����ϵͳ" << endl;
	cout << setw(40);
	cout << "*********************" << endl;
	
}
//��ʾ���˵�
void ShowRootMenu()
{
	cout << setw(40);
	cout << "��ѡ����" << endl;
	cout << endl;
	cout << setw(38);
	cout << "1 �������" << endl;
	cout << endl;
	cout << setw(38);
	cout << "2 ���ȫ��" << endl;
	cout << endl;
	cout << setw(38);
	cout << "3 ɾ��ͼ��" << endl;

}
//ѡ��˵�
void WaitUser()
{
	int iInputPage = 0;
	cout << "enter:�������˵� q�˳�" << endl;
	char buf[256];
	gets_s(buf);
	if (buf[0] == 'q')
	{
		system("exit");
	}
}
//��ȡ�û��ڲ˵��е�ѡ��
int GetSelect()
{
	char buf[256];
	gets_s(buf);
	return atoi(buf);
}
//���ͼ��
void GuideInput()
{
	char inName[NUM1];
	char inIsbn[NUM1];
	char inPrice[NUM2];
	char inAuthor[NUM2];
	cout << "����������" << endl;
	cin >> inName;
	cout << "����ISBN��" << endl;
	cin >> inIsbn;
	cout << "����۸�" << endl;
	cin >> inPrice;
	cout << "�������ߣ�" << endl;
	cin >> inAuthor;
	CBook book(inName, inIsbn, inPrice, inAuthor);
	book.WriterData();
	cout << "write finish" << endl;
	WaitUser();
}
long GetFileLength(ifstream& ifs)
{
	long tmppos;
	long respos;
	tmppos = ifs.tellg();
	ifs.seekg(0, ios::end);
	respos = ifs.tellg();
	ifs.seekg(tmppos, ios::beg);
	return respos;
}
//���ȫ��ģ��
void ViewData(int iSelPage = 1)
{
	int iPage = 0;
	int iCurPage = 0;
	int iDataCount = 0;
	char inName[NUM1];
	char inIsbn[NUM1];
	char inPrice[NUM2];
	char inAuthor[NUM2];
	bool bIndex = false;
	int iFileLength;
	iCurPage = iSelPage;
	ifstream ifile;
	ifile.open("book.dat", ios::binary);
	iFileLength = GetFileLength(ifile);
	iDataCount = iFileLength / (NUM1 + NUM1 + NUM2 + NUM2);
	if (iDataCount >= 1)
	{
		bIndex = true;
	}
	iPage = iDataCount / 20 + 1;
	ClearScreen();
	cout << "���м�¼" << iDataCount << " ";
	cout << "����ҳ��" << iPage << " ";
	cout << "��ǰҳ��" << iCurPage << " ";
	cout << "n ��ʾ��һҳ m ����" << endl;
	cout << setw(5) << "index";
	cout << setw(22) << "name" << setw(22) << "isbn";
	cout << setw(15) << "price" << setw(15) << "author";
	cout << endl;

	try
	{
		ifile.seekg((iCurPage - 1) * 20 * (NUM1 + NUM1 + NUM2 + NUM2), ios::beg);
		if (!ifile.fail())
		{
			for (int i = 1;i < 21;i++)
			{
				memset(inName, 0, 128);
				memset(inIsbn, 0, 128);
				memset(inPrice, 0, 50);
				memset(inAuthor, 0, 50);
				if (bIndex)
				{
					cout << setw(3) << ((iCurPage - 1) * 20 + i);
				}
				ifile.read(inName, NUM1);
				cout << setw(24) << inName;
				ifile.read(inIsbn, NUM1);
				cout << setw(24) << inIsbn;
				ifile.read(inPrice, NUM2);
				cout << setw(12) << inPrice;
				ifile.read(inAuthor, NUM2);
				cout << setw(12) << inAuthor;
				cout << endl;
				if (ifile.tellg() < 0)
				{
					bIndex = false;
				}
				else
				{
					bIndex = true;
				}
			}
		}

	}
	catch (...)
	{
		cout << "throw file exception" << endl;
		throw "file error occurred";
		ifile.close();
	}
	if (iCurPage < iPage)
	{
		iCurPage += 1;
		WaitView(iCurPage);
	}
	else
	{
		WaitView(iCurPage);
	}
	ifile.close();

}

//ģ�����ִ��
void mainloop()
{
	ShowWelcome();
	while (1)
	{
		ClearScreen();
		ShowWelcome();
		ShowRootMenu();
		switch (GetSelect())
		{
		case 1:
			ClearScreen();
			GuideInput();
			break;
		case 2:
			ClearScreen();
			ViewData();
			break;
		case 3:
			ClearScreen();
			DeleteBookFromFile();
			break;
		}
	}
}

void WaitView(int iCurPage)
{
	char buf[256];
	gets_s(buf);
	if (buf[0] == 'q')
	{
		system("exit");

	}
	if (buf[0] == 'm')
	{
		mainloop();
	}
	if (buf[0] == 'n')
	{
		ViewData(iCurPage);
	}

}




//ɾ��ͼ��ģ��
void DeleteBookFromFile()
{
	int iDelCount;
	cout << "input delete indes" << endl;
	cin >> iDelCount;
	CBook tmpBook;
	tmpBook.DeleteData(iDelCount);
	cout << "delete finish" << endl;
	WaitUser();
}






void  main()//�������
{
	SetScreenGrid();
	SetSysCaption("ͼ�����ϵͳ");
	mainloop();

}