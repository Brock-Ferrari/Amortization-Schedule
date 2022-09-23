// Brock Ferrari
// Amortization Schedule

#include <iostream>
#include <iomanip> // Necessary for setprecision(2)
using namespace std;

double CalcPayment(double principal, double rate, int term);
void Amortize(int currentPeriod, int totalPeriods, double paymentAmount, double monthlyInterestRate, double currentBalance);

int main()
{
	cout << "Welcome to the loan calculator, please enter the following information:" << endl << endl;

	cout << "How much would you like to borrow?: ";
	double principal = 0;
	cin >> principal;
	while (cin.fail() || principal < 0) // Ensures principal is a positive number
	{
		cout << "Your principal must be a positive number. Please try again." << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> principal;
	}
	cout << endl;

	cout << "What is the annual interest rate for your loan?: ";
	double rate = 0;
	cin >> rate;
	while (cin.fail() || rate < 0) // Ensures rate is a positive number
	{
		cout << "Your rate must be a positive number. Please try again." << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> rate;
	}
	rate = (rate / 12) / 100; // Converts annual interest rate to monthly rate.
	cout << endl;

	cout << "What is the term for your loan? Please enter either 10, 15, or 30: ";
	int years = 0;
	int checker = 0;
	cin >> years;
	while (cin.fail() || checker == 0) // Ensures year is either 10, 15, or 30.
	{
		if (years == 10 || years == 15 || years == 30)
			checker = 1; // Sets "checker" to 1 if correct value is inputted. Stays 0 if not.
		else
		{
			cout << "The term must be either 10, 15, or 30. Please try again." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin >> years;
		}
	}
	double term = years * 12; // Years to months
	cout << endl;

	double monthlyPayment = CalcPayment(principal, rate, term); // Determines monthly payment

	int currentPeriod = 1;
	double balance = principal;

	cout << "Payment \tAmount \t\tInterest \tPrincipal \tBalance" << endl << endl;

	cout << "\t\t\t\t\t\t\t\t" << balance << endl; // Prints initial balance

	cout << fixed << setprecision(2); // Sets values to 2 decimal places.

	Amortize(currentPeriod, term, monthlyPayment, rate, balance);
}

double CalcPayment(double principal, double rate, int term)
{
	double monthlyPayment = principal * (rate * pow(1 + rate, term)) / (pow(1 + rate, term) - 1); // Monthly payment equation
	return monthlyPayment; // Returns monthly payment to main
}

void Amortize(int currentPeriod, int totalPeriods, double paymentAmount, double monthlyInterestRate, double currentBalance)
{
	if (currentPeriod > totalPeriods) // Checks if current term exceeds total, ending recursion if so.
	{
		return;
	}
	else
	{
		cout << currentPeriod;
		currentPeriod++; // Increases current period by 1 every recursion

		cout << "\t\t" << paymentAmount;
		cout << "\t\t" << monthlyInterestRate * currentBalance; // Interest calculation
		cout << "\t\t" << paymentAmount - monthlyInterestRate * currentBalance; // Principal calculation

		currentBalance = currentBalance - (paymentAmount - monthlyInterestRate * currentBalance); // Updates balance
		cout << "\t\t" << currentBalance;

		cout << endl;

		Amortize(currentPeriod, totalPeriods, paymentAmount, monthlyInterestRate, currentBalance); // Recursion

		return;
	}
}