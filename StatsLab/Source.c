#include <stdio.h>

void printArray(int num[], int size);
void insertionSort(int num[], int size);
void frequency(int num[], int size);
void grading(int num[], int size);
double mean(int num[], int size);
int mode(int num[], int size);
double median(int num[], int size);

#define SIZE 30

int main(void) {
	int i = 0;
	int static num[SIZE] = { 90, 85, 100, 50, 50, 85, 60, 70, 55, 55, 80, 95, 70, 60, 95,
		80, 100, 75, 70, 95, 90, 90, 70, 95, 50, 65, 85, 95, 100, 65};
	
	//printf("Enter array:\n");
	//while(1 && i < SIZE) {
	//	scanf("%d", &num[i]);
	//	if (num[i] == -1) {
	//		break;
	//	}
	//	i++;
	//}

	printf("%s\n", "Unsorted:");
	printArray(num, SIZE);
	insertionSort(num, SIZE);
	printf("%s\n", "Ascending Order:");
	printArray(num, SIZE);
	frequency(num, SIZE);
	grading(num, SIZE);
	printf("%8s %6.1lf\n", "Mean:", mean(num, SIZE));
	printf("%8s %4d\n", "Mode:", mode(num, SIZE));
	printf("%8s %6.1lf\n", "Median:", median(num, SIZE));

	return 0;
}

void printArray(int num[], int size) {
	int i;

	for (i = 0; i < size; i++) {
		printf("%5d", num[i]);
		if (i % 5 == 4 || (i == size - 1)) {
			printf("%c", '\n');
		}
	}
}

void insertionSort(int num[], int size) {
	int i, j, temp;

	for (i = 1; i < size; i++) {
		temp = num[i];
		j = i - 1;
		while (j >= 0 && temp < num[j]) {
			num[j + 1] = num[j];
			j = j - 1;
		}
		num[j + 1] = temp;
	}
}

void frequency(int num[], int size) {

	int i;
	static int bin[101];

	for (i = 0; i < size; i++) {
		bin[num[i]]++;
	}
	putchar('\n');
	printf("%8s %16s\n", "value", "frequency");
	printf("%8s %16s\n", "-----", "---------");
	for (i = 0; i < size; i++) {
		printf("%7d %13d\n", num[i], bin[num[i]]);
	}
	//printf("%4s %8d", "100", bin[100]);
	//putchar('\n');
	//printf("%4s %8d", "95", bin[95]);
	//putchar('\n');
	//printf("%4s %8d", "90", bin[90]);
	//putchar('\n');
	//printf("%4s %8d", "85", bin[85]);
	//putchar('\n');
	//printf("%4s %8d", "80", bin[80]);
	//putchar('\n');
	//printf("%4s %8d", "75", bin[75]);
	//putchar('\n');
	//printf("%4s %8d", "70", bin[70]);
	//putchar('\n');
	//printf("%4s %8d", "65", bin[65]);
	//putchar('\n');
	//printf("%4s %8d", "60", bin[60]);
	//putchar('\n');
	//printf("%4s %8d", "55", bin[55]);
	//putchar('\n');
	//printf("%4s %8d", "50", bin[50]);
	putchar('\n');
}

void grading(int num[], int size) {

	int i;
	double passing, failing;
	passing = 0.0;
	failing = 0.0;

	for (i = 0; i < size; i++) {
		if (num[i] >= 60) {
			passing += 1;
		}
		else {
			failing += 1;
		}
	}
	
	putchar('\n');
	printf("%8s %6.1lf%c", "Passing:", ((passing / (double)size) * 100), '%');
	putchar('\n');
	printf("%8s %6.1lf%c", "Failing:", ((failing/ (double) size)*100), '%');
	putchar('\n');
}

double mean(int num[], int size) {

	int i, sum;
	double mean;
	sum = 0;
	mean = 0;

	for (i = 0; i < size; i++) {
		sum += num[i];
	}

	mean =  ((double)sum / (double)size);
	
	return mean;
}

int mode(int num[], int size) {
	int i, mode;
	static int bin[101];
	mode = 0;

	for (i = 0; i < size; i++) {
		bin[num[i]]++;
		if (bin[num[i]] > bin[mode]) {
			mode = num[i];
		}
	}

	return mode;
}

double median(int num[], int size) {
	double median;

	if (size % 2 == 0) {
		median = ((double)((num[size / 2] + num[size / 2 - 1])) / 2);
	} else {
		median = (double)(num[size / 2]);
	}

	return median;
}