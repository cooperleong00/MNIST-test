#include "pch.h"
#include "KNN.h"
using namespace cv;
using namespace std;
struct dis { double d; int label; };

bool cmp(dis& a, dis& b) {
	return a.d < b.d;
}

KNN::KNN(pic *p)
{
	this->p = p;
	model.resize(10);
}

vector<double> KNN::mat2dot(Mat mt)
{
	
	//起始点
	//28x28 分成 4x4个7x7的小块
	int i, j,stx,sty;
	double sumbychunk=0.0;
	vector<double> dot(16);
	for (i = 0; i < 4; i++) {
		sty = i * 7;
		for (j = 0; j < 4; j++) {
			stx = j * 7;
			//每块取平均灰度
			for (int ky = 0; ky < 7; ky++) {
				for (int kx = 0; kx < 7; kx++) {
					sumbychunk += mt.at<char>(stx+kx,sty+ky);
				}
			}
			//model[label][index][i * 4 + j] = sumbychunk / 49.0;
			dot[i * 4 + j] = sumbychunk / 49.0;
		}
	}
	return dot;
}

void KNN::train()
{
	int idx ,pcnum,total=0;
	string filename;
	for (int i = 0; i < 10; i++) {
		pcnum = p->GetTrainNum(i);
		model[i].resize(pcnum);
		filename = "E:/VisualStudioProject/MNIST/trainimage/pic2/";
		for (idx=0; idx < pcnum; idx++) {
			model[i][idx] = mat2dot(imread(filename + to_string(i) + '/' + to_string(idx+1) + ".bmp", 7));
			total++;
			p->display("training label:" + to_string(i) + " " + to_string(idx+1) + ".bmp\ntotal:"+to_string(total));
		}
	}
}

int KNN::predict(int K, int label,int index)
{
	
	string filename= "E:/VisualStudioProject/MNIST/trainimage/pic2/"+to_string(label) + '/' + to_string(index) + ".bmp";
	vector<double> tgdot = mat2dot(imread(filename, 0));
	vector<dis> disset(60000);
	int total = 0;
	for (int i = 0; i < 10; i++) {
		int num = p->GetTrainNum(i);
		for (int j = 0; j < num; j++) {
			disset[total].d = distance(tgdot, model[i][j]);
			disset[total].label = i;
			total++; 
			p->display("calculating distance:" + to_string(total));
		}
	}
	sort(disset.begin(), disset.end(),cmp);
	vector<int> labelnum(10,0);
	for (int i = 0; i < K; i++) {
		labelnum[disset[i].label]++;
	}
	int maxnum = 0,maxlabel=0;
	for (int i = 0; i < 10; i++) {
		if (labelnum[i] > maxnum) {
			maxnum = labelnum[i];
			maxlabel = i;
		}
	}
	return maxlabel;
}

void KNN::test(int K,int num)
{
	int correct = 0,p;
	for (int i = 0; i < 10; i++) {
		for (int j = 1; j <= num; j++) {
			p = predict(K, i, j);
			if ( p== i) {
				correct++;
			}
			cout << "predict:" << p << " true:" << i << endl;
		}
	}
	cout << "correct rate:" + to_string(correct / (10.0 * num)) << endl;
}

double KNN::distance(vector<double>& dot1, vector<double>& dot2)
{
	int dim = dot1.size(),i;
	if (dot2.size() != dim) {
		cout << "维数不同，无法计算距离\n";
		return -1.0;
	}
	double sum1 = 0.0,sum2=0.0,sum3=0.0,sum4=0.0;
	for (i = 0; i < dim-4; i+=4) {
		sum1 += (dot1[i] - dot2[i])*(dot1[i] - dot2[i]);
		sum2 += (dot1[i + 1] - dot2[i + 1]) * (dot1[i + 1] - dot2[i + 1]);
		sum3 += (dot1[i + 2] - dot2[i + 2]) * (dot1[i + 2] - dot2[i + 2]);
		sum4 += (dot1[i + 3] - dot2[i + 3]) * (dot1[i + 3] - dot2[i + 3]);
	}
	for (; i < dim; i++) {
		sum1 += (dot1[i] - dot2[i]) * (dot1[i] - dot2[i]);
	}
	return sqrt(sum1+sum2+sum3+sum4);
}
