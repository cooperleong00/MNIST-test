#ifndef KNN_H
#define KNN_H
#include "pic.h"
using namespace cv;
using namespace std;
class KNN {
public:
	KNN(pic *p);
	//输入矩阵
	vector<double> mat2dot(Mat mt);
	void train();
	int predict(int K, int label, int index);
	void test(int K,int num);
private:
	//28x28 分成 4x4个7x7的小块
	//每块取平均灰度
	vector<vector<vector<double>>> model;
	double distance(vector<double> &dot1,vector<double> &dot2);
	pic *p;
};

#endif
