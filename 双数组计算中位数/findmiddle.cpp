#include<iostream>
using namespace std;
float searchMid(int a[], int b[], int n, int aL, int bL, int aR, int bR) {
	float aMid, bMid;//数组a,b的中位数
	int aIndex, bIndex;//数组a,b的中位数的数组序号
 
	if (aR == aL) {
		return (a[aR] + b[bR]) / 2.0;
	}
 
	if ((aR - aL) % 2 == 0) {
		aMid = a[(aR + aL) / 2] / 1.0;
		bMid = b[(bR + bL) / 2] / 1.0;
		aIndex = (aR + aL) / 2;
		bIndex = (bR + bL) / 2;
 
		if (aMid == bMid) {
			return aMid;
		}
		else if (aMid < bMid) {
			return searchMid(a, b, n, aIndex, bL, aR, bIndex);
		}
		else {
			return searchMid(a, b, n, aL, bIndex, aIndex, bR);
		}
	}
	else {
		aMid = (a[(aR + aL + 1) / 2] + a[(aR + aL + 1) / 2 - 1]) / 2.0;
		bMid = (b[(bR + bL + 1) / 2] + b[(bR + bL + 1) / 2 - 1]) / 2.0;
		aIndex = (aR + aL + 1) / 2;
		bIndex = (bR + bL + 1) / 2;
 
		if (aMid == bMid) {
			return aMid;
		}
		else if (aMid < bMid) {
			if (a[aIndex] <b[bIndex] && a[aIndex - 1] > b[bIndex - 1]) {
				return aMid;
			}
			else if (a[aIndex] > b[bIndex] && a[aIndex - 1] < b[bIndex - 1]) {
				return bMid;
			}
			else {
				return searchMid(a, b, n, aIndex, bL, aR, bIndex - 1);
			}
		}
		else {
			if (a[aIndex] < b[bIndex] && a[aIndex - 1] > b[bIndex - 1]) {
				return aMid;
			}
			else if (a[aIndex] > b[bIndex] && a[aIndex - 1] < b[bIndex - 1]) {
				return bMid;
			}
			else {
				return searchMid(a, b, n, aL, bIndex, aIndex - 1, bR);
			}
		}
	}
}
 
int main() {
	int a[100], b[100];
	int n;
	cout << "请输入数组的长度：" << endl;
	cin >> n;
	cout << "请依次输入数组a的值：" << endl;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	cout << "请依次输入数组b的值：" << endl;
	for (int j = 0; j < n; j++) {
		cin >> b[j];
	}
	cout << "中位数是：" << endl;
	cout << searchMid(a, b, n, 0, 0, n - 1, n - 1);
}