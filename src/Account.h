#pragma once
#include <iostream>
#include <cctype>
#include <iomanip>
#include <vector>
std::vector<int> acnos; // A vector that will save all account's number so there can't be 2 accounts with the same acno

class Account
{
private:
	int acno; // Account Number
	char name[50]; // Owner's Name
	int balance;
	char type; // Type of Account

public:
	void new_acc();
	void show_account() const;
	void modify();

	inline void deposit(int x) { balance += x; }
	inline void draw(int x) { balance -= x; }

	inline int retacno() const { return acno; }
	inline const char* retname() const { return name; }
	inline int retbalance() const { return balance; }
	inline char rettype() const { return type; }
};

void Account::new_acc()
{
	bool valid;
	do
	{
		std::cout << "\nEnter the account No. : ";
		std::cin >> acno;

		// Checking if acno hasn't been entered before
		valid = true;
		for(auto it = acnos.begin(); it != acnos.end(); it++)
			if (acno == *it)
			{
				valid = false;
				break;
			}
	} while (acno <= 0 || !valid);
	acnos.push_back(acno);

	std::cout << "Enter the name of the account holder : ";
	std::cin.ignore();
	std::cin.getline(name, 50);

	do
	{
		std::cout << "Enter the type of the account (Current(C)/Savings(S)) : ";
		std::cin >> type;
		type = toupper(type);
	} while (type != 'C' && type != 'S');

	do
	{
		std::cout << "Enter the initial amount of money : ";
		std::cin >> balance;
	} while (balance < 0);

	std::cout << "\nAccount Created..";
}
void Account::show_account() const
{
	std::cout << "\nAccount No. : " << acno;
	std::cout << "\nAccount Holder Name : " << name;
	std::cout << "\nType of Account : " << (type == 'C' ? "Current" : "Savings");
	std::cout << "\nBalance amount : " << balance;
}
void Account::modify()
{
	std::cout << "\nAccount No. : " << acno;

	std::cout << "\nModify Account Holder Name : ";
	std::cin.ignore();
	std::cin.getline(name, 50);

	do
	{
		std::cout << "Modify Type of Account (Current(C)/Savings(S)): ";
		std::cin >> type;
		type = toupper(type);
	} while (type != 'C' && type != 'S');

	std::cout << "Modify Balance amount : ";
	std::cin >> balance;
}