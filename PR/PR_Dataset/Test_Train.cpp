#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>

using namespace std;

int main(){
	ifstream fin("wine.data");
	string s;
	int i=0;
	/*while (getline(fin, s)) {
		cout << s << endl;
	}*/
	for (i; i < 178; i++) {
		getline(fin,s);
		if (i % 2) {
				ofstream test("test.data",ios::app);
				test << s<<endl;
		}
		else {
			ofstream train("train.data", ios::app);
			train << s<<endl;
		}

	}
	

	system("PAUSE");
	return 0;
	}