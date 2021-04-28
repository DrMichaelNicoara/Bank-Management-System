#pragma once
#include <iostream>
#include <fstream>
#include "Account.h"

void intro()
{
	std::cout << "\n\n\n\t   BANK";
	std::cout << "\n\n\tMANAGEMENT";
	std::cout << "\n\n\t  SYSTEM";
	std::cout << "\n\n\n\nMADE BY : Nicoara Mihai";
	Sleep(3000);
}

void new_account()
{
	Account ac;
	ac.new_acc();

	std::ofstream outFile("account.dat", std::ios::binary | std::ios::app);
	outFile.write(reinterpret_cast<char*> (&ac), sizeof(Account));
	outFile.close();
}


//***************************************************************
//    	function to read specific record from file
//****************************************************************

void display_account(int acno)
{
	Account ac;
	std::ifstream inFile("account.dat", std::ios::binary);

	if (!inFile)
	{
		std::cout << "File could not be open !! Press any Key...";
		return;
	}

	// Show details of account
	bool found = false;
	while (inFile.read(reinterpret_cast<char*> (&ac), sizeof(Account)))
	{
		if (ac.retacno() == acno)
		{
			found = true;
			std::cout << "\nACCOUNT DETAILS\n";
			ac.show_account();
			break;
		}
	}

	inFile.close();
	if (found == false)
		std::cout << "\nAccount " << acno << " was Not Found!";
}


//***************************************************************
//    	function to modify record of file
//****************************************************************

void modify_account(int acno)
{
	Account ac;
	std::fstream File("account.dat", std::ios::binary | std::ios::in | std::ios::out);

	if (!File)
	{
		std::cout << "File could not be open !! Press any Key...";
		return;
	}

	// Search for the wanted account and modify it
	bool found = false;
	while (!File.eof() && found == false)
	{
		File.read(reinterpret_cast<char*> (&ac), sizeof(Account));
		if (ac.retacno() == acno)
		{
			found = true;
			ac.show_account();

			std::cout << "\n\nEnter the new data of the account" << std::endl;
			ac.modify();

			int pos = (-1) * static_cast<int>(sizeof(Account));
			File.seekp(pos, std::ios::cur);
			File.write(reinterpret_cast<char*> (&ac), sizeof(Account));
			std::cout << "\nAccount " << acno << " was Updated";
		}
	}

	File.close();
	if (found == false)
		std::cout << "\nAccount " << acno << " was Not Found ";
}


//***************************************************************
//    	function to delete record of file
//****************************************************************

void delete_account(int acno)
{
	Account ac;
	std::ifstream inFile("account.dat", std::ios::binary);

	if (!inFile)
	{
		std::cout << "File could not be open !! Press any Key...";
		return;
	}

	std::ofstream outFile("Temp.dat", std::ios::binary);

	// Create a new file Temp.dat that contains all the accounts except the one we want to delete
	// Then remove account.dat and Temp.dat will be the new account.dat
	inFile.seekg(0, std::ios::beg);
	bool found = false;
	while (inFile.read(reinterpret_cast<char*> (&ac), sizeof(Account)))
	{
		if (ac.retacno() != acno)
		{
			outFile.write(reinterpret_cast<char*> (&ac), sizeof(Account));
		}
		else found = true;
	}

	inFile.close();
	outFile.close();
	remove("account.dat");
	rename("Temp.dat", "account.dat");
	if (found) std::cout << "\nAccount " << acno << " was Deleted!";
	else std::cout << "\nAccount " << acno << " was not found!";
}


//***************************************************************
//    	function to display all accounts deposit list
//****************************************************************

void display_all()
{
	Account ac;
	std::ifstream inFile("account.dat", std::ios::binary);

	if (!inFile)
	{
		std::cout << "File could not be open !! Press any Key...";
		return;
	}

	bool none = true;
	std::cout << "\n\n\t\tACCOUNT LIST\n\n";
	std::cout << "====================================================\n";
	std::cout << "  No.      NAME           Type         Balance\n";
	std::cout << "====================================================\n";
	while (inFile.read(reinterpret_cast<char*> (&ac), sizeof(Account)))
	{
		std::cout << std::setw(3) << ac.retacno()
			<< std::setw(13) << ac.retname()
			<< std::setw(12) << ac.rettype()
			<< std::setw(16) << ac.retbalance() << std::endl;
		none = false;
	}
	if (none) std::cout << "There are no accounts yet.";

	inFile.close();
}


//***************************************************************
//    	function to deposit and withdraw amounts
//****************************************************************

void deposit_or_withdraw(int acno, int option) // option 1 = deposit  | option 2 = withdraw
{
	std::fstream File("account.dat", std::ios::binary | std::ios::in | std::ios::out);

	if (!File)
	{
		std::cout << "File could not be open !! Press any Key...";
		return;
	}

	Account ac;
	bool found = false;
	int amount;

	// Search for the wanted account then deposit or withdraw money
	while (!File.eof() && found == false)
	{
		File.read(reinterpret_cast<char*> (&ac), sizeof(Account));
		if (ac.retacno() == acno)
		{
			found = true;
			ac.show_account();

			if (option == 1)
			{
				std::cout << "\n\n\tTO DEPOSITE AMOUNT ";
				std::cout << "\n\nEnter the amount to be deposited : ";
				std::cin >> amount;
				ac.deposit(amount);
			}

			bool action_taken = true;
			if (option == 2)
			{
				std::cout << "\n\n\tTO WITHDRAW AMOUNT ";
				std::cout << "\n\nEnter The amount to be withdraw : ";
				std::cin >> amount;

				if (ac.retbalance() - amount < 0)
				{
					std::cout << "Insufficient balance !";
					action_taken = false;
				}
				else ac.draw(amount);
			}

			int pos = (-1) * static_cast<int>(sizeof(ac));
			File.seekp(pos, std::ios::cur);
			File.write(reinterpret_cast<char*> (&ac), sizeof(Account));
			if (action_taken) std::cout << "\n\nAccount " << acno << " Updated";
		}
	}

	File.close();
	if (!found) std::cout << "\nAccount " << acno << " Not Found!";
}