#ifndef GENEALOGY_HPP
#define GENEALOGY_HPP value
#include <iostream>
#include <fstream>
#include <queue>
using namespace std;
int tmp = 10000;
#include"Person.hpp"

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
	//考虑重名问题
	void searchPerson(const string& name);

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
	void clearPerson( Person* target );
	void resPrint( Person* member );
	Person* findPerson(const string& name, int num = 1);
};


void completeBranch(Person* branch, ifstream& fin) {
	int cursor = fin.tellg();
//cout << cursor;
	string name; 
	bool gender;
	int generation; 
	int DuplicationNumber; 
	string spouse; 

	fin >> generation >> name >> gender >> DuplicationNumber >> spouse;
//cout << generation << name << gender << DuplicationNumber << spouse << endl;
//cout << name.substr(1,name.length()-2) << spouse.substr(1,spouse.length()-2) << endl;
	Person* child = new Person();
	child->setGender(gender);
	child->setGeneration(generation);
	child->setDuplicationNumber(DuplicationNumber);
	child->setName(name.substr(1,name.length()-2));
	child->setSpouse(spouse.substr(1,spouse.length()-2));
//cout << fin.tellg();
	if (child->getGeneration() > branch->getGeneration()) {
		vector<Person*> children = branch->getChildren();
		children.push_back(child);
		branch->setChildren(children);
		child->setFather(branch);
		tmp = 10000;
		while (!fin.eof()&&tmp>child->getGeneration()) {
			completeBranch(child, fin);
//cout << generation << endl; 
		}
	} else {
		fin.seekg(cursor);
//cout << cursor << endl;
		delete child;
		child = NULL;
		tmp = generation;
	}
}

void writeBranch(Person* branch, ofstream& fout) {
	if (branch) {
		fout << branch->getGeneration() << " [" << branch->getName() << "] " 
			 << branch->getGender() << ' ' << branch->getDuplicationNumber()
			 << " [" << branch->getSpouse() << "] ";

		vector<Person*> children = branch->getChildren();
		for (auto i = children.begin(); i != children.end(); i++) {
			writeBranch(*i, fout);
		}
	}
}

void printBranch(Person* branch) {
	if (branch) {
		for (int i = 0; i < branch->getGeneration() - 1; ++i)
		{
			cout << ' ';
		}
		branch->printPerson();
		cout << endl;
		
		vector<Person*> children = branch->getChildren();
		for (auto i = children.begin(); i != children.end(); i++) {
			printBranch(*i);
		}
	}
};

void deleteBranch(Person* branch) {
	if (branch) {
//cout << "OK" << endl;
		vector<Person*> children = branch->getChildren();
		for (auto i = children.begin(); i != children.end(); i++) {
			if (*i) deleteBranch(*i);
			*i = NULL;
//(*i)->printPerson();
		}
	}
	delete branch;
}

Genealogy::Genealogy() {
	root = NULL;
}; 
//娓呯悊缂撳瓨
Genealogy::~Genealogy() {
	deleteGenealogy();
}; 
//璇诲彇鏂囦欢genealogy.txt
//鑻ユ枃浠朵腑鏈夋暟鎹紝瀹惰氨宸茬粡鍒涘缓锛岃繑鍥炲�间负true
//鑻ユ枃浠朵腑娌℃湁鏁版嵁锛岃〃绀哄璋变负绌烘垨杩樻湭鍒涘缓锛岃繑鍥瀎alse
bool Genealogy::readFile() {
	ifstream fin;
	string message;
	fin.open("genealogy.txt", ios::in);
	if (fin.eof()) {
		fin.close();
		return false;
	}
	if (root) {
		cout << "There must be something wrong" << endl;
		exit(0);
	}
	string name; 
	bool gender;
	int generation; 
	int DuplicationNumber; 
	string spouse; 

	fin >> generation >> name >> gender >> DuplicationNumber >> spouse;
	//cout << generation << name << gender << DuplicationNumber << spouse << endl;
	root = new Person();
	root->setGender(gender);
	root->setGeneration(generation);
	root->setDuplicationNumber(DuplicationNumber);
	root->setName(name.substr(1,name.length()-2));
	root->setSpouse(spouse.substr(1,spouse.length()-2));
	while (!fin.eof()) {
//cout << fin.tellg();
		completeBranch(root, fin);

// string s1;string s2;string s3;string s4;string s5;
// fin >> s1 >> s2 >> s3 >> s4 >> s5;
// cout << s1 << s2 << s3 << s4 << s5 << endl;
//cout << fin.tellg();
	}
	fin.close();
	return true;
}; 
//灏嗘枃浠跺啓鍏enealogy.txt
void Genealogy::writeFile() {
	ofstream fout;
	fout.open("genealogy.txt", ios::out);
	if (root) writeBranch(root, fout);
	else fout << "";
	fout.close();

	ifstream fin("genealogy.txt");  
	string str((std::istreambuf_iterator<char>(fin)),  
	                 std::istreambuf_iterator<char>());
	fin.close();

	fout.open("genealogy.txt");
	fout << str.substr(0,str.length()-1);
}; 
//鍒涘缓瀹惰氨
//鍒涘缓root锛岃姹傜敤鎴疯緭鍏ユ牴鑺傜偣root(绁栧厛)鐨勪俊鎭�
void Genealogy::creatGenealogy() {
	if (root) {
		cout << "There is a Genealogy here before, you can't create a new one." << endl;
		cout << "You can delete the old one, then you can create a new Genealogy." << endl; 
	} else {
		Person* ancestor = new Person();
		string name; //鑻辨枃鍚嶏紝濡侹obe Bryant
		string spouse; //閰嶅伓鐨勫悕瀛楋紝鍒濆鍖栦负鈥溾��

		ancestor->setGender(1);
		ancestor->setGeneration(1);
		ancestor->setDuplicationNumber(1);
		Person* father = NULL;
		ancestor->setFather(father);
		cout << "Please input the information of the ancestor." << endl;
		cout << "Please input the name:" << endl;
		cin >> name;
		ancestor->setName(name);
		cout << "Please input the his spouse:" << endl;
		cin >> spouse;
		ancestor->setSpouse(spouse);
		cout << "Create Genealogy successfully!" << endl;

		root = ancestor;
	}
}; 
//鍒犻櫎瀹惰氨
//璋冪敤writeFile()鍑芥暟
void Genealogy::deleteGenealogy() {
	if (root) {
		deleteBranch(root);
		root = NULL;
	}
}; 
//鎵撳嵃鏁翠釜瀹惰氨鍥�
void Genealogy::print() {
	if (root)
		printBranch(root);
};

void Genealogy::searchPerson( const string &name )
{
    string blank;

    if ( !root ) {
        cout << "GENEALOGYSYSTEM:~ User$ The Genealogy is empty!" << endl
             << "Press enter to continue..." << endl;
        getline( cin, blank );
        return;
    }

    Person* one = findPerson( name );

    if ( !one ) {
        cout << "GENEALOGYSYSTEM:~ User$ The person you are looking for doesn't exist."
             << "Press enter to continue..." << endl;
        getline( cin, blank );
        return;
    }

    resPrint( one );

    for ( int i = 1; i < one->getDuplicationNumber(); ++i ) {
        resPrint( findPerson( name, i+1 ) );
    }
}

void Genealogy::amendPerson()
{
    string name, blank;
    if ( !root ) {
        cout << "GENEALOGYSYSTEM:~ User$ The Genealogy is empty!" << endl
             << "Press enter to continue...";
        getline( cin, blank );
        return;
    }

    cout << "GENEALOGYSYSTEM:~ User$ Please enter the name of the person whose information you want to modify:" << endl
         << "GENEALOGYSYSTEM:~ User$ ";
    
    do {
        getline( cin, name );
    } while ( name.size() == 0 );

    Person *thePerson = findPerson( name );
    if ( !thePerson ) {
        cout << "GENEALOGYSYSTEM:~ User$ The person you are looking for doesn't exist."
             << "Press enter to continue...";
        getline( cin, blank );
        return;
    }

    if ( thePerson->getDuplicationNumber() > 1 ) {
        searchPerson( name );

        cout << "GENEALOGYSYSTEM:~ User$ Please enter the number following the name of the person"
             << " whose information you want to modify:" << endl;

        int num = 0, total = thePerson->getDuplicationNumber();
        cin >> num;
        while ( 1 ) {
            cout << "GENEALOGYSYSTEM:~ User$ ";
            cin >> num;

            if ( num > total ) {
                cout << "GENEALOGYSYSTEM:~ User$ Invalid! Please check and ENTER AGAIN."
                     << endl << "Press enter to continue...";
                getline( cin, blank );
                continue;
            }

            break;
        }

        thePerson = findPerson( name, num );
    }

    cout << "GENEALOGYSYSTEM:~ User$ Please enter the corresponding letter to"
         << " choose the information you want to modify"  << endl
         << "===========================================" << endl
         << "'Name'/'n' -> Modify name"                   << endl
         << "'Gender'/'g' -> Modify gender"               << endl
         << "'Spouse's name'/'s' -> Modify spouse's name" << endl
         << "===========================================" << endl;

    string operation;
    bool valid = false;
    while ( !valid ) {

        cout << "GENEALOGYSYSTEM:~ User$ ";

        getline( cin, operation );
        if ( operation.size() == 0 )
            continue;

        if ( operation != "n" && operation != "g" && operation != "s" ) {
            cout << "GENEALOGYSYSTEM:~ User$ Invalid! Please check and ENTER AGAIN."
                 << endl << "Press enter to continue...";
            getline( cin, blank );
            continue;
        }

        valid = true;

    }

    switch( operation.at( 0 ) ) {
        case 'n':
        {
            cout << "GENEALOGYSYSTEM:~ User$ Please enter the new name:" << endl
                 << "GENEALOGYSYSTEM:~ User$ ";
            string newName;

            do {
                getline( cin, newName );
            } while ( newName.size() == 0 );

            thePerson->setName( newName );

            cout << "GENEALOGYSYSTEM:~ User$ The name has been changed from "
                 << name << " to " << newName << "." << endl << "Press enter to continue...";
            getline( cin, blank );
        }

        case 'g':
        {
            cout << "GENEALOGYSYSTEM:~ User$ The gender has been changed from "
                 << ( thePerson->getGender() ? "Male" : "Female" )
                 << " to " 
                 << ( !thePerson->getGender() ? "Male" : "Female" )
                 << "." << endl << "Press enter to continue...";
            getline( cin, blank );
            thePerson->setGender( !thePerson->getGender() );
        }

        case 's':
        {
            cout << "GENEALOGYSYSTEM:~ User$ Please enter the new name:" << endl
                 << "GENEALOGYSYSTEM:~ User$ ";
            string newName;

            do {
                getline( cin, newName );
            } while ( newName.size() == 0 );

            thePerson->setSpouse( newName );

            cout << "GENEALOGYSYSTEM:~ User$ The spouse's name has been changed from "
                 << name << " to " << newName << "." << endl << "Press enter to continue...";
            getline( cin, blank );
        }

    }

}

void Genealogy::addPerson()
{
    string name, fatherName, blank;
    if ( !root ) {
        cout << "GENEALOGYSYSTEM:~ User$ The Genealogy is empty!" << endl
             << "Press enter to continue...";
        getline( cin, blank );
        return;
    }

    cout << "GENEALOGYSYSTEM:~ User$ Please enter the name of the person"
         << " you want to add:" << endl
         << "GENEALOGYSYSTEM:~ User$ ";

    do {
        getline( cin, name );
    } while ( name.size() == 0 );

    cout << endl << "GENEALOGYSYSTEM:~ User$ Please enter the corresponding number"
         << "to choose the gender of this person:" << endl
         << "====================================" << endl
         << "1 : Male" << endl << "2: Female" << endl
         << "====================================" << endl;

    int genderNum = 0;
    while ( 1 ) {
        cout << "GENEALOGYSYSTEM:~ User$ ";
        cin >> genderNum;

        if ( genderNum != 1 && genderNum != 2 ) {
            cout << "GENEALOGYSYSTEM:~ User$ Invalid! Please check and ENTER AGAIN."
                 << endl << "Press enter to continue...";
            getline( cin, blank );
            continue;
        }

        break;
    }

    cout << endl << "GENEALOGYSYSTEM:~ User$ Please enter the name of the person's father:" << endl;

    Person* father = nullptr;

    do {

        cout << "GENEALOGYSYSTEM:~ User$ ";
        do {
            getline( cin, fatherName );
        } while ( fatherName.size() == 0 );

        father = findPerson( fatherName );
        if ( !father ) {
            cout << "GENEALOGYSYSTEM:~ User$ The person you are looking for doesn't exist."
                 << " Please check and ENTER AGAIN." << endl
                 << "Press enter to continue...";
            getline( cin, blank );
            continue;
        }

        //more than 1 person have the same name
        if ( father->getDuplicationNumber() > 1 ) {
            searchPerson( fatherName );

            cout << "GENEALOGYSYSTEM:~ User$ Please enter the number following the name of the person"
                 << " whose information you want to modify:" << endl;

            int num = 0, total = father->getDuplicationNumber();
            while ( 1 ) {
                cout << "GENEALOGYSYSTEM:~ User$ ";
                cin >> num;

                if ( num > total ) {
                    cout << "GENEALOGYSYSTEM:~ User$ Invalid! Please check and ENTER AGAIN."
                         << endl << "Press enter to continue...";
                    getline( cin, blank );
                    continue;
                }

                break;
            }

            father = findPerson( fatherName, num );
        }

    } while ( father == nullptr );

    Person *newPerson = new Person(), *temp = nullptr;
    newPerson->setName( name );
    newPerson->setGender( genderNum == 1 ? true : false );
    newPerson->setGeneration( father->getGeneration()+1 );
    if ( temp = findPerson( name ), temp ) {
        int duplicationNum = temp->getDuplicationNumber();
        newPerson->setDuplicationNumber( duplicationNum+1 );
        temp->setDuplicationNumber( duplicationNum+1 );

        for ( int i = 1; i < duplicationNum; ++i ) {
            findPerson( name, i+1 )->setDuplicationNumber( duplicationNum+1 );
        }
    }
    newPerson->setFather( father );

    father->addChild( newPerson );

    cout << "GENEALOGYSYSTEM:~ User$ Adding successfully!" << endl
         << "Press enter to continue...";
    getline( cin, blank );
}

void Genealogy::deletePerson()
{
    string name, blank;
    if ( !root ) {
        cout << "GENEALOGYSYSTEM:~ User$ The Genealogy is empty!" << endl
             << "Press enter to continue...";
        getline( cin, blank );
        return;
    }

    cout << "GENEALOGYSYSTEM:~ User$ Please enter the name of the person you want to delete" << endl
         << "GENEALOGYSYSTEM:~ User$ ";

    do {
        getline( cin, name );
    } while ( name.size() == 0 );

    Person *thePerson = findPerson( name );
    if ( !thePerson ) {
        cout << "GENEALOGYSYSTEM:~ User$ The person you are looking for doesn't exist."
             << "Press enter to continue...";
        getline( cin, blank );
        return;
    }

    clearPerson( thePerson );
    cout << "GENEALOGYSYSTEM:~ User$ Deleting successfully!" << endl
         << "Press enter to continue...";
    getline( cin, blank );
}

void Genealogy::clearPerson( Person* target )
{
    if ( !target->getChildren().empty() ) {
        for ( auto per : target->getChildren() )
            clearPerson( per );
    }

    int duplicationNum = target->getDuplicationNumber();
    if ( target->getDuplicationNumber() > 1 ) {
        for ( int i = 0; i < duplicationNum; ++i ) {
            findPerson( target->getName(), i+1 )->setDuplicationNumber( duplicationNum-1 );
        }
    }
    
	auto temp = target->getFather()->getChildren();
    for ( auto it = temp.begin(); it != temp.end(); ++it ) {
        if ( (*it)->getName() == target->getName() ) {
            temp.erase( it );
            break;
        }
    }
    
    target->getFather()->setChildren( temp );

    delete target;
}

void Genealogy::resPrint( Person* member ) {

    cout << "Parents of     " << member->getName() << ": ";
    member->getFather()->printPerson();
    cout << endl;

    cout << "Information of " << member->getName() << ": ";
    member->printPerson();
    cout << endl;

    cout << "Children of    " << member->getName() << ": "; 
    vector<Person*> children = member->getChildren();

    for ( auto i = children.begin(); i != children.end(); i++) {
        (*i)->printPerson();
        cout << endl;
    }

}
Person* Genealogy::findPerson(const string& name, int num) {
	queue<Person*> allMember;
	allMember.push(root);
	while (!allMember.empty()) {
		vector<Person*> children = allMember.front()->getChildren();
		for (auto i = children.begin(); i != children.end(); i++) {
			allMember.push(*i);
		}
		if (allMember.front()->getName()==name) {
			if (num==1) {
				return allMember.front();	
			} else {
				num --;
			}
		}
		allMember.pop();
	}
	return nullptr;
};


#endif
