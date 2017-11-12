#ifndef GENEALOGY_HPP
#define GENEALOGY_HPP value

/*
	本质为多根树
	节点为Person对象
	父节点为父亲，子节点为孩子
	功能有：
		创建家谱；
		删除家谱；
		查找成员；
		删除成员；
		添加成员；
		修改成员信息；
		打印家谱；
*/
#include "Person.hpp"

class Genealogy
{
public:
	Genealogy(); 

	//清理缓存
	~Genealogy(); 

	//读取文件genealogy.txt
	//若文件中有数据，家谱已经创建，返回值为true
	//若文件中没有数据，表示家谱为空或还未创建，返回false
	bool readFile(); 

	//将文件写入genealogy.txt
	void writeFile(); 

	//创建家谱
	//创建root，要求用户输入根节点root(祖先)的信息
	void creatGenealogy(); 

	//删除家谱
	//调用writeFile()函数
	void deleteGenealogy(); 

	//查找成员
	//参数是成员名
	//返回一个Person指针
	//考虑重名问题
	Person* searchPerson(string name);

	//修改成员信息
	//调用searchPerson(string name)函数找到对应成员
	//可修改成员的名字或性别等信息
	void amendPerson();

	//添加成员
	//在函数内要求用户输入相关信息
	void addPerson();

	//删除成员
	//在函数内输入用户名
	void deletePerson();

	//打印整个家谱图
	void print();

private:
	Person* root;
};
#endif