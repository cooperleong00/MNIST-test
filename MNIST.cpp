

#include "pch.h"
#include "pic.h"
#include "KNN.h"
#include <iostream>

using namespace std;
using namespace cv;
//KNN k=9 890  0.796067
//KNN k=8 890  0.802921
//KNN k=7 890  0.804270
//KNN k=6 890  0.813708
//KNN K=5 890  0.825281
//KNN K=4 890  0.831573
//KNN k=3 890  0.849438
//KNN k=2 890  0.860899
//KNN k=1 890  1.000000
int main()
{
	ios::sync_with_stdio(false);
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


