#include <iostream>
#include "Genealogy.hpp"
#include "ui.hpp"
using namespace std;

int main(){

	Genealogy genealogy;
	bool isCreated = genealogy.readFile();
	int ope; //操作数

	while (getOperation(ope) != -1) { //调用函数，得到ope值
		if (isCreated || ope == 1) { //若已创建家谱或正在创建家谱
			switch(ope) {
				case 1:	//创建家谱
					UICreatGenealogy(isCreated);
					if (!isCreated) {
						genealogy.creatGenealogy();
						isCreated = true;
					}
					break;
				case 2: //查找成员
					genealogy.searchPerson(UISearchPerson());
					break;
				case 3: //删除成员
					genealogy.deletePerson();
					break;
				case 4: //添加成员
					genealogy.addPerson();
					break;
				case 5: //修改成员信息
					genealogy.amendPerson();
					break;
				case 6: //打印家谱
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