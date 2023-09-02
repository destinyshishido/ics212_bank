/*******************
//  
//  Name:        Destiny Shishido
//
//  Homework:    project2
//
//  Class:       ICS212
// 
//  Instructor:  Ravi Narayan
//
//  Date:        November 20, 2022
//  
//  File:        user_interface.cpp
//
//  Description: .
//
********************/

#include "record.h"
#include "llist.h"

#include <string>
#include <cstring>
#include <iostream>

int main(int argc, char *argv[])
{
    char name[30], address[60];
    std::string input, namestr, addressstr, temp;
    int accountno;
    llist database;

    std::cout << "Welcome to the bank database where you can access all bank records based on account number.\n";
    std::cout << "All records contain the account number, the account holder's address, and the account holder's name.\n\n";

    std::cout << "Listed below are your options.\n\n";
    std::cout << "add: Add a new record in the database\n";
    std::cout << "printall: Print all records in the database\n";
    std::cout << "find: Find record(s) with a specified account number\n";
    std::cout << "delete: Delete existing record(s) from the database using the account number as a key\n";
    std::cout << "quit: Quit the program\n\n";

    std::cout << "Make a selection. Press enter once finished.\n";
    std::getline(std::cin, input, '\n');

    while (std::strncmp(input.c_str(), "quit", input.length()) != 0)
    {
        if (std::strncmp(input.c_str(), "add", input.length()) == 0)
        {
            /* ADD */
            std::cout << "\nAdding a record.\n";

            /** Get account number from user **/
            std::cout << "Enter account number: ";
            while(!(std::cin >> accountno))
            {
                std::cout << "\nInvalid input. Enter a number.\nEnter account number: ";
                std::cin.clear();
                std::getline(std::cin, temp);
            }             
            std::getline(std::cin, temp);

            /** Get name from user **/
            std::cout << "Enter account holder's name: ";
            std::getline(std::cin, namestr);

            /** Get address from user **/
            std::cout << "Enter address: ";
            std::getline(std::cin, addressstr, '@');
            strcpy(name, namestr.c_str());
            strcpy(address, addressstr.c_str());
            database.addRecord(accountno, name, address);

            std::cout << "Record added.\n";
            std::getline(std::cin, temp);
        }
        else if (std::strncmp(input.c_str(), "printall", input.length()) == 0)
        {
            /* PRINT ALL */
            std::cout << "\nPrinting all records\n\n";
            database.printAllRecords();
        }
        else if (std::strncmp(input.c_str(), "find", input.length()) == 0)
        {
            /* FIND */
            std::cout << "\nFind record\n";

            /** Get account number from user **/
            std::cout << "Enter account number: ";
            while(!(std::cin >> accountno))
            {
                std::cout << "\nInvalid input. Enter a number.\nEnter account number: ";
                std::cin.clear();
                std::getline(std::cin, temp);
            }
            std::getline(std::cin, temp);

            database.findRecord(accountno);
        }
        else if (std::strncmp(input.c_str(), "delete", input.length()) == 0)
        {
            /* DELETE */
            std::cout<< "Deleting\n";

            /** Get account number from user **/
            std::cout << "Enter account number: ";
            while(!(std::cin >> accountno))
            {
                std::cout << "\nInvalid input. Enter a number.\nEnter account number: ";
                std::cin.clear();
                std::getline(std::cin, temp);
            }
            std::getline(std::cin, temp);

            database.deleteRecord(accountno);
        }
        else
        {
            /* handle bad input */
            std::cout<< "Invalid input\n";
        }

        std::cout << "\nWhat next? Make selection (add, printall, find, delete, quit)" << std::endl;
        std::getline(std::cin, input, '\n');
    }
    std::cout << "\nQUIT PROGRAM" << std::endl;
    return 0;
}
