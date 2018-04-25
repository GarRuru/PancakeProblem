#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<string.h>
using namespace std;

void upsidedown(int *stat, int k,int pancake,int g) {
	int start = 0,temp,action = k+1;
	while (start < k) {
		temp = stat[start];
		stat[start] = stat[k];
		stat[k] = temp;
		start += 1;
		k -= 1;
	}
	printf("[%d", stat[0]);
	for (int i = 1; i < pancake; i++) {
		printf(" %d", stat[i]);
	}
	printf("]");
	printf(", %d, 1, %d, %d\n", g, g + 1, action);
}

int main(){
    int testNumber;
	int pancake, g, preAction;
    scanf("%d",&testNumber);
    for(int i=0;i<testNumber;i++){
        scanf("%d",&pancake);
        int* stat = (int*)malloc(sizeof(int)*16);
		int* statcpy = (int*)malloc(sizeof(int) * 16);
        for(int j=0;j<pancake;j++){
            scanf("%d",&stat[j]);
        }
		//memcpy(statcpy, stat, sizeof(stat));
		scanf("%d%d", &g, &preAction);
		g += 1;
		for (int k = 2; k <= pancake; k++) {
			if (k != preAction) {
				//memcpy(statcpy, stat, sizeof(stat));
				for (int x = 0; x < pancake; x++) {
					statcpy[x] = stat[x];
				}
				upsidedown(statcpy, k - 1, pancake,g);
			}
		}
    }
    return 0;
}