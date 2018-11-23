#include<iostream>
#include<stdio.h>
#include<algorithm>
using namespace std;

#define MAXN 10005
#define MAXC 105
int convert(int hh, int mm, int ss) {
	return hh * 3600 + mm * 60 + ss;
}

struct Guest {
	int arrive;
	int service;
};

Guest guest[MAXN];
int endtime[MAXC];

bool cmp(Guest a, Guest b) {
	return a.arrive < b.arrive;
}

int main() {
	int n, k;
	scanf("%d%d", &n, &k);
	int st = convert(8, 0, 0);
	int ed = convert(17, 0, 0);
	fill(endtime, endtime + k, st);
	int hh, mm, ss,service;
	int count = 0;
	for (int i = 0; i < n; i++) {
		scanf("%d:%d:%d%d", &hh, &mm, &ss, &service);
		service = service * 60;
		int temp = convert(hh, mm, ss);
		if (temp <=ed ) {
			guest[count].arrive = temp;
			if(service<=3600) guest[count++].service = service;
			else guest[count++].service = 3600;
		}
	}
	sort(guest, guest + count, cmp);
	double ans=0;
	int cal = count;
	for (int i = 0; i < count; i++) {
		int min = 1000000000;     //!!!!
		int index=-1;
		for (int j = 0; j < k; j++) {
				if (endtime[j] < min) {
					index = j;
					min = endtime[j];
				}
		}
		if (guest[i].arrive >= min) {
			endtime[index] = guest[i].arrive + guest[i].service;
		}
		else {
			ans += (endtime[index] - guest[i].arrive);
			endtime[index] += guest[i].service;
		}
	}
	double result;
	if (count == 0) printf("0.0");
	else{
		result =( ans )/ 60/count;
		printf("%.1f", result);
	}
	
	system("pause");
	return 0;
}