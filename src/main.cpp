#include <iostream>
#include <windows.h>
#include "functions.h"

int main()
{
	intro();

	char ch;
	int num;

	do
	{
		do
		{
			system("cls");
			std::cout << "\n\n\n\tMAIN MENU";
			std::cout << "\n\n\t01. NEW ACCOUNT";
			std::cout << "\n\n\t02. DEPOSIT AMOUNT";
			std::cout << "\n\n\t03. WITHDRAW AMOUNT";
			std::cout << "\n\n\t04. DISPLAY ACCOUNT";
			std::cout << "\n\n\t05. ALL ACCOUNT HOLDER LIST";
			std::cout << "\n\n\t06. CLOSE AN ACCOUNT";
			std::cout << "\n\n\t07. MODIFY AN ACCOUNT";
			std::cout << "\n\n\t08. EXIT";
			std::cout << "\n\n\tSelect Your Option (1-8) : "; std::cin >> ch;
		} while (ch < '1' || ch > '8');


		system("cls");
		switch (ch)
		{
		case '1':
			new_account();
			break;
		case '2':
			std::cout << "\n\nEnter the account No. : "; std::cin >> num;
			deposit_or_withdraw(num, 1); // deposit = 1
			break;
		case '3':
			std::cout << "\n\nEnter the account No. : "; std::cin >> num;
			deposit_or_withdraw(num, 2); // withdraw = 2
			break;
		case '4':
			std::cout << "\n\nEnter The account No. : "; std::cin >> num;
			display_account(num);
			break;
		case '5':
			display_all();
			break;
		case '6':
			std::cout << "\n\nEnter The account No. : "; std::cin >> num;
			delete_account(num);
			break;
		case '7':
			std::cout << "\n\nEnter The account No. : "; std::cin >> num;
			modify_account(num);
			break;
		case '8':
			std::cout << "\n\n\tThanks for testing out our BANK MANAGEMENT SYSTEM\n\n\n";
			Sleep(3000);
			exit(0);
			break;
		default: exit(1);
		}

		std::cin.ignore();
		std::cin.get();
	} while (1);
	return 0;
}