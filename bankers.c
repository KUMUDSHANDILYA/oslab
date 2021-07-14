// Banker's Alogorithm

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
	int i, instances[r], allocated[n][r+1], max_need[n][r], need[n][r];
	for(i=0;i<r;i++){
		instances[i] = rand()%7 + 3;
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
			max_need[i][k] = rand()%(j[k] - temp);
			max_need[i][k] += allocated[i][k];
			if(max_need[i][k] > instances[k]){
				max_need[i][k] -= instances[k];
			}
		}
	}

	for(i=0;i<n;i++){
		for(k=0;k<r;k++){
			need[i][k] = max_need[i][k] - allocated[i][k];
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
	// max_need matrix
	printf("\n********************Max_need Matrix********************\n");
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
			printf("    %d", max_need[i][k]);
		}
		printf("\n");
	}

	// Need matrix
	printf("\n********************Need Matrix********************\n");
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
			printf("    %d", need[i][k]);
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

	int l,flag, count=0, sequence[n];
	for(l=0;l<n;l++){
		sequence[l] = -1;
	}
	while(count < n){
		for(i=0;i<n;i++){
			flag = 0;
			for(k=0;k<r;k++){
				if(allocated[i][r] == 1 || need[i][k] > availability[k]){
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
			sequence[count] = i;
		}
		count++;
	}
	for(i=0;i<n;i++){
		if(allocated[i][r] == 0){
			printf("\n\nUnsafe (Deadlock occurred.....)");
			printf("\nSequence - \n");
			for(l=0;l<n;l++){
				if(sequence[l] != -1){
					printf(" -> P%d", sequence[l]);
				}
			}
			break;
		}
	}
	if(i == n){
		printf("\n\nSafe (No Deadlock occurred.....)");
		printf("\nSafe sequence - \n");
		for(l=0;l<n;l++){
			printf(" -> P%d", sequence[l]);
		}
	}
	return 0;
}
