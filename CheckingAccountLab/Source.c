/***************
Program Name:      check.c
Author:            Raul Aguilar
Date Submitted:    October 11, 2015
Class:             CSCI 112 73481
Instructor:        Timothy Kraus
Compiler:          Microsoft Visual Studio Community 2015
OS:                Windows 10 Home
Description:       Reads the details of a monthly checking account and
	outputs a bank statement summarizing these transactions.
Input Files:       account.txt
Output Files:      None
*****************/

#include <stdio.h>
#include <stdlib.h>


FILE *fpIn;

void outputHeaders(void);
void initialBalance(int *month, double amount, double *balance, double *service, double *openBalance,
	double *closeBalance);
void deposit(double amount, double *balance, double *service,
	int *numDeposit, double *amtDeposit);
void check(double amount, double *balance, double *service,
	int *numCheck, double *amtCheck);
double accountAdjustment(double *prevMonthBalance, double closeBalance, double openBalance);
void outputSummary(int month, int numDeposit, double amtDeposit, int numCheck, double amtCheck,
	double openBalance, double service, double closeBalance, double prevMonthBalance, double accAdjustment);


int main(void) {
	char code;
	double amount, service, balance;
	double amtCheck, amtDeposit, openBalance, closeBalance, prevMonthBalance;
	double accAdjustment;
	int numCheck, numDeposit;
	int month;

	if (!(fpIn = fopen("account.txt", "r"))) {
		printf("account.txt could not be opened for input.\n");
		exit(1);
	}

	amount = 0.0;
	service = 0.0;
	balance = 0.0;
	amtCheck = 0.0;
	amtDeposit = 0.0;
	openBalance = 0.0;
	closeBalance = 0.0;
	prevMonthBalance = 0.0;
	numCheck = 0;
	numDeposit = 0;
	month = 0;

	outputHeaders();

	while (!feof(fpIn)) {
		fscanf(fpIn, "%c %lf\n", &code, &amount);
		if (code == 'I' && month == 0) {
			initialBalance(&month, amount, &balance, &service, &openBalance, &closeBalance);
		} else if (code == 'I' && month != 0) {
			accAdjustment = accountAdjustment(&prevMonthBalance, closeBalance, openBalance);
			closeBalance = balance - service;
			outputSummary(month, numDeposit, amtDeposit, numCheck, amtCheck, openBalance,
				service, closeBalance, prevMonthBalance, accAdjustment);
			outputHeaders();
			initialBalance(&month, amount, &balance, &service, &openBalance, &closeBalance);
		}
		if (code == 'D') {
			deposit(amount, &balance, &service, &numDeposit, &amtDeposit);
		}
		if (code == 'C') {
			check(amount, &balance, &service, &numCheck, &amtCheck);
		}
	} 

	accAdjustment = accountAdjustment(&prevMonthBalance, closeBalance, openBalance);
	closeBalance = balance - service;
	outputSummary(month, numDeposit, amtDeposit, numCheck, amtCheck, openBalance,
		service, closeBalance, prevMonthBalance, accAdjustment);

	fclose(fpIn);

	getc(stdin);
	return 0;
}

void outputHeaders(void) {
	printf("%s\n", "----------------------------------------------");
	printf("%-16s %9s %9s %9s\n", "Transaction", "Deposit", "Check", "Balance");
	printf("%-16s %9s %9s %9s\n", "-----------", "-------", "-----", "-------");
}

void initialBalance(int *month, double amount, double *balance, double *service, double *openBalance,
	double *closeBalance) {
	
	double adjustment;

	*service = (double) 3.00;
	*balance = amount;
	*openBalance = *balance;
	if ((*month) > 0) {
		*openBalance = amount;
		*balance = *closeBalance + amount;
		adjustment = (((*openBalance - *closeBalance) * 100) + 0.5) / 100 ;
		adjustment = (int)adjustment;
		if (adjustment != 0.00) {
			if ((*openBalance) > (*closeBalance)) {
				printf("%-16s %9.2lf %9s %9.2lf\n", "Adjustment", (*openBalance - *closeBalance), " ", *openBalance);
			} else if ((*openBalance) < (*closeBalance)) {
				printf("%-16s %9s %9.2lf %9.2lf\n", "Adjustment", " ", (*closeBalance - *openBalance), *openBalance);
			}
		}
	}
	
	printf("%-16s %9s %9s %9.2lf\n", "Initial Balance", " ", " ", *openBalance);

	(*month)++;
}

void deposit(double amount, double *balance, double *service, int *numDeposit, double *amtDeposit) {

	*service += (double) 0.03;
	*balance += amount;
	*amtDeposit += amount;
	
	printf("%-16s %9.2lf %9s %9.2lf\n", "Deposit", amount, " ", *balance);
	(*numDeposit)++;
}

void check(double amount, double *balance, double *service, int *numCheck, double *amtCheck) {

	*balance -= amount;
	*service += (double) 0.06;
	if (*balance < 0) {
		*service += (double) 5.00;
	}
	*amtCheck += amount;

	printf("%-16s %9s %9.2lf %9.2lf\n", "Check", " ", amount, *balance);
	(*numCheck)++;
}

double accountAdjustment(double *prevMonthBalance, double closeBalance, double openBalance) {

	double accAdjustment;

	*prevMonthBalance = closeBalance;
	accAdjustment = ((((openBalance- *prevMonthBalance) * 100) + 0.5) / 100);
	accAdjustment = (int)accAdjustment;

	return accAdjustment;
}

void outputSummary(int month, int numDeposit, double amtDeposit, int numCheck, double amtCheck,
	double openBalance, double service, double closeBalance, double prevMonthBalance, double accAdjustment) {

	putchar('\n'); putchar('\n');
	printf("%s ", "Bank Statement");
	printf("%s %d\n", "Month:", month);
	printf("%s\n", "--------------");
	printf("%-36s %9d\n", "Total number of deposits:", numDeposit);
	printf("%-36s %9.2lf\n", "Total amount deposits:", amtDeposit);
	printf("%-36s %9d\n", "Total number of checks:", numCheck);
	printf("%-36s %9.2lf\n", "Total amount checks:", amtCheck);
	printf("%-36s (%7.2lf)\n", "Total service charge:", service);
	if (month > 1) {
		printf("%-36s %9.2lf\n", "Previous closing balance:", prevMonthBalance);
		if (accAdjustment == 0.00 || prevMonthBalance < openBalance) {
			printf("%-36s %9.2lf\n", "Accounting adjustment:", accAdjustment);
		} else {
			printf("%-36s %9.2lf%c\n", "Accounting adjustment:", (prevMonthBalance - openBalance), '-');
		}
	}
	printf("%-36s %9.2lf\n", "Opening balance:", openBalance);
	printf("%-36s %9.2lf\n", "Closing balance:", closeBalance);
	putchar('\n');
}