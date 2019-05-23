#ifndef KNN_H
#define KNN_H
#include "pic.h"
using namespace cv;
using namespace std;
class KNN {
public:
	KNN(pic *p);
	//�������
	vector<double> mat2dot(Mat mt);
	void train();
	int predict(int K, int label, int index);
	void test(int K,int num);
private:
	//28x28 �ֳ� 4x4��7x7��С��
	//ÿ��ȡƽ���Ҷ�
	vector<vector<vector<double>>> model;
	double distance(vector<double> &dot1,vector<double> &dot2);
	pic *p;
};

#endif
