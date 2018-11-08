#include <iostream>
#include <atlimage.h>
#include"Bi.h"
#include"NN.h"
using namespace std;
void main()
{
	cout << "now using Nearest Neighbor...to enlargement the picture\n";
	cout << "btw, you can modify the path of picture in NN.h\n";
	NN();
	cout << "waiting for such a long time, thank you!\n";
	cout<<"new file name is: NN.jpg\n";

	cout << "now using Bilinear...to enlargement the picture\n";
	cout << "btw, you can modify the path of picture in Bi.h\n";
	Bi();
	cout << "waiting for such a long time, thank you!\n";
	cout << "new file name is: Bi.jpg\n";
	system("pause");
}