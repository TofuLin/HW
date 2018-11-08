#include <stdio.h>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
using namespace std;

void test_train() {
	ifstream fin("wine.data");
	string s;
	int i = 0;
	for (i; i < 178; i++) {
		getline(fin, s);
		if (i % 2) {
			ofstream test("test.txt", ios::app);
			test << s << endl;
		}
		else {
			ofstream train("train.txt", ios::app);
			train << s << endl;
		}

	}
}

void test_mod() {
	string s;
	float num;
	char c;
	float i=0.0;
	int j = 0;
	int line=0;
	ifstream test("test.txt");
	const int cnt = 14;
	size_t comma = 0;
	size_t comma2 = 0;
	int a = 0;
	while (!test.eof()) {
		line++;
		ofstream test2("test_test.txt", ios::app);
		getline(test, s);
		comma = s.find(',', 0);
		i = atof(s.substr(0, comma).c_str());
		//cout << i << ' ';
	while (comma < s.size() && j != cnt - 1)
		{
		a++;
		ofstream test2("test_test.txt", ios::app);
			comma2 = s.find(',', comma + 1);
			i = atof(s.substr(comma + 1, comma2 - comma - 1).c_str());
			if (a % 13) { test2 << i << ' '; }
			else { test2 << i; }
			cout << i << ' ';
			
		++j;
		comma = comma2;
		}
	if (line < 89) {
		cout << endl;
		test2 << endl;
	}
		j = 0;
	}
	}

void train_mod() {
	string s;
	float num;
	char c;
	float i = 0.0;
	int j = 0;
	int line = 0;
	ifstream train("train.txt");
	const int cnt = 14;
	size_t comma = 0;
	size_t comma2 = 0;
	int a = 0;
	while (!train.eof()) {
		ofstream test3("test_train.txt", ios::app);
		getline(train, s);
		comma = s.find(',', 0);
		i = atof(s.substr(0, comma).c_str());
		line++;
		cout << line<<endl;
		//cout << i << ' ';
		while (comma < s.size() && j != cnt - 1)
		{
			a++;
			ofstream test3("test_train.txt", ios::app);
			comma2 = s.find(',', comma + 1);
			i = atof(s.substr(comma + 1, comma2 - comma - 1).c_str());
			if (a % 13) { test3 << i << ' '; }
			else { test3 << i; }
			cout << i << ' ';
			++j;
			comma = comma2;
		}
		if (line < 89) {
			cout << endl;
			test3 << endl; }
		j = 0;
	}
}
	

void wine_mod() {
	string s;
	float num;
	char c;
	float i = 0.0;
	int j = 0;
	int line = 0;
	ifstream test("wine.data");
	const int cnt = 14;
	size_t comma = 0;
	size_t comma2 = 0;
	int a = 0;
	while (!test.eof()) {
		line++;
		ofstream test4("test_total.txt", ios::app);
		getline(test, s);
		comma = s.find(',', 0);
		i = atof(s.substr(0, comma).c_str());
		//cout << i << ' ';
		while (comma < s.size() && j != cnt - 1)
		{
			a++;
			ofstream test4("test_total.txt", ios::app);
			comma2 = s.find(',', comma + 1);
			i = atof(s.substr(comma + 1, comma2 - comma - 1).c_str());
			if (a % 13) { test4 << i << ' '; }
			else { test4 << i; }
			cout << i << ' ';

			++j;
			comma = comma2;
		}
		if (line < 178) {
			cout << endl;
			test4 << endl;
		}
		j = 0;
	}
}
