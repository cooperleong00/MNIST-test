#include "pch.h"
#include "pic.h"
using namespace cv;
using namespace std;
pic::pic(HANDLE hd)
{
	trainNum = { 5923,6742,5958,6131,5842,5421,5918,6265,5851,5949 };
	testNum = {980,1135,1032,1010,982,892,958,1028,974,1009};
	myhandle = hd;
}

int pic::GetTrainNum(int label)
{
	return trainNum[label];
}

int pic::GetTestNum(int label)
{
	return testNum[label];
}



void pic::display(string str)
{
	SetConsoleCursorPosition(myhandle, { 0,0 });
	cout << str;
}
