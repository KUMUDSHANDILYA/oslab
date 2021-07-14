// RAG

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
	int n,r;
	srand(time(0));
	n = rand()%16 + 5;
	r = rand()%16 + 5;
	printf("Total number of processes: %d\n", n);
	printf("Total number of resources: %d\n", r);

	//instances of resources
	int i, instances[r], allocated[n][r+1], request[n][r];
	for(i=0;i<r;i++){
		instances[i] = rand()%8 + 2;
		printf("\nTotal instances of R%d = %d", i, instances[i]);
	}
	printf("\n");
	int k,j[r];
	for(i=0;i<r;i++){
		j[i] = instances[i];
	}
	int temp;
	for(i=0;i<n;i++){
		for(k=0;k<r;k++){
			temp = rand()%j[k];
			allocated[i][k] = rand()%(j[k] - temp);
			j[k] -= allocated[i][k];
		}
		allocated[i][k] = 0;
	}

	for(i=0;i<n;i++){
		for(k=0;k<r;k++){
			j[k] = instances[k] - allocated[i][k];
		}
		for(k=0;k<r;k++){
			temp = rand()%j[k];
			request[i][k] = rand()%(j[k] - temp);
		}
	}

	// Allocation matrix
	printf("\n********************Allocation Matrix********************\n");
	printf("\n   ");
	for(i=0;i<r;i++){
		if(i<10){
			printf(" ");
		}
		printf("  R%d", i);
	}
	printf("\n");
	for(i=0;i<n;i++){
		printf("P%d", i);
		if(i<10){
			printf(" ");
		}
		for(k=0;k<r;k++){
			printf("    %d", allocated[i][k]);
		}
		printf("\n");
	}
	printf("\n\n");
	// Request matrix
	printf("\n********************Request Matrix********************\n");
	printf("\n   ");
	for(i=0;i<r;i++){
		if(i<10){
			printf(" ");
		}
		printf("  R%d", i);
	}
	printf("\n");
	for(i=0;i<n;i++){
		printf("P%d", i);
		if(i<10){
			printf(" ");
		}
		for(k=0;k<r;k++){
			printf("    %d", request[i][k]);
		}
		printf("\n");
	}

	int availability[r];
	for(i=0;i<r;i++){
		availability[i] = 0;
		for(k=0;k<n;k++){
			availability[i] += allocated[k][i];
		}
		availability[i] = instances[i] - availability[i];
	}

	printf("\n********************Availability Matrix********************\n");
	for(i=0;i<r;i++){
		printf("R%d ", i);
		if(i<10){
			printf(" ");
		}
	}
	printf("\n");
	for(i=0;i<r;i++){
		printf("%d   ", availability[i]);
	}

	int l,flag, count=0;
	while(count < n){
		for(i=0;i<n;i++){
			flag = 0;
			for(k=0;k<r;k++){
				if(allocated[i][r] == 1 || request[i][k] > availability[k]){
					flag = 1;
					break;
				}
			}
			if(flag == 0){
				break;
			}
		}

		if(flag == 0 && i!=n+1){
			for(k=0;k<r;k++){
				availability[k] += allocated[i][k];
			}
			printf("\n");
			for(l=0;l<r;l++){
				printf("%d   ", availability[l]);
			}
			allocated[i][r] = 1;
		}
		count++;
	}
	for(i=0;i<n;i++){
		if(allocated[i][r] == 0){
			printf("\n\nDeadlock occurred.....");
			break;
		}
	}
	if(i == n){
		printf("\n\nNo Deadlock occurred.....");
	}
	return 0;
}

