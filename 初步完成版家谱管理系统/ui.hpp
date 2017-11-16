#ifndef UI_HPP
#define UI_HPP value

#include <iostream>
#include <string>
using namespace std;


//�򿪳���Ľ��ܽ���
void introduction() {
	cout << "==========================================" << endl
		 << "             Genealogy System             " << endl
		 << "==========================================" << endl;
}


//���ܹ��ܶ�Ӧ������
void menu() {
	cout << "==========================================" << endl
		 << "                   MENU                   " << endl
		 << "------------------------------------------" << endl
		 << "'menu'/'m' -> View menu"					 << endl
		 << "'creat'/'c' -> Creat genealogy"			 << endl
		 << "'search'/'s' -> Search member" 			 << endl
		 << "'delete'/'d' -> Delete member"				 << endl
		 << "'add'/'ad' -> Add member"					 << endl
		 << "'amend'/'am' -> Amend member's information" << endl
		 << "'print'/'p' -> Print the genealogy"		 << endl
		 << "'quit'/'q' -> Quit Genealogy System"		 << endl
		 << "==========================================" << endl 
		 << endl;
}

//���û����õ����������ı�ope��ֵ��������ope
//������Ϊstring����
//menu->�鿴�����˵�,����0
//creat->�������ף�����1
//search->���ҳ�Ա������2
//delete->ɾ����Ա������3
//add->��ӳ�Ա������4
//amend->�޸ĳ�Ա��Ϣ������5
//print->��ӡ���ף�����6
//quit->�Ƴ����ף�����-1
int getOperation(int &ope) {
	string strOpe = "";
	do {
		if (strOpe != "") {
			cout << "GENEALOGYSYSTEM:~ User$ Wrong command! Please enter again!" << endl;
		}
		cout << endl
			 << "GENEALOGYSYSTEM:~ User$ ";
		cin >> strOpe;
		if (strOpe=="menu"||strOpe=="m") {
			ope = 0;
		} else if (strOpe=="creat"||strOpe=="c") {
			ope = 1;
		} else if (strOpe=="search"||strOpe=="s") {
			ope = 2;
		} else if (strOpe=="delete"||strOpe=="d") {
			ope = 3;
		} else if (strOpe=="add"||strOpe=="ad") {
			ope = 4;
		} else if (strOpe=="amend"||strOpe=="am") {
			ope = 5;
		} else if (strOpe=="print"||strOpe=="p") {
			ope = 6;
		} else if (strOpe=="quit"||strOpe=="q") {
			ope = -1;
		}
	} while (strOpe!="menu"&&strOpe!="m"
			&&strOpe!="creat"&&strOpe!="c"
			&&strOpe!="search"&&strOpe!="s"
			&&strOpe!="delete"&&strOpe!="d"
			&&strOpe!="add"&&strOpe!="ad"
			&&strOpe!="amend"&&strOpe!="am"
			&&strOpe!="print"&&strOpe!="p"
			&&strOpe!="quit"&&strOpe!="q");	
	return ope;		 	 
}



//�������׵�ui
//��isCreatedΪtrue����ʾ�����Ѿ������������ٴ���
//��isCreatedΪfalse����ʾ���׻�δ���������Դ�������
void UICreatGenealogy(bool isCreated) {
	if (isCreated) {
		cout << "GENEALOGYSYSTEM:~ User$ Error: Genealogy has been created! Can't be created again!" << endl;
	} else {
		cout << "GENEALOGYSYSTEM:~ User$ Creat genealogy successfully!" << endl;
	}
}



//���ҳ�Ա��ui
//�����û���Ҫ���ҵĳ�Ա��
string UISearchPerson() {
	string name;
	cout << "GENEALOGYSYSTEM:~ User$ Please enter the name of the member that you want to search!"<< endl
		 << "GENEALOGYSYSTEM:~ User$ ";
	cin >> name;

	return name;	 
}


//����������˳�����
void endProgram() {
	cout << "==========================================" << endl
		 << "                    Quit                  " << endl
		 << "==========================================" << endl
		 << endl;
}


#endif
