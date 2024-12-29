#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cmath>

using namespace std;

// Function to calculate the monthly payment
double calculateMonthlyPayment(double loanAmount, int loanPeriodMonths, double annualInterestRate) {
    int n = loanPeriodMonths;
    double IR = (annualInterestRate / 12.0) / 100.0;
    double D = ((pow(1 + IR, n) - 1) / (IR * pow(1 + IR, n)));
    double monthlyPayment = loanAmount / D;
    return monthlyPayment;
}

int main() {
    // Customer details
    string customerName;
    int customerAge;
    double monthlyIncome;

    // Input customer details
    cout << "Enter customer's details:" << endl;
    cout << "Name: ";
    cin >> customerName;
    cout << "Age: ";
    cin >> customerAge;
    cout << "Monthly Income: ";
    cin >> monthlyIncome;

    // Loan details
    string loanName[] = {"Vehicle", "Housing", "Education", "Senior Citizen", "Personal (60 months)", "Personal (84 months)"};
    int maxLoanAmount[] = {1000000, 2500000, 1500000, 500000, 2000000, 3000000};
    int maxRepayPeriod[] = {60, 60, 24, 60, 84};
    double annualInterestRate[] = {14.0, 8.0, 6.0, 4.5, 14.5, 16.2};
    int minAge[] = {18, 25, 25, 60, 30, 30};
    int maxAge[] = {55, 55, 35, INT_MAX, 55, 55}; 
    double minIncome[] = {45000, 100000, 45000, 35000, 100000, 100000};

    // Display available loan options
    cout << "Available loan options in Bank:" << endl;
    for (int i = 0; i < 6; i++) {
        cout << i + 1 << ". " << loanName[i] << " - Max Amount: " << maxLoanAmount[i] << " LKR, Max Repay Period: " << maxRepayPeriod[i] << " months, Interest Rate: " << annualInterestRate[i] << "%" << endl;
    }

    // Select a loan
    int loanChoice;
    cout << "Select a loan option (1-6): ";
    cin >> loanChoice;
    loanChoice--; // Adjust for array indexing

     if (customerAge < minAge[loanChoice] || customerAge > maxAge[loanChoice] || monthlyIncome < minIncome[loanChoice]) {
        cout << "You are not eligible for the selected loan." << endl;
        return 0;
    }

    // Input loan amount and repay period
    double requestedLoanAmount;
    int requestedRepayPeriod;
    cout << "Enter the amount you wish to borrow (up to " << maxLoanAmount[loanChoice] << " LKR): ";
    cin >> requestedLoanAmount;
    cout << "Enter the desired repayment period (up to " << maxRepayPeriod[loanChoice] << " months): ";
    cin >> requestedRepayPeriod;

    // Calculate monthly payment
    double monthlyPayment = calculateMonthlyPayment(requestedLoanAmount, requestedRepayPeriod, annualInterestRate[loanChoice]);

    // Calculate total amount paid and total interest earned by the bank
    double totalAmountPaid = monthlyPayment * requestedRepayPeriod;
    double totalInterestEarned = totalAmountPaid - requestedLoanAmount;

    // Print details to a text file
    ofstream outputFile((customerName + ".txt").c_str());
    outputFile << "Name of the customer: " << customerName << endl;
    outputFile << "Selected Loan: " << loanName[loanChoice] << endl;
    outputFile << "Maximum Repay Period Allowed: " << maxRepayPeriod[loanChoice] << " months" << endl;
    outputFile << "Annual Interest Rate: " << annualInterestRate[loanChoice] << "%" << endl;
    outputFile << "Requested loan amount: " << requestedLoanAmount << " LKR and repay period: " << requestedRepayPeriod << " months." << endl;

    // Print Table 1
    outputFile << setw(15) << "Month" << setw(20) << "Loan Remaining" << setw(20) << "Interest Payment" << setw(20) << "Loan Deduction" << endl;
    double remainingLoan = requestedLoanAmount;
    for (int month = 1; month <= requestedRepayPeriod; month++) {
        double interestPayment = remainingLoan * (annualInterestRate[loanChoice] / 12) / 100;
        double loanDeduction = monthlyPayment - interestPayment;
        remainingLoan -= loanDeduction;
        outputFile << setw(15) << month << setw(20) << fixed << setprecision(2) << remainingLoan << setw(20) << interestPayment << setw(20) << loanDeduction << endl;
    }

    outputFile << "Total amount paid by the customer at the end of the loan repayment period: " << totalAmountPaid << " LKR" << endl;
    outputFile.close();

    // Display results
    cout << "Monthly Repayment Amount: " << fixed << setprecision(2) << monthlyPayment << " LKR" << endl;
    cout << "Total Amount Paid: " << fixed << setprecision(2) << totalAmountPaid << " LKR" << endl;
    cout << "Total Interest Earned by the Bank: " << fixed << setprecision(2) << totalInterestEarned << " LKR" << endl;

    return 0;
}
