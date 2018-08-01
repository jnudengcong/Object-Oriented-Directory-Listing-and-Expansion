#include "Receiver.h"
#include "Pattern.h"
#include <iostream>

using namespace std;

void Receiver::menu()
{
	cout << "����1�ɲ鿴���ⲻͬĿ¼" << endl;
	cout << "����2������־ģʽ" << endl;
	cout << "����3�������ģʽ" << endl;
	cout << "����0�˳�" << endl;
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
			cout << "��������ȷ�����֣�" << endl;
			break;
		}
		menu();
	}
}
