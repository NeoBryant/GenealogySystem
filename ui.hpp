#ifndef UI_HPP
#define UI_HPP value

#include <iostream>
using namespace std;


//打开程序的介绍界面
void introduction();


//介绍功能对应操作数
void menu();

//从用户处得到操作数，改变ope的值，并返回ope
//操作数为string类型
//menu->查看操作菜单
//creat->创建家谱，返回1
//search->查找成员，返回2
//delete->删除成员，返回3
//add->添加成员，返回4
//amend->修改成员信息，返回5
//print->打印家谱，返回6
//q->推出家谱，返回-1
int getOperation(int &ope);



//创建家谱的ui
//若isCreated为true，表示家谱已经创建，不能再创建
//若isCreated为false，表示家谱还未创建，可以创建家谱
void UICreatGenealogy(bool isCreated);



//查找成员的ui
//返回用户所要查找的成员名
string UISearchPerson();


//结束程序的退出界面
void endProgram();


#endif