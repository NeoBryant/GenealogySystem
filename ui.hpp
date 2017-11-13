#ifndef UI_HPP
#define UI_HPP value

#include <iostream>
using namespace std;


//打开程序的介绍界面
void introduction() {
	cout << "==========================================" << endl
		 << "             Genealogy System             " << endl
		 << "==========================================" << endl;
}


//介绍功能对应操作数
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

//从用户处得到操作数，改变ope的值，并返回ope
//操作数为string类型
//menu->查看操作菜单,返回0
//creat->创建家谱，返回1
//search->查找成员，返回2
//delete->删除成员，返回3
//add->添加成员，返回4
//amend->修改成员信息，返回5
//print->打印家谱，返回6
//quit->推出家谱，返回-1
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
	}while (strOpe!="menu"||strOpe!="m"
			||strOpe!="creat"||strOpe!="c"
			||strOpe!="search"||strOpe!="s"
			||strOpe!="delete"||strOpe!="d"
			||strOpe!="add"||strOpe!="ad"
			||strOpe!="amend"||strOpe!="am"
			||strOpe!="print"||strOpe!="p"
			||strOpe!="quit"||strOpe!="q")	
	return ope;		 	 
}



//创建家谱的ui
//若isCreated为true，表示家谱已经创建，不能再创建
//若isCreated为false，表示家谱还未创建，可以创建家谱
void UICreatGenealogy(bool isCreated) {
	if (isCreated) {
		cout << "GENEALOGYSYSTEM:~ User$ Error: Genealogy has been created! Can't be created again!" << endl;
	} else {
		cout << "GENEALOGYSYSTEM:~ User$ Creat genealogy successfully!" << endl;
	}
}



//查找成员的ui
//返回用户所要查找的成员名
string UISearchPerson() {
	string name;
	cout << "GENEALOGYSYSTEM:~ User$ Please enter the name of the member that you want to search!" endl
		 << "GENEALOGYSYSTEM:~ User$ ";
	cin >> name;

	return name;	 
}


//结束程序的退出界面
void endProgram() {
	cout << "==========================================" << endl
		 << "                    Quit                  " << endl
		 << "==========================================" << endl
		 << endl;
}


#endif