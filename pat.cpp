#include<iostream>
#include<stdio.h>
#include<queue>
#include<algorithm>
using namespace std;

#define MAXW 25
#define MAXC 1005
#define INF 1000000000

struct Customer {
	int servetime;
	int index;
	Customer() {}
	Customer(int s, int i):servetime(s),index(i){}
};

struct Window {
	queue<Customer> que;
	int nextservetime;
}window[MAXW];

int finish[MAXC];

int main() {
	int n, m, k, q;
	scanf("%d%d%d%d", &n, &m, &k, &q);
	fill(finish, finish + k+1, -1);
	int count = 0;
	int inqueue = 0;
	while (count < k && inqueue<m) {
		for (int i = 0; i < n && count<k; i++) {
			int temp;
			scanf("%d", &temp);
			window[i].que.push(Customer(temp, count + 1));
			window[i].nextservetime = window[i].que.front().servetime + 8 * 60;
			count++;
		}
		inqueue++;
	}
	while (count < k) {
		int mintime = INF;
		int choose = -1;
		for (int i = 0; i < n; i++) {
			if (window[i].nextservetime < mintime) {
				choose = i;
				mintime = window[i].nextservetime;
			}
		}
		int temp;	
		scanf("%d", &temp);
		count++;
		if (mintime < 17 * 60) {
			finish[window[choose].que.front().index] = window[choose].nextservetime;
			window[choose].que.pop();
			window[choose].que.push(Customer(temp, count));
			window[choose].nextservetime += window[choose].que.front().servetime;
		}
	}
	for (int i = 0; i < n; i++) {
		while (!window[i].que.empty()) {
			finish[window[i].que.front().index] = window[i].nextservetime;
			if (window[i].nextservetime >= 17 * 60) break;
			window[i].que.pop();
			if(!window[i].que.empty()) window[i].nextservetime += window[i].que.front().servetime;
		}
	}
	for (int i = 0; i < q; i++) {
		if (i != 0) printf("\n");
		int temp;
		scanf("%d", &temp);
		if (finish[temp] == -1) {
			printf("Sorry");
		}
		else {
			printf("%02d:%02d", finish[temp] / 60, finish[temp] % 60);
		}
	}
	system("pause");
	return 0;
}