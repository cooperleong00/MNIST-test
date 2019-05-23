#ifndef PIC_H
#define PIC_H
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>
#include <cmath>
#include <algorithm>
using namespace cv;
using namespace std;
class pic {
public:
	pic(HANDLE hd);
	int GetTrainNum(int label);
	int GetTestNum(int label);
	void display(string str);
private:
	vector<int> trainNum;
	vector<int> testNum;
	HANDLE myhandle;
};
#endif 


