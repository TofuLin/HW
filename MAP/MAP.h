#include <string>
#include <set>                      
#include <map>                     
#include <vector>                
using namespace std;
/*
1) Alcohol
2) Malic acid
3) Ash
4) Alcalinity of ash
5) Magnesium
6) Total phenols
7) Flavanoids
8) Nonflavanoid phenols
9) Proanthocyanins
10)Color intensity
11)Hue
12)OD280/OD315 of diluted wines
13)Proline


*/
int trainnum = 89;
int testnum = 89;
int testtotal = 178;
struct oridata
{
	int M1;
	float M2;
	float M3;
	float M4;
	float M5;
	float M6;
	float M7;
	float M8;
	float M9;
	float M10;
	float M11;
	float M12;
	float M13;
	float M14;
};

int trainnum2 = 100;
int testnum2 = 100;
int testtotal2 = 200;
struct oridata2
{
	int N1;
	float N2;
	float N3;
	float N4;
	float N5;
	float N6;
	float N7;
	float N8;
	float N9;
	float N10;
	float N11;
	float N12;
	float N13;
	float N14;
	float N15;
	float N16;
	float N17;
	float N18;
	float N19;
	float N20;
	float N21;
};