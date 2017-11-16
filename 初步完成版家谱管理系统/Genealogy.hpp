#ifndef GENEALOGY_HPP
#define GENEALOGY_HPP value
#include <iostream>
#include <fstream>
#include <queue>
using namespace std;
int tmp = 10000;
#include"Person.hpp"

/*
	±¾ÖÊÎª¶à¸ùÊ÷
	½ÚµãÎªPerson¶ÔÏó
	¸¸½ÚµãÎª¸¸Ç×£¬×Ó½ÚµãÎªº¢×Ó
	¹¦ÄÜÓĞ£º
		´´½¨¼ÒÆ×£»
		É¾³ı¼ÒÆ×£»
		²éÕÒ³ÉÔ±£»
		É¾³ı³ÉÔ±£»
		Ìí¼Ó³ÉÔ±£»
		ĞŞ¸Ä³ÉÔ±ĞÅÏ¢£»
		´òÓ¡¼ÒÆ×£»
*/
#include "Person.hpp"

class Genealogy
{
public:
	Genealogy(); 

	//ÇåÀí»º´æ
	~Genealogy(); 

	//¶ÁÈ¡ÎÄ¼şgenealogy.txt
	//ÈôÎÄ¼şÖĞÓĞÊı¾İ£¬¼ÒÆ×ÒÑ¾­´´½¨£¬·µ»ØÖµÎªtrue
	//ÈôÎÄ¼şÖĞÃ»ÓĞÊı¾İ£¬±íÊ¾¼ÒÆ×Îª¿Õ»ò»¹Î´´´½¨£¬·µ»Øfalse
	bool readFile(); 

	//½«ÎÄ¼şĞ´Èëgenealogy.txt
	void writeFile(); 

	//´´½¨¼ÒÆ×
	//´´½¨root£¬ÒªÇóÓÃ»§ÊäÈë¸ù½Úµãroot(×æÏÈ)µÄĞÅÏ¢
	void creatGenealogy(); 

	//É¾³ı¼ÒÆ×
	//µ÷ÓÃwriteFile()º¯Êı
	void deleteGenealogy(); 

	//²éÕÒ³ÉÔ±
	//²ÎÊıÊÇ³ÉÔ±Ãû
	//¿¼ÂÇÖØÃûÎÊÌâ
	void searchPerson(const string& name);

	//ĞŞ¸Ä³ÉÔ±ĞÅÏ¢
	//µ÷ÓÃsearchPerson(string name)º¯ÊıÕÒµ½¶ÔÓ¦³ÉÔ±
	//¿ÉĞŞ¸Ä³ÉÔ±µÄÃû×Ö»òĞÔ±ğµÈĞÅÏ¢
	void amendPerson();

	//Ìí¼Ó³ÉÔ±
	//ÔÚº¯ÊıÄÚÒªÇóÓÃ»§ÊäÈëÏà¹ØĞÅÏ¢
	void addPerson();

	//É¾³ı³ÉÔ±
	//ÔÚº¯ÊıÄÚÊäÈëÓÃ»§Ãû
	void deletePerson();

	//´òÓ¡Õû¸ö¼ÒÆ×Í¼
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
//æ¸…ç†ç¼“å­˜
Genealogy::~Genealogy() {
	deleteGenealogy();
}; 
//è¯»å–æ–‡ä»¶genealogy.txt
//è‹¥æ–‡ä»¶ä¸­æœ‰æ•°æ®ï¼Œå®¶è°±å·²ç»åˆ›å»ºï¼Œè¿”å›å€¼ä¸ºtrue
//è‹¥æ–‡ä»¶ä¸­æ²¡æœ‰æ•°æ®ï¼Œè¡¨ç¤ºå®¶è°±ä¸ºç©ºæˆ–è¿˜æœªåˆ›å»ºï¼Œè¿”å›false
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
//å°†æ–‡ä»¶å†™å…¥genealogy.txt
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
//åˆ›å»ºå®¶è°±
//åˆ›å»ºrootï¼Œè¦æ±‚ç”¨æˆ·è¾“å…¥æ ¹èŠ‚ç‚¹root(ç¥–å…ˆ)çš„ä¿¡æ¯
void Genealogy::creatGenealogy() {
	if (root) {
		cout << "There is a Genealogy here before, you can't create a new one." << endl;
		cout << "You can delete the old one, then you can create a new Genealogy." << endl; 
	} else {
		Person* ancestor = new Person();
		string name; //è‹±æ–‡åï¼Œå¦‚Kobe Bryant
		string spouse; //é…å¶çš„åå­—ï¼Œåˆå§‹åŒ–ä¸ºâ€œâ€

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
//åˆ é™¤å®¶è°±
//è°ƒç”¨writeFile()å‡½æ•°
void Genealogy::deleteGenealogy() {
	if (root) {
		deleteBranch(root);
		root = NULL;
	}
}; 
//æ‰“å°æ•´ä¸ªå®¶è°±å›¾
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
