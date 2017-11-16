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
		指向父亲的指针
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
	void setName(string _name);

	//返回gender
	bool getGender();
	//设置gender
	void setGender(bool _gender);

	//返回generation
	int getGeneration();
	//设置generation
	void setGeneration(int _generation);

	//返回DuplicationNumber
	int getDuplicationNumber();
	//设置DuplicationNumber
	void setDuplicationNumber(int _DuplicationNumber);

	//返回spouse
	string getSpouse();
	//设置spouse
	void setSpouse(string _spouse);

	//返回children
	vector<Person*> getChildren();
	//设置children
	void setChildren(vector<Person*> _children);

	//返回father
	Person* getFather();
	//设置father
	void setFather(Person* _father);

	//打印成员信息
	void printPerson();
	//添加成员
	//在函数内要求用户输入相关信息
	void addChild(Person* child);

private:
	string name; //英文名，如Kobe Bryant
	bool gender; //1表示男 0表示女 默认为男
	int generation; //第几代成员，正数
	int DuplicationNumber; //第几个重名的人，默认为1
	string spouse; //配偶的名字，初始化为“”
	vector<Person*> children; //子女的指针容器
	Person* father; //指向双亲的指针
};

void Person::addChild(Person* child){
	children.push_back(child);
}

Person::Person(){
	name = "";
	gender = true;
	generation = 0;
	DuplicationNumber = 1;
	spouse = "";
	father = NULL;

}
Person::~Person(){

}

string Person::getName(){
	return name;
}

void Person::setName(string _name){
	name = _name;
}

bool Person::getGender(){
	return gender;
}

void Person::setGender(bool _gender){
	gender = _gender;
}

int Person::getGeneration(){
	return generation;
}

void Person::setGeneration(int _generation){
	generation = _generation;
}

int Person::getDuplicationNumber(){
	return DuplicationNumber;
}

void Person::setDuplicationNumber(int _DuplicationNumber){
	DuplicationNumber = _DuplicationNumber;
}


string Person::getSpouse(){
	return spouse;
}

void Person::setSpouse(string _spouse){
	spouse = _spouse;
}

vector<Person*> Person::getChildren(){
	return children;
}

void Person::setChildren(vector<Person*> _children){
	children = _children;
}

Person* Person::getFather(){
	return father;
}

void Person::setFather(Person* _father){
	father = _father;
}

void Person::printPerson(){
	cout << "Generation" << generation << ": " << name;
	cout << " Gender:";
	if(gender) cout << "M";
	else cout << "F";
	if(spouse != "") cout << " spouse:" << spouse;
}

#endif
