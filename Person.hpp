#ifndef PERSON_HPP
#define PERSON_HPP value

/*
	成员Person
	数据：
		名字
		性别
		结点指针容器
		代数
		第n个重名的人
*/
#include <iostream>
#include <vector>
#include <string>

using namespace std;
class Person
{
public:
	Person();
	~Person();

	//返回name
	string getName();
	//设置name
	void setName(string name);

	//返回gender
	bool getGender();
	//设置gender
	void setGender(bool gender);

	//返回generation
	int getGeneration();
	//设置generation
	void setGeneration(int generation);

	//返回DuplicationNumber
	int getDuplicationNumber();
	//设置DuplicationNumber
	void setDuplicationNumber(int DuplicationNumber);
	
	//返回spouse
	string getSpouse();
	//设置spouse
	void setSpouse(string spouse);

	//返回children
	vector<Person*> getChildren();
	//设置children
	void setChildren(vector<Person*> children);

	//返回father
	Person* getFather();
	//设置father
	void setFather(Person* father);

	//打印成员信息
	void printPerson();

private:
	string name; //英文名，如Kobe Bryant
	bool gender //1表示男 0表示女
	int generation; //第几代成员，正数
	int DuplicationNumber; //第几个重名的人，默认为1
	string spouse; //配偶的名字，初始化为“”
	vector<Person*> children; //子女的指针容器
	Person* father; //指向双亲的指针
};


#endif