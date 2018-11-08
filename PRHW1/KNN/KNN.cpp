#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <fstream>
#include <sstream>
#include <cassert>
#include <cmath>
#include <math.h>
#include <time.h>

 using namespace std;

 struct sample
 {
	     string type;
	     vector<double> features;
	 };

 void readTrain(vector<sample>& train, const string& file)
 {
	 ifstream fin(file.c_str());
	 if (!fin)
	 {
		 cerr << "File error!" << endl;
		 exit(1);
	 }
	 string line;
	 double s = 0.0;
	 while (getline(fin, line))
	 {
		 istringstream stringin(line);
		 sample ts;
		 stringin >> ts.type;
		 while (stringin >> s)
		 {
			 ts.features.push_back(s);
		 }
		 train.push_back(ts);
	 }  fin.close();
 }
	 void readTest(vector<sample>& test, const string& file)
	 {
	     ifstream fin(file.c_str());
	     if (!fin)
		     {
		         cerr << "File error!" << endl;
		         exit(1);
		     }
	     double s = 0.0;
	     string line;
	     while (getline(fin, line))
		     {
		         istringstream stringin(line);
		         sample ts;
		         while (stringin >> s)
			         {
			             ts.features.push_back(s);
			         }
		         test.push_back(ts);
		     }
	     fin.close();
	 }

 double euclideanDistance(const vector<double>& v1, const vector<double>& v2)
 {
	     double ret = 0.0;
		vector<double>::size_type i = 0;
		ret = pow((v1[i] / 14.83 - v2[i] / 14.83), 2) + pow((v1[i +1] / 5.8 - v2[i +1] / 5.8),2) + pow((v1[i + 2] / 3.23 - v2[i + 2] / 3.23), 2)
			+ pow((v1[i + 3] / 30 - v2[i + 3] / 30), 2) + pow((v1[i + 4] / 162 - v2[i + 4] / 162), 2) + pow((v1[i + 5] / 3.88 - v2[i + 5] / 3.88), 2)
			+ pow((v1[i + 6] / 5.08 - v2[i + 6] / 5.08), 2) + pow((v1[i + 7] / 0.66 - v2[i + 7] / 0.66), 2) + pow((v1[i + 8] / 3.58 - v2[i + 8] / 3.58), 2)
			+ pow((v1[i + 9] / 13 - v2[i + 9] / 13), 2) + pow((v1[i + 10] / 1.71 - v2[i + 10] / 1.71), 2) + pow((v1[i + 11] / 4 - v2[i + 11] / 4), 2) 
			+ pow((v1[i + 12] / 1680 - v2[i + 12] / 1680), 2);
	     return sqrt(ret);
	 }
 double euclideanDistance2(const vector<double>& v1, const vector<double>& v2)
 {
	 double ret = 0.0;
	 vector<double>::size_type i = 0;
	 ret = pow((v1[i] - v2[i] ), 2) + pow((v1[i + 1] - v2[i + 1] ), 2) + pow((v1[i + 2] - v2[i + 2] ), 2)
		 + pow((v1[i + 3]  - v2[i + 3] ), 2) + pow((v1[i + 4]- v2[i + 4]), 2) + pow((v1[i + 5]  - v2[i + 5] ), 2)
		 + pow((v1[i + 6]  - v2[i + 6] ), 2) + pow((v1[i + 7] - v2[i + 7] ), 2) + pow((v1[i + 8]  - v2[i + 8] ), 2)
		 + pow((v1[i + 9]  - v2[i + 9] ), 2) + pow((v1[i + 10]  - v2[i + 10]), 2) + pow((v1[i + 11]  - v2[i + 11]), 2)
		 + pow((v1[i + 12] - v2[i + 12]), 2) + pow((v1[i + 13] - v2[i + 13]), 2) + pow((v1[i + 14] - v2[i + 14]), 2)
		 + pow((v1[i + 15] - v2[i + 15]), 2) + pow((v1[i + 16] - v2[i + 16]), 2) + pow((v1[i + 17] - v2[i + 17]), 2)
		 + pow((v1[i + 18] - v2[i + 18]), 2) + pow((v1[i + 19] - v2[i + 19]), 2);
	 return sqrt(ret);
 }

 void initDistanceMatrix(vector<vector<double> >& result, const vector<sample>& train, const vector<sample>& test)
 {
	     for (vector<sample>::size_type i = 0; i != test.size(); ++i)
		     {
		         vector<double> vd;
		         for (vector<sample>::size_type j = 0; j != train.size(); ++j)
			         {
			             vd.push_back(euclideanDistance(test[i].features, train[j].features));
			         }
				 result.push_back(vd);
		     }
	 }

 void initDistanceMatrix2(vector<vector<double> >& result, const vector<sample>& train, const vector<sample>& test)
 {
	 for (vector<sample>::size_type i = 0; i != test.size(); ++i)
	 {
		 vector<double> vd;
		 for (vector<sample>::size_type j = 0; j != train.size(); ++j)
		 {
			 vd.push_back(euclideanDistance2(test[i].features, train[j].features));
		 }
		 result.push_back(vd);
	 }
 }
 void knnProcess(vector<sample>& test, const vector<sample>& train, const vector<vector<double> >& result, unsigned int k)
 {
	     for (vector<sample>::size_type i = 0; i != test.size(); ++i)
		     {
		         multimap<double, string> dts;
		         for (vector<double>::size_type j = 0; j != result[i].size(); ++j)
			         {
			             if (dts.size() < k)
				             {
				                 dts.insert(make_pair(result[i][j], train[j].type));
				             }
			             else
				             {
				                 multimap<double, string>::iterator it = dts.end();
				                 --it;
				                 if (result[i][j] < it->first)
					                 {
					                     dts.erase(it);
					                     dts.insert(make_pair(result[i][j], train[j].type));
					                 }
				             }
			         }
		         map<string, double> tds;
		         string type = "";
		         double weight = 0.0;
		         for (multimap<double, string>::const_iterator cit = dts.begin(); cit != dts.end(); ++cit)
			         {
				              ++tds[cit->second];

			             if (tds[cit->second] > weight)
				             {
				                 weight = tds[cit->second];
				                 type = cit->second;
				             }
			         }
		         test[i].type = type;
		     }
	 }

	 void writeTest(const vector<sample>& test, const string& file)
	 {
	     ofstream fout(file.c_str());
	     if (!fout)
		     {
		         cerr << "File error!" << endl;
		         exit(1);
		     }
	     for (vector<sample>::size_type i = 0; i != test.size(); ++i)
		     {
		         fout << test[i].type << '\t';
		         for (vector<double>::size_type j = 0; j != test[i].features.size(); ++j)
			         {
			             fout << test[i].features[j] << ' ';
			         }
		         fout << endl;
		     }
	 }

 void knn(const string& file1, const string& file2, const string& file3, int k)
 {
	     vector<sample> train, test;
	     readTrain(train, file1.c_str());
	     readTest(test, file2.c_str());
	     vector<vector<double> > result;
	     initDistanceMatrix(result, train, test);
	     knnProcess(test, train, result, k);
	     writeTest(test, file3.c_str());
	 }
 void knn2(const string& file1, const string& file2, const string& file3, int k)
 {
	 vector<sample> train, test;
	 readTrain(train, file1.c_str());
	 readTest(test, file2.c_str());
	 vector<vector<double> > result;
	 initDistanceMatrix2(result, train, test);
	 knnProcess(test, train, result, k);
	 writeTest(test, file3.c_str());
 }


 int main()
 {		
	 clock_t tstart = clock();
	    /* knn("train.txt", "test_test.txt", "result_test.txt", 5);
		 cout <<"time for test the test data: "<< (double)(clock() - tstart)/CLOCKS_PER_SEC<<"s"<<endl;
		 clock_t tstart2 = clock();
		 knn("train.txt", "test_train.txt", "result_train.txt", 5);
		 cout <<"time for test the train data: "<< (double)(clock() - tstart2) / CLOCKS_PER_SEC << "s" <<endl;
		 clock_t tstart3 = clock();
		 knn("train.txt", "test_total.txt", "result_total.txt", 5);
		 cout <<"time for test the tatal data: "<< (double)(clock() - tstart3) / CLOCKS_PER_SEC << "s" <<endl;
		*/

		 clock_t tstart4 = clock();
		 knn2("rantrain.data", "rantest.data", "result_test2.txt", 5);
		 cout << "time for test the test data: " << (double)(clock() - tstart4) / CLOCKS_PER_SEC << "s" << endl;
		 clock_t tstart5 = clock();
		 knn2("rantrain.data", "rantrain.data", "result_train2.txt", 5);
		 cout << "time for test the train data: " << (double)(clock() - tstart5) / CLOCKS_PER_SEC << "s" << endl;
		 clock_t tstart6 = clock();
		 knn2("rantrain.data", "totalran.data", "result_total2.txt", 5);
		 cout << "time for test the tatal data: " << (double)(clock() - tstart6) / CLOCKS_PER_SEC << "s" << endl;
		 system("PAUSE");


	     return 0;
	 }
