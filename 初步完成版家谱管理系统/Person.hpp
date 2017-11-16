#ifndef PERSON_HPP
#define PERSON_HPP value

/*
	��ԱPerson
	���ݣ�
		����
		�Ա�
		���ָ������
		����
		��n����������
		ָ���׵�ָ��
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

	//����name
	string getName();
	//����name
	void setName(string _name);

	//����gender
	bool getGender();
	//����gender
	void setGender(bool _gender);

	//����generation
	int getGeneration();
	//����generation
	void setGeneration(int _generation);

	//����DuplicationNumber
	int getDuplicationNumber();
	//����DuplicationNumber
	void setDuplicationNumber(int _DuplicationNumber);

	//����spouse
	string getSpouse();
	//����spouse
	void setSpouse(string _spouse);

	//����children
	vector<Person*> getChildren();
	//����children
	void setChildren(vector<Person*> _children);

	//����father
	Person* getFather();
	//����father
	void setFather(Person* _father);

	//��ӡ��Ա��Ϣ
	void printPerson();
	//��ӳ�Ա
	//�ں�����Ҫ���û����������Ϣ
	void addChild(Person* child);

private:
	string name; //Ӣ��������Kobe Bryant
	bool gender; //1��ʾ�� 0��ʾŮ Ĭ��Ϊ��
	int generation; //�ڼ�����Ա������
	int DuplicationNumber; //�ڼ����������ˣ�Ĭ��Ϊ1
	string spouse; //��ż�����֣���ʼ��Ϊ����
	vector<Person*> children; //��Ů��ָ������
	Person* father; //ָ��˫�׵�ָ��
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
