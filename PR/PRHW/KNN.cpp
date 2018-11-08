
/*similarity(A,B)=(a1xb1,a2xb2,a3xb3...a13xb13)/sqrt(a1^+a2^+...+a13^)xsqrt(b1^+b2^+...+b13^)
sum_xx += pow(a[i],2)
sum_xy += a[i]xb[i]
sum_yy += pow(b[i],2)
similarity=sum_xy/sqrt(sum_xx*sum_yy)

ref:http://enginebai.logdown.com/posts/241676/knn
*/


#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <fstream>
#include <sstream>
#include <cassert>
#include <cmath>
 using namespace std;

 struct sample
 {
	     string type;
	     vector<double> features;
	 };

 struct typeDistance
 {
	     string type;
	     double distance;
	 };

 bool operator < (const typeDistance& lhs, const typeDistance& rhs)
	 {
	     return lhs.distance < rhs.distance;
	 }
	 void readTrain(vector<sample>& train, const string& file)
	 {
	     ifstream fin(file.c_str());
	     if (!fin)
		     {
		         cerr << "File error!" << endl;
		         exit(1);
		     }
	     string line;
	     double d = 0.0;
	     while (getline(fin, line))
		     {
		         istringstream sin(line);
		         sample ts;
		         sin >> ts.type;
		         while (sin >> d)
			         {
			             ts.features.push_back(d);
			         }
		         train.push_back(ts);
		     }
	     fin.close();
	 }
	 void readTest(vector<sample>& test, const string& file)
	 {
	     ifstream fin(file.c_str());
	     if (!fin)
		     {
		         cerr << "File error!" << endl;
		         exit(1);
		     }
	     double d = 0.0;
	     string line;
	     while (getline(fin, line))
		     {
		         istringstream sin(line);
		         sample ts;
		         while (sin >> d)
			         {
			             ts.features.push_back(d);
			         }
		         test.push_back(ts);
		     }
	     fin.close();
	 }

 double euclideanDistance(const vector<double>& v1, const vector<double>& v2)
 {
	     assert(v1.size() == v2.size());
	     double ret = 0.0;
	     for (vector<double>::size_type i = 0; i != v1.size(); ++i)
		     {
		         ret += (v1[i] - v2[i]) * (v1[i] - v2[i]);
		     }
	     return sqrt(ret);
	 }

 void initDistanceMatrix(vector<vector<double> >& dm, const vector<sample>& train, const vector<sample>& test)
 {
	     for (vector<sample>::size_type i = 0; i != test.size(); ++i)
		     {
		         vector<double> vd;
		         for (vector<sample>::size_type j = 0; j != train.size(); ++j)
			         {
			             vd.push_back(euclideanDistance(test[i].features, train[j].features));
			         }
		         dm.push_back(vd);
		     }
	 }

 void knnProcess(vector<sample>& test, const vector<sample>& train, const vector<vector<double> >& dm, unsigned int k)
 {
	     for (vector<sample>::size_type i = 0; i != test.size(); ++i)
		     {
		         multimap<double, string> dts;
		         for (vector<double>::size_type j = 0; j != dm[i].size(); ++j)
			         {
			             if (dts.size() < k)
				             {
				                 dts.insert(make_pair(dm[i][j], train[j].type));
				             }
			             else
				             {
				                 multimap<double, string>::iterator it = dts.end();
				                 --it;
				                 if (dm[i][j] < it->first)
					                 {
					                     dts.erase(it);
					                     dts.insert(make_pair(dm[i][j], train[j].type));
					                 }
				             }
			         }
		         map<string, double> tds;
		         string type = "";
		         double weight = 0.0;
		         for (multimap<double, string>::const_iterator cit = dts.begin(); cit != dts.end(); ++cit)
			         {
			             // 不考虑权重的情况，在 k 个样例中只要出现就加 1
				              ++tds[cit->second];
				
				             // 这里是考虑距离与权重的关系，距离越大权重越小
				             //tds[cit->second] += 1.0 / cit->first;
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
				 cout << test[i].type << '\t';
		         for (vector<double>::size_type j = 0; j != test[i].features.size(); ++j)
			         {
			             fout << test[i].features[j] << ' ';
						 cout << test[i].features[j] << ' ';
			         }
		         fout << endl;
				 cout << endl;
		     }
	 }

 void knn(const string& file1, const string& file2, const string& file3, int k)
 {
	     vector<sample> train, test;
	     readTrain(train, file1.c_str());
	     readTest(test, file2.c_str());
	     vector<vector<double> > dm;
	     initDistanceMatrix(dm, train, test);
	     knnProcess(test, train, dm, k);
	     writeTest(test, file3.c_str());
	 }

 int main()
 {
	     knn("train.txt", "test.txt", "result.txt", 5);
		 system("PAUSE");
	     return 0;
	 }
