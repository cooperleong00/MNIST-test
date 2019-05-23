

#include "pch.h"
#include "pic.h"
#include "KNN.h"
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	pic *P = new pic(GetStdHandle(STD_OUTPUT_HANDLE));
	KNN knn(P);
	knn.train();
	//int lb, idx;
	//while (cin >> lb >> idx) {
	//	cout << "result: "<<knn.predict(7, lb, idx) << endl;
	//}
	int k, num;
	while (cin >> k >> num) {
		knn.test(k, num);
	}
	return 0;
}


