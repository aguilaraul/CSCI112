/***************
 Program Name:      penny.c
 Author:            Raul Aguilar
 Date Submitted:    September 29, 2015
 Date Modified:		December 19, 2016
 Class:             CSCI 112 73481
 Instructor:        Timothy Kraus
 Compiler:          Dev-C++ 5.11
 OS:                Windows 10 Home
 Description:       Assuming you keep doubling your deposit each day, how many days will it take to reach $1 million
 Input Files:       None
 Output Files:      None
 *****************/

#include <stdio.h>
#include <math.h>

void PrintHeader(void);
void GenerateTable(double accumulate);

int main (void) {
    
    double total;
    total = 0;
    
    printf("%s", "Please enter the amount of money you want to accumulate:\n");
    printf("%s", "$");
    scanf("%lf", &total);
    
    PrintHeader();
    GenerateTable(total);
    
    printf ("%s", "Press any key to exit");
    getch();
    return 0;
}

void PrintHeader (void) {
    printf("%3s %8s %11s\n", "Day", "Deposit", "Balance");
    printf("%3s %11s %11s\n", "---", "----------", "----------");
}

void GenerateTable (double accumulate) {
    
    double days, deposit, balance;
    
    deposit = 0.01;
    balance = 0.01;
    days = 1;
    
    do {
        printf("%3.0lf %11.2lf %11.2lf\n", days, deposit, balance);
        deposit *= 2;
        balance += deposit;
        days++;
    } while(balance <= accumulate);
    
    printf("%3.0lf %11.2lf %11.2lf\n", days, deposit, balance);
    printf("It took %.0lf days to generate at least $%.2lf\n", days, accumulate);
    
}
