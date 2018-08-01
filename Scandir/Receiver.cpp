#include "Receiver.h"
#include "Pattern.h"
#include <iostream>

using namespace std;

void Receiver::menu()
{
	cout << "输入1可查看任意不同目录" << endl;
	cout << "输入2进入日志模式" << endl;
	cout << "输入3进入差异模式" << endl;
	cout << "输入0退出" << endl;
}

void Receiver::select()
{
	menu();

	int tempInt;

	Pattern *p = Pattern::getInstance();
	while (cin >> tempInt)
	{
		getchar();
		switch (tempInt)
		{
		case 0:
			return;
		case 1:
			p->show();
			break;
		case 2:
			p->logPattern();
			break;
		case 3:
			p->difPattern();
			break;
		default:
			cout << "请输入正确的数字！" << endl;
			break;
		}
		menu();
	}
}
