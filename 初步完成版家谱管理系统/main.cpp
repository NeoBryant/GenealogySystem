#include <iostream>
#include "Genealogy.hpp"
#include "ui.hpp"
using namespace std;

int main(){

	Genealogy genealogy;
	bool isCreated = genealogy.readFile();
	int ope; //������

	while (getOperation(ope) != -1) { //���ú������õ�opeֵ
		if (isCreated || ope == 1) { //���Ѵ������׻����ڴ�������
			switch(ope) {
				case 0: //�鿴�˵�
					menu();
					break;
				case 1:	//��������
					UICreatGenealogy(isCreated);
					if (!isCreated) {
						genealogy.creatGenealogy();
						isCreated = true;
					}
					break;
				case 2: //���ҳ�Ա
					genealogy.searchPerson(UISearchPerson());
					break;
				case 3: //ɾ����Ա
					genealogy.deletePerson();
					break;
				case 4: //��ӳ�Ա
					genealogy.addPerson();
					break;
				case 5: //�޸ĳ�Ա��Ϣ
					genealogy.amendPerson();
					break;
				case 6: //��ӡ����
					genealogy.print();
					break;																								
			}
		} else {
			cout << "Please creat a genealogy firstly!" << endl;
		}
	}

	genealogy.writeFile();
	endProgram();

	return 0;
}
